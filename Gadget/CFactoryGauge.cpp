/*---------------------------------------------------------------------+\
|
|	CFactoryGauge.cpp  --
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
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
		Also implement hover for mouse
	21-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Utilize the new ParseInt and ParseFloat functions
		that are available on the TCharDescriptor
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Take advantage of the more descriptive errors returned
		by the equation factory.
	01-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Major changes to support V2 schema
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix a problem where the "bad-gauge" was not being displayed
		if the gauge was nested.
	11-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that the special error gauges are identified
		as background context.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Major changes so that we correctly support Elements that
		deal with foreground/background context.  The biggest
		changes were related to propagating the information to the
		parent nodes.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for passing the dictionary down to the Equation
		Factory so it can use it to validate the scripts.
	10-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Catch possible unwanted tags
	16-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix handling of Minimum and Maximum attributes for Shift
		tag.  The way we had it before would force these attributes
		to be required.  They should be optional.
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the Choose/When/Otherwise construct
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Maximum and Minimum limits on the Shift
		object.
	05-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the Rectangle object
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Progress towards GaugeXML 2.0
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	15-Sep-2009			M.Rose			(Reviewed by: J.Griswold)
		Manipulate code to satisfy linux gcc 4.2.1 compiler
	10-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Reworked how we the GaugeNotFound routine the name of the file.
		The previous method did not work because the correct data was
		not available at that point.
		Add support for Update nodes that include frequency
	10-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Identify the file in the GaugeNotFound method
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite
	27-Aug-2009			J.Griswold
		Allow the "Case" of a "Select/Case" tag-set to have an expression
		instead of just an "ExpressionResult".
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

#include "CFactoryGauge.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "CCharString.h"
#include "IDraw.h"

#include "CEqOpFormatString.h"
#include "CEqOpStrCat.h"
#include "CEqConstant.h"
#include "CEqOpMax.h"
#include "CEqOpMin.h"

namespace Yogi { namespace Gadget {
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

 * CFactoryGauge - constructor

\+---------------------------------------------------------------------*/
CFactoryGauge::CFactoryGauge
		(
		void
		)
		: VFactoryGauge()
{
}


/*---------------------------------------------------------------------+\

 * ~CFactoryGauge - destructor

\+---------------------------------------------------------------------*/
CFactoryGauge::~CFactoryGauge
		(
		void
		)
{
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Make -

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryGauge::Make
		(
		const char*	sName,
		int			nNest	// = 0 for no nest
		)
{
	CGaugePtr	pNode = 0;

	m_nNest = nNest;

	if ( OpenFile( sName ) )
	{
		//LogPrint( "CFactoryGauge::Make - parsing gauge %s\n", sName );
		CCharDescriptor	tName;
		XMLIterator		it( this );

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Gauge" )
					pNode = Gauge( &it );
				else if ( tName == "SimBase.Document" )
					pNode = SimBase_Document( &it );
				else if ( tName == "SimGauge.Gauge" )
					pNode = SimGauge_Gauge( &it );
				else
					it.Error( "Unrecognized Root Tag" );
				break;
			case XMLLite::NODE_ELEMENT:
				it.Error( "Unrecognized Root Tag" );
				break;
            default:
				break;
			}
		}

		if ( ! pNode )
		{
			pNode = GaugeProblem( sName );
		}
		else
		{
			if ( 0 != NestDepth() )
				it.Error( "XML file is not well-formed" );

			if ( 0 < ErrorLineNumber() )
			{
				delete pNode;
				pNode = GaugeProblem( sName );
			}
		}
	}
	else
	{
		pNode = GaugeNotFound( sName );
	}

	if ( 0 < ErrorLineNumber() )
		LogPrint( "CFactoryGauge: Problem making Gauge: %s - %d: %s\n",
					sName, ErrorLineNumber(), ErrorString().Pointer() );

	SetEquationPanelChild( 0 );

	return pNode;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * AttributeRadius -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::AttributeRadius
		(
		CResultValuePtr	pRValue,
		XMLIteratorPtr	pIt
		)
{
	bool		bResult = false;

	bResult = LoadNumberEquation( pRValue, "Radius", pIt );

	return bResult;
}


/*---------------------------------------------------------------------+\

 * AttributeColor -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::AttributeColor
		(
		CResultValuePtr	pRValue,
		const char*		sAttr,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;
//	const char*		s;
	VEquationPtr	pEq = 0;
	CCharDescriptor	tValue;
	CVariantData	v;
	CColor			c;

	tValue = pIt->AttributeValue( sAttr );
	if ( 0 < tValue.Length() )
	{
		pEq = MakeEquation( CFactoryEquation::E_COLOR, tValue );
		if ( pEq )
		{
			if ( ConstantEquation() )
			{
				v = pEq->GetValue( 0 );
				if ( CVariantData::T_STRING == v.GetType() )
					c = CColor::ColorFromName( v.operator CCharDescriptorRef() );
				else
					c = v.GetValueColor();
				v = c;
				pRValue->SetValue( v );
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
			c = CColor::ColorFromName( tValue );
			if ( c.IsNonColor() )
				c = CColor::ErrorColor();
			v = c;
			pRValue->SetValue( v );
			bResult = true;
		}
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * LoadStyles -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::LoadStyles
		(
		VGraphicPtr		pNode,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = true;

	if ( pNode )
	{
		if ( ! AttributeColor( pNode->Style()->LineColor(), "LineColor", pIt ) )
			AttributeColor( pNode->Style()->LineColor(), "Color", pIt );
		AttributeColor( pNode->Style()->FillColor(), "FillColor", pIt );
		AttributeColor( pNode->Style()->HaloColor(), "HaloColor", pIt );
		LoadNumberEquation( pNode->Style()->LineWidth(), "LineWidth", pIt );

	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * NodeStyles -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::NodeStyles
		(
		VGraphicPtr		p,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;

	tName = pIt->NodeName();
	if ( tName == "LineColor"  ||  tName == "Color" )
		bResult = ResultValueFromNodeColorValue( p->Style()->LineColor(), pIt );
	else if ( tName == "LineColorScript"  ||  tName == "ColorScript" )
		bResult = ResultValueFromNodeColorScript( p->Style()->LineColor(), pIt );
	else if ( tName == "FillColor" )
		bResult = ResultValueFromNodeColorValue( p->Style()->FillColor(), pIt );
	else if ( tName == "FillColorScript" )
		bResult = ResultValueFromNodeColorScript( p->Style()->FillColor(), pIt );
	else if ( tName == "HaloColor" )
		bResult = ResultValueFromNodeColorValue( p->Style()->HaloColor(), pIt );
	else if ( tName == "HaloColorScript" )
		bResult = ResultValueFromNodeColorScript( p->Style()->HaloColor(), pIt );
	else if ( tName == "LineWidth" )
		bResult = ResultValueFromNodeValueFloat( p->Style()->LineWidth(), pIt );
	else if ( tName == "LineWidthScript" )
		bResult = ResultValueFromNodeValueScript( p->Style()->LineWidth(), pIt );
	return bResult;
}




/*---------------------------------------------------------------------+\

 * SimBase_Document -

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryGauge::SimBase_Document
		(
		XMLIteratorPtr pIt
		)
{
	CGaugePtr		pNode = 0;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "SimGauge.Gauge" )
				pNode = SimGauge_Gauge( &it );
			else if ( tName == "Descr" )
				EatNode();
			else if ( tName == "Comment" )
				EatNode();
			else
				it.Error( "Unrecognized SimBase.Document Tag" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Descr" )
				EatNode();
			else if ( tName == "Filename" )
				EatNode();
			else if ( tName == "Comment" )
				EatNode();
			else
				it.Error( "Unrecognized SimBase.Document Tag" );

			break;
        default:
			break;
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * SimGauge_Gauge - process SimGauge.Gauge node

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryGauge::SimGauge_Gauge
		(
		XMLIteratorPtr pIt
		)
{
	return Gauge( pIt );
}





/*---------------------------------------------------------------------+\

 * Gauge - process Gauge node

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryGauge::Gauge
		(
		XMLIteratorPtr pIt
		)
{
	CGaugePtr	pNode = new CGauge;
	if ( pNode )
	{
		SetEquationPanelChild( pNode );

		m_bHasGVariables = false;

		CCharDescriptor	tName;
		CCharDescriptor	tValue;
		TArray<CElementPtr>	aElements;

		XMLIterator		it( pIt );

		tName = it.AttributeValue( "id" );
		if ( 0 < tName.Length() )
		{
			*(pNode->Name()) = tName;
		}
		else
		{
			tName = it.AttributeValue( "Name" );
			if ( 0 < tName.Length() )
				*(pNode->Name()) = tName;
		}

		tValue = it.AttributeValue( "Crop" );
		if ( 0 < tValue.Length() )
		{
			char	c = tValue.AtIndex(0);
			if ( ::strchr("tTyY", c) )
				pNode->SetCropped( true );
		}

		// we ignore this for now
		tValue = it.AttributeValue( "ArtDirectory" );

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Element" )
				{
					CElementPtr pElement = Element( &it );
					if ( pElement )
					{
						pNode->AddRenderable( pElement );
						pElement->SetParent( pNode );
						pNode->IncludeContext( pElement->GetChildContext() );
						aElements.AppendData( &pElement );
					}
				}
				else if ( tName == "ActionMap"
					||	tName == "KeyMap" )
				{
					CActionPtr pAction = ActionMap( &it );
					if ( pAction )
						pNode->SetAction( pAction );
				}
				else if ( tName == "MouseArea" )
				{
					CMouseAreaPtr pMouseArea = MouseArea( &it );
					if ( pMouseArea )
					{
						pNode->MouseAreaList()->AddArea( pMouseArea );
						pNode->IncrementMouseAreas();
					}
				}
				else if ( tName == "Update" )
				{
					Update( pNode, &it );
				}
				else if ( tName == "Include" )
				{
					VOwnershipPtr pInc = IncludeFile( &it );
					if ( pInc )
					{
						pNode->AddRenderable( pInc );
						pInc->SetParent( pNode );
						pNode->IncludeContext( pInc->GetChildContext() );
					}
				}
				else if ( tName == "Comment" )
				{
					EatNode();
				}
				else
				{
					VGraphicPtr pGraphic = grpGraphic( &it );
					if ( pGraphic )
						pNode->AddRenderable( pGraphic );
					else
						it.Error( "Unrecognized Gauge Tag" );
				}
				break;

			case XMLLite::NODE_ELEMENT:
				if ( grpSize( pNode->Size(), &it ) )
				{
					break;
				}
				else if ( tName == "Size" )
				{
					CSizePtr pSize = Size( &it );
					if ( pSize )
					{
						long	w;
						long	h;

						w = long(pSize->GetX());
						h = long(pSize->GetY());

						pNode->SetSize( w, h );

						delete pSize;
					}
				}
				else if ( tName == "Descr" )
				{
					EatNode();
				}
				else if ( tName == "Filename" )
				{
					EatNode();
				}
				else if ( tName == "Comment" )
				{
					EatNode();	// eat node
				}
				else
				{
					it.Error( "Unrecognized Gauge Tag" );
				}
				break;
            default:
				break;
			}
		}

		if ( pNode )
		{
			if ( m_bHasGVariables )
				pNode->AllocateLocalData();

			// case of undefined fore/back context
			if ( 0 == m_nNest )
			{
				if ( 0 == pNode->GetChildContext() )
				{
					CElementPtr*	p = aElements.PointArray();
					CElementPtr*	pEnd = p + aElements.Length();
					while ( p < pEnd )
					{
						if ( p )
						{
							(*p)->SetContext( CElement::CTX_FOREGROUND );
						}
						++p;
					}
				}
			}
		}

	}

	SetEquationPanelChild( 0 );

	return pNode;
}



/*---------------------------------------------------------------------+\

 * IncludeFile -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

CGaugePtr
		CFactoryGauge::IncludeFile
		(
		XMLIteratorPtr pIt
		)
{
	CGaugePtr	pNode = 0;

	if ( 0 < pIt->AttributeCount() )
	{
		CCharDescriptor	tValue;

		tValue = pIt->AttributeValue( "File" );
		if ( 0 < tValue.Length() )
		{
			CCharString	sPath = tValue;

			CFactoryGauge	factory;
			factory.SetDictionary( m_pDictionary );
			factory.SetRelativePath( this->m_sRelativePath.Pointer() );
			factory.SetVariableIF( this->m_pVariable );
			factory.SetExternalXMLIF( this->m_pIExternalXML );
			pNode = factory.Make( sPath.Pointer(), m_nNest + 1 );

			if ( 0 < factory.ErrorLineNumber() )
				LogPrint( "CFactoryGauge::IncludeFile: %s - %d: %s\n",
						sPath.Pointer(), factory.ErrorLineNumber(), factory.ErrorString().Pointer() );
		}
	}

	if ( ! pNode )
	{
		pIt->Error( "Problem with Include Tag" );
	}

	return pNode;
}

//END_OVERRUN_WARNING





/*---------------------------------------------------------------------+\

 * GaugeNotFound -

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryGauge::GaugeNotFound
		(
		const char* sName
		)
{
	CGaugePtr		pNode = new CGauge;
	CColor			clr = CColor::ErrorColor();
	CVariantData	vclr = clr;

	pNode->SetSize( 50, 50 );

	CElementPtr	pElem = new CElement;
	pNode->AddRenderable( pElem );
	pElem->SetParent( pNode );

	pElem->SetContext( CElement::CTX_BACKGROUND );
	pNode->IncludeContext( VRDR_CALCULATE_BACKGROUND );

	if ( sName )
	{
		const char*	p = sName + ::strlen(sName);
		while ( sName <= p )
		{
			if ( '\\' == *p  ||  '/' == *p )
				break;
			--p;
		}
		//if ( sName < p )
		//{
		//	--p;
		//	while ( sName <= p )
		//	{
		//		if ( '\\' == *p  ||  '/' == *p )
		//			break;
		//		--p;
		//	}
		//	if ( p < sName )
		//		p = sName;
		//}
		if ( '\\' == *p  ||  '/' == *p )
			++p;
		size_t	n = ::strlen(p);
		CCharDescriptor	tName( p, n );

		CGaugeTextPtr	pText = new CGaugeText;
		if ( pText )
		{
			pText->SetFontHeight( 12.0f );
			pText->Style()->LineColor()->SetValue( CVariantData( clr ) );
			pText->Point()->SetValues( 25, 1 );
			pText->SetVertAlign( VDraw::V_TOP );
			pText->SetAlign( VDraw::A_CENTER );
			pElem->AddRenderable( pText );

			CGaugeStringPtr	pString = new CGaugeString;
			pString->SetValue( CVariantData( tName ) );
			pText->AddString( pString );
		}
	}

	CPolylinePtr pPoly = new CPolyline;
	pElem->AddRenderable( pPoly );
	pPoly->Style()->LineColor()->SetValue( vclr );
	pPoly->Style()->LineWidth()->SetValue( CVariantData( 2.0f ) );
	CPointValuePtr pPoint;
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 50 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 50 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );

	pPoly = new CPolyline;
	pPoly->Style()->LineColor()->SetValue( vclr );
	pPoly->Style()->LineWidth()->SetValue( CVariantData( 2.0f ) );
	pElem->AddRenderable( pPoly );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 15, 15 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 20, 10 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 30, 10 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 35, 15 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 35, 20 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 25, 30 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 25, 40 );
	pPoly->AddPoint( pPoint );




	return pNode;
}

/*---------------------------------------------------------------------+\

 * GaugeProblem -

\+---------------------------------------------------------------------*/
CGaugePtr
		CFactoryGauge::GaugeProblem
		(
		const char*	sName
		)
{
	CGaugePtr		pNode = new CGauge;
	CColor			clr = CColor::ErrorColor();
	CVariantData	vclr = clr;
	CCharDescriptor	tName;
	CGaugeTextPtr	pText;
	CGaugeStringPtr	pString;

	pNode->SetSize( 50, 50 );
	CElementPtr	pElem = new CElement;
	pNode->AddRenderable( pElem );
	pElem->SetParent( pNode );

	pElem->SetContext( CElement::CTX_BACKGROUND );
	pNode->IncludeContext( VRDR_CALCULATE_BACKGROUND );

	GFLOAT	nRow = 1;

	if ( sName )
	{
		const char*	p = sName + ::strlen(sName);
		while ( sName <= p )
		{
			if ( '\\' == *p  ||  '/' == *p )
				break;
			--p;
		}
		if ( '\\' == *p  ||  '/' == *p )
			++p;
		size_t	n = ::strlen(p);
		tName = CCharDescriptor( p, n );

		pText = new CGaugeText;
		if ( pText )
		{
			pText->SetFontHeight( 12.0f );
			pText->Style()->LineColor()->SetValue( CVariantData( clr ) );
			pText->Point()->SetValues( 25, nRow );
			nRow += 12;
			pText->SetVertAlign( VDraw::V_TOP );
			pText->SetAlign( VDraw::A_CENTER );
			pElem->AddRenderable( pText );

			pString = new CGaugeString;
			pString->SetValue( CVariantData( tName ) );
			pText->AddString( pString );
		}
	}

	index_t	nErrLine = ErrorLineNumber();
	if ( 0 < nErrLine )
	{
		pText = new CGaugeText;
		if ( pText )
		{
			pText->SetFontHeight( 12.0f );
			pText->Style()->LineColor()->SetValue( CVariantData( clr ) );
			pText->Point()->SetValues( 25, nRow );
			nRow += 12.0f;
			pText->SetVertAlign( VDraw::V_TOP );
			pText->SetAlign( VDraw::A_CENTER );
			pElem->AddRenderable( pText );

			tName = ErrorString();
			pString = new CGaugeString;
			pString->SetValue( CVariantData( tName ) );
			pText->AddString( pString );
		}

		pText = new CGaugeText;
		if ( pText )
		{
			CCharString	sLine;
			sLine.Format( "Line # %d", long(nErrLine) );
			pText->SetFontHeight( 12.0f );
			pText->Style()->LineColor()->SetValue( CVariantData( clr ) );
			pText->Point()->SetValues( 25, nRow );
			nRow += 12.0f;;
			pText->SetVertAlign( VDraw::V_TOP );
			pText->SetAlign( VDraw::A_CENTER );
			pElem->AddRenderable( pText );

			tName = ErrorString();
			pString = new CGaugeString;
			pString->SetValue( CVariantData( sLine ) );
			pText->AddString( pString );
		}

	}

	CPolylinePtr pPoly = new CPolyline;
	pElem->AddRenderable( pPoly );
	pPoly->Style()->LineColor()->SetValue( vclr );
	pPoly->Style()->LineWidth()->SetValue( CVariantData( 2.0f ) );
	CPointValuePtr pPoint;
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 50 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 50 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );

	pPoly = new CPolyline;
	pPoly->Style()->LineColor()->SetValue( vclr );
	pPoly->Style()->LineWidth()->SetValue( CVariantData( 2.0f ) );
	pElem->AddRenderable( pPoly );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 50 );
	pPoly->AddPoint( pPoint );




	return pNode;
}


/*---------------------------------------------------------------------+\

 * Element -

\+---------------------------------------------------------------------*/
CElementPtr
		CFactoryGauge::Element
		(
		XMLIteratorPtr		pIt
		)
{
	CElementPtr	pNode = new CElement;
	if ( pNode )
	{
		XMLIterator			it( pIt );
		CCharDescriptor		tName;
		CCharDescriptor		tValue;
		VOwnershipPtr		pOData;
		VRenderablePtr		pData;
		CVisiblePtr			pVis;
		int					mRdr = 0;
		ControlObjects		control;

		CElement::EContext	eCtx = CElement::CTX_GROUP;
		tValue = pIt->AttributeValue( "Context" );
		if ( 0 < tValue.Length() )
		{
			tValue.ConvertLowercase();
			if ( tValue == "group" )
			{
				eCtx = CElement::CTX_GROUP;
			}
			else if ( tValue == "foreground" )
			{
				eCtx = CElement::CTX_FOREGROUND;
				mRdr = VRDR_CALCULATE_FOREGROUND;
			}
			else if ( tValue == "background" )
			{
				eCtx = CElement::CTX_BACKGROUND;
				mRdr = VRDR_CALCULATE_BACKGROUND;
			}
			else if ( tValue == "application" )
			{
				eCtx = CElement::CTX_APPLICATION;
				mRdr = VRDR_CALCULATE_APPLICATION;
			}
		}
		pNode->SetContext( eCtx );
		pNode->IncludeContext( mRdr );


		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				pOData = grpElementContent( &it );
				if ( pOData )
				{
					pNode->AddRenderable( pOData );
					pOData->SetParent( pNode );
					pNode->IncludeContext( pOData->GetChildContext() );
				}
				else
				{
					pData = grpElementControl( &control, &it );
					if ( pData )
					{
						if ( NOUPDATE != pData )
							pNode->AddRenderable( pData );
					}
					else
					{
						it.Error( "Unexpected node in Element tag" );
					}
				}
				break;
			case XMLLite::NODE_ELEMENT:
				pOData = grpElementContent( &it );
				if ( pOData )
				{
					pNode->AddRenderable( pOData );
					pOData->SetParent( pNode );
					pNode->IncludeContext( pOData->GetChildContext() );
				}
				else if ( tName == "Visible"
						||	tName == "Visibility" )
				{
					pVis = Visible( &it );
					if ( pVis )
						pNode->SetVisible( pVis );
				}
				else
				{
					pData = grpElementControl( &control, &it );
					if ( pData )
					{
						if ( NOUPDATE != pData )
							pNode->AddRenderable( pData );
					}
					else
					{
						it.Error( "Unexpected node in Element tag" );
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

 * ForLoop - Acts similar to Element

\+---------------------------------------------------------------------*/
CForLoopPtr
		CFactoryGauge::ForLoop
		(
		XMLIteratorPtr pIt
		)
{
	CForLoopPtr	pNode = new CForLoop;
	if ( pNode )
	{
		VRenderablePtr	pData;
		VOwnershipPtr	pOData;
		VEquationPtr	pEq;
		CCharDescriptor	tName;
		ControlObjects	control;

		XMLIterator		it( pIt );

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "InitialExpression" )
				{
					pEq = ScriptContainer( &it );
					if ( pEq )
						pNode->SetInitEquation( pEq );
				}
				else if ( tName == "TestExpression"
						||	tName == "Expression" )
				{
					pEq = ScriptContainer( &it );
					if ( pEq )
						pNode->SetTestEquation( pEq );
				}
				else if ( tName == "IncrementExpression" )
				{
					pEq = ScriptContainer( &it );
					if ( pEq )
						pNode->SetIncrEquation( pEq );
				}
				else
				{
					pOData = grpElementContent( &it );
					if ( pOData )
					{
						pNode->AddRenderable( pOData );
						pOData->SetParent( pNode );
						pNode->IncludeContext( pOData->GetChildContext() );
					}
					else
					{
						pData = grpElementControl( &control, &it );
						if ( pData )
						{
							if ( NOUPDATE != pData )
								pNode->AddRenderable( pData );
						}
						else
						{
							it.Error( "Unrecognized tag in ForLoop" );
						}
					}
				}
				break;
			case XMLLite::NODE_ELEMENT:
				pOData = grpElementContent( &it );
				if ( pOData )
				{
					pNode->AddRenderable( pOData );
					pOData->SetParent( pNode );
					pNode->IncludeContext( pOData->GetChildContext() );
				}
				else
				{
					pData = grpElementControl( &control, &it );
					if ( pData )
					{
						if ( NOUPDATE != pData )
							pNode->AddRenderable( pData );
					}
					else
					{
						it.Error( "Unrecognized tag in ForLoop" );
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

 * Choose -

\+---------------------------------------------------------------------*/
CChoosePtr
		CFactoryGauge::Choose
		(
		XMLIteratorPtr pIt
		)
{
	CChoosePtr	pNode = new CChoose;

	if ( pNode )
	{
		CCharDescriptor	tName;
		XMLIterator		it( pIt );

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "When" )
				{
					CChooseWhenPtr pWhen = ChooseWhen( &it );
					if ( pWhen )
					{
						pNode->AddWhen( pWhen );
						pWhen->SetParent( pNode );
						pNode->IncludeContext( pWhen->GetChildContext() );
					}
				}
				else if ( tName == "Otherwise" )
				{
					CChooseWhenPtr pWhen = ChooseWhen( &it );
					if ( pWhen )
					{
						pNode->SetOtherwise( pWhen );
						pWhen->SetParent( pNode );
						pNode->IncludeContext( pWhen->GetChildContext() );
					}
				}
				else if ( tName == "Comment" )
				{
					EatNode();
				}
				else
				{
					it.Error( "Unrecognized Tag in Select" );
				}
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Comment" )
				{
					;
				}
				else
				{
					it.Error( "Unrecognized Tag in Select" );
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

 * ChooseWhen -

\+---------------------------------------------------------------------*/
CChooseWhenPtr
		CFactoryGauge::ChooseWhen
		(
		XMLIteratorPtr pIt
		)
{
	CChooseWhenPtr	pNode = new CChooseWhen;
	if ( pNode )
	{
		CCharDescriptor	tName;
		VRenderablePtr	pData;
		VOwnershipPtr	pOData;
		XMLIterator		it( pIt );
		ControlObjects	control;

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Comment" )
				{
					;
				}
				else
				{
					pOData = grpElementContent( &it );
					if ( pOData )
					{
						pNode->AddRenderable( pOData );
						pOData->SetParent( pNode );
						pNode->IncludeContext( pOData->GetChildContext() );
					}
					else
					{
						pData = grpElementControl( &control, &it );
						if ( pData )
						{
							if ( NOUPDATE != pData )
								pNode->AddRenderable( pData );
						}
						else
						{
							it.Error( "Unrecognized tag in Choose/When" );
						}
					}
				}
				break;
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Expression" )
				{
					VEquationPtr pEq = Expression( &it );
					if ( pEq )
						pNode->SetEquation( pEq );
				}
				else if ( tName == "Comment" )
				{
					EatNode();
				}
				else
				{
					pOData = grpElementContent( &it );
					if ( pOData )
					{
						pNode->AddRenderable( pOData );
						pOData->SetParent( pNode );
						pNode->IncludeContext( pOData->GetChildContext() );
					}
					else
					{
						pData = grpElementControl( &control, &it );
						if ( pData )
						{
							if ( NOUPDATE != pData )
								pNode->AddRenderable( pData );
						}
						else
						{
							it.Error( "Unrecognized tag in Choose/When" );
						}
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

 * Select -

\+---------------------------------------------------------------------*/
CSelectPtr
		CFactoryGauge::Select
		(
		XMLIteratorPtr pIt
		)
{
	CSelectPtr	pNode = new CSelect;

	if ( pNode )
	{
		CCharDescriptor	tName;
		XMLIterator		it( pIt );

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Expression" )
				{
					VEquationPtr pEq = Expression( &it );
					if ( pEq )
						pNode->SetEquation( pEq );
				}
				else if ( tName == "Case" )
				{
					CSelectCasePtr pCase = SelectCase( &it );
					if ( pCase )
					{
						pNode->AddCase( pCase );
						pCase->SetParent( pNode );
						pNode->IncludeContext( pCase->GetChildContext() );
					}
				}
				else if ( tName == "CaseElse" )
				{
					CSelectCasePtr pCase = SelectCase( &it );
					if ( pCase )
					{
						pNode->SetCaseElse( pCase );
						pCase->SetParent( pNode );
						pNode->IncludeContext( pCase->GetChildContext() );
					}
				}
				else if ( tName == "Comment" )
				{
					EatNode();
				}
				else
				{
					it.Error( "Unrecognized Tag in Select" );
				}
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Comment" )
				{
					;
				}
				else
				{
					it.Error( "Unrecognized Tag in Select" );
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

 * SelectCase -

\+---------------------------------------------------------------------*/
CSelectCasePtr
		CFactoryGauge::SelectCase
		(
		XMLIteratorPtr pIt
		)
{
	CSelectCasePtr	pNode = new CSelectCase;
	if ( pNode )
	{
		CCharDescriptor	tName;
		VRenderablePtr	pData;
		VOwnershipPtr	pOData;
		XMLIterator		it( pIt );
		ControlObjects	control;

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				if ( tName == "ExpressionResult" )
				{
					CVariantData v = ExpressionResult( &it );
					pNode->SetValue( v );
				}
				else if ( tName == "Comment" )
				{
					;
				}
				else
				{
					pOData = grpElementContent( &it );
					if ( pOData )
					{
						pNode->AddRenderable( pOData );
						pOData->SetParent( pNode );
						pNode->IncludeContext( pOData->GetChildContext() );
					}
					else
					{
						pData = grpElementControl( &control, &it );
						if ( pData )
						{
							if ( NOUPDATE != pData )
								pNode->AddRenderable( pData );
						}
						else
						{
							it.Error( "Unrecognized tag in Select/Case" );
						}
					}
				}
				break;
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Expression" )
				{
					VEquationPtr pEq = ScriptContainer( &it );
					if ( pEq )
						pNode->SetEquation( pEq );
				}
				else if ( tName == "Comment" )
				{
					EatNode();
				}
				else
				{
					pOData = grpElementContent( &it );
					if ( pOData )
					{
						pNode->AddRenderable( pOData );
						pOData->SetParent( pNode );
						pNode->IncludeContext( pOData->GetChildContext() );
					}
					else
					{
						pData = grpElementControl( &control, &it );
						if ( pData )
						{
							if ( NOUPDATE != pData )
								pNode->AddRenderable( pData );
						}
						else
						{
							it.Error( "Unrecognized tag in Select/Case" );
						}
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

 * Rotation -

\+---------------------------------------------------------------------*/
CRotationPtr
		CFactoryGauge::Rotation
		(
		CRotationPtr	pInput,
		XMLIteratorPtr	pIt
		)
{
	CRotationPtr	pNode = 0;
	CCharDescriptor	tValue;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{

		tValue = pIt->NodeValue();
		if ( 0 < tValue.Length() )
		{
			VEquationPtr pEq = MakeEquation( CFactoryEquation::E_LENGTH, tValue );
			if ( pEq )
			{
				if ( pInput )
					pNode = pInput;
				else
					pNode = new CRotation;
				if ( pNode )
				{
					if ( ConstantEquation() )
					{
						GFLOAT	f = pEq->GetValue( 0 );
						pNode->SetValue( f );
						delete pEq;
					}
					else
					{
						pNode->SetEquation( pEq );
					}
				}
			}
			else
			{
				Error( EquationErrorString() );
			}
		}

	}
	else if ( XMLLite::NODE_ELEMENT_BEGIN == pIt->NodeType() )
	{
		if ( pInput )
			pNode = pInput;
		else
			pNode = new CRotation;
		if ( pNode )
		{
			XMLIterator		it( pIt );
			CCharDescriptor	tName;

			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Expression" )
					{
						VEquationPtr pEq = Expression( &it );
						if ( pEq )
						{
							if ( ConstantEquation() )
							{
								GFLOAT	f = pEq->GetValue( 0 );
								pNode->SetValue( f );
								delete pEq;
							}
							else
							{
								pNode->SetEquation( pEq );
							}
						}
					}
					else if ( tName == "Delay" )
					{
						;	// to be added
					}
					else if ( tName == "Comment" )
					{
						EatNode();
					}
					else
					{
						it.Error( "Unexpected tag in Rotation" );
					}
					break;
				case XMLLite::NODE_ELEMENT:
					if ( tName == "ExpressionResult" )
					{
					}
					else if ( tName == "DegreesPointsTo" )
					{
						;	// to be added
					}
					else if ( tName == "PointsTo" )
					{
						;	// to be added
					}
					else if ( tName == "Comment" )
					{
						EatNode();
					}
					else
					{
						it.Error( "Unexpected tag in Rotation" );
					}
					break;
                default:
					break;
				}
			}
		}
	}
	if ( pNode == pInput )
		pNode = (CRotationPtr)NOUPDATE;

	return pNode;
}

/*---------------------------------------------------------------------+\

 * Shift -

\+---------------------------------------------------------------------*/
CShiftPtr
		CFactoryGauge::Shift
		(
		CShiftPtr		pInput,
		XMLIteratorPtr	pIt
		)
{
	CShiftPtr		pNode = 0;
	CCharDescriptor	tValue;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( 0 < pIt->AttributeCount() )
		{
			if ( pInput )
				pNode = pInput;
			else
				pNode = new CShift;
			if ( pNode )
			{
				do	// sequence
				{
					CResultValue	tX;
					CResultValue	tY;
					VEquationPtr	pMin;
					VEquationPtr	pMax;

					if ( ! LoadNumberEquation( &tX, "X", pIt ) )
					{
						pIt->Error( "Problem with Shift X parameter" );
						break;
					}
					if ( ! LoadNumberEquation( &tY, "Y", pIt ) )
					{
						pIt->Error( "Problem with Shift Y parameter" );
						break;
					}

					GetAttributeEquation( &pMin, "Minimum", pIt );
					GetAttributeEquation( &pMax, "Maximum", pIt );

					VEquationPtr	pEqX = tX.GetEquation();
					VEquationPtr	pEqY = tY.GetEquation();
					VEquationPtr	pEq = 0;
					if ( pEqY )
					{
						*pNode->ScaleX() = GFLOAT_0;
						*pNode->ScaleY() = GFLOAT_1;
						pEq = pEqY->Clone();
					}
					else if ( pEqX )
					{
						*pNode->ScaleX() = GFLOAT_1;
						*pNode->ScaleY() = GFLOAT_0;
						pEq = pEqX->Clone();
					}


					VEquationOperatorBinaryPtr	pTemp;
					if ( pMin )
					{
						pTemp = new CEquationOperatorMax;
						if ( pTemp )
						{
							pTemp->SetLeft( pMin );
							pTemp->SetRight( pEq );
							pEq = pTemp;
						}
					}

					if ( pMax )
					{
						pTemp = new CEquationOperatorMin;
						if ( pTemp )
						{
							pTemp->SetLeft( pMax );
							pTemp->SetRight( pEq );
							pEq = pTemp;
						}
					}

					pNode->Expression()->SetEquation( pEq );

				} sequence;
			}
		}
	}
	else if ( XMLLite::NODE_ELEMENT_BEGIN == pIt->NodeType() )
	{
		if ( pInput )
			pNode = pInput;
		else
			pNode = new CShift;
		if ( pNode )
		{
			XMLIterator		it( pIt );
			CCharDescriptor	tName;

			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Expression" )
					{
						VEquationPtr	pEq = Expression( &it );
						if ( pEq )
						{
							pNode->Expression()->SetEquation( pEq );
						}
					}
					else if ( tName == "Scale" )
					{
						GFLOAT	aList[2] = {GFLOAT_0, GFLOAT_0};
						int		nCount;
						nCount = it.NodeValueAsFloatArray( aList, 2 );
						if ( 0 < nCount )
						{
							*pNode->ScaleX() = aList[0];
							*pNode->ScaleY() = aList[1];
						}

					}

					break;
				default:
					break;
				}
			}
		}
	}

	if ( pNode == pInput )
		pNode = (CShiftPtr)NOUPDATE;

	return pNode;
}



/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
CSizePtr
		CFactoryGauge::Size
		(
		XMLIteratorPtr pIt
		)
{
	CSizePtr		pNode = 0;
	//CCharDescriptor	tValue;

	if ( 0 < pIt->AttributeCount() )
	{
		float	x;
		float	y;

		x = pIt->AttributeValueAsFloat( "X" );
		y = pIt->AttributeValueAsFloat( "Y" );

		pNode = new CSize;
		if ( pNode )
			pNode->SetPointValue( x, y );
	}
	else
	{
		long		nCount;
		GFLOAT		fList[2];

		nCount = pIt->NodeValueAsFloatArray( fList, 2 );
		if ( 2 == nCount )
		{
			pNode = new CSize;
			if ( pNode )
				pNode->SetValues( fList[0], fList[1] );
		}
		else
		{
			pIt->Error( "Problem with Size Properties" );
		}
	}

	return pNode;
}




/*---------------------------------------------------------------------+\

 * Visible -

\+---------------------------------------------------------------------*/
CVisiblePtr
		CFactoryGauge::Visible
		(
		XMLIteratorPtr pIt
		)
{
	CVisiblePtr		pNode = 0;
	CCharDescriptor	tValue;

	tValue = pIt->NodeValue();
	if ( 0 < tValue.Length() )
	{
		VEquationPtr pEq = MakeEquation( CFactoryEquation::E_BOOLEAN, tValue );
		if ( pEq )
		{
			pNode = new CVisible;
			if ( pNode )
				pNode->SetEquation( pEq );
		}
		else
		{
			pIt->Error( EquationErrorString() );
		}
	}

	return pNode;
}



/*---------------------------------------------------------------------+\

 * Expression -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryGauge::Expression
		(
		XMLIteratorPtr pIt
		)
{
	VEquationPtr	pNode = 0;
	VEquationPtr	pMin = 0;
	VEquationPtr	pMax = 0;
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
			else if ( tName == "Minimum" )
			{
				pMin = Script( &it );
			}
			else if ( tName == "Maximum" )
			{
				pMax = Script( &it );
			}
			else if ( tName == "Comment" )
			{
				EatNode();
			}
			else
			{
				it.Error( "Unexpected tag in Expression" );
			}
			break;
        default:
            break;
		}
	}

	if ( pNode )
	{
		VEquationOperatorBinaryPtr	pTemp;
		if ( pMin )
		{
			pTemp = new CEquationOperatorMax;
			if ( pTemp )
			{
				pTemp->SetLeft( pMin );
				pTemp->SetRight( pNode );
				pNode = pTemp;
			}
		}

		if ( pMax )
		{
			pTemp = new CEquationOperatorMin;
			if ( pTemp )
			{
				pTemp->SetLeft( pMax );
				pTemp->SetRight( pNode );
				pNode = pTemp;
			}
		}
	}

	return pNode;
}




/*---------------------------------------------------------------------+\

 * ExpressionResult -

\+---------------------------------------------------------------------*/
CVariantData
		CFactoryGauge::ExpressionResult
		(
		XMLIteratorPtr pIt
		)
{
	CVariantData	pNode;
	CCharDescriptor	tValue;

	tValue = pIt->NodeValue();
	if ( 0 < tValue.Length() )
	{
		VEquationPtr pEq = MakeEquation( CFactoryEquation::E_UNDEFINED, tValue );
		if ( pEq )
		{
			if ( ConstantEquation() )
			{
				pNode = pEq->GetValue( 0 );
			}
			else
			{
				pIt->Error( "ExpressionResult must not contain script" );
			}
			delete pEq;
		}
		else
		{
			pIt->Error( "Bad Value in ExpressionResult" );
		}
	}

	return pNode;
}




/*---------------------------------------------------------------------+\

 * MouseArea -

\+---------------------------------------------------------------------*/
CMouseAreaPtr
		CFactoryGauge::MouseArea
		(
		XMLIteratorPtr pIt
		)
{
	CMouseAreaPtr	pNode = new CMouseArea;
	CCharDescriptor	tName;

	XMLIterator		it( pIt );

	GFLOAT			fLeft = 0;
	GFLOAT			fTop = 0;
	GFLOAT			fBottom = 0;
	GFLOAT			xSize = 0;
	GFLOAT			ySize = 0;

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "MouseClick"
				||	tName == "MouseDown" )
			{
				MouseClick( pNode, &it );
				pNode->SetClickType( CMouseLocate::M_DOWN );
			}
			else if ( tName == "MouseUp" )
			{
				MouseClick( pNode, &it );
				pNode->SetClickType( CMouseLocate::M_UP );
			}
			else if ( tName == "MouseMove" )
			{
				MouseClick( pNode, &it );
				pNode->SetClickType( CMouseLocate::M_MOVE );
			}
			else if ( tName == "MouseHover" )
			{
				MouseClick( pNode, &it );
				pNode->SetClickType( CMouseLocate::M_HOVER );
			}
			else
			{
				it.Error( "Unrecognized MouseArea Tag" );
			}
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "FloatPosition" )
			{
				CPositionPtr pPos = FloatPosition( 0, &it );
				if ( pPos )
				{
					fLeft = pPos->GetX();
					fTop = pPos->GetY();
					delete pPos;
				}
			}
			else if ( tName == "Position" )
			{
				CPositionPtr pPos = Position( &it );
				if ( pPos )
				{
					fLeft = pPos->GetX();
					fTop = pPos->GetY();
					delete pPos;
				}
			}
			else if ( tName == "Size" )
			{
				CSizePtr pSize = Size( &it );
				if ( pSize )
				{
					xSize = pSize->GetX();
					ySize = pSize->GetY();
					delete pSize;
				}
			}
			else if ( tName == "Visibility"
					||	tName == "Visible" )
			{
				CVisiblePtr pVis = Visible( &it );
				if ( pVis )
					pNode->SetVisibility( pVis );
			}
			else if ( tName == "CursorType" )
			{
				;
			}
			else
			{
				it.Error( "Unrecognized MouseArea Tag" );
			}
			break;
        default:
			break;
		}
	}
	if ( pNode )
	{
		pNode->SetArea( fLeft, fTop, fLeft+xSize, fBottom+ySize );
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * MouseClick -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::MouseClick
		(
		CMouseAreaPtr	pMouseArea,
		XMLIteratorPtr	pIt
		)
{
	bool			pNode = false;
	CCharDescriptor	tName;
	CCharDescriptor	tValue;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			break;

		case XMLLite::NODE_ELEMENT:
			if ( tName == "KeyEvent"
				||	tName == "Event" )
			{
				tValue = it.NodeValue();
				if ( 0 < tValue.Length() )
				{
					pMouseArea->SetEvent( tValue );
				}
			}
			else if ( tName == "Script" )
			{
				VEquationPtr pEq = Script( &it );
				if ( pEq )
					pMouseArea->SetEquation( pEq );
			}
			else
			{
				it.Error( "Unrecognized Tag in MouseClick" );
			}
			break;
        default:
			break;
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * Arc -

\+---------------------------------------------------------------------*/
CArcPtr
		CFactoryGauge::Arc
		(
		XMLIteratorPtr pIt
		)
{
	CArcPtr				pNode = 0;
	XMLLite::ENODETYPE	eType;

	eType = pIt->NodeType();
	if ( XMLLite::NODE_ELEMENT == eType )
	{
		do	// sequence
		{
			if ( pIt->AttributeCount() < 1 )
				break;

			pNode = new CArc;
			if ( ! pNode )
				break;

			if ( ! LoadXY( pNode->Axis(), pIt ) )
				break;

			if ( ! LoadStyles( pNode, pIt ) )
				break;

			if ( ! AttributeRadius( pNode->Radius(), pIt ) )
				break;

			if ( ! LoadNumberEquation( pNode->StartAngle(), "StartAngle", pIt ) )
				break;

			if ( ! LoadNumberEquation( pNode->EndAngle(), "EndAngle", pIt ) )
				break;

		} sequence;	// end sequence

	}
	else if ( XMLLite::NODE_ELEMENT_BEGIN == eType )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		pNode = new CArc;
		if ( pNode )
		{
			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpOrigin( pNode->Axis(), &it ) )
							break;

						if ( grpStartAngle( pNode->StartAngle(), &it ) )
							break;

						if ( grpEndAngle( pNode->EndAngle(), &it ) )
							break;

						if ( grpRadius( pNode->Radius(), &it ) )
							break;

						if ( grpLineStyle( pNode, &it ) )
							break;

						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( "Unrecongized tag in Arc" );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( "Unrecognized tag in Arc" );
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

 * Circle -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

CCirclePtr
		CFactoryGauge::Circle
		(
		XMLIteratorPtr pIt
		)
{
	CCirclePtr	pNode = 0;
	XMLLite::ENODETYPE	eType;
	const char	kErrorUnknownTag[] = "Unrecongized tag in Circle";

	eType = pIt->NodeType();
	if ( XMLLite::NODE_ELEMENT == eType )
	{
		do	// sequence
		{
			if ( pIt->AttributeCount() < 1 )
				break;

			pNode = new CCircle;
			if ( ! pNode )
				break;

			if ( ! LoadXY( pNode->Axis(), pIt ) )
				break;

			if ( ! LoadStyles( pNode, pIt ) )
				break;

			if ( ! AttributeRadius( pNode->Radius(), pIt ) )
				break;

		} sequence;	// end sequence

	}
	else if ( XMLLite::NODE_ELEMENT_BEGIN == eType )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		pNode = new CCircle;
		if ( pNode )
		{
			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpOrigin( pNode->Axis(), &it ) )
							break;

						if ( grpRadius( pNode->Radius(), &it ) )
							break;

						if ( grpFillStyle( pNode, &it ) )
							break;

						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( kErrorUnknownTag );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( kErrorUnknownTag );
					break;
                default:
                    break;
				}
			}
		}
	}

	return pNode;
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * GaugeStringFormat -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

VEquationPtr
		CFactoryGauge::GaugeStringFormat
		(
		const char*	s,
		long*		pnOutProcessed		// number of characters processed
		)
{
	VEquationPtr	pEq = 0;	// returned
	long			nOut = 0;	// argument return
	const char*		sBase = s;
	const char*		sEnd = s + ::strlen( s );

	do	// sequence
	{
		if ( '%' != *s )
			break;
		if ( '(' != *(s+1) )
			break;

		s += 2;
		const char*		sEqBegin = s;
		const char*		sEqEnd = 0;
		char			sData[256];
		VEquationPtr	pTempEq = 0;

		while ( s < sEnd )
		{
			if ( ')' == *s  &&  '%' == *(s+1) )
			{
				sEqEnd = s;
				s += 2;
				break;
			}
			++s;
		}
		if ( 0 == sEqEnd )
			break;

		pTempEq = MakeEquation( CFactoryEquation::E_UNDEFINED,
								sEqBegin, static_cast<size_t>(sEqEnd - sEqBegin) );
		if ( ! pTempEq )
			break;

		sEqEnd = 0;
		if ( '!' != *s )
		{
			delete pTempEq;
			break;
		}
		++s;
		sEqBegin = s;
		while ( s < sEnd )
		{
			if ( '!' == *s )
			{
				sEqEnd = s;
				++s;
				break;
			}
			++s;
		}
		if ( 0 == sEqEnd )
		{
			delete pTempEq;
			break;
		}

		if ( sEqEnd - sEqBegin < 1 )
		{
			delete pTempEq;
			break;
		}

		sData[0] = '%';
		::strncpy_s( sData+1, sizeof(sData)-1, sEqBegin, static_cast<rsize_t>(sEqEnd - sEqBegin) );
		*(sData+1 + (sEqEnd - sEqBegin)) = 0;

		CEquationOperatorFormatStringPtr pFormatEq = new CEquationOperatorFormatString;
		pFormatEq->SetFormat( sData );
		pFormatEq->SetOperand( pTempEq );
		pEq = pFormatEq;


		nOut = long(s - sBase);
	} sequence;	// end sequence

	*pnOutProcessed = nOut;
	return pEq;
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * GaugeStringParse -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryGauge::GaugeStringParse
		(
		CCharDescriptorRef	rString
		)
{
	VEquationPtr				pEq = 0;
	VEquationPtr				pFmt = 0;
	CEquationOperatorStrCatPtr	pCat = 0;
	CEquationConstantPtr		pConst = 0;
	CCharString		sConst;
	const char*		s = rString.Pointer();
	const char*		sEnd = s + rString.Length();
	const char*		sBase = s;
	const char*		sCBase = s;
	long			nCount;

	while ( s < sEnd )
	{
		if ( '%' == *s  &&  '(' == *(s+1) )
		{
			pFmt = GaugeStringFormat( s, &nCount );
			if ( pFmt )
			{
				if ( sCBase < s )
				{
					sConst = CCharString( sCBase, static_cast<size_t>(s - sCBase) );
					pConst = new CEquationConstant;
					pConst->SetValue( CVariantData( sConst ) );

					if ( pEq )
					{
						pCat = new CEquationOperatorStrCat;
						pCat->SetLeft( pEq );
						pCat->SetRight( pConst );
						pEq = pCat;
					}
					else
					{
						pEq = pConst;
					}
				}
				if ( pEq )
				{
					pCat = new CEquationOperatorStrCat;
					pCat->SetLeft( pEq );
					pCat->SetRight( pFmt );
					pEq = pCat;
				}
				else
				{
					pEq = pFmt;
				}
				s += nCount;
				sCBase = s;
			}
			else
			{
				++s;
			}
		}
		else
		{
			++s;
		}
	}
	if ( sBase < sCBase  &&  sCBase < s )
	{
		sConst = CCharString( sCBase, static_cast<size_t>(s - sCBase) );
		pConst = new CEquationConstant;
		pConst->SetValue( CVariantData( sConst ) );

		if ( pEq )
		{
			pCat = new CEquationOperatorStrCat;
			pCat->SetLeft( pEq );
			pCat->SetRight( pConst );
			pEq = pCat;
		}
		else
		{
			pEq = pConst;
		}
	}


	return pEq;
}

/*---------------------------------------------------------------------+\

 * GaugeString -

\+---------------------------------------------------------------------*/
CGaugeStringPtr
		CFactoryGauge::GaugeString
		(
		XMLIteratorPtr pIt
		)
{
	CGaugeStringPtr	pNode = new CGaugeString;

	if ( pNode )
	{
		CCharDescriptor	tValue;
		tValue = pIt->NodeValue();
		if ( 0 < tValue.Length() )
		{
			CVariantData v;
			VEquationPtr pEq = GaugeStringParse( tValue );
			if ( pEq )
			{
				if ( ConstantEquation() )
				{
					v = pEq->GetValue( 0 );
					pNode->SetValue( v );
					delete pEq;
				}
				else
				{
					pNode->SetEquation( pEq );
				}
			}
			else
			{
				v = tValue;
				pNode->SetValue( v );
			}
		}
	}

	return pNode;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CGaugeTextPtr
		CFactoryGauge::GaugeText
		(
		XMLIteratorPtr pIt
		)
{
	CGaugeTextPtr	pNode = new CGaugeText;
	if ( pNode )
	{
		CCharDescriptor	tName;
		CCharDescriptor	tValue;

		if ( 2 < pIt->AttributeCount() )
		{
			do	// sequence
			{
				if ( ! LoadStyles( pNode, pIt ) )
					break;

				if ( ! LoadXY( pNode->Point(), pIt ) )
					break;

				long nLength = pIt->AttributeValueAsInt( "Length" );
				pNode->SetMaxLength( nLength );

				tValue = pIt->AttributeValue( "Font" );
				if ( 0 < tValue.Length() )
					pNode->SetFontName( tValue );

				if ( ! LoadNumberEquation( pNode->FontHeight(), "Height", pIt ) )
					break;

			} sequence;	// end sequence

			VDraw::EAlignments			eAlign = VDraw::A_LEFT;
			VDraw::EVerticalAlignments	eVertAlign = VDraw::V_BASELINE;
			tValue = pIt->AttributeValue( "Align" );
			if ( 0 < tValue.Length() )
			{
				tValue.ConvertLowercase();
				if ( tValue == "left" )
					eAlign = VDraw::A_LEFT;
				else if ( tValue == "center" )
					eAlign = VDraw::A_CENTER;
				else if ( tValue == "right" )
					eAlign = VDraw::A_RIGHT;
				pNode->SetAlign( eAlign );
			}

			tValue = pIt->AttributeValue( "VerticalAlign" );
			if ( 0 < tValue.Length() )
			{
				tValue.ConvertLowercase();
				if ( tValue == "baseline" )
					eVertAlign = VDraw::V_BASELINE;
				else if ( tValue == "absbottom"
						||	tValue == "bottom" )
					eVertAlign = VDraw::V_ABSBOTTOM;
				else if ( tValue == "middle"
						||	tValue == "center" )
					eVertAlign = VDraw::V_MIDDLE;
				else if ( tValue == "top" )
					eVertAlign = VDraw::V_TOP;
				pNode->SetVertAlign( eVertAlign );
			}

			CGaugeStringPtr	pGString = 0;

			XMLIterator	it( pIt );
			while ( it.NextChild() )
			{
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:
					tName = it.NodeName();
					if ( tName == "String" )
					{
						pGString = GaugeString( &it );
						if ( pGString )
							pNode->AddString( pGString );
					}
					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					it.Error( "Malformed String" );
					break;
                default:
                    break;
				}
			}
		}
		else
		{
			XMLIterator		it( pIt );
			//CCharDescriptor	tName;

			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpOrigin( pNode->Point(), &it ) )
							break;

						if ( grpFontColor( pNode, &it ) )
							break;

						if ( grpBackgroundColor( pNode, &it ) )
							break;

						if ( grpFontHeight( pNode->FontHeight(), &it ) )
							break;


						if ( tName == "FontFace" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								pNode->SetFontName( tValue );
								break;
							}
						}


						if ( tName == "HorizontalAlign" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EAlignments	eAlign = VDraw::A_LEFT;
								tValue.ConvertLowercase();
								if ( tValue == "left" )
									eAlign = VDraw::A_LEFT;
								else if ( tValue == "center" )
									eAlign = VDraw::A_CENTER;
								else if ( tValue == "right" )
									eAlign = VDraw::A_RIGHT;
								pNode->SetAlign( eAlign );
								break;
							}
						}

						if ( tName == "VerticalAlign" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EVerticalAlignments	eVertAlign = VDraw::V_BASELINE;
								tValue.ConvertLowercase();
								if ( tValue == "baseline" )
									eVertAlign = VDraw::V_BASELINE;
								else if ( tValue == "absbottom"
										||	tValue == "bottom" )
									eVertAlign = VDraw::V_ABSBOTTOM;
								else if ( tValue == "middle"
										||	tValue == "center" )
									eVertAlign = VDraw::V_MIDDLE;
								else if ( tValue == "top" )
									eVertAlign = VDraw::V_TOP;
								pNode->SetVertAlign( eVertAlign );
								break;
							}
						}


						if ( tName == "GaugeString" )
						{
							CGaugeStringPtr	pGString = 0;
							pGString = GaugeString( &it );
							if ( pGString )
							{
								pNode->AddString( pGString );
								break;
							}
						}


						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( "Unrecongized tag in GaugeText" );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( "Unrecognized tag in GaugeText" );
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

 * Image -

\+---------------------------------------------------------------------*/
CImagePtr
		CFactoryGauge::Image
		(
		XMLIteratorPtr	pIt
		)
{
	CImagePtr			pNode = 0;
	XMLLite::ENODETYPE	eType;
	CCharDescriptor		tValue;

	eType = pIt->NodeType();
	if ( XMLLite::NODE_ELEMENT_BEGIN == eType )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		pNode = new CImage;
		if ( pNode )
		{
			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpFillStyle( pNode, &it ) )
							break;

						if ( grpOrigin( pNode->Origin(), &it ) )
							break;

						if ( grpSize( pNode->Size(), &it ) )
							break;

						if ( tName == "HorizontalAlign" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EAlignments	eAlign = VDraw::A_CENTER;
								tValue.ConvertLowercase();
								if ( tValue == "left" )
									eAlign = VDraw::A_LEFT;
								else if ( tValue == "center" )
									eAlign = VDraw::A_CENTER;
								else if ( tValue == "right" )
									eAlign = VDraw::A_RIGHT;
								pNode->SetAlign( eAlign );
								break;
							}
						}

						if ( tName == "VerticalAlign" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EVerticalAlignments	eVertAlign = VDraw::V_MIDDLE;
								tValue.ConvertLowercase();
								if ( tValue == "bottom" )
									eVertAlign = VDraw::V_ABSBOTTOM;
								else if ( tValue == "middle"
										||	tValue == "center" )
									eVertAlign = VDraw::V_MIDDLE;
								else if ( tValue == "top" )
									eVertAlign = VDraw::V_TOP;
								pNode->SetVertAlign( eVertAlign );
								break;
							}
						}

						if ( tName == "Fitment" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EFitments	eFitment = VDraw::F_FILL;
								tValue.ConvertLowercase();
								if ( tValue == "fill" )
									eFitment = VDraw::F_FILL;
								else if ( tValue == "original" )
									eFitment = VDraw::F_ORIGINAL;
								else if ( tValue == "scaled" )
									eFitment = VDraw::F_SCALED;
								else if ( tValue == "zoom" )
									eFitment = VDraw::F_ZOOM;
								pNode->SetFitment( eFitment );
								break;
							}
						}

						if ( tName == "File" )
						{
							CCharStringPtr	ps = pNode->File();
							CCharDescriptor	cs = it.NodeValue();

							char	sFolder[1024];
							char	sFile[128];

							cs.CopyTo( sFile, sizeof(sFile) );

							const char*	sApp = ::GetUserConfigFolder();
							::strcpy_s( sFolder, sizeof(sFolder), sApp );

							char*	t = sFolder + ::strlen(sFolder) - 1;
							if ( FOLDER_SEPARATOR_C == *t )
								::strcat_s( sFolder, sizeof(sFolder),
											"images" FOLDER_SEPARATOR_S );
							else
								::strcat_s( sFolder, sizeof(sFolder),
											FOLDER_SEPARATOR_S "images" FOLDER_SEPARATOR_S );

							::strcat_s( sFolder, sizeof(sFolder), sFile );

							*ps = sFolder;

							break;
						}


						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( "Unrecongized tag in Image" );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( "Unrecognized tag in Image" );
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

 * Video -

\+---------------------------------------------------------------------*/
CVideoPtr
		CFactoryGauge::Video
		(
		XMLIteratorPtr	pIt
		)
{
	CVideoPtr			pNode = 0;
	XMLLite::ENODETYPE	eType;
	CCharDescriptor		tValue;

	eType = pIt->NodeType();
	if ( XMLLite::NODE_ELEMENT_BEGIN == eType )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		pNode = new CVideo;
		if ( pNode )
		{
			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpOrigin( pNode->Origin(), &it ) )
							break;

						if ( grpSize( pNode->Size(), &it ) )
							break;

						if ( grpLineStyle( pNode, &it ) )
							break;

						if ( tName == "HorizontalAlign" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EAlignments	eAlign = VDraw::A_CENTER;
								tValue.ConvertLowercase();
								if ( tValue == "left" )
									eAlign = VDraw::A_LEFT;
								else if ( tValue == "center" )
									eAlign = VDraw::A_CENTER;
								else if ( tValue == "right" )
									eAlign = VDraw::A_RIGHT;
								pNode->SetAlign( eAlign );
								break;
							}
						}

						if ( tName == "VerticalAlign" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EVerticalAlignments	eVertAlign = VDraw::V_MIDDLE;
								tValue.ConvertLowercase();
								if ( tValue == "bottom" )
									eVertAlign = VDraw::V_ABSBOTTOM;
								else if ( tValue == "middle"
										||	tValue == "center" )
									eVertAlign = VDraw::V_MIDDLE;
								else if ( tValue == "top" )
									eVertAlign = VDraw::V_TOP;
								pNode->SetVertAlign( eVertAlign );
								break;
							}
						}


						if ( tName == "Fitment" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								VDraw::EFitments	eFitment = VDraw::F_FILL;
								tValue.ConvertLowercase();
								if ( tValue == "fill" )
									eFitment = VDraw::F_FILL;
								else if ( tValue == "original" )
									eFitment = VDraw::F_ORIGINAL;
								else if ( tValue == "scaled" )
									eFitment = VDraw::F_SCALED;
								else if ( tValue == "zoom" )
									eFitment = VDraw::F_ZOOM;
								pNode->SetFitment( eFitment );
								break;
							}
						}

						if ( tName == "Source" )
						{
							if ( ResultValueFromNodeValue( pNode->Source(), &it ) )
								break;
						}

						if ( tName == "SourceScript" )
						{
							if ( ResultValueFromNodeValueScript( pNode->Source(), &it ) )
								break;
						}

						if ( tName == "Mirror" )
						{
							if ( ResultValueFromNodeValueBool( pNode->Mirror(), &it ) )
								break;
						}

						if ( tName == "MirrorScript" )
						{
							if ( ResultValueFromNodeValueScript( pNode->Mirror(), &it ) )
								break;
						}


						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( "Unrecongized tag in Video" );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( "Unrecognized tag in Video" );
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

 * Line -

\+---------------------------------------------------------------------*/
CLinePtr
		CFactoryGauge::Line
		(
		XMLIteratorPtr pIt
		)
{
	CLinePtr	pNode = new CLine;
	if ( pNode )
	{
		CCharDescriptor	tName;
		CPointValuePtr	pData;
		int				nCoord = 1;

		LoadStyles( pNode, pIt );

		XMLIterator		it( pIt );
		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Point" )
				{
					pData = Point( &it );
					if ( pData )
					{
						switch ( nCoord )
						{
						case 1:
							pNode->SetBegin( *pData );
							break;
						case 2:
							pNode->SetEnd( *pData );
							break;
						}
						++nCoord;
						delete pData;
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

 * Pie -

\+---------------------------------------------------------------------*/
CPiePtr
		CFactoryGauge::Pie
		(
		XMLIteratorPtr pIt
		)
{
	CPiePtr	pNode = 0;
	XMLLite::ENODETYPE	eType;

	eType = pIt->NodeType();
	if ( XMLLite::NODE_ELEMENT == eType )
	{
		do	// sequence
		{
			if ( pIt->AttributeCount() < 1 )
				break;

			pNode = new CPie;
			if ( ! pNode )
				break;

			if ( ! LoadXY( pNode->Axis(), pIt ) )
				break;

			if ( ! LoadStyles( pNode, pIt ) )
				break;

			if ( ! AttributeRadius( pNode->Radius(), pIt ) )
				break;

			if ( ! LoadNumberEquation( pNode->StartAngle(), "StartAngle", pIt ) )
				break;

			if ( ! LoadNumberEquation( pNode->EndAngle(), "EndAngle", pIt ) )
				break;

		} sequence;	// end sequence

	}
	else if ( XMLLite::NODE_ELEMENT_BEGIN == eType )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		pNode = new CPie;
		if ( pNode )
		{
			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpOrigin( pNode->Axis(), &it ) )
							break;

						if ( grpStartAngle( pNode->StartAngle(), &it ) )
							break;

						if ( grpEndAngle( pNode->EndAngle(), &it ) )
							break;

						if ( grpRadius( pNode->Radius(), &it ) )
							break;

						if ( grpFillStyle( pNode, &it ) )
							break;

						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( "Unrecongized tag in Pie" );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( "Unrecognized tag in Pie" );
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

 * Point -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CFactoryGauge::Point
		(
		XMLIteratorPtr pIt
		)
{
	CPointValuePtr	pNode = 0;

	if ( 0 < pIt->AttributeCount() )
	{
		pNode = new CPointValue;
		if ( pNode )
		{
			if ( ! LoadXY( pNode, pIt ) )
			{
				delete pNode;
				pNode = 0;
			}
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * Polygon -

\+---------------------------------------------------------------------*/
CPolygonPtr
		CFactoryGauge::Polygon
		(
		XMLIteratorPtr pIt
		)
{
	CPolygonPtr		pNode = 0;
	CCharDescriptor	tName;
	CPointValuePtr	pData;
	XMLIterator		it( pIt );

	pNode = new CPolygon;
	if ( pNode )
	{
		LoadStyles( pNode, pIt );

		while ( it.NextChild() )
		{
			switch( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
			case XMLLite::NODE_ELEMENT:
				tName = it.NodeName();
				if ( tName == "Point" )
				{
					pData = Point( &it );
					if ( pData )
						pNode->AddPoint( pData );
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

 * Polyline -

\+---------------------------------------------------------------------*/
CPolylinePtr
		CFactoryGauge::Polyline
		(
		XMLIteratorPtr pIt
		)
{
	CPolylinePtr	pNode = 0;
	CCharDescriptor	tName;
	CPointValuePtr	pData;
	XMLIterator		it( pIt );

	pNode = new CPolyline;
	if ( pNode )
	{
		LoadStyles( pNode, pIt );

		while ( it.NextChild() )
		{
			switch( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
			case XMLLite::NODE_ELEMENT:
				tName = it.NodeName();
				if ( tName == "Point" )
				{
					pData = Point( &it );
					if ( pData )
						pNode->AddPoint( pData );
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

 * Rectangle -

\+---------------------------------------------------------------------*/
CRectanglePtr
		CFactoryGauge::Rectangle
		(
		XMLIteratorPtr pIt
		)
{
	CRectanglePtr		pNode = 0;
	XMLLite::ENODETYPE	eType;
	CCharDescriptor		tValue;

	eType = pIt->NodeType();
	if ( XMLLite::NODE_ELEMENT == eType )
	{
		do	// sequence
		{
			if ( pIt->AttributeCount() < 1 )
				break;

			pNode = new CRectangle;
			if ( ! pNode )
				break;

			if ( ! LoadXY( pNode->Origin(), pIt ) )
				break;

			if ( ! LoadStyles( pNode, pIt ) )
				break;


			if ( ! LoadNumberEquation( pNode->Width(), "Width", pIt ) )
				break;

			if ( ! LoadNumberEquation( pNode->Height(), "Height", pIt ) )
				break;

			VDraw::CORNERSTYLE	eCorner = VDraw::C_SQUARE;
			tValue = pIt->AttributeValue( "CornerStyle" );
			if ( 0 < tValue.Length() )
			{
				tValue.ConvertLowercase();
				if ( tValue == "square" )
					eCorner = VDraw::C_SQUARE;
				else if ( tValue == "bevel" )
					eCorner = VDraw::C_BEVEL;
				else if ( tValue == "round" )
					eCorner = VDraw::C_ROUND;
				else if ( tValue == "rabbet" )
					eCorner = VDraw::C_RABBET;
				else if ( tValue == "cove" )
					eCorner = VDraw::C_COVE;
				else
					pIt->Error( "unrecognized CornerStyle value" );
				pNode->SetCornerStyle( eCorner );

			}

			if ( ! LoadNumberEquation( pNode->Corner(), "Corner", pIt ) )
				break;

		} sequence;	// end sequence

	}
	else if ( XMLLite::NODE_ELEMENT_BEGIN == eType )
	{
		XMLIterator		it( pIt );
		CCharDescriptor	tName;

		pNode = new CRectangle;
		if ( pNode )
		{
			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT:

					do // sequence
					{
						if ( grpOrigin( pNode->Origin(), &it ) )
							break;

						if ( grpSize( pNode->Size(), &it ) )
							break;

						if ( grpFillStyle( pNode, &it ) )
							break;

						VDraw::CORNERSTYLE	eCorner = VDraw::C_SQUARE;
						if ( tName == "CornerStyle" )
						{
							tValue = it.NodeValue();
							if ( 0 < tValue.Length() )
							{
								tValue.ConvertLowercase();
								if ( tValue == "square" )
									eCorner = VDraw::C_SQUARE;
								else if ( tValue == "bevel" )
									eCorner = VDraw::C_BEVEL;
								else if ( tValue == "round" )
									eCorner = VDraw::C_ROUND;
								else if ( tValue == "rabbet" )
									eCorner = VDraw::C_RABBET;
								else if ( tValue == "cove" )
									eCorner = VDraw::C_COVE;
								else
									it.Error( "unrecognized CornerStyle value" );
								pNode->SetCornerStyle( eCorner );
							}
							break;
						}

						if ( tName == "Corner" )
						{
							if ( ResultValueFromNodeValueFloat( pNode->Corner(), &it ) )
								break;
						}

						if ( tName == "CornerScript" )
						{
							if ( ResultValueFromNodeValueScript( pNode->Corner(), &it ) )
								break;
						}


						if ( tName == "Comment" )
						{
							EatNode();
							break;
						}

						it.Error( "Unrecongized tag in Rectangle" );

					} sequence;

					break;
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Comment" )
						EatNode();
					else
						it.Error( "Unrecognized tag in Rectangle" );
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

 * FloatPosition -

\+---------------------------------------------------------------------*/
CPositionPtr
		CFactoryGauge::FloatPosition
		(
		CPositionPtr	pInput,
		XMLIteratorPtr	pIt
		)
{
	CPositionPtr	pNode = 0;
	long			nCount;
	GFLOAT			fList[2];

	nCount = pIt->NodeValueAsFloatArray( fList, 2 );
	if ( 2 == nCount )
	{
		if ( pInput )
			pNode = pInput;
		else
			pNode = new CPosition;
		if ( pNode )
			pNode->SetValues( fList[0], fList[1] );

		if ( pNode == pInput )
			pNode = (CPositionPtr)NOUPDATE;
	}

	return pNode;
}



/*---------------------------------------------------------------------+\

 * LeftScript -

\+---------------------------------------------------------------------*/
CPositionPtr
		CFactoryGauge::LeftScript
		(
		CPositionPtr	pInput,
		XMLIteratorPtr	pIt
		)
{
	CPositionPtr	pNode = 0;
	CCharDescriptor	tValue;

	tValue = pIt->NodeValue();
	if ( 0 < tValue.Length() )
	{
		VEquationPtr	pEq;

		pEq = MakeEquation( CFactoryEquation::E_COORDINATE, tValue );
		if ( pEq )
		{
			if ( pInput )
				pNode = pInput;
			else
				pNode = new CPosition;
			if ( pNode )
				pNode->SetXEquation( pEq );
			if ( pNode == pInput )
				pNode = (CPositionPtr)NOUPDATE;
		}
		else
		{
			pIt->Error( EquationErrorString() );
		}
	}

	return pNode;
}




/*---------------------------------------------------------------------+\

 * TopScript -

\+---------------------------------------------------------------------*/
CPositionPtr
		CFactoryGauge::TopScript
		(
		CPositionPtr	pInput,
		XMLIteratorPtr	pIt
		)
{
	CPositionPtr	pNode = 0;
	CCharDescriptor	tValue;

	tValue = pIt->NodeValue();
	if ( 0 < tValue.Length() )
	{
		VEquationPtr	pEq;

		pEq = MakeEquation( CFactoryEquation::E_COORDINATE, tValue );
		if ( pEq )
		{
			if ( pInput )
				pNode = pInput;
			else
				pNode = new CPosition;
			if ( pNode )
				pNode->SetYEquation( pEq );

			if ( pNode == pInput )
				pNode = (CPositionPtr)NOUPDATE;
		}
		else
		{
			pIt->Error( EquationErrorString() );
		}
	}
	return pNode;
}


/*---------------------------------------------------------------------+\

 * Axis -

\+---------------------------------------------------------------------*/
CAxisPtr
		CFactoryGauge::Axis
		(
		XMLIteratorPtr pIt
		)
{
	CAxisPtr	pNode = 0;
	long		nCount;
	GFLOAT		fList[2];

	nCount = pIt->NodeValueAsFloatArray( fList, 2 );
	if ( 2 == nCount )
	{
		pNode = new CAxis;
		if ( pNode )
			pNode->SetValues( fList[0], fList[1] );
	}

	return pNode;
}







/*---------------------------------------------------------------------+\

 * ElementContent - Processes the contents of an Element

 * Assumes that the "current" node is inside of an Element

\+---------------------------------------------------------------------*/
VOwnershipPtr
		CFactoryGauge::grpElementContent
		(
		XMLIteratorPtr		pIt
		)
{
	VOwnershipPtr	pNode = 0;

	pNode = grpGraphic( pIt );
	if ( ! pNode )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		switch ( pIt->NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "Comment" )
			{
				EatNode();
			}
			else
			{
				if ( tName == "Element" )
					pNode = Element( pIt );
				else if ( tName == "ForLoop" )
					pNode = ForLoop( pIt );
				else if ( tName == "Select" )
					pNode = Select( pIt );
				else if ( tName == "Choose" )
					pNode = Choose( pIt );
				else if ( tName == "Include" )
					pNode = IncludeFile( pIt );

			}
			break;

		case XMLLite::NODE_ELEMENT:
			if ( tName == "Comment" )
			{
				;	// just ignore it
			}
			else
			{
				if ( tName == "Include" )
					pNode = IncludeFile( pIt );

			}
			break;
        default:
            break;
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * grpElementControl - Processes the contents of an Element

			Assumes that the "current" node is inside of an Element
			It is possible for this function to return ~0 for an address.

\+---------------------------------------------------------------------*/
VRenderablePtr
		CFactoryGauge::grpElementControl
		(
		ControlObjects*		pCtl,
		XMLIteratorPtr		pIt
		)
{
	VRenderablePtr	pNode = 0;

	pNode = grpGraphic( pIt );
	if ( ! pNode )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		switch ( pIt->NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Comment" )
			{
				EatNode();	// just ignore it
			}
			else
			{
				if ( tName == "Position" )
				{
					pNode = Position( pIt );
				}
				else if ( tName == "FloatPosition" )
					pNode = pCtl->SetPosition( FloatPosition( pCtl->pPosition, pIt ) );
				else if ( tName == "LeftScript" )
					pNode = pCtl->SetPosition( LeftScript( pCtl->pPosition, pIt ) );
				else if ( tName == "TopScript" )
					pNode = pCtl->SetPosition( TopScript( pCtl->pPosition, pIt ) );
				else if ( tName == "Axis" )
					pNode = Axis( pIt );
				else if ( tName == "Rotation" )
					pNode = pCtl->SetRotation( Rotation( pCtl->pRotation, pIt ) );
				else if ( tName == "Shift" )
					pNode = pCtl->SetShift( Shift( pCtl->pShift, pIt ) );

			}
			break;
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "Comment" )
			{
				EatNode();
			}
			else
			{
				if ( tName == "Rotation" )
					pNode = pCtl->SetRotation( Rotation( pCtl->pRotation, pIt ) );
				else if ( tName == "Shift" )
					pNode = pCtl->SetShift( Shift( pCtl->pShift, pIt ) );
			}
			break;
        default:
            break;
		}
	}

	return pNode;
}


/*---------------------------------------------------------------------+\

 * Graphic -

\+---------------------------------------------------------------------*/
VGraphicPtr
		CFactoryGauge::grpGraphic
		(
		XMLIteratorPtr pIt
		)
{
	VGraphicPtr		pGraphic = 0;
	CCharDescriptor	tName;

	tName = pIt->NodeName();

	if ( tName == "Arc" )
		pGraphic = Arc( pIt );
	else if ( tName == "Circle" )
		pGraphic = Circle( pIt );
	else if ( tName == "GaugeText" )
		pGraphic = GaugeText( pIt );
	else if ( tName == "Line" )
		pGraphic = Line( pIt );
	else if ( tName == "Pie" )
		pGraphic = Pie( pIt );
	else if ( tName == "Polygon" )
		pGraphic = Polygon( pIt );
	else if ( tName == "Polyline" )
		pGraphic = Polyline( pIt );
	else if ( tName == "Rectangle"
			||	tName == "Rect" )
		pGraphic = Rectangle( pIt );
	else if ( tName == "Video" )
		pGraphic = Video( pIt );
	else if ( tName == "Image" )
		pGraphic = Image( pIt );

	return pGraphic;
}



/*---------------------------------------------------------------------+\

 * grpOrigin -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpOrigin
		(
		VCoordinatePtr	pNode,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;

	if ( pNode )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		if ( tName == "Axis"
			||	tName == "Origin" )
		{
			bResult = Float2FromNodeValue( pNode, pIt );
		}
		else if ( tName == "OriginX" )
		{
			bResult = ResultValueFromNodeValueFloat( pNode->X(), pIt );
		}
		else if ( tName == "OriginY" )
		{
			bResult = ResultValueFromNodeValueFloat( pNode->Y(), pIt );
		}
		else if ( tName == "OriginXScript" )
		{
			bResult = ResultValueFromNodeValueScript( pNode->X(), pIt );
		}
		else if ( tName == "OriginYScript" )
		{
			bResult = ResultValueFromNodeValueScript( pNode->Y(), pIt );
		}
	}

	return bResult;
}


bool	CFactoryGauge::grpPoint
		(
		VCoordinatePtr	,//pNode,
		XMLIteratorPtr	//pIt
		)
{
	return false;
}


bool	CFactoryGauge::grpPosition
		(
		VCoordinatePtr	,//pNode,
		XMLIteratorPtr	//pIt
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * grpSize -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpSize
		(
		VCoordinatePtr	pNode,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;

	if ( pNode )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		if ( tName == "Size" )
		{
			bResult = Float2FromNodeValue( pNode, pIt );
		}
		else if ( tName == "Width" )
		{
			bResult = ResultValueFromNodeValueFloat( pNode->X(), pIt );
		}
		else if ( tName == "WidthScript" )
		{
			bResult = ResultValueFromNodeValueScript( pNode->X(), pIt );
		}
		else if ( tName == "Height" )
		{
			bResult = ResultValueFromNodeValueFloat( pNode->Y(), pIt );
		}
		else if ( tName == "HeightScript" )
		{
			bResult = ResultValueFromNodeValueScript( pNode->Y(), pIt );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * grpStartAngle -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpStartAngle
		(
		CResultValuePtr	pRV,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;

	if ( pRV )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		if ( tName == "StartAngle" )
		{
			bResult = ResultValueFromNodeValueFloat( pRV, pIt );
		}
		else if ( tName == "StartAngleScript" )
		{
			bResult = ResultValueFromNodeValueScript( pRV, pIt );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * grpEndAngle -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpEndAngle
		(
		CResultValuePtr	pRV,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;

	if ( pRV )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		if ( tName == "EndAngle" )
		{
			bResult = ResultValueFromNodeValueFloat( pRV, pIt );
		}
		else if ( tName == "EndAngleScript" )
		{
			bResult = ResultValueFromNodeValueScript( pRV, pIt );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * grpRadius -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpRadius
		(
		CResultValuePtr	pRV,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;

	if ( pRV )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		if ( tName == "Radius" )
		{
			bResult = ResultValueFromNodeValueFloat( pRV, pIt );
		}
		else if ( tName == "RadiusScript" )
		{
			bResult = ResultValueFromNodeValueScript( pRV, pIt );
		}
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * grpLineStyle -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpLineStyle
		(
		VGraphicPtr		p,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;

	tName = pIt->NodeName();
	if ( tName == "LineColor"  ||  tName == "Color" )
		bResult = ResultValueFromNodeColorValue( p->Style()->LineColor(), pIt );
	else if ( tName == "LineColorScript"  ||  tName == "ColorScript" )
		bResult = ResultValueFromNodeColorScript( p->Style()->LineColor(), pIt );
	else if ( tName == "LineWidth" )
		bResult = ResultValueFromNodeValueFloat( p->Style()->LineWidth(), pIt );
	else if ( tName == "LineWidthScript" )
		bResult = ResultValueFromNodeValueScript( p->Style()->LineWidth(), pIt );

	if ( bResult )
		bResult |= grpHaloStyle( p, pIt );
	return bResult;
}


/*---------------------------------------------------------------------+\

 * grpFillStyle -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpFillStyle
		(
		VGraphicPtr		p,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;

	tName = pIt->NodeName();

	bResult = grpLineStyle( p, pIt );
	if ( ! bResult )
	{
		if ( tName == "FillColor" )
			bResult = ResultValueFromNodeColorValue( p->Style()->FillColor(), pIt );
		else if ( tName == "FillColorScript" )
			bResult = ResultValueFromNodeColorScript( p->Style()->FillColor(), pIt );
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * grpFillStyle -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpHaloStyle
		(
		VGraphicPtr		p,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;

	tName = pIt->NodeName();

	if ( tName == "HaloColor" )
		bResult = ResultValueFromNodeColorValue( p->Style()->HaloColor(), pIt );
	else if ( tName == "HaloColorScript" )
		bResult = ResultValueFromNodeColorScript( p->Style()->HaloColor(), pIt );

	return bResult;
}



/*---------------------------------------------------------------------+\

 * grpFontColor -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpFontColor
		(
		VGraphicPtr		p,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;

	tName = pIt->NodeName();
	if ( tName == "FontColor"  ||  tName == "Color" )
		bResult = ResultValueFromNodeColorValue( p->Style()->LineColor(), pIt );
	else if ( tName == "FontColorScript"  ||  tName == "ColorScript" )
		bResult = ResultValueFromNodeColorScript( p->Style()->LineColor(), pIt );

	if ( bResult )
		bResult |= grpHaloStyle( p, pIt );
	return bResult;
}



/*---------------------------------------------------------------------+\

 * grpBackgroundColor -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpBackgroundColor
		(
		VGraphicPtr		p,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;

	tName = pIt->NodeName();

	bResult = grpFontColor( p, pIt );
	if ( ! bResult )
	{
		if ( tName == "BackgroundColor" )
			bResult = ResultValueFromNodeColorValue( p->Style()->FillColor(), pIt );
		else if ( tName == "BackgroundColorScript" )
			bResult = ResultValueFromNodeColorScript( p->Style()->FillColor(), pIt );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * grpFontHeight -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::grpFontHeight
		(
		CResultValuePtr	pRV,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;

	if ( pRV )
	{
		CCharDescriptor	tName;

		tName = pIt->NodeName();
		if ( tName == "FontHeight" )
		{
			bResult = ResultValueFromNodeValueFloat( pRV, pIt );
		}
		else if ( tName == "FontHeightScript" )
		{
			bResult = ResultValueFromNodeValueScript( pRV, pIt );
		}
	}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * Float2FromNodeValue -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::Float2FromNodeValue
		(
		VCoordinatePtr	pNode,
		XMLIteratorPtr	pIt
		)
{
	bool	bResult = false;
	long	nCount;
	GFLOAT	fList[2];

	if ( pNode )
	{
		nCount = pIt->NodeValueAsFloatArray( fList, 2 );
		if ( 2 == nCount )
		{
			pNode->SetValues( fList[0], fList[1] );
			bResult = true;
		}
	}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * ResultValueFromNodeValue -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::ResultValueFromNodeValue
		(
		CResultValuePtr	pResultValue,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( ! pIt->NodeEmpty() )
		{
			CCharDescriptor	s = pIt->NodeValue();
			CVariantData	v = s;
			pResultValue->SetValue( v );
			bResult = true;
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * ResultValueFromNodeValueFloat -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::ResultValueFromNodeValueFloat
		(
		CResultValuePtr	pResultValue,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( ! pIt->NodeEmpty() )
		{
			float	f = pIt->NodeValueAsFloat();
			pResultValue->SetValue( CVariantData( f ) );
			bResult = true;
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ResultValueFromNodeValueBool -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::ResultValueFromNodeValueBool
		(
		CResultValuePtr	pResultValue,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( ! pIt->NodeEmpty() )
		{
			CCharDescriptor	tBool = pIt->NodeValue();
			char	c = *tBool.Pointer();
			bool	b = false;
			switch ( ::tolower( c ) )
			{
			case 'y':
			case 't':
			case '1':
				b = true;
				break;
			default:
				break;
			}
			pResultValue->SetValue( CVariantData( b ) );
			bResult = true;
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ResultValueFromNodeColorValue -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::ResultValueFromNodeColorValue
		(
		CResultValuePtr	pResultValue,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( ! pIt->NodeEmpty() )
		{
			tValue = pIt->NodeValue();
			CVariantData	v;
			long			nValue;
			size_t			n;
			nValue = tValue.ParseInt( &n );
			if ( 0 < n )
			{
				CColor	c;
				c.SetColorLong( nValue );
				v = c;
				pResultValue->SetValue( v );
				bResult = true;
			}
			else
			{
				CColor	c = CColor::ColorFromName( tValue );
				if ( ! c.IsNonColor() )
				{
					v = c;
					pResultValue->SetValue( v );
					bResult = true;
				}
				else
				{
					pIt->Error( "Unrecognized color name" );
				}
			}
		}
	}
	return bResult;
}




/*---------------------------------------------------------------------+\

 * ResultValueFromNodeValueScript -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::ResultValueFromNodeValueScript
		(
		CResultValuePtr	pResult,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( ! pIt->NodeEmpty() )
		{
			tValue = pIt->NodeValue();
			VEquationPtr	pEq;
			pEq = MakeEquation( CFactoryEquation::E_UNDEFINED,
								tValue );
			if ( pEq )
			{
				pResult->SetEquation( pEq );
				bResult = true;
			}
			else
			{
				pIt->Error( EquationErrorString() );
			}
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ResultValueFromNodeColorScript -

\+---------------------------------------------------------------------*/
bool	CFactoryGauge::ResultValueFromNodeColorScript
		(
		CResultValuePtr	pResult,
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		if ( ! pIt->NodeEmpty() )
		{
			tValue = pIt->NodeValue();
			VEquationPtr	pEq;
			pEq = MakeEquation( CFactoryEquation::E_COLOR,
								tValue );
			if ( pEq )
			{
				CVariantData	v;
				if ( ConstantEquation() )
				{
					CColor	c;
					v = pEq->GetValue( 0 );
					if ( CVariantData::T_STRING == v.GetType() )
						c = CColor::ColorFromName( v.operator CCharDescriptorRef() );
					else
						c = v.GetValueColor();
					v = c;
					pResult->SetValue( v );
					delete pEq;
					bResult = true;
				}
				else
				{
					pResult->SetEquation( pEq );
					bResult = true;
				}
			}
			else
			{
				pIt->Error( EquationErrorString() );
			}
		}
	}
	return bResult;
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
