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
|	CFactoryPanelTester.cpp  --  FILE RETIRED
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
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#if 0	// FILE RETIRED


#include "stdafx.h"
#include "CFactoryPanelTester.h"
#include "CFactoryGaugeTester.h"
#include "CFactoryGauge.h"
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

 * <summary>CFactoryPanelTester - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  19-Jul-2009

\+---------------------------------------------------------------------*/
CFactoryPanelTester::CFactoryPanelTester
		(
		void
		)
		: m_pFactoryGauge( 0 )
{
	m_pFactoryGauge = FactoryGauge();
}


/**--------------------------------------------------------------------+\

 * <summary>~CFactoryPanelTester - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  19-Jul-2009

\+---------------------------------------------------------------------*/
CFactoryPanelTester::~CFactoryPanelTester
		(
		void
		)
{
	if ( m_pFactoryGauge )
		delete m_pFactoryGauge;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


CPanelPtr
		CFactoryPanelTester::Make
		(
		char *sName
		)
{
	CPanelPtr	pPanel = new CPanel;
	CGaugePtr	pGauge;
	long		nPadding = 10;
	long		nMargin = 10;
	long		w;
	long		h;
	float		x = float(nPadding + nMargin);
	float		y = float(nPadding + nMargin);
	long		nRow = 0;

	CFactoryGauge	tRealFactory;

	pGauge = tRealFactory.Make( "gauges/arcs" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}

	pGauge = tRealFactory.Make( "gauges/dial" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}


	pGauge = tRealFactory.Make( "gauges/slider" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}



	pGauge = tRealFactory.Make( "gauges/sliderhider" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}


	pGauge = tRealFactory.Make( "gauges/oilpressurelight" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}


	pGauge = tRealFactory.Make( "gauges/snake" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}




	y += float(nMargin + nRow);
	x = float(nPadding + nMargin);

	pGauge = tRealFactory.Make( "gauges/rotary270" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}

	pGauge = tRealFactory.Make( "gauges/rotary" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}

	pGauge = tRealFactory.Make( "gauges/temperature" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}

	pGauge = tRealFactory.Make( "gauges/fuel" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}

	pGauge = tRealFactory.Make( "gauges/tempgreen" );
	if ( pGauge )
	{
		pGauge->GetSize( 0, w, h );
		pGauge->Position()->SetPointValue( x, y );
		pPanel->AddChild( pGauge );
		nRow = nRow < h ? h : nRow;
		x += float(w + nMargin);
	}



	return pPanel;
}





/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

VFactoryGaugePtr
		CFactoryPanelTester::FactoryGauge
		(
		void
		)
{
	if ( ! m_pFactoryGauge )
		m_pFactoryGauge = new CFactoryGaugeTester;
	return m_pFactoryGauge;

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
