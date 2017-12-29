/*---------------------------------------------------------------------+\
|
|	CFactoryPanel.cpp  --  Make a panel object from XML
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
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Allow the panel to specify the width and height of gauge.
	23-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Implement a "Layout" script capability that allows the
		use of registers and shared data during layout.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for passing the dictionary down to the Equation
		Factory so it can use it to validate the scripts.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Support gauge equation operators 'height' & 'width'
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite Parser
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
/*---------------------------------------------------------------------+\

 * CFactoryPanel - constructor

\+---------------------------------------------------------------------*/
CFactoryPanel::CFactoryPanel
		(
		void
		)
		: VFactoryPanel(),
		m_pGauge( 0 ),
		m_pGgFactory( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CFactoryPanel - destructor

\+---------------------------------------------------------------------*/
CFactoryPanel::~CFactoryPanel
		(
		void
		)
{
	if ( m_pGgFactory )
		delete m_pGgFactory;
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CPanelPtr
		CFactoryPanel::Make
		(
		const char*	sName
		)
{
	CPanelPtr	pNode = 0;

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
				if ( tName == "Panel" )
					pNode = Panel( &it );
				break;
            default:
                break;
			}
		}
		if ( 0 < ErrorLineNumber() )
		{
			LogPrint( "CFactoryPanel: Problem making Panel %s - %s %d: %s\n",
				sName, ErrorStreamName().Pointer(), ErrorLineNumber(), ErrorString().Pointer() );
			if ( pNode )
			{
				delete pNode;
				pNode = 0;
			}
		}
	}

	return pNode;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * MakeGauge -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

CGaugePtr
		CFactoryPanel::MakeGauge
		(
		CCharDescriptorRef	rName
		)
{
	CGaugePtr	pG = 0;
	if ( ! m_pGgFactory )
	{
		m_pGgFactory = new CFactoryGauge;
		m_pGgFactory->SetDictionary( m_pDictionary );
		m_pGgFactory->SetRelativePath( "gauges" );
		m_pGgFactory->SetVariableIF( m_pVariable );
		m_pGgFactory->SetExternalXMLIF( this->m_pIExternalXML );
	}

	CCharString	sName = rName;

	pG = m_pGgFactory->Make( sName.Pointer() );
	return pG;
}

//END_OVERRUN_WARNING






/*---------------------------------------------------------------------+\

 * Panel - process Panel node

\+---------------------------------------------------------------------*/
CPanelPtr
		CFactoryPanel::Panel
		(
		XMLIteratorPtr	pIt
		)
{
	CPanelPtr		pNode = new CPanel;
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( "id" );
	if ( 0 < tValue.Length() )
		*(pNode->Name()) = tValue;

	XMLIterator	it( pIt );


	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "GaugeInstance" )
			{
				CGaugePtr pGauge = GaugeInstance( &it );
				if ( pGauge )
				{
					pNode->AddChild( pGauge );
					long n = pGauge->MouseAreas();
					if ( 0 < n )
						pNode->IncrementMouseAreas( n );
				}
			}
			else if ( tName == "Comment" )
			{
				// simply skip over this item
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
				VEquationPtr pEq = ScriptContainer( &it );
				if ( pEq )
					pNode->SetUpdate( pEq );
			}
			else if ( tName == "Layout" )
			{
				VEquationPtr pEq = ScriptContainer( &it );
				if ( pEq )
					pNode->SetLayoutScript( pEq );
			}
			else if ( tName == "Comment" )
			{
				EatNode();
			}
			break;
        default:
            break;
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * GaugeInstance -

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryPanel::GaugeInstance
		(
		XMLIteratorPtr pIt
		)
{
	CGaugePtr		pNode = 0;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( "Name" );
	if ( 0 < tValue.Length() )
	{
		pNode = MakeGauge( tValue );
	}
	else
	{
		tValue = pIt->AttributeValue( "id" );
		if ( 0 < tValue.Length() )
			pNode = MakeGauge( tValue );
	}
	if ( pNode )
	{
		SetEquationPanelChild( pNode );
		LoadNumberEquation( pNode->Size()->X(), "Width", pIt );
		LoadNumberEquation( pNode->Size()->Y(), "Height", pIt );

		LoadXY( pNode->Position(), pIt );
		SetEquationPanelChild( 0 );
	}


	return pNode;
}
















VFactoryGaugePtr
		CFactoryPanel::FactoryGauge
		(
		void
		)
{
	if ( ! m_pGgFactory )
		m_pGgFactory = new CFactoryGauge;
	return m_pGgFactory;
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

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

