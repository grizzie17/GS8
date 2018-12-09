/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2009 DRS Test & Energy Management LLC						|
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
|	CVehicleDataReader.cpp  --  brief description of what CVehicleDataReader.cpp is for
|
|	Purpose:
|	File Custodian:		M.Rose
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
	06-Jul-2010			P.Hogan			(Reviewed by: J.Griswold)
		Changed case of Stdafx.h include file for compatibility with
		case sensitive file systems. Changed graphics events
		arguments for compatibility with IGraphicsEvent.
	03-Dec-2009			M.Rose			(Reviewed by: N.Graham)
		Fix bug, check for good pointer to shared memory buffer.
		Reduce memcpy usage to only when good new messages rec'd.
	03-Dec-2009			M.Rose			(Reviewed by: P.Hogan)
		Add sequence number to vehicle data messaging so that
		stale data does not trigger updates.
	19-Nov-2009			M.Rose			(Reviewed by: P.Hogan)
		Fix linux side of dynamic message buffer size
    19-Nov-2009         P.Hogan         (Reviewed by: M.Rose)
        Changed to event driven graphics updates
	18-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Move local message buffer from loop to member variable
	13-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Setup multicast configuration done via
		vehicledataconfiguration.xml file.
	05-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Make MSWIN OS Vehicle data reader a separate thread
	15-Oct-2009			M.Rose			(Reviewed by: P.Hogan)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include <math.h>
#include <errno.h>
#include <string.h>

#include "CVehicleDataReader.h"

#include "UPlatform.h"
//#include "gauges.h"

#if defined( OS_LINUX )
#	include <unistd.h> // need for inet_aton
#	include <net/if.h>
#	include <sys/ioctl.h>
#	include <arpa/inet.h>
#	include <fcntl.h>
#	include <pthread.h>
#   include "GraphicsEventParam.h"
#endif

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
const char xmlHdr[]		=	"<?xml version=";
const char xmlRoot[]	=	"<VehicleData";
const char xmlRootEnd[]	=	"</VehicleData>";
const char xmlData[]	=	"<Parameters";
const char xmlDataEnd[]	=	"</Parameters>";

namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/


#if defined ( OS_LINUX )

pthread_mutex_t		mutex_save_vdr; // saved vehicle data

#elif defined ( OS_MSWIN )

HANDLE				mutex_save_vdr;
LPCWSTR				p_mutexName;

#endif

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CVehicleDataReader - constructor</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
CVehicleDataReader::CVehicleDataReader
		(
		void
		)
		:
		m_pGoodMsg( NULL ),
		m_nSequence( 0 ),
		m_bInitDone( 0 ),
		m_nMilli( 0 ),
		m_msgTimer( 0 ),
		m_nMultiCastPort( 0 ),
		m_nMCTimeOut( 0 ),
		m_nMCMaxMsgSize( 1024 )
{
	memset(m_sMultiCastAddr,0,INET_ADDRSTRLEN);
	memset(&gVDMsgs,0,sizeof(gVDMsgs));
}


/**--------------------------------------------------------------------+\

 * <summary>~CVehicleDataReader - destructor</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+----------------------------------------------------------------------*/
CVehicleDataReader::~CVehicleDataReader
		(
		void
		)
{
	if ( m_pGoodMsg )
		delete [] m_pGoodMsg;
	m_pGoodMsg = NULL;

	if ( gVDMsgs.msg1.pMsg )
		delete [] gVDMsgs.msg1.pMsg;
	gVDMsgs.msg1.pMsg = NULL;

	if ( gVDMsgs.msg2.pMsg )
		delete [] gVDMsgs.msg2.pMsg;
	gVDMsgs.msg2.pMsg = NULL;
#if defined ( OS_LINUX )

	pthread_mutex_destroy(&mutex_save_vdr);

#elif defined ( OS_MSWIN )

	CloseHandle(mutex_save_vdr);

#endif

}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>GetActiveData - get pointer to ready data</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
const char*
		CVehicleDataReader::GetActiveData
		(
		void
		)
{
	char* p = 0;
	if ( gVDMsgs.msg1.bReady == true )
	{
		p = gVDMsgs.msg1.pMsg;
	}
	else if ( gVDMsgs.msg2.bReady == true )
	{
		p = gVDMsgs.msg2.pMsg;
	}

	return p;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>SetActiveData	- set data buffer pointer</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
unsigned int
		CVehicleDataReader::SaveActiveData
		(
		CVehicleDataReader* arg
		)
{
	if ( NULL == arg ) // bail quick if so
		return 0;

	CVehicleDataReader* m_pVDR = (CVehicleDataReader*)arg;

	int dataLen			= 0;
	char* msg			= 0;
	long* len			= 0;
	unsigned int* seq	= 0;
	bool* bNew			= 0;
	bool* bOld			= 0;

	if ( m_pVDR )
		m_pVDR->m_nSequence	= 0;
	/*
	char up[] = "Up";
	char dw[] = "Down";
	char* who = 0;
	*/
	while ( m_pVDR )
	{
		dataLen = m_pVDR->ReadActiveData();
		if ( 0 < dataLen )
		{
			m_pVDR->m_nSequence++;

#if defined( OS_LINUX )

			pthread_mutex_lock(&mutex_save_vdr); // lock before reading, setting pointers

#elif defined ( OS_MSWIN )

			WaitForSingleObject(mutex_save_vdr,INFINITE);

#endif
			if ( gVDMsgs.msg1.bReady == false )
			{
				msg  =  gVDMsgs.msg1.pMsg;
				len  = &gVDMsgs.msg1.nLen;
				seq  = &gVDMsgs.msg1.nSeq;
				bNew = &gVDMsgs.msg1.bReady;
				bOld = &gVDMsgs.msg2.bReady;
				//who = up;
			}
			else // when msg1.bReady == true, must put new data in msg2
			{
				msg  =  gVDMsgs.msg2.pMsg;
				len  = &gVDMsgs.msg2.nLen;
				seq  = &gVDMsgs.msg2.nSeq;
				bNew = &gVDMsgs.msg2.bReady;
				bOld = &gVDMsgs.msg1.bReady;
				//who = dw;
			}
			// pointers set, write new data
			*seq = m_pVDR->m_nSequence;

			*len = dataLen;
			memcpy(msg,m_pVDR->m_pGoodMsg,dataLen);
			msg[dataLen] = 0;

			*bNew = true;
			*bOld = false;

#if defined( OS_LINUX )

			pthread_mutex_unlock(&mutex_save_vdr); // unlock, writes done

#if defined( OS_LINUX_VDDS )
            // ToDo: Hard coding the used display for M1200. Remove when this
            // is read from a configuration file.
            //
//            setVddsGraphicsEvent(m_pVDR->m_eventDescr[0], DATA_AVAILABLE, 0);
            for (int i = 0; i < NUM_DISPLAYS; i++)
            {
                setVddsGraphicsEvent(m_pVDR->m_eventDescr[i], DATA_AVAILABLE, 0);
            }
#endif

#elif defined ( OS_MSWIN )

			ReleaseMutex(mutex_save_vdr);

#endif
			//char tx[48];memcpy(tx,&msg[24],31);tx[31]=0;printf("\n,VMD %s dataLen %d, %s,\n",who,dataLen,tx);
			// finished gettig new data

		} // end if ( 0 < dataLen )

	} // end while ( m_pVDR )

	return 0; // will never be here

} // end unsigned int	CVehicleDataReader::SaveActiveData

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>CalculateMilliTime - relative to OS local</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataReader::CalculateMilliTime
		(
		void
		)
{
	m_nMilli = milliseconds();
}


/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>Initialize - get good socket to receive vehicle data</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

int		CVehicleDataReader::Initialize
		(
		void
		)
{
	m_bInitDone = false;
	int goodInit = 0;

	memset(&m_mreq,0,sizeof(m_mreq));

	if ( m_pGoodMsg == NULL  &&  0 < m_nMCMaxMsgSize )
		m_pGoodMsg = new char[m_nMCMaxMsgSize];

	if ( NULL == m_pGoodMsg )
	{
		//TODO application Alert
		printf("ALERT! NO memory to put vehicle data in\n");
		goodInit = -12;

		return goodInit;
	}

#if defined( OS_LINUX )

	pthread_mutexattr_t mxAttr;
	pthread_mutexattr_init(&mxAttr);
	int rval = pthread_mutexattr_settype(&mxAttr,PTHREAD_MUTEX_ERRORCHECK);
	if ( 0 == rval )
    	rval = pthread_mutex_init (&mutex_save_vdr, &mxAttr);

    if ( rval != 0 )
		printf("CVehicleDataReader constructor, mutex init ERROR %d, errno %d : %s,\n",rval,errno,strerror(errno));


	if ( inet_aton(m_sMultiCastAddr,(in_addr*)&m_mreq.imr_multiaddr.s_addr) < 0 )
		goodInit = -1;

	struct ifreq ifr;
	strcpy( ifr.ifr_name, "eth0" );
	ifr.ifr_ifru.ifru_addr.sa_family = AF_INET;

	int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); // temporary socket variable
	if ( sock ) // just to get local host address
	{
		if ( -1 < ioctl(sock, SIOCGIFADDR, &ifr) )
		{
			m_mreq.imr_interface.s_addr = ((struct sockaddr_in*)&ifr.ifr_ifru.ifru_addr)->sin_addr.s_addr;
			//char* sIp = inet_ntoa(m_mreq.imr_interface);	debugging
		}
		else
		{
			goodInit = -3;
		}

		close(sock); // yes, close every time, temporary socket only
	}
	else
	{
		goodInit = -2;
	}

#else
/*------------------------------------------------------------------*/
/*							Windows specific						*/

	// do windows mutex work here

	mutex_save_vdr = CreateMutex(NULL,false,p_mutexName);

	m_mreq.imr_multiaddr.s_addr = inet_addr(m_sMultiCastAddr);

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 ); // specific WinSock DLL
	if ( (WSAStartup( wVersionRequested, &wsaData )) != 0 )
		goodInit = -4;

	if (LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2)
		goodInit = -5;

	if ( goodInit < 0 ) //TODO: Alert "Could not find a usable WinSock DLL"
		WSACleanup( );

	char sHost[128] = {0};
	if ( ::gethostname(sHost, sizeof(sHost)) == 0 ) // get local host name
		{
		struct hostent* pHost = ::gethostbyname(sHost);
			if ( pHost != NULL )
			{
			memcpy(&m_mreq.imr_interface,pHost->h_addr_list[0],pHost->h_length);
			//char* sIp = inet_ntoa(m_mreq.imr_interface);	debugging
			}
			else
			{
				WSAGetLastError(); // error handling
				goodInit = -7;
			}
		}
	else
	{
		WSAGetLastError(); // error handling
		goodInit = -6;
	}

/*--------------			End Windows specific		--------------*/
/*--------------------------------------------------------------------*/
#endif
#if defined( OS_LINUX_VDDS )
    for (int i = 0; i < NUM_DISPLAYS; i++)
    {
        m_eventDescr[i] = openVddsGraphics(i);
    }
#endif

	m_xmlFD = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if ( m_xmlFD < 0 )
		goodInit = -8;
	else
		++goodInit;

	/*
	http://www.tldp.org/HOWTO/Multicast-HOWTO-6.html
	If not otherwise specified, multicast datagrams are sent with a default time to live (TTL) value of 1,
	to prevent them to be forwarded beyond the local network.
	*/

	unsigned int opt = 1;
	if ( setsockopt(m_xmlFD,SOL_SOCKET,SO_REUSEADDR,(const char*)&opt,sizeof(opt)) < 0 )
		goodInit = -9;
	else
		++goodInit;

	memset(&m_LocAddr,0,sizeof(m_LocAddr));
	m_LocAddr.sin_family = AF_INET;

	m_LocAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_LocAddr.sin_port = htons(m_nMultiCastPort);

	if ( bind(m_xmlFD,(struct sockaddr*)&m_LocAddr,sizeof(m_LocAddr)) < 0 )
		goodInit = -10;
	else
		++goodInit;

#if defined( OS_LINUX )

	if ( setsockopt(m_xmlFD,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&m_mreq,sizeof(m_mreq)) < 0 )

#else // OS_MSWIN

	if ( setsockopt(m_xmlFD,IPPROTO_IP,IP_ADD_MEMBERSHIP,(const char*)&m_mreq,sizeof(m_mreq)) < 0 )

#endif
	{
		goodInit = -11;
	}

	if ( 0 < goodInit )
	{
		goodInit = m_xmlFD;
		m_bInitDone = true;
	}
	else
	{
#if defined( OS_LINUX )
		close(m_xmlFD);
		m_xmlFD = -1;
#elif defined ( OS_MSWIN )
		closesocket(m_xmlFD);
		m_xmlFD = 0;
#endif
		//TODO application Alert
	}

	CalculateMilliTime();
	m_msgTimer = m_nMilli;

	return goodInit;
}
//END_OVERRUN_WARNING

/**--------------------------------------------------------------------+\

 * <summary>GetXMLMsg - The workhorse method for this class/thread</summary>

 * <remarks>Key, this is a blocking socket, running in a separate thread.
			This method blocks in recvfrom until data, message is available.
			The message gets a very basic validation check before being saved.
  </remarks>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
int		CVehicleDataReader::GetXMLMsg
		(
		void
		)
{
	m_nRxBytes = 0; // return value

	if ( m_pGoodMsg )
	{

		//int recvCt=0, goodCt=0;
		if ( 0 < m_xmlFD )	// valid socket
		{
			socklen_t len = sizeof(m_LocAddr);
			m_pGoodMsg[0] = 0;
			m_nRxBytes = (long)recvfrom(m_xmlFD,m_pGoodMsg,m_nMCMaxMsgSize-1,0,(struct sockaddr*)&m_LocAddr,&len);
			//++recvCt;

			printf( "**************** warning reading from wrong place \n" );

			if ( 0 < m_nRxBytes )
			{
				if ( false == MsgIsOk(m_pGoodMsg,m_nRxBytes) )
				{
					m_nRxBytes = 0;
				}
				//else
				//	++goodCt;
			}
			else if ( m_nRxBytes < 0 ) // error from recvfrom
			{
	#if defined ( OS_LINUX )

				if ( EBADFD != errno || EBADF != errno )
					close(m_xmlFD);
					m_xmlFD = -1;

	#elif defined ( OS_MSWIN )

				if ( WSAGetLastError() != WSAEBADF )
					closesocket(m_xmlFD);
					m_xmlFD = 0;

	#endif
				m_bInitDone = false;
			}

			CalculateMilliTime();
			m_Span = m_nMilli - m_msgTimer;

			if ( m_nMCTimeOut < m_Span)
			{
				//TODO application Alert
				printf("ALERT! Socket %d, Active data NOT updated for %ld\n",m_xmlFD,(long)m_Span);
			}

			if ( 0 < m_nRxBytes )
				m_msgTimer = m_nMilli; // reset timer since a valid message was received

		} // end if ( 0 < m_xmlFD )	// valid socket
		else
		{
			//TODO application Alert
			printf("ALERT! FAILED to open Socket to read vehicle data on\n");
		}

		//printf("\n  GetXMLMsg reads %d, good message count %d,",recvCt,goodCt);

	}
	return m_nRxBytes;

} // end int		CVehicleDataReader::GetXMLMsg


/**--------------------------------------------------------------------+\

 * <summary>MsgIsOk - very basic XML well-form-ed-ness check</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
bool	CVehicleDataReader::MsgIsOk
		(
		char* buf,
		unsigned int len
		)
{
	char*	posHdr	= NULL;
	char*	posRoot	= NULL;
	char*	posREnd	= NULL;
	char*	posData = NULL;
	char*	posDEnd = NULL;

	if ( buf == NULL || len < 1 )
		return false;

	buf[len] = 0; // NULL terminate buffer/string

	posHdr = strstr(buf,xmlHdr);
	if (  posHdr == NULL )
	{
		posHdr = buf;	// Maybe no header? Set at first byte, should be == Root
	}

	posRoot = strstr(posHdr,xmlRoot);
	if ( posRoot == NULL )
		return false;

	posData = strstr(posRoot,xmlData);
	if ( posData == NULL )
		return false;

	posDEnd = strstr(posData,xmlDataEnd);
	if ( posDEnd == NULL )
		return false;

	posREnd = strstr(posDEnd,xmlRootEnd);
	if ( posREnd == NULL )
		return false;

	posHdr = strchr(posREnd,'>');
	if ( posHdr == NULL )
		return false;

	++posHdr = 0; // insure any garbage bytes past posREnd does not matter

	return true;
}

/**--------------------------------------------------------------------+\

 * <summary>ReadActiveData - get message from socket interface</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
int		CVehicleDataReader::ReadActiveData
		(
		void
		)
{
	if ( m_bInitDone == false )
	{
		if ( Initialize() < 1 )
		{
			//TODO: send Alert command
			return 0;
		}
	}

	return GetXMLMsg();
}

/**--------------------------------------------------------------------+\

 * <summary>SetMCAddress - copies supplied char array (string) to member
							variable holding Multicast address
  </summary>

 * <remarks/>

 * (author)M.Rose  --  09-Nov-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataReader::SetMCAddress
		(
		CCharDescriptorRef r
		)
{
	r.CopyTo(m_sMultiCastAddr,sizeof(m_sMultiCastAddr));
}

/**--------------------------------------------------------------------+\

 * <summary>SetMCPort - brief statement</summary>

 * <remarks/>

 * (author)M.Rose  --  09-Nov-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataReader::SetMCPort
		(
		long p
		)
{
	if ( 0 < p )
		SetMCPort((unsigned short)p);
}


void	CVehicleDataReader::SetMCPort
		(
		unsigned short p
		)
{
	if ( 0 < p )
		m_nMultiCastPort = p;
}

/**--------------------------------------------------------------------+\

 * <summary>SetMCTimeout - brief statement</summary>

 * <remarks/>

 * (author)M.Rose  --  09-Nov-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataReader::SetMCTimeout
		(
		int t
		)
{
	if ( 0 < t )
		m_nMCTimeOut = t;
}

/**--------------------------------------------------------------------+\

 * <summary>SetMCMaxMsgSize - brief statement</summary>

 * <remarks/>

 * (author)M.Rose  --  09-Nov-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataReader::SetMCMaxMsgSize
		(
		int m
		)
{
	if ( 0 < m )
	{
		m_nMCMaxMsgSize = m;
		gVDMsgs.maxSiz = m;

		if ( gVDMsgs.msg1.pMsg )
			delete [] gVDMsgs.msg1.pMsg;

		gVDMsgs.msg1.pMsg = new char[m];

		if ( gVDMsgs.msg2.pMsg )
			delete [] gVDMsgs.msg2.pMsg;

		gVDMsgs.msg2.pMsg = new char[m];
	}
}

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)M.Rose  --  15-Oct-2009

\+---------------------------------------------------------------------*/
