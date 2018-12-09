/*---------------------------------------------------------------------+\
|
|	CGaugeText.cpp  --  Implementation of Text style
						(contains actual text)
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
	01-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Handle multiple string objects
		Changes to support V2 schema
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetFontName that uses descriptor to send the name instead
		of null terminated string.
	29-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		React to class hierarchy change for CCharString/CCharDescriptor
	02-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CGaugeText.h"

#include "UPlatform.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
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

 * CGaugeText - constructor

\+---------------------------------------------------------------------*/
CGaugeText::CGaugeText
		(
		void
		)
		: VGraphic(),
		m_pPoint( 0 ),
		m_nMaxLength( 0 ),
		m_tFontName(),
		m_tFontHeight(),
		m_eAlign( VDraw::A_LEFT ),
		m_eVertAlign( VDraw::V_BASELINE ),
		m_aStrings()
{
	m_tFontName = CCharDescriptor("sans-serif");
	m_tFontHeight.SetValue( CVariantData( GFLOAT_10 ) );
}

/*---------------------------------------------------------------------+\

 * CGaugeText - copy constructor

\+---------------------------------------------------------------------*/
CGaugeText::CGaugeText
		(
		CGaugeTextRef	r
		)
		: VGraphic( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CGaugeText - destructor

\+---------------------------------------------------------------------*/
CGaugeText::~CGaugeText
		(
		void
		)
{
	if ( m_pPoint )
		delete m_pPoint;

	CGaugeStringPtr*	p = m_aStrings.PointArray();
	if ( p )
	{
		CGaugeStringPtr*	pEnd = p + m_aStrings.Length();
		while ( p < pEnd )
		{
			if ( *p )
				delete (*p);
			++p;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * Point -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CGaugeText::Point
		(
		void
		)
{
	if ( ! m_pPoint )
		m_pPoint = new CPointValue;
	return m_pPoint;
}


/*---------------------------------------------------------------------+\

 * SetMaxLength -

\+---------------------------------------------------------------------*/
void	CGaugeText::SetMaxLength
		(
		long n
		)
{
	m_nMaxLength = n;
}


/*---------------------------------------------------------------------+\

 * SetFontName -

\+---------------------------------------------------------------------*/
void	CGaugeText::SetFontName
		(
		const char* s
		)
{
	m_tFontName = s;
}


/*---------------------------------------------------------------------+\

 * SetFontName -

\+---------------------------------------------------------------------*/
void	CGaugeText::SetFontName
		(
		CCharDescriptorRef r
		)
{
	m_tFontName = r;
}


/*---------------------------------------------------------------------+\

 * SetFontHeight -

\+---------------------------------------------------------------------*/
void	CGaugeText::SetFontHeight
		(
		float f
		)
{
	m_tFontHeight.SetValue( CVariantData( f ) );
}

/*---------------------------------------------------------------------+\

 * FontHeight -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CGaugeText::FontHeight
		(
		void
		)
{
	return &m_tFontHeight;
}


/*---------------------------------------------------------------------+\

 * SetAlign -

\+---------------------------------------------------------------------*/
void	CGaugeText::SetAlign
		(
		VDraw::EAlignments e
		)
{
	m_eAlign = e;
}


/*---------------------------------------------------------------------+\

 * SetVertAlign -

\+---------------------------------------------------------------------*/
void	CGaugeText::SetVertAlign
		(
		VDraw::EVerticalAlignments e
		)
{
	m_eVertAlign = e;
}


/*---------------------------------------------------------------------+\

 * AddString -

\+---------------------------------------------------------------------*/
void	CGaugeText::AddString
		(
		CGaugeStringPtr pString
		)
{
	CGaugeStringPtr* p = m_aStrings.AppendArray();
	if ( p )
		(*p) = pString;
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
int		CGaugeText::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	if ( m_tFontHeight.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;

	if ( m_pPoint )
		nResult |= m_pPoint->Calculate( pDict );

	CGaugeStringPtr*	p = m_aStrings.PointArray();
	if ( p )
	{
		CGaugeStringPtr*	pEnd = p + m_aStrings.Length();

		while ( p < pEnd )
		{
			if ( *p )
			{
				if ( (*p)->Calculate( pDict ) )
					nResult |= VRDR_CALCULATE_UNDETERMINED;
			}
			++p;
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CGaugeText::Render
		(
		VDictionaryPtr pDict,
		VDrawPtr pDraw
		)
{
	bool	bResult = VGraphic::Render( pDict, pDraw );
	if ( bResult )
	{
		GFLOAT	x;
		GFLOAT	y;

		x = m_pPoint->GetX();
		y = m_pPoint->GetY();

		CCharString		sText;
		GFLOAT	fHeight = m_tFontHeight.GetCachedValue();

		pDraw->FontParams( m_tFontName.Pointer(), fHeight );

		CGaugeStringPtr*	p = m_aStrings.PointArray();
		if ( p )
		{
			size_t	nStrings = m_aStrings.Length();
			if ( 1 < nStrings )
			{
				switch ( m_eVertAlign )
				{
				case VDraw::V_TOP:
					// we don't need to do anything
					break;
				case VDraw::V_ABSBOTTOM:
					y -= fHeight * (nStrings - 1);
					break;
				case VDraw::V_MIDDLE:
					y -= fHeight * (nStrings/2);
					break;
                default:
                    break;
				}
			}
			CGaugeStringPtr*	pEnd = p + nStrings;
			while ( p < pEnd )
			{
				if ( *p )
				{
					sText = (CCharDescriptorRef)(*p)->GetCachedValue();
					//sText = (*p)->GetCachedValue();
					long	n = long(sText.Length());
					if ( 0 < n )
					{
						//n = min( n, 0 < m_nMaxLength ? m_nMaxLength : n );
						//long	n = long(sText.Length());
						pDraw->TextString( x, y, m_eAlign, m_eVertAlign, sText.Pointer(), n );
					}
					y += fHeight;
				}
				++p;
			}
		}
	}
	return bResult;
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
