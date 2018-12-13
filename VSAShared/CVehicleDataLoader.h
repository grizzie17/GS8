/*---------------------------------------------------------------------+\
|
|	CVehicleDataLoader.h  --  brief description of what CVehicleDataLoader.h is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	03-Dec-2009			M.Rose			(Reviewed by: P.Hogan)
		Add sequence number to vehicle data messaging so that
		stale data does not trigger updates.
	19-Nov-2009			M.Rose			(Reviewed by: P.Hogan)
		Fix linux side of dynamic message buffer size
	13-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Setup multicast configuration done via
		vehicledataconfiguration.xml file.
	05-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Make MSWIN OS Vehicle data reader a separate thread
	26-Oct-2009			M.Rose			(Reviewed by: P.Hogan)
		Remove xml vehicle data message read processing so
		it can be in a single separate reader thread
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
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Integrate CFactoryVehicleData
	23-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CVehicleDataLoader
#define _H_CVehicleDataLoader
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


#include "CApplicationGauge.h"
#include "UVehicleData.h"
#include "CFactoryVehicleData.h"
#include "TPointer.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CVehicleDataLoader*			CVehicleDataLoaderPtr;
typedef class CVehicleDataLoader&			CVehicleDataLoaderRef;
typedef const class CVehicleDataLoader&	ConstCVehicleDataLoaderRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CVehicleDataLoader
{
//	class lifecycle  ----------------------------------------------------
public:
					CVehicleDataLoader();
	virtual			~CVehicleDataLoader();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void		SetApplication( CApplicationGaugePtr p );

	void		UpdateActivePage( void );

	bool		SizeMsgBuf(size_t size);

	static
	VDMessages_t*
				GetVDMessages( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	int			GetActiveData(char* buf);

//	protected data  -----------------------------------------------------

	CApplicationGaugePtr			m_pApplication;
	Yogi::Core::TPointer<CFactoryVehicleData>	m_pVehicleData;

	time_t					m_nMilliStart;
	time_t					m_nMilli;
	time_t					m_nMsgTimer;

	char*					m_pMsgBuf;
	size_t					m_nBufSiz;
	size_t					m_nMsgLen;
	unsigned int			m_nSequence;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

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



#endif /* _H_CVehicleDataLoader */
