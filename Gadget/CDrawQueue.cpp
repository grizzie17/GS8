/*---------------------------------------------------------------------+\
|
|	CDrawQueue.cpp  --  brief description of what CDrawQueue.cpp is for
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
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	30-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDrawQueue.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
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

 * CDrawQueue - constructor

\+---------------------------------------------------------------------*/
CDrawQueue::CDrawQueue
		(
		void
		)
		//:
		//m_nCropLeft( 0.0f ),
		//m_nCropTop( 0.0f ),
		//m_nCropRight( 0.0f ),
		//m_nCropBottom( 0.0f )
		: m_bCropped( false )
		, m_nXPosition( 0 )
		, m_nYPosition( 0 )
		, m_nXShift( 0 )
		, m_nYShift( 0 )
		, m_nXAxis( 0 )
		, m_nYAxis( 0 )
		, m_fRotation( 0.0 )
		, m_fScale( 0.0 )
		, m_bVisible( true )
		, m_aGraphics()
{
	m_aGraphics.SetBlockSize( 16 );
}

/*---------------------------------------------------------------------+\

 * CDrawQueue - copy constructor

\+---------------------------------------------------------------------*/
CDrawQueue::CDrawQueue
		(
		CDrawQueueRef
		)
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CDrawQueue - destructor

\+---------------------------------------------------------------------*/
CDrawQueue::~CDrawQueue
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

bool	CDrawQueue::SetCropRectangle
		(
		float left,
		float top,
		float right,
		float bottom
		)
{
	m_nCropLeft = left;
	m_nCropTop = top;
	m_nCropRight = right;
	m_nCropBottom = bottom;
	m_bCropped = true;

	return true;
}


/*---------------------------------------------------------------------+\

 * SetPosition -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::SetPosition
		(
		float	x,
		float	y
		)
{
	m_nXPosition = x;
	m_nYPosition = y;
	return true;
}

/*---------------------------------------------------------------------+\

 * SetAxis -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::SetAxis
		(
		float x,
		float y
		)
{
	m_nXAxis = x;
	m_nYAxis = y;
	return true;
}

/*---------------------------------------------------------------------+\

 * SetShift -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::SetShift
		(
		float x,
		float y
		)
{
	m_nXShift = x;
	m_nYShift = y;
	return true;
}

/*---------------------------------------------------------------------+\

 * SetRotation -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::SetRotation
		(
		float fRadians
		)
{
	m_fRotation = fRadians;
	return true;
}

/*---------------------------------------------------------------------+\

 * SetScale -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::SetScale
		(
		float fScale
		)
{
	m_fScale = fScale;
	return true;
}


/*---------------------------------------------------------------------+\

 * SetVisible -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::SetVisible
		(
		bool	bVisible
		)
{
	m_bVisible = bVisible;
	return true;
}


/*---------------------------------------------------------------------+\

 * AddGraphic -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::AddGraphic
		(
		VRenderablePtr pGraphic
		)
{
	if ( m_bVisible )
		m_aGraphics.AppendData( &pGraphic );
	return true;
}


/*---------------------------------------------------------------------+\

 * RenderGraphics -

\+---------------------------------------------------------------------*/
bool	CDrawQueue::RenderGraphics
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = true;
	if ( m_bVisible )
	{
		size_t	n = m_aGraphics.Length();
		if ( 0 < n )
		{
			pDraw->push( m_nXPosition, m_nYPosition,
						m_nXShift, m_nYShift,
						m_nXAxis, m_nYAxis,
						m_fRotation, m_fScale );

			if ( m_bCropped )
				pDraw->PushCropRectangle( long(m_nCropLeft), long(m_nCropTop),
										long(m_nCropRight), long(m_nCropBottom) );

			VRenderablePtr*	p = m_aGraphics.PointArray();
			VRenderablePtr*	pEnd = p + n;

			while ( p < pEnd )
			{
				bResult = (*p)->Render( pDict, pDraw );
				if ( ! bResult )
					break;
				++p;
			}

			pDraw->pop();

			if ( m_bCropped )
				pDraw->PopCropRectangle();
		}
	}
	return bResult;
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




}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
