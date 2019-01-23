/*---------------------------------------------------------------------+\
|
|	CServiceVehicleDataSample.h  --  brief description of what CServiceVehicleDataSample.h is for
|
|	Purpose:
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceVehicleDataSample
#define _H_CServiceVehicleDataSample
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CSocket.h"
#include "VPluginService.h"

#include "IDictionaryUser.h"
#include "IVehicleDataSample.h"

#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMutex.h"
#include "UPlatformThreads.h"

#include "CDateTime.h"
//#include <sys/timeb.h>


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/



#define	SSPC_MAX_CHANNELS	16
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CServiceVehicleDataSample*		CServiceVehicleDataSamplePtr;
typedef class CServiceVehicleDataSample&		CServiceVehicleDataSampleRef;
typedef const class CServiceVehicleDataSample&	ConstCServiceVehicleDataSampleRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceVehicleDataSample : public VPluginService,
						implements_ IDictionaryUser,
						implements_ IVehicleDataSample
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CServiceVehicleDataSample );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IDictionaryUser
	virtual
	bool	SetDictionary
			(
			VDictionaryPtr	p	// IN:	dictionary pointer
			);

	//	IVehicleDataSample

	virtual
	Yogi::Core::NResult
			StartDataFlow
			(
			void
			);

	virtual
	Yogi::Core::NResult
			StopDataFlow
			(
			void
			);

	virtual
	Yogi::Core::NResult
			ToggleDataFlow
			(
			void
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


	virtual
	Yogi::Core::NResult
			LocalStart
			(
			void
			);

	virtual
	Yogi::Core::NResult
			LocalStop
			(
			void
			);


	static
	UThreadRtn
			RunGlue
			(
			void*	pThis
			);

	UThreadRtn
			Run
			(
			void
			);

	long	BuildVehicleXML();
	void	CalculateMilliTime();



//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;

	Yogi::Core::CSocketUDPPtr	m_pSocket;		// multicast socket
	Yogi::Core::CCharString	m_sMCAddress;
	long					m_nMCPort;

	::UThreadHdl			m_hThread;

	long					m_nFrequency;	// milliseconds

	char					m_sData[1024*4];

	long					m_nMilliStart;
	long					m_nMilli;
	Yogi::Core::CDateTime	m_oTime;
	//timeb					m_tTimeb;
	//struct tm				m_tTm;


private:
//	private types  ------------------------------------------------------

	typedef VPluginService	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
			);

public:
	//	IService
	virtual
	Yogi::Core::NResult
			Start
			(
			void
			);

	virtual
	Yogi::Core::NResult
			Stop
			(
			void
			);


};

}}

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


#endif /* _H_CServiceVehicleDataSample */
