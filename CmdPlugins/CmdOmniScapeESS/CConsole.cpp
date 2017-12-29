/*---------------------------------------------------------------------+\
|
|	CConsole.cpp  --  brief description of what CConsole.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformTime.h"
#include "UPlatformString.h"
#include "CConsole.h"
#include "CDateTime.h"

NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

#define	USE_TXTHREAD	1

#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
//#define	LOCAL_PRINT( fmt, ... )





// low order bit indicates whether we have had some sort of past activity
#define ESS_M_STATE	0x00FF
#define	ESS_K_INACTIVE	0
#define	ESS_K_ACTIVE	1
#define ESS_K_IDLE		2
#define	ESS_K_PAUSED	3
#define	ESS_K_DEAD		4
#define ESS_K_WAIT		5

// which DSPs have been tested
#define	ESS_K_DSP1	0x00000100
#define	ESS_K_DSP2	0x00000200
#define	ESS_K_DSP3	0x00000400
#define	ESS_K_DSP4	0x00000800

// which DSPs have failed
#define	ESS_K_DSP1F	0x00001000
#define	ESS_K_DSP2F	0x00002000
#define	ESS_K_DSP3F	0x00004000
#define	ESS_K_DSP4F	0x00008000

// which DSPs are actively being tested
#define	ESS_K_DSP1A	0x00010000
#define	ESS_K_DSP2A	0x00020000
#define	ESS_K_DSP3A	0x00040000
#define	ESS_K_DSP4A	0x00080000

#define ESS_K_NETT	0x00100000
#define	ESS_K_NETF	0x00200000
#define	ESS_K_NETA	0x00400000

#define	ESS_K_FAIL	0x10000000		// sticky failure


#define	TN_ALWAYS	TPX_LAMBDA

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|												 						|
\+---------------------------------------------------------------------*/



static
NResult	trans_notify
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );
	else
		pCon->Notify( pTrans->sToken );

	return NR_S_SUCCESS;
}

#if 0
static
NResult	trans_save_xfercount
		(
		CConsolePtr	,//pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	// todo: parse string to get count of bytes transferred
	return NR_S_SUCCESS;
}
#endif


static
NResult	trans_sleep
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	millisleep( 1000 );
	return NR_S_SUCCESS;
}




static
NResult	trans_ethaddr
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sTemp[80];
	sprintf_s( sTemp, sizeof( sTemp ),
	           "setenv ethaddr 00:05:09:FF:AA:%02lX\r",
	           (unsigned long)pCon->GetIndex() + 1 );
	pCon->WritePort( sTemp, strlen( sTemp ) );
	return NR_S_SUCCESS;
}

static
NResult	trans_ipaddr
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sTemp[80];
	sprintf_s( sTemp, sizeof( sTemp ),
	           "setenv ipaddr 192.168.0.%ld\r",
	           pCon->GetIndex() * 5 + 200 + 5 );
	pCon->WritePort( sTemp, strlen( sTemp ) );
	return NR_S_SUCCESS;
}

static
NResult	trans_test_ipaddr
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	sToken,
		int			//nTokenLen
		)
{
	char	sTemp[80];
	sprintf_s( sTemp, sizeof( sTemp ),
	           "192.168.0.%ld",
	           pCon->GetIndex() * 5 + 200 + 5 );

	if ( strstr( sToken, sTemp ) )
		return NR_S_SUCCESS;
	else
		return NR_E_FAIL;
}

static
NResult	trans_ifconfig
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sTemp[80];
	sprintf_s( sTemp, sizeof( sTemp ),
	           "ifconfig eth0 192.168.0.%ld up\r",
	           pCon->GetIndex() * 5 + 200 + 5 );
	pCon->WritePort( sTemp, strlen( sTemp ) );
	return NR_S_SUCCESS;
}

static
NResult	trans_bootargs
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sTemp[256];
	CCharString	sServerIP;

	sServerIP = pCon->GetServerIP();

	sprintf_s( sTemp, sizeof( sTemp ),
	           "setenv bootargs console=ttyS0,115200n8 root=/dev/nfs rw "
	           "eth=00:05:09:ff:aa:%02lx "
	           "ip=192.168.0.%ld "
	           "nfsroot=%s:/tftpboot stdin=serial stdout=serial\r",
	           (unsigned long)pCon->GetIndex() + 1,
	           pCon->GetIndex() * 5 + 200 + 5,
	           sServerIP.Pointer()
	         );
	pCon->WritePort( sTemp, strlen( sTemp ) );
	return NR_S_SUCCESS;
}



static
NResult	trans_nfs_mount
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sTemp[256];
	CCharString	sServerIP;

	sServerIP = pCon->GetServerIP();

	sprintf_s( sTemp, sizeof( sTemp ),
	           "mount -t nfs -o proto=tcp %s:/tftpboot /remote\r",
	           sServerIP.Pointer()
	         );
	pCon->WritePort( sTemp, strlen( sTemp ) );
	return NR_S_SUCCESS;
}




static
NResult	trans_set_serverip
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sTemp[256];
	CCharString	sServerIP;

	sServerIP = pCon->GetServerIP();

	sprintf_s( sTemp, sizeof( sTemp ),
	           "setenv serverip %s\r",
	           sServerIP.Pointer()
	         );
	pCon->WritePort( sTemp, strlen( sTemp ) );
	return NR_S_SUCCESS;
}






static
NResult	make_dsp_bootloader
		(
		char*		sOutput,
		long		nMaxOutput,
		CConsolePtr	,//pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
//	int		i = pCon->GetIndex() + 1;

	sprintf_s( sOutput, (size_t)nMaxOutput,
	           "./DSP_Bootloader -z -d 1 -n 4 -c /remote/omniscape/Generic_Main_Config_File.cfg \r" );
	return NR_S_SUCCESS;
}
static
NResult	trans_dsp_bootloader
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	sToken,
		int			nTokenLen
		)
{
	char	sTemp[256];

	make_dsp_bootloader( sTemp, sizeof( sTemp ),
	                     pCon, pTrans, sToken, nTokenLen );

	pCon->WritePort( sTemp, strlen( sTemp ) );
	pCon->Notify( "Loading DSPs" );
	return NR_S_SUCCESS;
}







static
NResult	trans_validate_written
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	sToken,
		int			nTokenLen
		)
{
	//if ( 79 < nTokenLen )
	//	nTokenLen = 79;	// kludge around serial port buffering problem
	if ( pCon->CompareLastWritten( sToken, nTokenLen ) )
	{
		return NR_S_SUCCESS;
	}
	else
	{
		if ( pTrans->pXdata )
			pCon->Notify( pTrans->pXdata );

		return NR_E_FAIL;
	}
}





static
NResult	trans_ping
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	long	n = 0;
	char	sCommand[100];
	char	sTemp[30];
	char	sDashes[10];

	n = ( pCon->GetCount() + 1 ) % 5;
	pCon->SetCount( n );
	CCharString	sIP = pCon->GetTestingIP();

	sprintf_s( sCommand, sizeof( sCommand ),
	           "ping -c 1 -q %s\r",
	           sIP.Pointer() );

	for ( int i = 0; i < 5; ++i )
	{
		if ( i == n )
			sDashes[i] = '+';
		else
			sDashes[i] = '.';
	}

	sDashes[5] = '\0';
	sprintf_s( sTemp, sizeof( sTemp ),
	           "Testing %s", sDashes );
	pCon->Notify( sTemp );


	millisleep( 1000 );
	pCon->WritePort( sCommand, strlen( sCommand ) );
	return NR_S_SUCCESS;
}



static
NResult	trans_ping_failed
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	pCon->SetDspState( false );

	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	return NR_S_SUCCESS;
}


static
NResult	trans_ping_success
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	pCon->SetDspState( true );

	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	return NR_S_SUCCESS;
}



static
NResult	trans_srvr_ping
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	sCommand[100];

	pCon->SetCount( 0 );
	CCharString	sIP = pCon->GetTestingIP();

	sprintf_s( sCommand, sizeof( sCommand ),
	           "ping -c 1 -q %s\r",
	           sIP.Pointer() );

	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	millisleep( 10 );

	pCon->WritePort( sCommand, strlen( sCommand ) );
	return NR_S_SUCCESS;
}

static
NResult	trans_setdate
		(
		CConsolePtr	pCon,
		XTransPtr	,//pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	char	st[100];

	CDateTime	d = CDateTime::CurrentTime();
	d.FormatLocal( st, sizeof( st ), "%Y-%m-%d %H:%M:%S" );

	//d.FormatISO( st, sizeof(st), true );

	char	sCommand[100];

	sprintf_s( sCommand, sizeof( sCommand ),
	           "date -s '%s'\r", st );


	pCon->WritePort( sCommand, strlen( sCommand ) );
	return NR_S_SUCCESS;
}

static
NResult	trans_srvr_ping_failed
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	pCon->SetCount( 0 );
	pCon->SetDspState( false );

	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	pCon->SetCount( -1 );

	return NR_S_SUCCESS;
}


static
NResult	trans_srvr_ping_success
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	pCon->SetCount( 0 );
	pCon->SetDspState( true );

	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	pCon->SetCount( -1 );

	return NR_S_SUCCESS;
}




static
NResult	trans_initstate
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	pCon->InitState();

	if ( pTrans->pXdata )
		pCon->Notify( pTrans->pXdata );

	return NR_S_SUCCESS;
}


static
NResult	trans_failure
		(
		CConsolePtr	pCon,
		XTransPtr	pTrans,
		const char*	,//sToken,
		int			//nTokenLen
		)
{
	pCon->SetFailureState( pTrans->pXdata );

	return NR_S_SUCCESS;
}




extern XTrans	g_flash_saveenv[];
extern XTrans	g_uboot_interrupt[];		// forward declaration
extern XTrans	g_entry[];
extern XTrans	g_ping[];
extern XTrans	g_dsp_bootloader[];





static XTrans	g_ping_result[]
=
{
	{ " 100% packet loss", 0, g_ping,  trans_ping_failed, 0 },
	{ " 0% packet loss", 0, g_ping, trans_ping_success, 0 },
	{ "Network is unreachable", "\r", g_ping, trans_ping_failed, 0 },
	{ "lookup failure", "\r", g_ping, trans_ping_failed, 0 },
	{ "any key to stop", "\r", g_uboot_interrupt, 0, 0 },
	{ "input overrun", "\r", g_ping, trans_ping_failed, 0 },
	{ "not responding, still trying", 0, g_ping, trans_srvr_ping_failed, 0 },
	{ "Paused?", "\r", g_ping, trans_srvr_ping_failed, 0 },
	{ "#", "\r", g_ping, trans_sleep, 0 },
	{0}
};



XTrans	g_ping[]
=
{
	{ "data bytes", 0, g_ping_result, 0, 0 },
	{ "Paused?", "\r", 0, trans_srvr_ping_failed, 0 },
	{ "not responding, still trying", "\r", 0, trans_srvr_ping_failed, 0 },
	{ "#", 0, 0, trans_ping, 0 },
	{0}
};






static XTrans	g_dsp_bootloader_v[]
=
{
	{ "ALL DSPs loaded", "echo 'DSPs loaded'\r", g_ping, 0, 0 },
	{ "not responding, still trying", "\r", 0, trans_failure, "NFS..." },
	{ "DSP_Bootloader configuration file ERROR", "\r", g_entry, trans_notify, "Bootloader config error" },
	{ "Paused?", "\r", g_entry, 0, 0 },
	{ "No such file", "\r", g_dsp_bootloader, 0, 0 },
	{0}
};






XTrans	g_dsp_bootloader[]
=
{
	{ "#", 0, g_dsp_bootloader_v, trans_dsp_bootloader, 0 },
	{0}
};


//static XTrans	g_vdds_0600[]
//={
//	{ "not responding, still trying", 0, 0, trans_failure, "NFS..." },
//	{ "#", "insmod ./vdds_0600.ko\r", g_dsp_bootloader, 0, 0 },
//	{0}
//};


//static XTrans	g_cd_omniscape[]
//={
//	{ "#", "cd /remote/omniscape\r", g_vdds_0600, 0, 0 },
//	{0}
//};















///////////////////////////////////////////////////////////////



static XTrans	g_closeapp[]
=
{
	{ TPX_LAMBDA, 0, 0, trans_sleep, "Please Close Loader" },
	{0}
};


static XTrans	g_cpx_done[]
=
{
	{ "DRS DDS #", "reset\r", 0, trans_notify, "Resetting" },
	{ "U-Boot", 0, 0, trans_notify, "U-Boot" },
	{ "Linux", 0, 0, trans_notify, "Starting Linux" },
	{ "Filename 'uImage'", 0, 0, trans_notify, "Booting" },
	{ "DSP Bootloader", 0, 0, trans_notify, "Loading DSPs" },
	{ "###", 0, 0, trans_notify, "Application Starting" },
	{ "udhcp", 0, 0, trans_notify, "Wasting time with DHCP" },
	{ "vdds_start", 0, 0, trans_notify, "Loading VDDS Drivers" },
	{ "Initialization Complete", 0, g_closeapp, 0, 0 },
	{0}
};


static XTrans	g_cpx_cycle[]
=
{
	{ "DRS DDS #", "reset\r", g_cpx_done, trans_notify, "Resetting" },
	{ "U-Boot", 0, g_cpx_done, trans_notify, "U-Boot" },
	{ "Linux", 0, g_cpx_done, trans_notify, "Starting Linux" },
	{ "Filename 'uImage'", 0, 0, trans_notify, "Booting" },
	{ "#", 0, 0, trans_sleep, "Cycle Power to Finish" },
	{0}
};


static XTrans	g_cpx_umount[]
=
{
	{ "#", "umount /remote\r", g_cpx_cycle, 0, 0 },
	{0}
};


static XTrans	g_cpx_cdroot[]
=
{
	{ "#", "cd /\r", g_cpx_umount, 0, 0 },
	{0}
};


static XTrans	g_cpx_installv[]
=
{
	{ "Done", 0, g_cpx_cdroot, trans_sleep, "Cycle Power to Finish" },
	{ "Mounting dev", 0, 0, trans_notify, "Remounting flash" },
	{ "DSP Binary", 0, 0, trans_notify, "Updating DSP refs" },
	{ "files to flash", 0, 0, trans_notify, "Installing files" },
	{0}
};

static XTrans	g_cpx_install[]
=
{
	{ "Done", 0, g_cpx_cycle, 0, 0 },
	{ "#", "./flash_install.sh\r", g_cpx_installv, trans_notify, "Installing..." },
	{0}
};

static XTrans	g_cpx[]
=
{
	{ "#", "cd /remote\r", g_cpx_install, 0, 0 },
	{0}
};


static XTrans	g_killall[]
=
{
	{ "#", "killall vdds_main_app\r", g_cpx, 0, 0 },
	{0}
};



static XTrans	g_nfs_mount_v[]
=
{
	{ TPX_LAMBDA, "\r", g_killall, trans_validate_written, 0 },
	{ TPX_LAMBDA, "\r", g_killall, 0, 0 },
	{0}
};

static XTrans	g_nfs_mount[]
=
{
	{ "not responding, still trying", 0, 0, trans_srvr_ping_failed, "NFS..." },
	{ "No route to host", "\r", 0, trans_srvr_ping_failed, "NFS ?" },
	{ "#", 0, g_nfs_mount_v, trans_nfs_mount, 0 },
	{0}
};


static XTrans	g_nfs_mkdir[]
=
{
	{ "#", "mkdir -p /remote\r", g_nfs_mount, 0, 0 },
	{0}
};



static XTrans	g_setdate[]
=
{
	{ "#", 0, g_nfs_mkdir, trans_setdate, 0 },
	{0}
};


static XTrans	g_ifconfig_v[]
=
{
	{ "input overrun", "\r", g_entry, trans_notify, "overrun" },
	{ TPX_LAMBDA, "\r", g_setdate, trans_validate_written, 0 },
	{ TPX_LAMBDA, "\r", g_setdate, 0, 0 },
	{0}
};


static XTrans	g_ifconfig[]
=
{
	{ "not responding, still trying", 0, 0, trans_srvr_ping_failed, "NFS..." },
	{ "#", 0, g_ifconfig_v, trans_ifconfig, 0 },
	{0}
};


static XTrans	g_root_welcome[]
=
{
	{ "Welcome to ", "\r", 0, trans_notify, "Login" },
	{ "any key to stop",	"   ",	g_uboot_interrupt, 0, 0 },
	{ "login:", "root\r", 0, 0, 0 },
	{ "password:", "\r", 0, 0, 0 },
	{ "#", "\r", g_ifconfig, 0, 0 },
	{0}
};





static XTrans	g_root_login[]
=
{
	{ "login:", "root\r", g_root_welcome,  trans_notify, "Login" },
	{ "password:", "\r", 0, 0, 0 },
	{ "Retry count exceeded; starting again", 0, 0, trans_srvr_ping_failed, "NFS?" },
	{ "not responding, still trying", 0, 0, trans_srvr_ping_failed, "NFS..." },
	{ "U-Boot", 0, 0, trans_notify, "U-Boot" },
	{ "Linux", 0, 0, trans_notify, "Starting Linux" },
	{ "Filename 'uImage'", 0, 0, trans_notify, "Booting" },
	{0}
};






static XTrans	g_flash_reset[]
=
{
	{ "U-Boot", 0, g_root_login, trans_notify, "U-Boot" },
	{ "Unknown command", "echo 'oops'\r", 0, trans_notify, "garbled command" },
	{ "DRS DDS #", "reset\r", 0, trans_notify, "Resetting" },
	{0}
};




static XTrans	g_final_saveenv[]
=
{
	{ "done", "echo 'saveenv complete'\r", g_flash_reset, 0, 0 },
	{ "Unknown command", "echo 'oops'\r", 0, trans_notify, "garbled command" },
	{ "DRS DDS #", "saveenv\r", 0, trans_notify, "Flash setup" },
	{0}
};


static XTrans	g_uboot_set_bootargs_flash[]
=
{
	{ "DRS DDS #", "setenv bootargs console=ttyS0,115200n8 root=/dev/ram initrd=0x82000000,32M rw ip=off mem=120M\r", g_final_saveenv, trans_notify, "Flash setup" },
	{ "Unknown command", "echo 'oops'\r", g_flash_saveenv, trans_notify, "garbled command" },
	{0}
};


static XTrans	g_uboot_set_bootcmd_flash[]
=
{
	{ "DRS DDS #", "setenv bootcmd 'cp.b 0x2440000 0x82000000 0x3fffff;bootm 0x2040000'\r", g_uboot_set_bootargs_flash, trans_notify, "Flash setup" },
	{ "Unknown command", "echo 'oops'\r", g_flash_saveenv, trans_notify, "garbled command" },
	{ "#", "echo 'dummy'\r", 0, 0, 0 },
	{0}
};



static XTrans	g_set_essload[]
=
{
	{ "Unknown command", "echo 'oops'\r", g_flash_saveenv, trans_notify, "garbled command" },
	{ "DRS DDS #", "setenv essload 'loaded'\r", g_uboot_set_bootcmd_flash, 0, 0 },
	{ "#", "echo 'dummy'\r", 0, 0, 0 },
	{0}
};





XTrans	g_flash_saveenv[]
=
{
	{ "done", "echo 'saveenv complete'\r", g_set_essload, 0, 0 },
	{ "Unknown command", "echo 'oops'\r", 0, trans_notify, "garbled command" },
	{ "DRS DDS #", "saveenv\r", 0, 0, 0 },
	{ "#", "echo 'dummy'\r", 0, 0, 0 },
	{0}
};






static XTrans	g_flash_rfs_cp[]
=
{
	{ "done", "echo 'complete rfs cp.b'\r", g_flash_saveenv, 0, 0 },
	{ "/", 0, 0, trans_notify, "FileSys load .  " },
	{ "-", 0, 0, trans_notify, "FileSys load  . " },
	{ "\\", 0, 0, trans_notify, "FileSys load   ." },
	{ "Unknown command", "echo 'oops'\r", 0, trans_notify, "garbled command" },
	// for now we are hardcoding this ... but it needs to be done via trans_f
	{ "DRS DDS #", "cp.b 0x82000000 0x2440000 0x30ae6e\r", 0, trans_notify, "FileSys load" },
	{0}
};

static XTrans	g_flash_rfs_tftp[]
=
{
	{ "Bytes transferred =", "echo 'complete rfs tftp'\r", g_flash_rfs_cp, trans_srvr_ping_success, 0 },
	{ "DRS DDS #", "tftp  0x82000000  rfs.img.gz\r", 0, trans_notify, "FileSys xfer" },
	{ "Retry count exceeded; starting again", 0, 0, trans_failure, "NFS?" },
	{ "not responding, still trying", 0, 0, trans_failure, "NFS..." },
	{ "Unknown command", "echo 'oops'\r", 0, trans_notify, "garbled command" },
	{0}
};

static XTrans	g_flash_rfs_erase[]
=
{
	{ "Completed", "echo 'complete rfs erase'\r", g_flash_rfs_tftp, 0, 0 },
	{ "Unknown command", "echo 'oops'\r", 0, trans_notify, "garbled command" },
	{ "DRS DDS #", "erase 0x02440000 0x0279FFFF\r", 0, trans_notify, "FileSys init" },
	{0}
};



static XTrans	g_flash_uimage_cp[]
=
{
	{ "done", "echo 'complete uImage cp.b'\r", g_flash_rfs_erase, 0, 0 },
	{ "/", 0, 0, trans_notify, "uImage load /" },
	{ "-", 0, 0, trans_notify, "uImage load -" },
	{ "\\", 0, 0, trans_notify, "uImage load \\" },
	{ "DRS DDS #", "cp.b 0x80400000 0x2040000 0x1360e8\r", 0, trans_notify, "uImage load" },
	// for now we are hardcoding this ... but it needs to be done via trans_f
	{0}
};

static XTrans	g_flash_uimage_tftp[]
=
{
	{ "Bytes transferred =", "echo 'complete uImage tftp'\r", g_flash_uimage_cp, trans_srvr_ping_success, 0 },
	{ "Retry count exceeded; starting again", 0, 0, trans_failure, "NFS?" },
	{ "not responding, still trying", 0, 0, trans_failure, "NFS..." },
	{ "DRS DDS #", "tftp 0x80400000 uImage\r", 0, trans_notify, "uImage xfer" },
	{0}
};

static XTrans	g_flash_uimage_erase[]
=
{
	{ "Completed", "echo 'complete uImage erase'\r", g_flash_uimage_tftp, 0, 0 },
	{ "DRS DDS #", "erase 0x02040000 0x0243FFFF\r", 0, trans_notify, "uImage init" },
	{0}
};










static XTrans	g_uboot2_print_essload[]
=
{
	{ "not defined", "\r", g_flash_uimage_erase, trans_notify, "Reloading Flash" },
	{ "essload=", "\r", g_set_essload, 0, 0 },
	{ "DRS DDS #", "print essload\r", 0, 0, 0 },
	{0}
};







static XTrans	g_uboot2_ping_server[]
=
{
	{ "done", 0, g_uboot2_print_essload, trans_srvr_ping_success, 0 },
	{ "not responding, still trying", 0, g_entry, trans_srvr_ping_failed, "NFS?" },
	{ "count exceeded; starting again", 0, g_entry, trans_srvr_ping_failed, "NFS?" },
	{ "No route to host", "\r", g_entry, trans_srvr_ping_failed, "NFS?" },
	{ "DRS DDS #", "tftp  0x80400000  remote_debug.txt\r", 0, trans_notify, "Ethernet test" },
	{0}
};









XTrans	g_uboot2_interrupt[]
=
{
	{ "DRS DDS #", "echo 'autoboot stopped'\r",	g_uboot2_ping_server, 0, 0 },
	{ "4", "  ", 0, 0, 0 },
	{ "3", "  ", 0, 0, 0 },
	{ "2", "  ", 0, 0, 0 },
	{0}
};









static XTrans	g_uboot_reset[]
=
{
	{ "DRS DDS #", "reset\r", 0, 0, 0 },
	{ "any key to stop autoboot",	"   ",	g_uboot2_interrupt, 0, 0 },
	{0}
};





static XTrans	g_uboot_saveenv[]
=
{
	{ "DRS DDS #", "saveenv\r", 0, 0, 0 },
	{ "done", 0, g_uboot_reset, 0, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};


static XTrans	g_uboot_set_bootargs[]
=
{
	{ "DRS DDS #", 0, g_uboot_saveenv, trans_bootargs, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	g_uboot_set_bootcmd[]
=
{
	{ "DRS DDS #", "setenv bootcmd 'tftpboot;bootm'\r", g_uboot_set_bootargs, 0, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	g_uboot_set_serverip[]
=
{
	{ "DRS DDS #", "\r", g_uboot_set_bootcmd, trans_set_serverip, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	g_uboot_set_ipaddr[]
=
{
	{ "DRS DDS #", 0, g_uboot_set_serverip, trans_ipaddr, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	g_uboot_set_etha[]
=
{
	{ "DRS DDS #", 0, g_uboot_set_ipaddr, trans_ethaddr, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	g_uboot_interrupted[]
=
{
	{ "DRS DDS #", "echo 'autoboot stopped'\r", g_uboot_set_etha, trans_initstate, "Bootloader..." },
	{0}
};

XTrans	g_uboot_interrupt[]
=
{
	{ "DRS DDS #", "\r",	g_uboot_interrupted, 0, 0 },
	{ "4", "  ", 0, 0, 0 },
	{ "3", "  ", 0, 0, 0 },
	{ "2", "  ", 0, 0, 0 },
	{0}
};



//static XTrans	g_reboot[]
//={
//	{ "#", "reboot -f\r", g_entry, trans_notify, "Rebooting" },
//	0
//};


static XTrans	g_cycle_power[]
=
{
	{ "any key to stop autoboot",	"   ",	g_uboot_interrupt, 0, 0 },
	{ "Retry count exceeded; starting again", "\r", 0, trans_srvr_ping_failed, "Pls Cycle Power" },
	{ "not responding, still trying", 0, 0, trans_srvr_ping_failed, "NFS..." },
	{ "DRS DDS #", "echo '--' \r", g_uboot_interrupted, 0, 0 },
	{ "#", "echo 'Please Cycle Power'\r", 0, trans_sleep, "Pls Cycle Power" },
	{ "password:", "\r", g_entry, 0, 0 },
	{ "login:", "\r", g_entry, 0, 0 },
	{0}
};


static XTrans	g_loaded_test[]
=
{
	{ "inet addr:", "\r", g_root_welcome, trans_test_ipaddr, 0 },
	{ "#", "\r", g_cycle_power, trans_notify, "Pls Cycle Power" },
	{0}
};

static XTrans	g_loaded_ifconfig_eth[]
=
{
	{ "inet addr:", "\r", g_root_welcome, trans_test_ipaddr, 0 },
	{ "eth0", 0, g_loaded_test, 0, 0 },
	{ "ethO", 0, g_loaded_test, 0, 0 },
	//{ "#", "\r", g_cycle_power, trans_notify, "Cycle Power Pls" },
	{0}
};


static XTrans	g_loaded_ifconfig[]
=
{
	{ "#", "ifconfig\r", g_loaded_ifconfig_eth, trans_notify, "ifconfig" },
	{0}
};


static XTrans	g_srvr_eth[]
=
{
	{ " 100% packet loss", "\r", g_entry,  trans_srvr_ping_failed, "Ethernet?" },
	{ " 0% packet loss", "\r", g_loaded_ifconfig, trans_srvr_ping_success, 0 },
	{ "Network is unreachable", "\r", g_entry, trans_srvr_ping_failed, "Ethernet?" },
	{ "lookup failure", "\r", g_entry, trans_srvr_ping_failed, "Ethernet?" },
	{0}
};


#if 0
static XTrans	g_loaded_ifconfig[]
=
{
	{ "#", "ifconfig\r", g_loaded_ifconfig_eth, 0, 0 },
	{0}
};
#endif

static XTrans	g_loaded[]
=
{
	{ "print: not found", 0, g_srvr_eth, trans_srvr_ping, "eth" },
	{ "any key to stop autoboot",	"   ",	g_uboot_interrupt, 0, 0 },
	{ "DRS DDS #", "echo 'loading'\r", g_uboot_interrupted, 0, 0 },
	{0}
};

// this test whether or not we are in uboot or linux
static XTrans	g_loaded_print[]
=
{
	{ "any key to stop autoboot",	"   ",	g_uboot_interrupt, 0, 0 },
	{ "#", "print\r", g_loaded, 0, 0 },
	{0}
};



XTrans	g_entry[]
=
{
	{ "any key to stop autoboot",	"   ",	g_uboot_interrupt, 0, 0 },
	{ "Retry count exceeded; starting again", "\r", TPX_EXIT, trans_srvr_ping_failed, "Cycle Power" },
	{ "not responding, still trying", 0, TPX_EXIT, trans_srvr_ping_failed, "NFS..." },
	{ "login:", "root\r", TPX_EXIT, 0, 0 },
	{ "password:", "\r", TPX_EXIT, 0, 0 },
	{ "DRS DDS #", "print\r", g_uboot_interrupted, 0, 0 },
	{ "#", "\r", g_loaded_print, trans_notify, "Cycle Power" },
	{0}
};

/*---------------------------------------------------------------------+\
|	Setup as Virigin System												|
\+---------------------------------------------------------------------*/


static XTrans	v_uboot_reset[]
=
{
	{ "DRS DDS #", "reset\r", 0, trans_notify, "Virg: Cycle Power" },
	{0}
};





static XTrans	v_uboot_saveenv[]
=
{
	{ "DRS DDS #", "saveenv\r", 0, 0, 0 },
	{ "done", 0, v_uboot_reset, 0, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};


static XTrans	v_uboot_set_essload[]
=
{
	{ "DRS DDS #", "setenv essload\r", v_uboot_saveenv, 0, 0 },
	{0}
};


static XTrans	v_uboot_set_bootargs[]
=
{
	{
		"DRS DDS #",
		"setenv bootargs console=ttyS0,115200n8 root=/dev/nfs rw "
		"eth=00:05:09:ff:aa:aa "
		"ip=192.168.1.200 "
		"nfsroot=192.168.1.4:/tftpboot stdin=serial stdout=serial\r",
		v_uboot_set_essload, 0, 0
	},
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	v_uboot_set_bootcmd[]
=
{
	{ "DRS DDS #", "setenv bootcmd 'tftpboot;bootm'\r", v_uboot_set_bootargs, 0, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	v_uboot_set_serverip[]
=
{
	{ "DRS DDS #", "setenv serverip 192.168.1.4\r", v_uboot_set_bootcmd, 0, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	v_uboot_set_ipaddr[]
=
{
	{ "DRS DDS #", "setenv ipaddr 192.168.1.200\r", v_uboot_set_serverip, 0, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	v_uboot_set_etha[]
=
{
	{ "DRS DDS #", "setenv ethaddr 00:05:09:FF:AA:AA\r", v_uboot_set_ipaddr, trans_ethaddr, 0 },
	{ "#", "\r", 0, 0, 0 },
	{0}
};

static XTrans	v_uboot_interrupted[]
=
{
	{ "DRS DDS #", "echo 'autoboot stopped'\r", v_uboot_set_etha, trans_notify, "Virginizing" },
	{0}
};

XTrans	v_uboot_interrupt[]
=
{
	{ "DRS DDS #", "\r",	v_uboot_interrupted, 0, 0 },
	{ "4", "  ", 0, 0, 0 },
	{ "3", "  ", 0, 0, 0 },
	{ "2", "  ", 0, 0, 0 },
	{0}
};




XTrans	v_virgin_setup[]
=
{
	{ "any key to stop autoboot",	"   ",	v_uboot_interrupt, 0, 0 },
	{ "DRS DDS #", "print\r", v_uboot_interrupted, 0, 0 },
	{0}
};





/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CConsole - constructor

\+---------------------------------------------------------------------*/
CConsole::CConsole
		(
		void
		)
		: m_oMutex()
		, m_oSemaphore()
		//, m_oSignal()
		, m_hThreadRx( 0 )
		, m_hThreadTx( 0 )
		, m_oPort()
		, m_sPortName()
		, m_sServerIP()
		, m_nCount( 0 )
		, m_aProcessors( 0 )
		, m_sLogfile()
		, m_hLogfile( 0 )
{
	m_aProcessors = new XProc[5];
}


/*---------------------------------------------------------------------+\

 * ~CConsole - destructor

\+---------------------------------------------------------------------*/
CConsole::~CConsole
		(
		void
		)
{
	Stop( 0 );

	if ( m_hLogfile )
		fclose( m_hLogfile );

	if ( m_aProcessors )
		delete [] m_aProcessors;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * LoadSettings -

\+---------------------------------------------------------------------*/
void	CConsole::LoadSettings
		(
		CSerialPortSettingsPtr p
		)
{
	if ( p )
		m_oPort.LoadSettings( *p );
}


/*---------------------------------------------------------------------+\

 * SetPortName -

\+---------------------------------------------------------------------*/
void	CConsole::SetPortName
		(
		const char*	s
		)
{
	DbgPrint( "%s : %s\n", __PRETTY_FUNCTION__, s );
	m_oPort.SetPortName( s );
	m_sLogfile = BuildPath( s );
	m_sPortName = s;
}


/*---------------------------------------------------------------------+\

 * SetServerIP -

\+---------------------------------------------------------------------*/
void	CConsole::SetServerIP
		(
		const char*	s
		)
{
	m_sServerIP = s;
}


/*---------------------------------------------------------------------+\

 * SetCallback -

\+---------------------------------------------------------------------*/
void	CConsole::SetCallback
		(
		long			nIndex,
		CApplicationGaugePtr	p
		)
{
	m_nPortIndex = nIndex;
	m_pApplication = p;
	m_pDataPage = p->DictPageData();
	m_pConstantsPage = p->DictPageConstants();

	CCharString		sESS;
	CCharString		sEmpty;
	CVariantData	v;

	sESS.Format( "ESS %d PORT OPEN", m_nPortIndex+1 );
	v = m_bOpen = false;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsOpen = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry( (unsigned long)m_ndsOpen, v );

	sESS.Format( "ESS %d PORT NAME", m_nPortIndex+1 );
	v = this->m_sPortName;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsPortName = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsPortName, v );

	sESS.Format( "ESS %d STATE", m_nPortIndex+1 );
	v = 0L;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsState = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsState, v );

	sESS.Format( "ESS %d ACTIVE", m_nPortIndex+1 );
	v = 0L;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsActive = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsActive, v );

	sESS.Format( "ESS %d TESTED", m_nPortIndex+1 );
	v = 0L;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsTested = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsTested, v );

	sESS.Format( "ESS %d FAILED", m_nPortIndex+1 );
	v = 0L;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsFailed = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsFailed, v );

	sESS.Format( "ESS %d MESSAGE", m_nPortIndex+1 );
	v = m_sMessage = sEmpty;
	m_pDataPage->AddEntry( sESS, v );
	m_ndsMessage = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsMessage, v );

	sESS.Format( "ESS %d MILLI", m_nPortIndex+1 );
	v = m_nMilli = milliseconds();
	m_pDataPage->AddEntry( sESS, v );
	m_ndsMilli = m_pDataPage->LocateEntry( sESS );
	m_pDataPage->UpdateEntry((unsigned long)m_ndsMilli, v );


}


/*---------------------------------------------------------------------+\

 * InitState -

\+---------------------------------------------------------------------*/
void	CConsole::InitState
		(
		void
		)
{
	CCharString	sEmpty;

	m_pFirstState = g_entry;
	m_pCurrentState = g_entry;
	m_nCount = 0;
	m_nPrevCount = 0;

	m_nWriteCount = 0;

	m_nState = 0;
	m_nTested = 0;
	m_nActive = 0;
	m_nFailed = 0;
	m_sMessage = sEmpty;
	m_nMilliStart = milliseconds();
	m_nMilli = m_nMilliStart;
	m_nDspIndex = 0;

	for ( int i = 0; i < 5; ++i )
	{
		m_aProcessors[i].sIP.Format( "192.168.0.%d", m_nPortIndex * 5 + 200 + 5 + i );
		m_aProcessors[i].bTest = false;
		m_aProcessors[i].nTests = 0;
		m_aProcessors[i].nFailures = 0;
		m_aProcessors[i].nMilli = 0;
	}

	m_aProcessors[0].sIP = m_sServerIP;


}



/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
bool	CConsole::Start
		(
		VDictionaryPtr	//pDictionary
		)
{
	bool	bResult = false;
	NResult	nr;

	CCharString		sESS;
	CCharString		sEmpty;
	CVariantData	v;

	//CMutexLocker	lock( &m_oMutex );

	LOCAL_PRINT( "CConsole::Start[%d] - Begin\n", m_nPortIndex );

	do_sequence
	{
		m_bOpen = false;
		m_bInputBusy = false;

		m_sLogfile = BuildPath( m_sPortName.Pointer() );


		InitState();




		m_oPort.SetTimeout( 200 );
		//m_oPort.SetNonblocking( true );
		nr = m_oPort.Open( CSerial::MODE_ReadWrite );

		if ( NR_FAILED( nr ) )
			break;

		m_bOpen = true;


		m_oPort.Flush();



		m_hThreadRx = ThreadCreate( ( UThreadFunction )ThreadRxGlue, this );

		if ( ! m_hThreadRx )
			break;

//#ifdef USE_TXTHREAD
		m_hThreadTx = ThreadCreate( ( UThreadFunction )ThreadTxGlue, this );

		if ( ! m_hThreadTx )
			break;

//#endif
		const char sStarting[] = "\recho 'starting'\r";
		WritePort( sStarting, strlen( sStarting ) );

		fopen_s( &m_hLogfile, m_sLogfile.Pointer(), "w+" );
//		if ( 0 != r )
//			break;


		bResult = true;
	}

	if ( ! bResult )
	{
		if ( m_hThreadRx )
			ThreadClose( m_hThreadRx );

		m_hThreadRx = 0;

		if ( m_hThreadTx )
			ThreadClose( m_hThreadTx );

		m_hThreadTx = 0;

		if ( m_oPort.IsOpen() )
			m_oPort.Close();

		m_bOpen = false;
	}

	LOCAL_PRINT( "CConsole::Start[%d] - End\n", m_nPortIndex );

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Stop -

\+---------------------------------------------------------------------*/
bool	CConsole::Stop
		(
		VDictionaryPtr	//pDictionary
		)
{

	CMutexLocker	lock( &m_oMutex );

	if ( m_hThreadRx )
		ThreadClose( m_hThreadRx );

	m_hThreadRx = 0;

	if ( m_hThreadTx )
		ThreadClose( m_hThreadTx );

	m_hThreadTx = 0;

	if ( m_hLogfile )
		fclose( m_hLogfile );

	m_hLogfile = 0;

	m_oPort.Close();
	m_bOpen = false;
	m_nState = 0;
	m_sMessage = "";

	for ( int i = 0; i < 5; ++i )
	{
		m_aProcessors[i].bTest = false;
		m_aProcessors[i].nTests = 0;
		m_aProcessors[i].nFailures = 0;
		m_aProcessors[i].nMilli = 0;
	}

	//if ( pDictionary )
	//{
	//	Calculate( pDictionary );
	//}

	return true;
}


/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
bool	CConsole::Calculate
		(
		VDictionaryPtr //pDictionary
		)
{
	CVariantData	v;
	long		nMilli = milliseconds();
	long		nDelta = nMilli - m_nMilli;
	long		nState;


	m_oMutex.Lock();

	// calculate current state

	nState = m_nState & ESS_K_FAIL;		// save the failure state (clear all else)
	long	nActive = 0;
	long	nFailed = 0;
	long	nTested = 0;

	XProc*	p = &m_aProcessors[0];

	for ( int i = 0; i < 5; ++i, ++p )
	{
		if ( 0 < p->nTests )
		{
			nTested |= 1 << i;

			if ( 0 < p->nFailures )
			{
				nFailed |= 1 << i;

				if ( 2 < p->nFailures )
					nState |= ESS_K_FAIL;
			}

			if ( i == m_nDspIndex )
				nActive = 1 << m_nDspIndex;
		}
	}



	if ( 5 < m_nCount )
	{
		if ( nDelta < 4000 )
			nState |= ESS_K_ACTIVE;
		else if ( nDelta < 30000 )
			nState |= ESS_K_PAUSED;
		else if ( nDelta < 120000 )
			nState |= ESS_K_WAIT;
		else
			nState |= ESS_K_FAIL | ESS_K_WAIT;
	}
	else
	{
		if ( nDelta < 5 * 60 * 1000 )
			nState |= ESS_K_INACTIVE;
		else if ( nDelta < 10 * 60 * 1000 )
			nState |= ESS_K_IDLE;
		else
			nState |= ESS_K_DEAD;
	}

	m_nPrevCount = m_nCount;
	m_nState = nState;
	m_nActive = nActive;
	m_nTested = nTested;
	m_nFailed = nFailed;

	m_oMutex.Unlock();

	v = nState;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsState, v );

	v = nActive;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsActive, v );

	v = nTested;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsTested, v );

	v = nFailed;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsFailed, v );

	v = m_bOpen;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsOpen, v );
	//pDictionary->PutData( m_ndsOpen, &v );

	v = m_sPortName;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsPortName, v );

	v = m_sMessage;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsMessage, v );
	//pDictionary->PutData( m_ndsMessage, &v );

	v = nMilli - m_nMilliStart;
	m_pDataPage->UpdateEntry((unsigned long)m_ndsMilli, v );
	//pDictionary->PutData( m_ndsMilli, &v );



//#ifdef USE_TXTHREAD
	if ( m_nWriteCount < 1 )
	{
		if ( 20000 < nDelta )
		{
			if ( m_nCount < 1 )
			{
				const char	sEcho[] = "echo 'Are you there?'\r";
				nDelta %= 10000;
				nDelta /= 100;

				if ( nDelta < 25 )
					WritePort( sEcho, strlen( sEcho ) );

				m_pCurrentState = g_entry;
			}
			else
			{
				const char	sEcho[] = "\recho 'Paused?'\r";

				if ( 30000 < nDelta )
				{
					WritePort( sEcho, strlen( sEcho ) );

					if ( 60000 < nDelta )
						m_pCurrentState = g_entry;
				}
			}
		}
	}

//#endif


	return true;
}


bool	CConsole::Virginize
		(
		void
		)
{
	m_pCurrentState = v_virgin_setup;
	Notify( "Prep: Virginize" );

	return true;
}





/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CConsole::WritePort
		(
		const char*	sBuffer,
		size_t		nCount
		)
{
	bool	bResult = true;

	//LOCAL_PRINT( "CConsole::WritePort[%d] nCount = %ld\n", m_nPortIndex, nCount );

	CMutexLocker	lock( &m_oMutex );

	if ( m_nWriteCount + nCount < ( long )sizeof( m_aWriteBuffer ) )
	{

		memcpy_s( &m_aWriteBuffer[m_nWriteCount],
		          sizeof( m_aWriteBuffer )-m_nWriteCount,
		          sBuffer, nCount );

		m_nWriteCount += nCount;
		//DbgPrint( "WritePort::nCount = %ld\n", m_nWriteCount );

		if ( 0 < m_nWriteCount )
			m_oSemaphore.Signal();

		//m_oSignal.Set();
	}


	return bResult;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CConsole::CompareLastWritten
		(
		const char*	sBuffer,
		long		//nCount
		)
{
	CMutexLocker	lock( &m_oMutex );

	if ( strstr( sBuffer, ( const char* )m_aLastWriteBuffer ) )
		return true;
	else
		return false;

	//if ( 0 == ::strncmp( (const char*)m_aWriteBuffer, sBuffer, m_nWriteCount ) )
	//	return true;
	//else
	//	return false;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
long	CConsole::GetIndex
		(
		void
		)
{
	return m_nPortIndex;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
ConstCCharStringRef
		CConsole::GetServerIP
		(
		void
		)
{
	return m_sServerIP;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
ConstCCharStringRef
		CConsole::GetTestingIP
		(
		void
		)
{
	int	n = umin( umax( m_nDspIndex,0L ),4L );
	return m_aProcessors[n].sIP;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CConsole::Notify
		(
		const char*	sComment
		)
{
	CMutexLocker	lock( &m_oMutex );
	m_sMessage = sComment;

	return true;

}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
long	CConsole::GetCount
		(
		void
		)
{
	CMutexLocker	lock( &m_oMutex );

	return m_nDspIndex;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CConsole::SetCount
		(
		long	n
		)
{
	CMutexLocker	lock( &m_oMutex );

	m_nDspIndex = n;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CConsole::SetDspState
		(
		bool	b
		)
{
	CMutexLocker	lock( &m_oMutex );

	int	n = umin( umax( m_nDspIndex,0L ),4L );

	XProc*	p = &m_aProcessors[n];

	if ( b )
	{
		if ( p->nTests < 3  &&  p->nFailures == p->nTests )
			p->nFailures = 0;	// a bit of grace
	}
	else
	{
		p->nFailures += 1;
	}

	p->bTest = b;
	p->nTests += 1;
	p->nMilli = milliseconds();

}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CConsole::SetFailureState
		(
		const char* s
		)
{
	if ( s )
	{
		Notify( s );
	}
	else
	{
		Notify( "Unspecified Failure" );
	}

	CMutexLocker	lock( &m_oMutex );
	m_nState |= ESS_K_FAIL;
}


bool	CConsole::InputBusy
		(
		void
		)
{
	bool	bResult = false;

	if ( 0 < m_oPort.AvailableBytes() )
	{
		bResult = true;
	}

	//else
	//{
	//	CMutexLocker	lock( &m_oMutex );
	//	if ( m_bInputBusy )
	//		bResult = true;
	//}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * ThreadRxGlue -

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CConsole::ThreadTxGlue
		(
		void*	pArg
		)
{
	CConsolePtr	pThis = CConsolePtr( pArg );

	if ( pThis )
		pThis->ThreadTx();

	return ( UThreadRtn ) 0;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
UThreadRtn
		CConsole::ThreadTx
		(
		void
		)
{
	LOCAL_PRINT( "CConsole::ThreadTx  thread starting\n" );
	bool	bNeedWrite = false;

	forever_loop
	{
		//LOCAL_PRINT( "ThreadTx::m_nWriteCount = %ld\n", m_nWriteCount );

		// only write if we have emptied the read buffer
		if ( 0 < m_nWriteCount  &&  ! InputBusy() )
		{

			m_oMutex.Lock();
			size_t	n = m_nWriteCount;
			uint_t	i = n;
			const unsigned char*	p = ( const unsigned char* )m_aWriteBuffer;

			while ( 0 < i )
			{
				millisleep( 10 );
				m_oPort.Write( p, umin( uint_t( 4 ), i ) );
				p += 4;
				i -= 4;
			}

			bNeedWrite = false;

			memcpy_s( m_aLastWriteBuffer, sizeof( m_aLastWriteBuffer ),
			          m_aWriteBuffer, n );
			m_nLastWriteCount = n;

			if ( m_aLastWriteBuffer[m_nLastWriteCount-1] == '\r' )
				--m_nLastWriteCount;

			m_aLastWriteBuffer[m_nLastWriteCount] = 0;

			m_nWriteCount = 0;
			m_oMutex.Unlock();
		}
		else
		{
			if ( ! bNeedWrite )
			{
				//m_oSignal.Wait();
				m_oSemaphore.Wait();

				if ( 0 < m_nWriteCount )
					bNeedWrite = true;
			}
			else
			{
				millisleep( 200 );
			}
		}

	}

	return ( UThreadRtn ) 0;
}






/*---------------------------------------------------------------------+\

 * ThreadRxGlue -

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CConsole::ThreadRxGlue
		(
		void*	pArg
		)
{
	CConsolePtr	pThis = CConsolePtr( pArg );

	if ( pThis )
		pThis->ThreadRx();

	return ( UThreadRtn ) 0;
}

/*---------------------------------------------------------------------+\

 * ThreadRx -

\+---------------------------------------------------------------------*/
UThreadRtn
		CConsole::ThreadRx
		(
		void
		)
{
	unsigned char	buffer[1024];
	size_t			nCount;
	//unsigned long	nWriteable;

	buffer[0] = 0;

	//WritePort( "print\r", 6 );

	forever_loop
	{

		nCount = 0;
		//m_oMutex.Lock();
		//nWriteable = 0;
		//m_oMutex.Unlock();
		//if ( nWriteable < 1 )
		//{
#if 1

		do
		{
			size_t	n = m_oPort.Read( buffer+nCount, sizeof( buffer )-1-nCount );
			nCount += n;

		}
		while ( 0 < m_oPort.AvailableBytes()
		&&	nCount < sizeof( buffer )-1 );

#else
		nCount = m_oPort.Read( buffer, sizeof( buffer )-1 );
#endif

		if ( 0 < nCount )
		{
			//LOCAL_PRINT( "ThreadRx::nCount = %ld\n", nCount );
			buffer[nCount] = 0;	// null-terminate

			m_oMutex.Lock();

			m_nCount += nCount;
			m_nMilli = milliseconds();

			m_oMutex.Unlock();

#if 1
#if defined( _DEBUG )
			DbgPrint( "[[%d]]", nCount );

			for ( unsigned long i = 0; i < nCount; ++i )
			{
				unsigned int	c = buffer[i] & 0x00FFu;

				if ( ' ' <= c  &&  c <= '~' )
				{
					DbgPrint( "%c", c );
				}
				else
				{
					if ( '\n' == c  ||  '\r' == c )
						DbgPrint( "%c", c );
					else if ( 8 == c )		// backspace
						DbgPrint( "%c", '.' );
					else
						DbgPrint( "%%%02X", c );
				}
			}

#endif
#endif
			//m_oMutex.Lock();
			//m_bInputBusy = true;
			//m_oMutex.Unlock();

			ProcessStream( ( char* )buffer, long( nCount ) );

			//m_oMutex.Lock();
			//m_bInputBusy = false;
			//m_oMutex.Unlock();

			if ( m_hLogfile )
			{
				fwrite( buffer, nCount, 1, m_hLogfile );
				fflush( m_hLogfile );
			}


		}

		//}
		//else
		//{
		//	millisleep( 10 );
		//}
	}

	return ( UThreadRtn ) 0;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CConsole::ProcessStream
		(
		char*	sBuffer,
		long	nCount
		)
{
	bool	bResult = true;

	// break sBuffer into multiple lines

	char*	p = sBuffer;
	char*	pBegin = p;
	char*	pEnd = p + nCount;

	long	nLen = 0;

	while ( p < pEnd )
	{
		switch ( *p )
		{
		case '\r':
		case '\n':
			nLen = long( p - pBegin );

			if ( 0 < nLen )
			{
				*p = 0;
				bResult = ProcessLine( pBegin, nLen );
			}

			pBegin = p+1;

			break;

		default:
			break;
		}

		++p;
	}

	nLen = long( p - pBegin );

	if ( 0 < nLen )
	{
		*p = 0;
		bResult = ProcessLine( pBegin, nLen );
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CConsole::ProcessLine
		(
		const char*	sBuffer,
		long		nCount
		)
{
	bool		bResult = true;
	XTransPtr	p = m_pCurrentState;
	//DbgPrint( "\nProcessLine:*p = %p\n", p );



#if 0
#if defined( _DEBUG )
	DbgPrint( "\n[[[ %d ]]]", nCount );

	for ( long i = 0; i < nCount; ++i )
	{
		unsigned int	c = sBuffer[i] & 0x00FF;

		if ( ' ' <= c  &&  c <= '~' )
		{
			DbgPrint( "%c", c );
		}
		else
		{
			if ( 8 == c )		// backspace
				DbgPrint( "%c", '.' );
			else
				DbgPrint( "%%%02X", c );

			if ( '\n' == c  ||  '\r' == c )
				DbgPrint( "%c", c );
		}
	}

#endif
#endif

	if ( p )
	{

		bool	bProcess = false;

		while ( p )
		{
			if ( p->sToken )
			{
				if ( TN_ALWAYS == p->sToken )
					bProcess = true;
				else if ( strstr( sBuffer, p->sToken ) )
					bProcess = true;
				else
					bProcess = false;

				if ( bProcess )
				{
					NResult	nr = NR_S_SUCCESS;

					if ( p->pFunc )
						nr = ( *p->pFunc )( this, p, sBuffer, nCount );

					if ( NR_SUCCEEDED( nr ) )
					{
						if ( p->sResponse )
						{
							WritePort( p->sResponse, strlen( p->sResponse ) );
						}

						if ( p->pNextState )
						{
							//LOCAL_PRINT( "\n>>> state change = %p\n\n", p->pNextState );
							m_pCurrentState = p->pNextState;
							bResult = true;
						}

						break;
						//if ( TPX_EXIT == p->pNextState )
						//{
						//	bResult = true;
						//	break;
						//}
						//else if ( TPX_FAIL == p->pNextState )
						//{
						//	//SetFailureState( "Failed State" );
						//	bResult = false;
						//	break;
						//}
						//else if ( TPX_NEXT == p->pNextState )
						//{
						//	bResult = true;
						//	break;
						//}
						//else
					}
				}
			}
			else
			{
				//SetFailureState( "Unrecognized State" );
				//bResult = false;
				bResult = true;
				break;
			}

			++p;
		}
	}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * BuildPath -

\+---------------------------------------------------------------------*/
CCharString
		CConsole::BuildPath
		(
		const char*	//sPort
		)
{
	char		sPath[1024];
	CCharString	sName;

	CDateTime	dNow = CDateTime::CurrentTime();

	dNow.FormatGMT( sPath, sizeof( sPath ), "%Y%m%d-%H%M" );
	sName.Format( "logfiles\\log_%d-%s.log", m_nPortIndex+1, sPath );


	//sName.Format( "log_%s.log", sPort );

	const char*	s = GetUserConfigFolder();
	PathBuild( sPath, sizeof( sPath ), s, sName.Pointer() );

	return CCharString( sPath );
}




/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
