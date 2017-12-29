/*---------------------------------------------------------------------+\
|
|	CGauge.cpp  --  brief description of what CGauge.cpp is for
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	13-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the 'Frequency' node
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CGauge.h"

#include "CDrawQueue.h"
#include "CDictPageLazyLoad.h"
#include "CDictionaryMemory.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
//USING_NAMESPACE_COMMON
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

 * CGauge - constructor

\+---------------------------------------------------------------------*/
CGauge::CGauge
		(
		void
		)
		: VPanelChild(),
		m_pLocalData( 0 ),
		m_aList(),
		m_pMouseAreaList( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CGauge - copy constructor

\+---------------------------------------------------------------------*/
CGauge::CGauge
		(
		CGaugeRef	r
		)
		: VPanelChild( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CGauge - destructor

\+---------------------------------------------------------------------*/
CGauge::~CGauge
		(
		void
		)
{
	if ( m_pLocalData )
	{
		m_pLocalData->Release();
		//delete m_pLocalData;
	}

	VRenderablePtr*	p = m_aList.PointArray();
	VRenderablePtr*	pEnd = p + m_aList.Length();

	while ( p < pEnd )
	{
		if ( *p )
			delete *p;
		++p;
	}

	if ( m_pMouseAreaList )
		delete m_pMouseAreaList;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CGaugeRef
		CGauge::operator=
		(
		CGaugeRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * AddRenderable -

\+---------------------------------------------------------------------*/
bool	CGauge::AddRenderable
		(
		VRenderablePtr pComp
		)
{
	bool	bResult = false;
	index_t	n = (index_t)m_aList.Length();
	VRenderablePtr*	p = m_aList.PointItem( n );

	if ( p )
	{
		*p = pComp;
		bResult = true;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * AllocateLocalData -

\+---------------------------------------------------------------------*/
bool	CGauge::AllocateLocalData
		(
		void
		)
{
	m_pLocalData = new CDictPageLazyLoad;
	if ( m_pLocalData )
	{
		m_pLocalData->AddRef();
		return true;
	}
	else
	{
		return false;
	}
}



/*---------------------------------------------------------------------+\

 * MouseAreaList -

\+---------------------------------------------------------------------*/
CMouseAreaListPtr
		CGauge::MouseAreaList
		(
		void
		)
{
	if ( ! m_pMouseAreaList )
		m_pMouseAreaList = new CMouseAreaList;
	return m_pMouseAreaList;
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


/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
int		CGauge::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int		nResult = VRDR_CALCULATE_NONE;

	if ( CanCalculate( pDict ) )
	{
		VRenderablePtr	*p = m_aList.PointArray();
		VRenderablePtr	*pEnd = p + m_aList.Length();

		pDict->PushDictionaryPage( m_pLocalData );

		VDictionaryPtr		pDictMem = pDict;
		CDictionaryMemory	tDictMemory( pDict, this );		// setup local registers
		if ( 'M' != pDict->GetType() )
			pDictMem = &tDictMemory;

		nResult |= VPanelChild::Calculate( pDictMem );

		while ( p < pEnd )
		{
			if ( *p )
				nResult |= (*p)->Calculate( pDictMem );
			++p;
		}

		if ( m_pMouseAreaList )
			m_pMouseAreaList->Calculate( pDictMem );


		pDict->PopDictionaryPage();

	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CGauge::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool			bResult = true;
	VRenderablePtr	*p = m_aList.PointArray();

	if ( p )
	{
		VRenderablePtr	*pEnd = p + m_aList.Length();
		CDrawQueue	tQueue;

		pDict->PushDictionaryPage( m_pLocalData );

		VDictionaryPtr		pDictMem = pDict;
		CDictionaryMemory	tDictMemory( pDict, this );		// setup local registers
		if ( 'M' != pDict->GetType() )
			pDictMem = &tDictMemory;

		if ( m_bCropped )
		{
			GFLOAT	w, h;

			w = m_tSize.GetX();
			h = m_tSize.GetY();

			tQueue.SetCropRectangle( 0, 0, w, h );

			//pDraw->PushCropRectangle( 0, 0, long(w), long(h) );
		}

		while ( p < pEnd )
		{
			if ( *p )
			{
				bResult = (*p)->PreRender( pDictMem, &tQueue );
				if ( !bResult )
					break;
			}
			++p;
		}
		if ( bResult )
			bResult = tQueue.RenderGraphics( pDictMem, pDraw );

		//if ( m_bCropped )
		//	pDraw->PopCropRectangle();

		pDict->PopDictionaryPage();
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetChildContext -

\+---------------------------------------------------------------------*/
int		CGauge::GetChildContext
		(
		void
		)
{
	int		m = 0;
	VRenderablePtr*	h = m_aList.PointArray();
	if ( h )
	{
		VRenderablePtr*	hEnd = h + m_aList.Length();
		while ( h < hEnd )
		{
			m = (*h)->GetChildContext();
			IncludeContext( m );
			++h;
		}
	}
	return VPanelChild::GetChildContext();
}





/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	CGauge::ProcessEvent
		(
		VDictionaryPtr			pDict,
		VDictionary::Selector	vEvent
		)
{
	bool			bResult = false;

	pDict->PushDictionaryPage( m_pLocalData );

	VDictionaryPtr		pDictMem = pDict;
	CDictionaryMemory	tDictMemory( pDict, this );		// setup local registers
	if ( 'M' != pDict->GetType() )
		pDictMem = &tDictMemory;

	// the real work is done by the base class
	bResult = VPanelChild::ProcessEvent( pDictMem, vEvent );

	pDict->PopDictionaryPage();
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	CGauge::ProcessMouse
		(
		VDictionaryPtr	pDict,
		CMouseLocatePtr	pMouseLocate
		)
{
	bool			bResult = false;

	if ( m_pMouseAreaList )
	{
		pDict->PushDictionaryPage( m_pLocalData );

		VDictionaryPtr		pDictMem = pDict;
		CDictionaryMemory	tDictMemory( pDict, this );		// setup local registers
		if ( 'M' != pDict->GetType() )
			pDictMem = &tDictMemory;

		bResult = m_pMouseAreaList->ProcessMouse( pDictMem, pMouseLocate );

		pDict->PopDictionaryPage();
	}

	return bResult;
}




NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

