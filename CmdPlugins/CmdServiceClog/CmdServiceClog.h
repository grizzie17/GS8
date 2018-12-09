/*---------------------------------------------------------------------+\
|
|	CmdServiceClog.h  --  Header for CmdServiceClog Plugin
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
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdServiceClog
#define _H_CmdServiceClog
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "IVehicleDataSample.h"

#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMutex.h"


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
typedef class CmdServiceClog*		CmdServiceClogPtr;
typedef class CmdServiceClog&		CmdServiceClogRef;
typedef const class CmdServiceClog&	ConstCmdServiceClogRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdServiceClog : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdServiceClog);

public:
//	supported interfaces  -----------------------------------------------


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------



//	protected functions  ------------------------------------------------

	// registered commands
	bool		cmdStart( ConstCVariantDataRef r );
	bool		cmdStop( ConstCVariantDataRef r );
	bool		cmdToggle( ConstCVariantDataRef r );




//	protected data  -----------------------------------------------------



	VDictionary::Selector	m_nCmdStart;
	VDictionary::Selector	m_nCmdStop;
	VDictionary::Selector	m_nCmdToggle;
	VDictionary::Selector	m_nCmdToggleLegacy;

	CCharString				m_sServiceName;






private:
//	private functions  --------------------------------------------------

	typedef	VPluginCommand	inherited;

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

public:
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

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
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



#endif /* _H_CmdServiceClog */
