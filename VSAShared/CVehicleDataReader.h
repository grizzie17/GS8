/*---------------------------------------------------------------------+\
|
|	CVehicleDataReader.h  --  brief description of what CVehicleDataReader.h is for
|
|	Purpose:
|	File Custodian:		M.Rose
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
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
	15-Oct-2009			M.Rose			(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CVehicleDataReader
#define _H_CVehicleDataReader
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

#include "UMachine.h"

#if defined( OS_LINUX )
#	include <sys/socket.h>
#	include <netinet/in.h>
#elif defined( OS_MSWIN )
#	include <winsock2.h>
#	include <ws2tcpip.h>
#endif

#ifdef OS_LINUX_VDDS
#   include <mqueue.h>
#   include "vdds_graphics.h"
#endif

#include "UVehicleData.h"
#include "CCharDescriptor.h"




namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CVehicleDataReader*		CVehicleDataReaderPtr;
typedef class CVehicleDataReader&		CVehicleDataReaderRef;
typedef const class CVehicleDataReader&	ConstCVehicleDataReaderRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/
const int NUM_DISPLAYS = 4;

class CVehicleDataReader
{
//	class lifecycle  ----------------------------------------------------
public:
					CVehicleDataReader();
	virtual			~CVehicleDataReader();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	int				Initialize(void);

	void			CalculateMilliTime( void );

	const char*		GetActiveData( void );

	int				ReadActiveData(void);

	static unsigned int	SaveActiveData( CVehicleDataReader* arg );

	void 			SetMCAddress(Yogi::Core::CCharDescriptorRef r);
	void 			SetMCPort(unsigned short p);
	void 			SetMCPort(long p);
	void 			SetMCTimeout(int t);
	void			SetMCMaxMsgSize(int m);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	int			GetXMLMsg( void );

	bool		MsgIsOk( char* buf, unsigned int len );

//	protected data  -----------------------------------------------------

	char*					m_pGoodMsg;
	unsigned int			m_nSequence;

	bool					m_bInitDone;

	time_t					m_nMilli;

#if defined(OS_LINUX)
	int						m_xmlFD;
#else
	SOCKET					m_xmlFD;
#endif

	struct sockaddr_in		m_LocAddr;
	//struct sockaddr			m_LocAddr;
	struct ip_mreq			m_mreq;

	long					m_nRxBytes;

	fd_set					m_FDset;
	time_t					m_Span;
	time_t					m_msgTimer;

	char 					m_sMultiCastAddr[INET_ADDRSTRLEN];
	unsigned short			m_nMultiCastPort;
	int						m_nMCTimeOut;
	int 					m_nMCMaxMsgSize;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------
#if defined( OS_LINUX_VDDS )
    mqd_t                   m_eventDescr[NUM_DISPLAYS];
#endif
//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}



#endif /* _H_CVehicleDataReader */
