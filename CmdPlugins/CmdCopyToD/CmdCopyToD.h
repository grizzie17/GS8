/*---------------------------------------------------------------------+\
|
|	CmdCopyToD.h  --  brief description of what CmdCopyToD.h is for
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
	17-May-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdCopyToD
#define _H_CmdCopyToD
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"


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
typedef class CmdCopyToD*		CmdCopyToDPtr;
typedef class CmdCopyToD&		CmdCopyToDRef;
typedef const class CmdCopyToD&	ConstCmdCopyToDRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdCopyToD : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:
					CmdCopyToD();
					CmdCopyToD( Yogi::Common::ISupportsPtr pOwner );
					CmdCopyToD( const char* sName, Yogi::Common::ISupportsPtr pOwner );
protected:
	virtual			~CmdCopyToD();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::THashTable<Yogi::Core::CCharString, Yogi::Common::CVariantData>	m_aList;
	Yogi::Common::THashTable<VDictionary::Selector, long>	m_aCommands;


private:
//	private functions  --------------------------------------------------

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
			Yogi::Common::ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr		pLib
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
//		Yogi::Common::THashValueFromKey<Yogi::Gadget::VDictionary::Selector>
//		(
//		const Yogi::Gadget::VDictionary::Selector&	key
//		)
//{
//	long	nHash = key & 0x00FFFFFF;
//	return nHash;
//}





#endif /* _H_CmdCopyToD */
