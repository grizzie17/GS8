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
|	CVehicleDataLoader.cpp  --  brief description of what CVehicleDataLoader.cpp is for
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
	06-Jul-2010			P.Hogan			(Reviewed by: J.Griswold)
		Changed case of Stdafx.h include file for compatibility with
		case sensitive file systems.
	03-Dec-2009			M.Rose			(Reviewed by: N.Graham)
		Fix bug, check for good pointer to shared memory buffer.
		Reduce memcpy usage to only when good new messages rec'd.
	03-Dec-2009			M.Rose			(Reviewed by: P.Hogan)
		Add sequence number to vehicle data messaging so that
		stale data does not trigger updates.
	19-Nov-2009			M.Rose			(Reviewed by: P.Hogan)
		Fix linux side of dynamic message buffer size
	13-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Setup multicast configuration done via
		vehicledataconfiguration.xml file.
	05-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Add MSWIN OS code to handle Vehicle data reader as
		a separate thread
	26-Oct-2009			M.Rose			(Reviewed by: P.Hogan)
		Remove xml vehicle data message read processing so
		it can be in a single separate reader thread
	08-Oct-2009			M.Rose			(Reviewed by: R.Hosea)
		Fix MsgIsOk so xml header is optional
		Speed up strstr searches, pass good pointer to next search
	05-Oct-2009			M.Rose			(Reviewed by: J.Griswold)
		Fix compiler warnings
	03-Oct-2009			M.Rose			(Reviewed by: R.Hosea)
		Read socket, process data robustness, correctness
	29-Sep-2009			M.Rose			(Reviewed by: R.Hosea)
		Fix gcc compile errors
	23-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Rename to CVehicleDataLoader
	22-Sep-2009			M.Rose			(Reviewed by: R.Hosea)
		Add test generation of Alert data
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add test generation of Alert data
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		transition to gmtime_s to resolve MSVC
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Integrate CFactoryVehicleData
	23-Aug-2009			J.Griswold
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

#include "CVehicleDataLoader.h"

#if defined( OS_LINUX )
#	include <pthread.h>
#	include <unistd.h>
	// need for inet_aton
#	include "arpa/inet.h"
#	include <fcntl.h>
#endif

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

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
VDMessages_t		gVDMsgs;

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


class CVehicleReadCallBack : public XMLLite::VReadCallBack
{
public:
	CVehicleReadCallBack
		(
		char*	s,
		size_t	n
		)
		: m_pMsg( s ),
		m_nMsgLen( n )
	{}

	virtual
	size_t	Read					// RTN:	returns number of bytes actually read
			(
			void*			pBuffer,		// OUT: buffer to receive data
			size_t			nBytesToRead,	// IN:	number of bytes to read
			XMLLite::ETEXT_FORMAT			// IN:	target format
			)
	{
		size_t	n = nBytesToRead < m_nMsgLen ? nBytesToRead : m_nMsgLen;
		if ( 0 == memcpy_s( pBuffer, nBytesToRead, m_pMsg, n ) )
			return n;
		else
			return 0;
	}

	/*
		Gets the size of the file (stream)
	*/
	virtual
	size_t	GetSize		// RTN:	return file (stream) size in bytes
			(
			void
			)
	{
		return m_nMsgLen;
	}

	/*
		Get a name associated with the call-back stream.
		For files this should be name of the file or
		at least a partial path with name.
	*/
	//BEGIN_OVERRUN_WARNING
	virtual
	size_t	GetName					// RTN:	string length of name
			(
			char*			sTarget,	// OUT:	buffer to receive name
			size_t			nSizeTarget	// IN:	size of target
			)
	{
		char	sName[] = "VehicleData";
		if ( 0 < nSizeTarget )
			strcpy_s( sTarget, nSizeTarget, sName );
		return strlen( sName );
	}
	//END_OVERRUN_WARNING


protected:
	char*	m_pMsg;
	size_t	m_nMsgLen;
};


/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CVehicleDataLoader - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
CVehicleDataLoader::CVehicleDataLoader
		(
		void
		)
		: m_pApplication( 0 ),
		m_pVehicleData( 0 ),
		m_nMilliStart( 0 ),
		m_nMilli( 0 ),
		m_nMsgTimer( 0 ),
		m_pMsgBuf( NULL ),
		m_nBufSiz( 0 ),
		m_nMsgLen( 0 ),
		m_nSequence( 0 )
{
}


/**--------------------------------------------------------------------+\

 * <summary>~CVehicleDataLoader - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
CVehicleDataLoader::~CVehicleDataLoader
		(
		void
		)
{
	if ( m_pMsgBuf )
		delete [] m_pMsgBuf;
	m_pMsgBuf = NULL;

}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>SetApplication - create, set access pointer</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataLoader::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;

	if ( ! m_pVehicleData )
		m_pVehicleData = new CFactoryVehicleData;

	m_pVehicleData->SpecifyActivePage( p->DictPageActive() );
	m_pVehicleData->SpecifyNotifyPage( p->DictPageNotify() );
}


/**--------------------------------------------------------------------+\

 * <summary>UpdateActivePage - put vehicle data into dictionary</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
void	CVehicleDataLoader::UpdateActivePage
		(
		void
		)
{
	m_nMsgLen = 0;
	if ( SizeMsgBuf(gVDMsgs.maxSiz) )
	{
		m_nMsgLen = GetActiveData( m_pMsgBuf );
	}

	if ( 0 < m_nMsgLen )
	{
		CVehicleReadCallBack	callback( m_pMsgBuf, m_nMsgLen );
		m_pVehicleData->LoadData( &callback );
	}
}

/**--------------------------------------------------------------------+\

 * <summary>SizeMsgBuf - get good socket to receive vehicle data</summary>

 * <remarks/>

 * (author)M.Rose  --  12-Nov-2009

\+---------------------------------------------------------------------*/
bool	CVehicleDataLoader::SizeMsgBuf
	(
	size_t	size
	)
{
	if ( m_nBufSiz < size )
	{
		if ( NULL != m_pMsgBuf )
			delete [] m_pMsgBuf;

		m_pMsgBuf = new char[size];

		if ( NULL == m_pMsgBuf )
			return false;

		m_nBufSiz = size;
		return true;
	}
	else
	{
		return true;
	}
}



//static
VDMessages_t*
		CVehicleDataLoader::GetVDMessages
		(
		void
		)
{
	return 0;
	//return &gVDMsgs;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>GetActiveData - get message from socket interface</summary>

 * <remarks/>

 * (author)M.Rose  --  28-Sep-2009

\+---------------------------------------------------------------------*/
int		CVehicleDataLoader::GetActiveData
	(
    char* dataBuf
	)
{
	int len = 0;
	VDMsg_t* pMsg	= 0;

	if ( dataBuf )
	{
#if defined( OS_LINUX )

	pthread_mutex_lock(&mutex_save_vdr); // lock before reading

#elif defined ( OS_MSWIN )

	WaitForSingleObject(mutex_save_vdr,INFINITE);

#endif

	if ( true == gVDMsgs.msg1.bReady )
	{
		pMsg = &gVDMsgs.msg1;
	}
	else if ( true == gVDMsgs.msg2.bReady )
	{
		pMsg = &gVDMsgs.msg2;
	}

	if ( pMsg )
	{
		if ( m_nSequence < pMsg->nSeq )	// message sequence, only pickup a higher sequence
		{								// otherwize, do nothing, data stale
			memcpy(dataBuf,pMsg->pMsg,pMsg->nLen);

			len = pMsg->nLen;
			m_nSequence = pMsg->nSeq;
		}
	}

#if defined( OS_LINUX )

	pthread_mutex_unlock(&mutex_save_vdr); // unlock after reading

#elif defined ( OS_MSWIN )

	ReleaseMutex(mutex_save_vdr);

#endif

	dataBuf[len] = 0; // good when data exists and when no data
	}

	return len;
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

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
