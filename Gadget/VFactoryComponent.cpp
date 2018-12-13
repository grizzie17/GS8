/*---------------------------------------------------------------------+\
|
|	VFactoryComponent.cpp  --  brief description of what VFactoryComponent.cpp is for
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the pseudo-interface VVariable
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Take advantage of the more descriptive errors returned
		by the equation factory.
	02-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		upgraded the 'Update' node to V2 schema
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for passing the dictionary down to the Equation
		Factory so it can use it to validate the scripts.
	22-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Allow Frequency to be floating point
	16-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add some additional error handling/reporting
	25-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Use NodeValueAsFloatArray to process comma separated values
		in the Position function
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for update nodes that include frequency
	10-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add some XML error messages
	03-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "VFactoryComponent.h"

#include "UFloat.h"
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

 * VFactoryComponent - constructor

\+---------------------------------------------------------------------*/
VFactoryComponent::VFactoryComponent
		(
		void
		)
		: VFactoryLite()
		, m_pEqFactory( 0 )
		, m_bHasGVariables( false )
		, m_pKeyNames( 0 )
		, m_pPanelChild( 0 )
		, m_pDictionary( 0 )
		, m_1000( 1000.0f )
{
}


/*---------------------------------------------------------------------+\

 * ~VFactoryComponent - destructor

\+---------------------------------------------------------------------*/
VFactoryComponent::~VFactoryComponent
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetDictionary -

\+---------------------------------------------------------------------*/
void	VFactoryComponent::SetDictionary
		(
		VDictionaryPtr	pDict
		)
{
	m_pDictionary = pDict;
	if ( m_pDictionary )
		m_pVariable = m_pDictionary->GetVariableIF();
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * MakeEquation -

\+---------------------------------------------------------------------*/
VEquationPtr
		VFactoryComponent::MakeEquation
		(
		CFactoryEquation::FEquationTargets	eTarget,
		ConstCCharDescriptorRef				rString
		)
{
	if ( 0 < rString.Length() )
		return MakeEquation( eTarget, rString.Pointer(), rString.Length() );
	else
		return 0;
}

/*---------------------------------------------------------------------+\

 * MakeEquation -

\+---------------------------------------------------------------------*/
VEquationPtr
		VFactoryComponent::MakeEquation
		(
		CFactoryEquation::FEquationTargets	eTarget,
		const char*							s,
		size_t								n
		)
{
	VEquationPtr	pEq = 0;

	if ( ! m_pEqFactory )
	{
		m_pEqFactory = new CFactoryEquation;
		m_pEqFactory->SetDictionary( m_pDictionary );
	}

	if ( m_pEqFactory )
	{
		m_pEqFactory->SetGauge( m_pPanelChild );

		pEq = m_pEqFactory->MakeEquation( eTarget, s, long(n) );
		if ( pEq )
			m_bHasGVariables = m_pEqFactory->HasGVariables()  ||  m_bHasGVariables;
	}

	return pEq;
}

/*---------------------------------------------------------------------+\

 * ConstantEquation -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::ConstantEquation
		(
		void
		)
{
	if ( m_pEqFactory )
		return m_pEqFactory->IsConstant();
	else
		return false;
}


/*---------------------------------------------------------------------+\

 * EquationErrorString -

\+---------------------------------------------------------------------*/
char*	VFactoryComponent::EquationErrorString
		(
		void
		)
{
	if ( m_pEqFactory )
		return m_pEqFactory->GetError();
	else
		return 0;
}


/*---------------------------------------------------------------------+\

 * SetEquationPanelChild -

\+---------------------------------------------------------------------*/
void	VFactoryComponent::SetEquationPanelChild
		(
		VPanelChildPtr p
		)
{
	m_pPanelChild = p;
}


/*---------------------------------------------------------------------+\

 * ActionMap -

\+---------------------------------------------------------------------*/
CActionPtr
		VFactoryComponent::ActionMap
		(
		XMLIteratorPtr	pIt
		)
{
	CActionPtr	pNode = 0;		// change this to be the type of the node that we are processing

	pNode = new CAction;
	if ( pNode )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		while ( it.NextChild() )
		{
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				tName = it.NodeName();
				if ( tName == "Trigger" )
				{
					CTriggerPtr	pTrigger = Trigger( &it );
					if ( pTrigger )
					{
						if ( pNode )
							pNode->AddTrigger( pTrigger );
					}
					else
					{
						delete pNode;
						pNode = 0;
					}
				}
				break;
            default:
                break;
			}
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * Trigger -

\+---------------------------------------------------------------------*/
CTriggerPtr
		VFactoryComponent::Trigger
		(
		XMLIteratorPtr	pIt
		)
{
	CTriggerPtr	pNode = new CTrigger;
	if ( pNode )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;
		CCharDescriptor	tValue;

		while ( it.NextChild() )
		{
			if ( pNode )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:
					if ( tName == "KeyEvent"  ||  tName == "Event" )
					{
						tValue = it.NodeValue();
						if ( 0 < tValue.Length() )
						{
							pNode->SetName( tValue );
						}
					}
					else if ( tName == "Script" )
					{
						VEquationPtr pEq = Script( &it );
						if ( pEq )
							pNode->SetEquation( pEq );
					}
					else if ( tName == "Comment" )
					{
						EatNode();
					}
					else
					{
						it.Error( "Unrecognized tag in Trigger node" );
						if ( pNode )
							delete pNode;
						pNode = 0;
					}
					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					break;
                default:
                    break;
				}
			}
		}
	}

	return pNode;
}



/*---------------------------------------------------------------------+\

 * ScriptContainer -

\+---------------------------------------------------------------------*/
VEquationPtr
		VFactoryComponent::ScriptContainer
		(
		XMLIteratorPtr pIt
		)
{
	VEquationPtr	pNode = 0;
	CCharDescriptor	tName;
	CCharDescriptor	tValue;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "Script" )
			{
				pNode = Script( &it );
			}
			break;
        default:
            break;
		}
	}
	return pNode;
}



/*---------------------------------------------------------------------+\

 * Script -

 * We assume that the current node is aleady "Script"

\+---------------------------------------------------------------------*/
VEquationPtr
		VFactoryComponent::Script
		(
		XMLIteratorPtr	pIt
		)
{
	VEquationPtr	pNode = 0;
	CCharDescriptor	tValue;

	tValue = pIt->NodeValue();

	if ( 0 < tValue.Length() )
	{
		pNode = MakeEquation( CFactoryEquation::E_UNDEFINED, tValue );
		if ( ! pNode )
			pIt->Error( EquationErrorString() );
	}


	return pNode;
}


/*---------------------------------------------------------------------+\

 * KeyName -

\+---------------------------------------------------------------------*/
int		VFactoryComponent::KeyName
		(
		ConstCCharDescriptorRef	rName
		)
{
	if ( ! m_pKeyNames )
		m_pKeyNames = new CKeyNames;
	return m_pKeyNames->GetKey( rName );
}







/*---------------------------------------------------------------------+\

 * KeyEventMap -

\+---------------------------------------------------------------------*/
CKeyEventMapPtr
		VFactoryComponent::KeyEventMap
		(
		XMLIteratorPtr	pIt
		)
{
	CKeyEventMapPtr	pNode = new CKeyEventMap;

	if ( pNode )
	{
		CCharDescriptor	tName;
		XMLIterator		it( pIt );

		while ( it.NextChild() )
		{
			switch( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				tName = it.NodeName();
				if ( tName == "OnDown" )
				{
					OnKeyEvent( "OnDown", pNode->DownArray(), &it );
				}
				else if ( tName == "OnRepeat" )
				{
					OnKeyEvent( "OnRepeat", pNode->RepeatArray(), &it );
				}
				else if ( tName == "OnUp" )
				{
					OnKeyEvent( "OnUp", pNode->UpArray(), &it );
				}
				else
				{
					it.Error( "Unrecognized tag for KeyEventMap node" );
				}
				break;
            default:
                break;
			}
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * OnKeyEvent -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::OnKeyEvent
		(
		const char*	,	//sTag
		CKeyEventMap::KeyEventArray*	pEventArray,
		XMLIteratorPtr	pIt
		)
{
	bool	bNode = true;

	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "Key" )
				bNode = OnKey( pEventArray, &it );
			break;
        default:
            break;
		}
	}

	return bNode;
}





/*---------------------------------------------------------------------+\

 * OnKey -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::OnKey
		(
		CKeyEventMap::KeyEventArray*	pEventArray,
		XMLIteratorPtr	pIt
		)
{
	bool	pNode = false;

	if ( 0 < pIt->AttributeCount() )
	{
		CCharDescriptor	tName;
		CCharDescriptor	tValue;

		tName = pIt->AttributeValue( "id" );
		if ( 0 < tName.Length() )
		{
			int	nKey = KeyName( tName );
			if ( nKey )
			{
				tValue = pIt->AttributeValue( "Event" );
				if ( 0 < tValue.Length() )
				{
					CKeyEventMap::KEYEVENT	e;
					e.key = static_cast<unsigned char>(nKey);
					e.modifiers = 0;
					e.selector.SetName( tValue );

					pEventArray->AppendData( &e );
					pNode = true;
				}
			}
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * Update -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::Update
		(
		VControlPtr		pControl,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = true;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Script" )
			{
				VEquationPtr pEq = Script( &it );
				if ( pEq )
					pControl->SetUpdate( pEq );
			}
			else if ( tName == "Frequency" )
			{
				int		n;
				GFLOAT	f = it.NodeValueAsFloat();
				if ( GFLOAT_1_10 < f )
					n = static_cast<int>( m_1000 / f );
				else
					n = 0;
				pControl->SetUpdateFrequency( n );
			}
			else if ( tName == "Comment" )
			{
				EatNode();
			}
			else
			{
				it.Error( "Unrecognized tag within Update node" );
				bResult = false;
			}
			break;
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "Comment" )
			{
				EatNode();
			}
			else if ( tName == "Update" )
			{
				EatNode();
			}
			else
			{
				it.Error( "Unrecongized tag within Update node" );
			}
			break;

        default:
            break;

		}
	}
	return bResult;
}






/*---------------------------------------------------------------------+\

 * LoadNumberEquation -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::LoadNumberEquation
		(
		CResultValuePtr	pRValue,
		const char*		sAttr,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( sAttr );
	if ( 0 < tValue.Length() )
	{
		VEquationPtr	pEq;
		pEq = MakeEquation( CFactoryEquation::E_COORDINATE, tValue );
		if ( pEq )
		{
			if ( ConstantEquation() )
			{
				GFLOAT f = pEq->GetValue( 0 );
				pRValue->SetValue( f );
				delete pEq;
				bResult = true;
			}
			else
			{
				pRValue->SetEquation( pEq );
				bResult = true;
			}
		}
		else
		{
			pIt->Error( EquationErrorString() );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * LoadNumberEquation -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::GetAttributeEquation
		(
		VEquationPtr*	hEq,
		const char*		sAttr,
		XMLIteratorPtr	pIt
		)
{
	*hEq = 0;
	bool			bResult = false;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( sAttr );
	if ( 0 < tValue.Length() )
	{
		VEquationPtr	pEq;
		pEq = MakeEquation( CFactoryEquation::E_COORDINATE, tValue );
		if ( pEq )
		{
			*hEq = pEq;
		}
		else
		{
			pIt->Error( EquationErrorString() );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * LoadXY -

\+---------------------------------------------------------------------*/
bool	VFactoryComponent::LoadXY
		(
		VCoordinatePtr	pNode,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = true;

	if ( pNode )
	{
		bResult = LoadNumberEquation( pNode->X(), "X", pIt );
		if ( bResult )
			bResult = LoadNumberEquation( pNode->Y(), "Y", pIt );
		//if ( ! bResult )
		//	LogPrint( "%s - problem parsing attributes X, Y - %d: %s\n",
		//			__FUNCTION__, pIt->Tokenizer()->ErrorLineNumber(),
		//			pIt->Tokenizer()->ErrorString().Pointer() );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Position -

\+---------------------------------------------------------------------*/
CPositionPtr
		VFactoryComponent::Position
		(
		XMLIteratorPtr	pIt
		)
{
	CPositionPtr	pNode = 0;

	if ( pIt->NodeEmpty() )
	{
		if ( 0 < pIt->AttributeCount() )
		{
			pNode = new CPosition;
			if ( pNode )
			{
				if ( ! LoadXY( pNode, pIt ) )
				{
					pIt->Error( "Problem with Position Attributes" );
					delete pNode;
					pNode = 0;
				}
			}
		}
	}
	else
	{
		long	nCount;
		GFLOAT	fList[2];

		nCount = pIt->NodeValueAsFloatArray( fList, 2 );
		if ( 2 == nCount )
		{
			pNode = new CPosition;
			if ( pNode )
				pNode->SetValues( fList[0], fList[1] );
		}
		else
		{
			pIt->Error( "Problem with Position Parameters" );
		}
	}

	return pNode;
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
