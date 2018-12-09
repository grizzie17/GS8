/*---------------------------------------------------------------------+\
|
|	CmdVehicleDataLoader.h  --  Header for CmdVehicleDataLoader Plugin
|
|	Purpose:

		Test whether OmniScape is active or not

|
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
	18-Jul-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdVehicleDataLoader
#define _H_CmdVehicleDataLoader
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "IActiveXML.h"

#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMutex.h"
#include "CFactoryVehicleData.h"


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
typedef class CmdVehicleDataLoader*		CmdVehicleDataLoaderPtr;
typedef class CmdVehicleDataLoader&		CmdVehicleDataLoaderRef;
typedef const class CmdVehicleDataLoader&	ConstCmdVehicleDataLoaderRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdVehicleDataLoader : public VPluginCommand,
						implements_ IActiveXMLClient
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdVehicleDataLoader);

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IActiveXMLClient
	virtual
	NResult	NotifyXMLAvailable
			(
			void
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------



//	protected functions  ------------------------------------------------




	bool	CmdLoadData
			(
			ConstCVariantDataRef	rData
			);

	bool	CmdLoadInit
			(
			ConstCVariantDataRef	rData
			);


//	protected data  -----------------------------------------------------


	VDictionary::Selector	m_nCmdLoadData;
	VDictionary::Selector	m_nCmdLoadInit;
	CFactoryVehicleDataPtr	m_pFactory;

	CCharString				m_sServiceName;
	IActiveXMLPtr			m_pIActiveXML;
	index_t					m_nSequence;
	long					m_nLastNotify;






private:
//	private functions  --------------------------------------------------

	typedef	VPluginCommand	inherited;

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
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);


	//	ICommandPlugin
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VCommandSetupPtr		pCommandSetup
			);

	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector	selCommand,
			ConstCVariantDataRef	vData
			);

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



#endif /* _H_CmdVehicleDataLoader */
