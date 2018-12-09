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
#include "VPluginService.h"

#include "IDictionaryUser.h"
#include "IVehicleDataSample.h"

#include "CSocket.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMutex.h"

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
	NResult	StartDataFlow
			(
			void
			);

	virtual
	NResult	StopDataFlow
			(
			void
			);

	virtual
	NResult	ToggleDataFlow
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
	NResult	LocalStart
			(
			void
			);

	virtual
	NResult	LocalStop
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

	CSocketUDPPtr			m_pSocket;		// multicast socket
	CCharString				m_sMCAddress;
	long					m_nMCPort;

	UThreadHdl				m_hThread;

	long					m_nFrequency;	// milliseconds

	char					m_sData[1024*4];

	long					m_nMilliStart;
	long					m_nMilli;
	CDateTime				m_oTime;
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
			ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr pLib
			);

public:
	//	IService
	virtual
	NResult	Start
			(
			void
			);

	virtual
	NResult	Stop
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
