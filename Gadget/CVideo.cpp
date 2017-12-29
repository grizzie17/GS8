/*---------------------------------------------------------------------+\
|
|	CVideo.cpp  --  brief description of what CVideo.cpp is for
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
	28-Mar-2010			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CVideo.h"
#include "UMachine.h"
#if defined( OS_MSWIN )
#	include <olectl.h>
#	include <ole2.h>
#endif
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

 * CVideo - constructor

\+---------------------------------------------------------------------*/
CVideo::CVideo
		(
		void
		)
		: VGraphic(),
		m_tSource(),
		m_tOrigin(),
		m_tSize(),
		m_eAlign( VDraw::A_CENTER ),
		m_eVertAlign( VDraw::V_MIDDLE ),
		m_eFitment( VDraw::F_FILL ),
		m_tMirror()
{
}

/*---------------------------------------------------------------------+\

 * CVideo - copy constructor

\+---------------------------------------------------------------------*/
CVideo::CVideo
		(
		CVideoRef	r
		)
		: VGraphic( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CVideo - destructor

\+---------------------------------------------------------------------*/
CVideo::~CVideo
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVideoRef
		CVideo::operator=
		(
		CVideoRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * Origin -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CVideo::Source
		(
		void
		)
{
	return &m_tSource;
}


/*---------------------------------------------------------------------+\

 * Origin -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CVideo::Origin
		(
		void
		)
{
	return &m_tOrigin;
}


/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
CSizePtr
		CVideo::Size
		(
		void
		)
{
	return &m_tSize;
}

/*---------------------------------------------------------------------+\

 * SetAlign -

\+---------------------------------------------------------------------*/
void	CVideo::SetAlign
		(
		VDraw::EAlignments e
		)
{
	m_eAlign = e;
}


/*---------------------------------------------------------------------+\

 * SetVertAlign -

\+---------------------------------------------------------------------*/
void	CVideo::SetVertAlign
		(
		VDraw::EVerticalAlignments e
		)
{
	m_eVertAlign = e;
}


/*---------------------------------------------------------------------+\

 * SetFitment -

\+---------------------------------------------------------------------*/
void	CVideo::SetFitment
		(
		VDraw::EFitments	e
		)
{
	m_eFitment = e;
}


/*---------------------------------------------------------------------+\

 * SetMirror -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CVideo::Mirror
		(
		void
		)
{
	return &m_tMirror;
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
int		CVideo::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	if ( m_tSource.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	nResult |= m_tOrigin.Calculate( pDict );
	nResult |= m_tSize.Calculate( pDict );
	if ( m_tMirror.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CVideo::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = VGraphic::Render( pDict, pDraw );
	if ( bResult )
	{
		CVariantData	vSource;
		GFLOAT	x;
		GFLOAT	y;
		GFLOAT	nWidth;
		GFLOAT	nHeight;
		bool	bMirror;

		vSource = m_tSource.GetCachedValue();

		x = m_tOrigin.GetX();
		y = m_tOrigin.GetY();

		nWidth = m_tSize.GetX();
		nHeight = m_tSize.GetY();

		bMirror = m_tMirror.GetCachedValue();

		pDraw->Video( x, y, nWidth, nHeight,
					vSource,
					m_eFitment, m_eAlign, m_eVertAlign,
					bMirror );


	}
	return bResult;
}



NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

