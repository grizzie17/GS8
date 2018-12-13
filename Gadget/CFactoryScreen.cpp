/*---------------------------------------------------------------------+\
|
|	CFactoryScreen.cpp  --  Make a screen object
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
	11-Dec-2018			J.Griswold
		Migrate to correctly using namespaces.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for passing the dictionary down to the Equation
		Factory so it can use it to validate the scripts.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for 'Update' and 'KeyEventMap' nodes
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite parser
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CFactoryScreen.h"
#include "CFactoryPanel.h"
#include "LogFile.h"
#include "UPlatform.h"
#include "CCharString.h"
#include "CEqOpFormatString.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
using namespace Yogi::XMLLite;
namespace Yogi { namespace Gadget {
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

 * CFactoryScreen - constructor

\+---------------------------------------------------------------------*/
CFactoryScreen::CFactoryScreen
		(
		void
		)
		: VFactoryScreen()
		, m_pPnlFactory( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CFactoryScreen - destructor

\+---------------------------------------------------------------------*/
CFactoryScreen::~CFactoryScreen
		(
		void
		)
{
	if ( m_pPnlFactory )
		delete m_pPnlFactory;
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Make -

\+---------------------------------------------------------------------*/
CScreenPtr
		CFactoryScreen::Make
		(
		const char*	sName
		)
{
	CScreenPtr	pNode = 0;

	if ( OpenFile( sName ) )
	{
		XMLIterator		it( this );
		CCharDescriptor	tName;

		while ( it.NextChild() )
		{
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				tName = it.NodeName();
				if ( tName == "Screen" )
					pNode = Screen( &it );
				else
					it.Error( "Unrecognized root keyword in screen" );
				break;
            default:
                break;
			}
		}
	}

	return pNode;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * MakePanel -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

CPanelPtr
		CFactoryScreen::MakePanel
		(
		CCharDescriptorRef	rName
		)
{
	CPanelPtr	pP = 0;
	if ( ! m_pPnlFactory )
	{
		m_pPnlFactory = new CFactoryPanel;
		m_pPnlFactory->SetDictionary( m_pDictionary );
		m_pPnlFactory->SetRelativePath( "panels" );
		m_pPnlFactory->SetVariableIF( m_pVariable );
		m_pPnlFactory->SetExternalXMLIF( m_pIExternalXML );
	}

	CCharString	sName = rName;

	pP = m_pPnlFactory->Make( sName.Pointer() );
	if ( ! pP )
		LogPrint( "CFactoryScreen: Problem making Panel %s - %s\n",
				sName.Pointer(), m_pPnlFactory->ErrorString().Pointer() );
	return pP;
}

//END_OVERRUN_WARNING







/*---------------------------------------------------------------------+\

 * Screen - process Screen node

\+---------------------------------------------------------------------*/
CScreenPtr
		CFactoryScreen::Screen
		(
		XMLIteratorPtr	pIt
		)
{
	CScreenPtr	pNode = 0;

	m_bHasGVariables = false;

	pNode = new CScreen;

	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( "id" );
	if ( 0 < tValue.Length() )
		*(pNode->Name()) = tValue;

	VEquationPtr	pEq;
	tValue = pIt->AttributeValue( "Active" );
	if ( 0 < tValue.Length() )
	{
		pEq = MakeEquation( CFactoryEquation::E_STRING, tValue.Pointer(), tValue.Length() );
		if ( pEq )
			pNode->SetActivePanelEquation( pEq );
	}


	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "PanelInstance" )
			{
				CPanelPtr pPanel = PanelInstance( &it );
				if ( pPanel )
					pNode->AddPanel( pPanel, pPanel->Name()->Pointer() );
			}
			else if ( tName == "Comment" )
			{
			}
			else
			{
				it.Error( "Unrecognized token in Screen" );
			}
			break;
		case XMLLite::NODE_ELEMENT_BEGIN:
			tName = it.NodeName();
			if ( tName == "ActionMap"  ||  tName == "KeyMap" )
			{
				CActionPtr pAction = ActionMap( &it );
				if ( pAction )
					pNode->SetAction( pAction );
			}
			else if ( tName == "KeyEventMap" )
			{
				CKeyEventMapPtr pKeyEventMap = KeyEventMap( &it );
				if ( pKeyEventMap )
					pNode->SetKeyEventMap( pKeyEventMap );
			}
			else if ( tName == "Update" )
			{
				VEquationPtr pEq2 = ScriptContainer( &it );
				if ( pEq2 )
					pNode->SetUpdate( pEq2 );
			}
			else if ( tName == "Comment" )
			{
				EatNode();
			}
			else
			{
				it.Error( "Unrecognized token in Screen" );
			}
			break;
        default:
            break;
		}
	}


	return pNode;
}


/*---------------------------------------------------------------------+\

 * PanelInstance -

\+---------------------------------------------------------------------*/
CPanelPtr
		CFactoryScreen::PanelInstance
		(
		XMLIteratorPtr	pIt
		)
{
	CPanelPtr	pNode = 0;

	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( "Name" );
	if ( 0 < tValue.Length() )
	{
		pNode = MakePanel( tValue );
	}
	else
	{
		tValue = pIt->AttributeValue( "id" );
		if ( 0 < tValue.Length() )
			pNode = MakePanel( tValue );
	}


	return pNode;
}












/*---------------------------------------------------------------------+\

 * FactoryPanel -

\+---------------------------------------------------------------------*/
VFactoryPanelPtr
		CFactoryScreen::FactoryPanel
		(
		void
		)
{
	if ( ! m_pPnlFactory )
		m_pPnlFactory = new CFactoryPanel;
	return m_pPnlFactory;
}





/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
