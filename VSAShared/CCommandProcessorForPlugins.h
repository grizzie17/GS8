/*---------------------------------------------------------------------+\
|
|	CCommandProcessorForPlugins.h  --  Example command processor class
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
	12-Jul-2010			J.Griswold		(Reviewed by: P.Hogan)
		Add optional InitialState pointer for the RegisterCommand func.
	16-May-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCommandProcessorForPlugins
#define _H_CCommandProcessorForPlugins
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCommandProcessor.h"
#include "CApplicationGauge.h"
#include "VDictionary.h"
#include "TDictionaryIndexed.h"
#include "ICommandPlugin.h"
#include "CPluginLibrary.h"


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
typedef class CCommandProcessorForPlugins*			CCommandProcessorForPluginsPtr;
typedef class CCommandProcessorForPlugins&			CCommandProcessorForPluginsRef;
typedef const class CCommandProcessorForPlugins&	ConstCCommandProcessorForPluginsRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCommandProcessorForPlugins
					: public CCommandProcessor
					, implements_ VCommandSetup
{
//	class lifecycle  ----------------------------------------------------
public:
					CCommandProcessorForPlugins();
	virtual			~CCommandProcessorForPlugins();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::THashTable<VDictionary::Selector, ICommandPluginPtr>
							m_tCommands;
	Yogi::Common::IPluginLibraryPtr		m_pLibrary;
	VDictionaryPtr			m_pDictionary;
	VDictionaryPagePtr		m_pDictCommands;

	ICommandPluginPtr		m_pCommandPlugin;	// temporary pointer


private:
//	private types  ------------------------------------------------------

	typedef CCommandProcessor	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VFunctionProcessor
public:
	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector				sel,
			Yogi::Common::ConstCVariantDataRef	vData
			);

	//	CCommandProcessor
	virtual
	void	SetApplication
			(
			CApplicationGaugePtr p
			);

	virtual
	void	InitializeFunctions
			(
			void
			);

	virtual
	void    AddCommandPlugin
			(
			Yogi::Common::ISupportsPtr pSupports
			);

	//	VCommandSetup
	virtual
	VDictionary::Selector
			RegisterCommand
			(
			const char*						sCommandName,
			Yogi::Common::CVariantDataPtr	pInitialState = 0
			);

	virtual
	VDictionary::Selector
			RegisterCommand
			(
			Yogi::Core::ConstCCharDescriptorRef	rCommandName,
			Yogi::Common::CVariantDataPtr		pInitialState = 0
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


//template<>
//inline
//unsigned long
//		THashValueFromKey<Yogi::Gadget::VDictionary::Selector>
//		(
//		const VDictionary::Selector&	key
//		)
//{
//	long	nHash = key & 0x00FFFFFF;
//	return nHash;
//}
//





#endif /* _H_CCommandProcessorForPlugins */
