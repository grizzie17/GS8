/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2009 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CFactoryScreenTester.cpp  --  FILE RETIRED
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	15-Sep-2009			J.Griswold		(Reviewed by: xxxx)
		THIS FILE IS RETIRED
	19-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/


#if 0	// FILE RETIRED



/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CFactoryScreenTester.h"
//#include "CFactoryPanelTester.h"
#include "CFactoryPanel.h"
#include "CGauge.h"
#include "CEqVariable.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
#ifdef _DEBUG 
#undef THIS_FILE 
static char THIS_FILE[] = __FILE__; 
#endif 


NAMESPACE_GADGET_BEGIN

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
/**--------------------------------------------------------------------+\

 * <summary>CFactoryScreenTester - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  19-Jul-2009

\+---------------------------------------------------------------------*/
CFactoryScreenTester::CFactoryScreenTester
		(
		void
		)
		: m_pFactoryPanel( 0 )
{
	FactoryPanel();
}


/**--------------------------------------------------------------------+\

 * <summary>~CFactoryScreenTester - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  19-Jul-2009

\+---------------------------------------------------------------------*/
CFactoryScreenTester::~CFactoryScreenTester
		(
		void
		)
{
	if ( m_pFactoryPanel )
		delete m_pFactoryPanel;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


CScreenPtr
		CFactoryScreenTester::Make
		(
		char *sName
		)
{
	CScreenPtr	pScreen = new CScreen;

	CEquationVariablePtr	pVarPanel = new CEquationVariable;
	pVarPanel->SetVariableName( "T:PANEL" );
	pScreen->SetActivePanelEquation( pVarPanel );

	CPanelPtr	pPanel = m_pFactoryPanel->Make( "panels/test" );
	pScreen->AddPanel( pPanel, "test" );

	return pScreen;
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

VFactoryPanelPtr
		CFactoryScreenTester::FactoryPanel
		(
		void
		)
{
	if ( ! m_pFactoryPanel )
		m_pFactoryPanel = new CFactoryPanel;
		//m_pFactoryPanel = new CFactoryPanelTester;
	return m_pFactoryPanel;
}


/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


NAMESPACE_GADGET_END



#endif	// FILE RETIRED


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  19-Jul-2009

\+---------------------------------------------------------------------*/

