/*---------------------------------------------------------------------+\
|
|	CCommandProcessorWorkbench.cpp  --  Sample CommandProcessor
|
|	Purpose:
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
	26-Mar-2010			J.Griswold		(Reviewed by: M.Rose) [1]
		Add support for new ESA vehicle
	18-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Reworked to use base class as CCommandProcessor
	12-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Disable older edit camera commands.
		Fix a problem with the "View Layout" command that was
		preventing it from working correctly when the views
		had not changed (only the layout changed).
	10-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add "new" commands for editing cameras
		Also add "Blackout" command
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add commands for editing cameras
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for the new "Constants" dictionary page
	11-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add entries for the side-rear cameras
	25-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add command to toggle which VehicleData XML processor
		that we are going to use.
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add access to the Reload function on the application
	31-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Correct spelling of "Camera Right-Forward Color"
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CCommandProcessorWorkbench.h"


NAMESPACE_GADGET_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CCommandProcessorWorkbench - constructor

\+---------------------------------------------------------------------*/
CCommandProcessorWorkbench::CCommandProcessorWorkbench
		(
		void
		)
		: inherited()
{
}


/*---------------------------------------------------------------------+\

 * ~CCommandProcessorWorkbench - destructor

\+---------------------------------------------------------------------*/
CCommandProcessorWorkbench::~CCommandProcessorWorkbench
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/




void	CCommandProcessorWorkbench::InitializeFunctions
		(
		void
		)
{
	inherited::InitializeFunctions();

	VDictionaryPagePtr	pFunc = m_pApplication->DictPageCommands();
	if ( pFunc )
	{
		CVariantData	v;




		v = "";
		m_xViewLayout = v;
		m_xVideoFeed1 = v;
		m_xVideoFeed2 = v;
		m_xVideoFeed3 = v;
		m_xVideoFeed4 = v;
		m_bVideoDirty = true;





	}
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


bool	CCommandProcessorWorkbench::ProcessRequest
		(
		VDictionary::Selector sel,
		ConstCVariantDataRef vData
		)
{
	bool			bResult = true;
	CVariantData	v = vData;
		bResult = inherited::ProcessRequest( sel, vData );
	return bResult;

}


NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

