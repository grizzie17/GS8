/*---------------------------------------------------------------------+\
|
|	CmdConstant.h  --  Header for CmdConstant Plugin - used to add constants to the dictionary.
|
|	Purpose:
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
	19-Jul-2010			J.Griswold		(Reviewed by: xxxx)
		Move m_aList to protected section
	12-Jul-2010			S.Snider		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdConstant
#define _H_CmdConstant
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "THash.h"

#include "UDeclGadget.h"


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
typedef class CmdConstant*       CmdConstantPtr;
typedef class CmdConstant&       CmdConstantRef;
typedef const class CmdConstant& ConstCmdConstantRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class GADGET_CLASS CmdConstant : public VPluginCommand
{
    //	class lifecycle  ----------------------------------------------------
public:
    COM_LIFECYCLE( CmdConstant );

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

    Yogi::Common::THashTable<Yogi::Core::CCharString,
            Yogi::Common::CVariantData>
            m_aList;

private:
    //	private types  ----------------------------------------------------

    typedef VPluginCommand inherited;

    //	private functions  --------------------------------------------------

    //	private data  -------------------------------------------------------

    //============================== Overrides ==============================
public:
    //	ICommandPlugin
    virtual bool
    Initialize(
            CApplicationGaugePtr pApplication, VCommandSetupPtr pCommandSetup );

    virtual bool
    ProcessRequest( VDictionary::Selector      selCommand,
            Yogi::Common::ConstCVariantDataRef vData );

    //	IPluginLoadConfiguration
    virtual bool
    Load( Yogi::Common::VPluginConfigurationPtr pConfig,
            Yogi::Common::VPluginLibraryPtr     pLib );
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

}}  // namespace Yogi::Gadget


#endif /* _H_CmdConstant */
