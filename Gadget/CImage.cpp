/*---------------------------------------------------------------------+\
|
|	CImage.cpp  --  brief description of what CImage.cpp is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CImage.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
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

 * CImage - constructor

\+---------------------------------------------------------------------*/
CImage::CImage
		(
		void
		)
		: VGraphic()
		, m_sFile()
		, m_tOrigin()
		, m_tSize()
		, m_eAlign( IDraw::A_LEFT )
		, m_eVertAlign( IDraw::V_TOP )
		, m_eFitment( IDraw::F_SCALED )
		, m_pImage( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CImage - copy constructor

\+---------------------------------------------------------------------*/
CImage::CImage
		(
		CImageRef	r
		)
		: VGraphic( r )
		, m_sFile( r.m_sFile )
		, m_tOrigin( r.m_tOrigin )
		, m_tSize( r.m_tSize )
		, m_eAlign( r.m_eAlign )
		, m_eVertAlign( r.m_eVertAlign )
		, m_eFitment( r.m_eFitment )
		, m_pImage( 0 )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CImage - destructor

\+---------------------------------------------------------------------*/
CImage::~CImage
		(
		void
		)
{
	if ( m_pImage )
		m_pImage->Destroy();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CImageRef
		CImage::operator=
		(
		CImageRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}



/*---------------------------------------------------------------------+\

 * Origin -

\+---------------------------------------------------------------------*/
ConstCCharStringPtr
		CImage::File
		(
		void
		)
{
	return &m_sFile;
}


/*---------------------------------------------------------------------+\

 * Origin -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CImage::Origin
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
		CImage::Size
		(
		void
		)
{
	return &m_tSize;
}

/*---------------------------------------------------------------------+\

 * SetAlign -

\+---------------------------------------------------------------------*/
void	CImage::SetAlign
		(
		VDraw::EAlignments e
		)
{
	m_eAlign = e;
}


/*---------------------------------------------------------------------+\

 * SetVertAlign -

\+---------------------------------------------------------------------*/
void	CImage::SetVertAlign
		(
		VDraw::EVerticalAlignments e
		)
{
	m_eVertAlign = e;
}


/*---------------------------------------------------------------------+\

 * SetFitment -

\+---------------------------------------------------------------------*/
void	CImage::SetFitment
		(
		VDraw::EFitments	e
		)
{
	m_eFitment = e;
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
int		CImage::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	nResult |= m_tOrigin.Calculate( pDict );
	nResult |= m_tSize.Calculate( pDict );
	return nResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CImage::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = VGraphic::Render( pDict, pDraw );
	if ( bResult )
	{
		if ( 0 < m_sFile.Length() )
		{
			GFLOAT	x;
			GFLOAT	y;
			GFLOAT	nWidth;
			GFLOAT	nHeight;

			x = m_tOrigin.GetX();
			y = m_tOrigin.GetY();

			nWidth = m_tSize.GetX();
			nHeight = m_tSize.GetY();

			if ( ! m_pImage )
			{
				pDraw->ImageLoadFile( m_sFile.Pointer(), &m_pImage );
			}
			if ( m_pImage )
				pDraw->ImagePreloaded( x, y, nWidth, nHeight, m_pImage,
									m_eFitment, m_eAlign, m_eVertAlign );
			else
				pDraw->Image( x, y, nWidth, nHeight, m_sFile.Pointer(),
							m_eFitment, m_eAlign, m_eVertAlign );
		}


	}
	return bResult;
}




}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
