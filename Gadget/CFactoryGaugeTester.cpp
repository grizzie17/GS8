/*---------------------------------------------------------------------+\
|
|	GaugeFactory.cpp  --  FILE RETIRED
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
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#if 0	// FILE RETIRED


#include "stdafx.h"
#include "CFactoryGaugeTester.h"

#include "CColor.h"
#include "CDictionary.h"

#include "CEqVariable.h"
#include "CRotation.h"
#include "CEqOpNegate.h"
#include "CEqConstant.h"
#include "CEqOpMultiply.h"
#include "CEqOpSubtract.h"
#include "CVariantData.h"
#include "CFactoryEquation.h"

#include "CAxis.h"
#include "CElement.h"
#include "CGauge.h"
#include "CGaugeString.h"
#include "CGaugeText.h"
#include "CPosition.h"
#include "CShift.h"
#include "CVisible.h"

#include "CPoint.h"
#include "CPolyline.h"
#include "CPolygon.h"
#include "CLine.h"
#include "CCircle.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
/**--------------------------------------------------------------------+\

 * <summary>CFactoryGaugeTester - constructor</summary>

 * <remarks/>

 * (author) J.Griswold  --  01-Jun-2009

\+---------------------------------------------------------------------*/
CFactoryGaugeTester::CFactoryGaugeTester
		(
		void
		)
		: m_nSelected( 0 ),
		m_pFactoryEquation( 0 )
{
	m_pFactoryEquation = new CFactoryEquation;
}

/**--------------------------------------------------------------------+\

 * <summary>CFactoryGaugeTester - copy constructor</summary>

 * <remarks/>

 * (author) J.Griswold  --  01-Jun-2009

\+---------------------------------------------------------------------*/
CFactoryGaugeTester::CFactoryGaugeTester
		(
		CFactoryGaugeTesterRef	r
		)
{
	// TODO: add instructions to copy data from "r" to "this"
}

/**--------------------------------------------------------------------+\

 * <summary>~CFactoryGaugeTester - destructor</summary>

 * <remarks/>

 * (author) J.Griswold  --  01-Jun-2009

\+---------------------------------------------------------------------*/
CFactoryGaugeTester::~CFactoryGaugeTester
		(
		void
		)
{
	if ( m_pFactoryEquation )
		delete m_pFactoryEquation;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

CGaugePtr
		CFactoryGaugeTester::Make
		(
		char *sName
		)
{
	SelectName( sName );
	return Get();
}

/**---------------------------------------------------------------------+\

 * <summary>operator= - assignment operator</summary>

 * <remarks/>

 * (author) J.Griswold  --  01-Jun-2009

\+---------------------------------------------------------------------*/
CFactoryGaugeTesterRef
		CFactoryGaugeTester::operator=
		(
		CFactoryGaugeTesterRef	r
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

void	CFactoryGaugeTester::SelectName
		(
		char*	sName
		)
{
	if ( 0 == ::_stricmp( sName, "test" ) )
		m_nSelected = 1;
	else if ( 0 == ::_stricmp( sName, "simpletest" ) )
		m_nSelected = 2;
	else if ( 0 == ::_stricmp( sName, "slider" ) )
		m_nSelected = 3;
	else if ( 0 == ::_stricmp( sName, "sliderHider" ) )
		m_nSelected = 4;
	else if ( 0 == ::_stricmp( sName, "dial" ) )
		m_nSelected = 5;
	else
		m_nSelected = 0;
}





CGaugePtr
		CFactoryGaugeTester::Get_slider()
{

	VEquationPtr	pEq;
	bool			bGVars = false;


	CGaugePtr	pGauge = new CGauge;
	pGauge->SetSize( 40, 200 );

	CElementPtr	pSuperElem = new CElement;
	pGauge->AddRenderable( pSuperElem );

	CPositionPtr	pPosition;
	//pPosition = new CPosition;
	//pPosition->SetPointValue( 40, 20 );
	//pSuperElem->AddRenderable( pPosition );

	CElementPtr	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );



	CPolylinePtr	pPoly = new CPolyline;
	pElem->AddRenderable( pPoly );
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COLOR,
		" 'green' 'darkorange' (T:PULSER) (T:SLIDER.YELLOW) < ? 'crimson' (T:PULSER) (T:SLIDER.RED) < ?   " );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoly->Style()->SetLineColor( pEq );
	pPoly->Style()->SetLineWidth( 3 );

	CPointValuePtr	pPoint;

	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 25, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 25, 200 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 20, 200 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE,
		" (T:SLIDER.YELLOW) 2 * " );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->X()->SetValue( 0 );
	pPoint->Y()->SetEquation( pEq );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );



	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );

	pPosition = new CPosition;
	pPosition->SetPointValue( 10, 0 );
	pElem->AddRenderable( pPosition );

	CShiftPtr	pShift = new CShift;
	pElem->AddRenderable( pShift );


	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER)  2.0f * /-/ (>G:TEST)" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();

	pShift->X()->SetValue( 0.0 );
	pShift->Y()->SetEquation( pEq );



	CPolygonPtr pPolyg = new CPolygon;
	pElem->AddRenderable( pPolyg );

	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COLOR,
		" 'limegreen' 'orange' (T:PULSER) (T:SLIDER.YELLOW) < ? 'red' (T:PULSER) (T:SLIDER.RED) < ?   " );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPolyg->Style()->SetFillColor( pEq );
	pPolyg->Style()->SetLineColor( CColor::ColorFromName( "nothing" ) );
	pPolyg->Style()->SetLineWidth( 0.0f );


	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPolyg->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 24, -6 );
	pPolyg->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 24, 6 );
	pPolyg->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPolyg->AddPoint( pPoint );

	if ( bGVars )
		pGauge->AllocateLocalData();




	return pGauge;
}



CGaugePtr
		CFactoryGaugeTester::Get_sliderHider()
{

	VEquationPtr	pEq;
	bool			bGVars = false;


	CGaugePtr	pGauge = new CGauge;
	pGauge->SetSize( 40, 200 );

	CVisiblePtr	pVis = new CVisible;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_LENGTH,
		"(T:SLIDER.YELLOW) (T:PULSER) <" );
	pVis->SetEquation( pEq );
	pGauge->AddRenderable( pVis );

	CElementPtr	pSuperElem = new CElement;
	pGauge->AddRenderable( pSuperElem );

	CPositionPtr	pPosition;
	//pPosition = new CPosition;
	//pPosition->SetPointValue( 40, 20 );
	//pSuperElem->AddRenderable( pPosition );

	CElementPtr	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );



	CPolylinePtr	pPoly = new CPolyline;
	pElem->AddRenderable( pPoly );
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COLOR,
		" 'green' 'darkorange' (T:PULSER) (T:SLIDER.YELLOW) < ? 'firebrick' (T:PULSER) (T:SLIDER.RED) < ?   " );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoly->Style()->SetLineColor( pEq );
	pPoly->Style()->SetLineWidth( 3 );

	CPointValuePtr	pPoint;

	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 25, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 25, 200 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 20, 200 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE,
		" (T:SLIDER.YELLOW) 2 * " );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->X()->SetValue( 0 );
	pPoint->Y()->SetEquation( pEq );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );



	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );

	pPosition = new CPosition;
	pPosition->SetPointValue( 10, 0 );
	pElem->AddRenderable( pPosition );

	CShiftPtr	pShift = new CShift;
	pElem->AddRenderable( pShift );


	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER)  2.0f * /-/ (>G:TEST)" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();

	pShift->X()->SetValue( 0.0 );
	pShift->Y()->SetEquation( pEq );



	CPolygonPtr pPolyg = new CPolygon;
	pElem->AddRenderable( pPolyg );

	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COLOR,
		" 'limegreen' 'orange' (T:PULSER) (T:SLIDER.YELLOW) < ? 'red' (T:PULSER) (T:SLIDER.RED) < ?   " );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPolyg->Style()->SetFillColor( pEq );
	pPolyg->Style()->SetLineColor( CColor::ColorFromName( "nothing" ) );
	pPolyg->Style()->SetLineWidth( 0.0f );


	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPolyg->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 24, -6 );
	pPolyg->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 24, 6 );
	pPolyg->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPolyg->AddPoint( pPoint );

	if ( bGVars )
		pGauge->AllocateLocalData();




	return pGauge;
}




CGaugePtr
CFactoryGaugeTester::Get_dial()
{
	bool			bGVars = false;
	CColor			c;
	VEquationPtr	pEq;


	CGaugePtr	pGauge = new CGauge;
	pGauge->SetSize( 220, 220 );

	CElementPtr	pSuperElem = new CElement;
	pGauge->AddRenderable( pSuperElem );

	CPositionPtr pPos;
	pPos = new CPosition;
	pPos->SetPointValue( 10, 10 );
	pSuperElem->AddRenderable( pPos );

	CCirclePtr	pCircle = new CCircle;
	pCircle->Axis()->SetPointValue( 100, 100 );
	pCircle->Radius()->SetValue( 106 );
	//pCircle->Style()->SetLineWidth( 2 );
	pCircle->Style()->SetFillColor( CColor::ColorFromName( "dimgray" ) );
	pSuperElem->AddRenderable( pCircle );

	pCircle = new CCircle;
	pCircle->Axis()->SetPointValue( 100, 100 );
	pCircle->Radius()->SetValue( 102 );
	pCircle->Style()->SetLineWidth( 4 );
	pCircle->Style()->SetLineColor( CColor::ColorFromName( "darkgray" ) );
	pSuperElem->AddRenderable( pCircle );

	//CCirclePtr	pCircle = new CCircle;
	//pCircle->Axis()->SetPointValue( 100, 100 );
	//pCircle->Radius()->SetValue( 100 );
	//pCircle->Style()->SetLineWidth( 2 );
	//pCircle->Style()->SetLineColor( CColor::ColorFromName( "purple" ) );
	//pSuperElem->AddRenderable( pCircle );


	CElementPtr		pElem;
	CRotationPtr	pRotation;
	CPositionPtr	pPosition;
	CPolygonPtr		pPoly;
	CPointValuePtr	pPoint;



	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );

	pRotation = new CRotation;
	pElem->AddRenderable( pRotation );
	//pEq = tEqFactory.MakeEquation( CFactoryEquation::E_LENGTH, "pi2 (T:SPIN) -" );
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_LENGTH, "pi2 (T:SLIDER) 50 % 50 / pi2 * -" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	// pi2 (T:SLIDER) 2 * 100 % * 100 /
	//(3.141592654f*2) * ((float(g_nValue) * 2) % 100 / 100.0f)
	// (T:SLIDER) 2 * 100 % 100 / pi2 *
	pRotation->SetEquation( pEq );

	pPosition = new CPosition;
	pPosition->SetPointValue( 100, 100 );
	pElem->AddRenderable( pPosition );

	pPoly = new CPolygon;
	pElem->AddRenderable( pPoly );
	c = CColor::ColorFromName( "lightgray" );
	pPoly->Style()->SetLineColor( c );
	pPoly->Style()->SetLineWidth( 1 );
	pPoly->Style()->SetFillColor( c );

	pPoint = new CPointValue;
	pPoint->SetPointValue( 80, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 105, -8 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 106, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 105, 8 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 80, 0 );
	pPoly->AddPoint( pPoint );

	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );

	pRotation = new CRotation;

	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_LENGTH, "(T:SPIN) s0" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pRotation->SetEquation( pEq );
	pElem->AddRenderable( pRotation );

	pPosition = new CPosition;
	pPosition->SetPointValue( 104, 104 );
	pElem->AddRenderable( pPosition );

	pPoly = new CPolygon;
	pElem->AddRenderable( pPoly );
	c = CColor::ColorFromName( "black" );
	pPoly->Style()->SetLineColor( c );
	pPoly->Style()->SetLineWidth( 1 );
	pPoly->Style()->SetFillColor( c );

	pPoint = new CPointValue;
	pPoint->SetPointValue( -20, -6 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 90, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( -20, 6 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( -20, -6 );
	pPoly->AddPoint( pPoint );


	pElem = new CElement;
	pSuperElem->AddRenderable( pElem );

	pRotation = new CRotation;

	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_LENGTH, "l0" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pRotation->SetEquation( pEq );
	pElem->AddRenderable( pRotation );

	pPosition = new CPosition;
	pPosition->SetPointValue( 100, 100 );
	pElem->AddRenderable( pPosition );

	pPoly = new CPolygon;
	pElem->AddRenderable( pPoly );
	c = CColor::ColorFromName( "red" );
	pPoly->Style()->SetLineColor( c );
	pPoly->Style()->SetLineWidth( 1 );
	pPoly->Style()->SetFillColor( c );

	pPoint = new CPointValue;
	pPoint->SetPointValue( -20, -6 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 90, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( -20, 6 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( -20, -6 );
	pPoly->AddPoint( pPoint );



	if ( bGVars )
		pGauge->AllocateLocalData();


	return pGauge;
}



CGaugePtr
		CFactoryGaugeTester::Get_test()
{
	bool				bGVars = false;
	CFactoryEquation	tEqFactory;
	CColor				c;
	VEquationPtr		pEq;

	CGaugePtr	pGauge = new CGauge;

	CElementPtr	pElem = new CElement;
	pGauge->AddRenderable( pElem );

	CPositionPtr	pPosition;
	pPosition = new CPosition;
	pPosition->SetPointValue( 0, 100 );
	pElem->AddRenderable( pPosition );

	CPolylinePtr pPoly = new CPolyline;
	pElem->AddRenderable( pPoly );
	c = CColor::ColorFromName( "green" );
	pPoly->Style()->SetLineColor( c );
	pPoly->Style()->SetLineWidth( 3 );

	float	x = 0;
	float	fStep = 40;

	CPointValuePtr	pPoint;
	pPoint = new CPointValue;
	pPoint->SetPointValue( x, 0 );
	pPoly->AddPoint( pPoint );
	x += fStep;


	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "100 (T:PULSER) - 25 -" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->Y()->SetEquation( pEq );
	pPoint->X()->SetValue( CVariantData( x ) );
	pPoly->AddPoint( pPoint );
	x += fStep;

	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER) 1.5 * 50 -" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->Y()->SetEquation( pEq );
	pPoint->X()->SetValue( CVariantData( x ) );
	pPoly->AddPoint( pPoint );
	x += fStep;

	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER) 2.0 / 50 -" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->Y()->SetEquation( pEq );
	pPoint->X()->SetValue( CVariantData( x ) );
	pPoly->AddPoint( pPoint );
	x += fStep;

	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER) 1.5 * /-/ 50 +" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->Y()->SetEquation( pEq );
	pPoint->X()->SetValue( CVariantData( x ) );
	pPoly->AddPoint( pPoint );
	x += fStep;

	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER)" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->Y()->SetEquation( pEq );
	pPoint->X()->SetValue( CVariantData( x ) );
	pPoly->AddPoint( pPoint );
	x += fStep;

	pPoint = new CPointValue;
	pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_COORDINATE, "(T:PULSER) 1.25 * 50 - /-/" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();
	pPoint->Y()->SetEquation( pEq );
	pPoint->X()->SetValue( CVariantData( x ) );
	pPoly->AddPoint( pPoint );
	x += fStep;

	pPoint = new CPointValue;
	pPoint->SetPointValue( x, 0 );
	pPoly->AddPoint( pPoint );


	pGauge->SetSize( long(x), 300 );

	if ( bGVars )
		pGauge->AllocateLocalData();


	return pGauge;
}

CGaugePtr
		CFactoryGaugeTester::Get_simpletest()
{
	bool	bGVars = false;

	CGaugePtr	pGauge = new CGauge;
	pGauge->SetSize( 100, 100 );

	CLinePtr		pLine = new CLine;
	pGauge->AddRenderable( pLine );


	VEquationPtr pEq = m_pFactoryEquation->MakeEquation( CFactoryEquation::E_UNDEFINED,
		"(T:MILLI) 800 % 600 <" );
	bGVars = bGVars  ||  m_pFactoryEquation->HasGVariables();

	CVisiblePtr	pVis = new CVisible;
	pVis->SetEquation( pEq );
	pGauge->AddRenderable( pVis );



	CPolygonPtr pPoly = new CPolygon;
	pGauge->AddRenderable( pPoly );
	CColor c = CColor::ColorFromName( "red" );
	pPoly->Style()->SetLineColor( c );
	pPoly->Style()->SetLineWidth( 1 );
	pPoly->Style()->SetFillColor( c );

	CPointValuePtr	pPoint;
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 90, 0 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 90, 70 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 70 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 0, 0 );
	pPoly->AddPoint( pPoint );


	pPoly = new CPolygon;
	pGauge->AddRenderable( pPoly );
	c = CColor::ColorFromName( "black" );
	pPoly->Style()->SetLineColor( c );
	pPoly->Style()->SetLineWidth( 1 );
	pPoly->Style()->SetFillColor( c );

	//CPointValuePtr	pPoint;
	pPoint = new CPointValue;
	pPoint->SetPointValue( 10, 20 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 20 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 25 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 70, 20 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 80, 22 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 80, 28 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 70, 25 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 35 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 50, 50 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 10, 50 );
	pPoly->AddPoint( pPoint );
	pPoint = new CPointValue;
	pPoint->SetPointValue( 10, 20 );
	pPoly->AddPoint( pPoint );




	CGaugeTextPtr	pText = new CGaugeText;
	pText->Point()->SetPointValue( 45, 70+2 );
	pText->SetAlign( VDraw::A_CENTER );
	pText->SetVertAlign( VDraw::V_TOP );
	pText->SetFontHeight( 15.0 );
	pText->SetFontName( "Arial" );
	pText->Style()->SetLineColor( CColor::ColorFromName( "red" ) );

	CGaugeStringPtr	pString = new CGaugeString;
	pString->SetValue( CVariantData( "OIL PRESSURE" ) );
	pText->AddString( pString );
	pGauge->AddRenderable( pText );






	if ( bGVars )
		pGauge->AllocateLocalData();

	return pGauge;
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

CGaugePtr
		CFactoryGaugeTester::Get
		(
		void
		)
{
	switch ( m_nSelected )
	{
	case 1:
		return Get_test();
	case 2:
		return Get_simpletest();
	case 3:
		return Get_slider();
	case 4:
		return Get_sliderHider();
	case 5:
		return Get_dial();
	default:
		return 0;
	}
}

}}


#endif	// FILE RETIRED

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author) J.Griswold  --  01-Jun-2009

\+---------------------------------------------------------------------*/
