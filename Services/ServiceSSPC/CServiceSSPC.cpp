/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CServiceSSPC.cpp  --  brief description of what CServiceSSPC.cpp is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <unistd.h>

#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "can4linux.h"
#include "CServiceSSPC.h"
#include "VPluginFactory.h"
#include "UNResult.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

namespace Yogi { namespace Gadget {

// Uncomment the following #define to enable debug printing statements
//
//#define CServiceSSPC_DBG_PRINT


// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
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

PLUGIN_CREATE_FACTORY( CServiceSSPC );





//#include <include/asm/arch/can4linux.h>

//CAN Defines
#define PRIORITY 6
#define R        0
#define DP       0
#define PF       239


//CAN Addresses
int CanHost = 0xEF;
int CanSspc = 0xE0;




/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CServiceSSPC - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  08-Sep-2010

\+---------------------------------------------------------------------*/
CServiceSSPC::CServiceSSPC
		(
		void
		)
		: inherited(),
		m_sPort(),
		m_nBaud( 500 ),
		m_nChannelCount( 0 ),
		m_nDelay(8),
		m_nRetry(3),
		m_nChannelState(0),
		m_pRxThread( 0 ),
		m_pTxThread( 0 )
{
}

CServiceSSPC::CServiceSSPC
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_sPort(),
		m_nBaud( 500 ),
		m_nChannelCount( 0 ),
		m_nDelay(8),
		m_nRetry(3),
		m_nChannelState(0),
		m_pRxThread( 0 ),
		m_pTxThread( 0 )
{
}

CServiceSSPC::CServiceSSPC
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_sPort(),
		m_nBaud( 500 ),
		m_nChannelCount( 0 ),
		m_nDelay(8),
		m_nRetry(3),
		m_nChannelState(0),
		m_pRxThread( 0 ),
		m_pTxThread( 0 )
{
}

/**--------------------------------------------------------------------+\

 * <summary>CServiceSSPC - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  08-Sep-2010

\+---------------------------------------------------------------------*/
CServiceSSPC::~CServiceSSPC
		(
		void
		)
{
	if ( m_bRunning )
		Stop();
}

/*=====================================================================+\
||	 interface implementation functions									|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IService
\+---------------------------------------------------------------------*/


NResult	CServiceSSPC::Start
		(
		void
		)
{
	NResult	nr = NR_E_NOTHREAD;

	CMutexLocker	lock( &m_oMutex );	// automatically unlocks when function exits

	do_sequence
	{
		m_pRxThread = ThreadCreate( (UThreadFunction)RunGlueRx, this );
		if ( ! m_pRxThread )
			break;

		m_pTxThread = ThreadCreate( (UThreadFunction)RunGlueTx, this );
		if ( ! m_pTxThread )
		{
			ThreadClose( m_pRxThread );
			break;
		}

		m_bRunning = true;
		nr = NR_S_SUCCESS;

	}

	return nr;

}


NResult	CServiceSSPC::Stop
		(
		void
		)
{
	if ( m_pRxThread )
	{
		ThreadClose( m_pRxThread );
		m_pRxThread = 0;
	}
	if ( m_pTxThread )
	{
		ThreadClose( m_pTxThread );
		m_pTxThread = 0;
	}
	m_bRunning = false;
	return NR_S_SUCCESS;
}




/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/**--------------------------------------------------------------------+\

 * <summary>Load - Load parameters from XML</summary>

 * <remarks/>

 * (author)J.Griswold  --  08-Sep-2010

\+---------------------------------------------------------------------*/
bool	CServiceSSPC::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		m_sPort = pConfig->GetParameterAsString("Port","/dev/can0");
		m_nBaud = pConfig->GetParameterAsInteger("Baud", 500 );
		m_nChannelCount = pConfig->GetParameterAsIntegerArray( m_aChannels, SSPC_MAX_CHANNELS, "Channels" );
		m_nDelay = pConfig->GetParameterAsInteger( "Delay", 8 );
		m_nRetry = pConfig->GetParameterAsInteger( "Retries", 3 );
	}

	return bResult;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/
long	CServiceSSPC::vddsOpenCanPort
		(
		char*	port_to_open,
		unsigned int *port_name
		)
{
	long status = 0;

	// Open the CAN port
	*port_name = open((const char *)port_to_open, O_RDWR,0);
    if (*port_name < 0)
    {
        printf("ERROR: Could not open can port %s\n", port_to_open);
        return (-1);
    }
    return status;
}
            /* device descriptor */ /* bit rate */
int		CServiceSSPC::set_bitrate
		(
		int can_fd,
		int baud
		)
{
    Config_par_t  cfg;
    volatile Command_par_t cmd;

    cmd.cmd = CMD_STOP;
    ioctl(can_fd, CAN_IOCTL_COMMAND, &cmd);

    cfg.target = CONF_TIMING;
    cfg.val1   = baud;
    ioctl(can_fd, CAN_IOCTL_CONFIG, &cfg);

    cmd.cmd = CMD_RESET;
    ioctl(can_fd, CAN_IOCTL_COMMAND, &cmd);

    cmd.cmd = CMD_START;
    ioctl(can_fd, CAN_IOCTL_COMMAND, &cmd);
    return 0;
}



void	CServiceSSPC::Power_On_Cameras
		(
		void
		)
{
	int status;
	canmsg_t txmsg;
	canmsg_t rxmsg;
	Send_par_t  sendmsg;
	int canHandle;

	unsigned short int channelStateTemp = 0x00;

	int i=0;
	int j=0;
	int error = 0;

	//Set the Read CAN to non blocking so the Program will not hang if the SSPC Card is not there
	rxmsg.flags |= O_NONBLOCK;

	LogPrint("\nTurning Cameras On\n");

	status = 0;

	status = vddsOpenCanPort(m_sPort, (unsigned int*)&canHandle);
	status = set_bitrate(canHandle, m_nBaud);


	//pause so that the CAN port can be open and configured
	sleep(1);

	// build arbitration id by or'ing PDU format, source, and destination
	txmsg.id  = (PRIORITY << 26);	// priority
	txmsg.id |= (R 	  << 25); // R
	txmsg.id |= (DP 	  << 24); // DP
	txmsg.id |= (PF 	  << 16);	// PF
	txmsg.id |=  CanHost;		// Source
	txmsg.id |= (CanSspc  << 8); 	// Destination

	txmsg.flags = MSG_EXT;	// extended ID flag (IDC)
	txmsg.length = 4;

	//clear data
	for(i=0; i<8; i++)
	{
		txmsg.data[i] = 0x00;
	}

	//Create message
	txmsg.data[0] = 0x01;

	for(i=0; i<m_nChannelCount; i++)
	{
		//Reset variables
		status = -1;

		//Update the current list of channels with the new channel
		channelStateTemp = m_nChannelState;
		channelStateTemp |= (1 << m_aChannels[i]);
		txmsg.data[2] = channelStateTemp & 0xFF;
		txmsg.data[3] = (channelStateTemp >> 8) & 0xFF;

		//Send the CAN Message
		sendmsg.Tx = &txmsg;
		status = write(canHandle, &txmsg, 1);

		//Display the information to the console
		LOCAL_PRINT("\nPower on channel %d: ", m_aChannels[i]);
		LOCAL_PRINT("\nCAN ID 0x%x, data=0x%x%x%x%x%x%x%x%x\n",
				txmsg.id, txmsg.data[1], txmsg.data[0],
				txmsg.data[3], txmsg.data[2],
				txmsg.data[5], txmsg.data[4],
				txmsg.data[7], txmsg.data[6]);

		if (status == -1)
		{
			LogPrint("\nCAN write error");
		}
		else if (status == 0)
		{
			LogPrint("\nCAN transmit timed out\n");
		}
		else
		{
			LOCAL_PRINT("\nCAN transmit Success\n");
		}

		for(j=0; j<m_nRetry; j++)
		{
			//Get Responce back from SSPC
			status = read(canHandle, &rxmsg, 1);

			if(status > 0)
			{
				if(rxmsg.data[0] == 0x02)
				{
					m_nChannelState = (rxmsg.data[3] << 8);
					m_nChannelState |= rxmsg.data[2];
				}

				LOCAL_PRINT("\nRx from SSPC: CANID: 0x%x\n", rxmsg.id);
				LOCAL_PRINT("Received data: 0x%x%x%x%x%x%x%x%x\n", rxmsg.data[1], rxmsg.data[0], rxmsg.data[3], rxmsg.data[2], rxmsg.data[5], rxmsg.data[4], rxmsg.data[7], rxmsg.data[6]);
				break;
			}
		}

		//Wait till the next channel can be turned on
		sleep(m_nDelay);
	}

	//Loop through and see which SSPC Ports are On or Off
	error = 0;
	for(i=0; i<16; i++)
	{
		if(((m_nChannelState >> i) & 0x01) == 1)
		{
			LOCAL_PRINT("\nChannel %d is On", i);

			for(j=0; j < m_nChannelCount; j++)
			{
				if(m_aChannels[j] == i)
				{
					error++;
				}
			}
		}
	}

	//Close the CAN Port
	close(canHandle);

	if(error == m_nChannelCount)
	{
		LogPrint("All Cameras are ON\n");
	}
	else
	{
		LogPrint("\n\nSome Cameras are OFF\n");
	}
}



/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>RunGlue - Function to call "Run" from within spawned thread</summary>

 * <remarks/>

 * (author)J.Griswold  --  08-Sep-2010

\+---------------------------------------------------------------------*/
//static
unsigned int
		CServiceSSPC::RunGlueRx
		(
		void*	pVoid
		)
{
	CServiceSSPCPtr	pThis = (CServiceSSPCPtr)pVoid;

	pThis->RunRx();

	return 0;
}


void	CServiceSSPC::RunRx
		(
		void
		)
{
    int             status;
    canmsg_t rxmsg;


    status = 0;

	status = vddsOpenCanPort( m_sPort, (unsigned int*)&m_nCanHandle );
	status = set_bitrate( m_nCanHandle, m_nBaud );


    while(1)
    {
        //Get Responce back from SSPC
		status = 0;
        status = read(m_nCanHandle, &rxmsg, 1);

        if(status > 0)
        {
			if(rxmsg.data[0] == 0x02){
				m_nChannelState = (rxmsg.data[3] << 8);
				m_nChannelState |= rxmsg.data[2];
			}

            LOCAL_PRINT("\nRx from SSPC: CANID: 0x%x\n", rxmsg.id);
            LOCAL_PRINT("Received data: 0x%x%x%x%x%x%x%x%x\n", rxmsg.data[1], rxmsg.data[0], rxmsg.data[3], rxmsg.data[2], rxmsg.data[5], rxmsg.data[4], rxmsg.data[7], rxmsg.data[6]);
		}
    }

}

unsigned int
		CServiceSSPC::RunGlueTx
		(
		void*	pVoid
		)
{
	CServiceSSPCPtr	pThis = (CServiceSSPCPtr)pVoid;

	pThis->RunTx();

	return 0;
}


void	CServiceSSPC::RunTx
		(
		void
		)
{
	int status;
	canmsg_t txmsg;
	Send_par_t  sendmsg;
	unsigned short int channelStateTemp = 0x00;
	int i=0;
	int j=0;
	int error = 0;

	LogPrint("\nTurning Cameras On\n");
	//pause so that the CAN port can be open and configured
	sleep(1);
	// build arbitration id by or'ing PDU format, source, and destination
	txmsg.id  = (PRIORITY << 26);	// priority
	txmsg.id |= (R 	  << 25); // R
	txmsg.id |= (DP 	  << 24); // DP
	txmsg.id |= (PF 	  << 16);	// PF
	txmsg.id |=  CanHost;		// Source
	txmsg.id |= (CanSspc  << 8); 	// Destination
	txmsg.flags = MSG_EXT;	// extended ID flag (IDC)
	txmsg.length = 4;
	//clear data
	for(i=0; i<8; i++)
	{
		txmsg.data[i] = 0x00;
	}
	//Create message
	txmsg.data[0] = 0x01;
	for(i=0; i<m_nChannelCount; i++)
	{
		//Reset variables
		status = -1;
		//Update the current list of channels with the new channel
		channelStateTemp = m_nChannelState;
		channelStateTemp |= (1 << m_aChannels[i]);
		txmsg.data[2] = channelStateTemp & 0xFF;
		txmsg.data[3] = (channelStateTemp >> 8) & 0xFF;
		//Send the CAN Message
		sendmsg.Tx = &txmsg;
		status = write(m_nCanHandle, &txmsg, 1);
		//Display the information to the console
		LOCAL_PRINT("\nPower on channel %d: ", m_aChannels[i]);
		LOCAL_PRINT("\nCAN ID 0x%x, data=0x%x%x%x%x%x%x%x%x\n", txmsg.id, txmsg.data[1], txmsg.data[0], txmsg.data[3], txmsg.data[2], txmsg.data[5], txmsg.data[4], txmsg.data[7], txmsg.data[6]);
		if (status == -1)
		{
			LogPrint("\nCAN write error");
		}
		else if (status == 0)
		{
			LogPrint("\nCAN transmit timed out\n");
		}
		else
		{
			LOCAL_PRINT("\nCAN transmit Success\n");
		}
		//Wait till the next channel can be turned on
		sleep(m_nDelay);
	}
	error = 0;
	for(i=0; i<16; i++)
	{
		if(((m_nChannelState >> i) & 0x01) == 1)
		{
			LOCAL_PRINT("\nChannel %d is On", i);
			for(j=0; j<m_nChannelCount; j++)
			{
				if(m_aChannels[j] == i)
				{
					error++;
				}
			}
		}
	}
	close(m_nCanHandle);
	if(error == m_nChannelCount)
	{
		LogPrint("\n\nAll Cameras are ON\n");
	}
	else
	{
		LogPrint("\n\nSome Cameras are OFF\n");
	}
}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  08-Sep-2010

\+---------------------------------------------------------------------*/


}}
