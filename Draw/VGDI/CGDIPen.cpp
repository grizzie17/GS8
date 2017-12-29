/*---------------------------------------------------------------------+\
|
|	CGDIPen.cpp  --  brief description of what CGDIPen.cpp is for
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
	29-Jun-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "CGDIPen.h"

NAMESPACE_COMMON_BEGIN
/*---------------------------------------------------------------------+\
|								
|	Local defines / constants	
|								
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Local Type Definitions	
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Private Global Variables
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Public Global Variables	
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|						
|	External Variables	
|						
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||			
||	 Code	
||			
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CGDIPen - constructor

\+---------------------------------------------------------------------*/
CGDIPen::CGDIPen
		(
		void
		)
		: inherited()
		, m_hPen( 0 )
		, m_bStock( false )
		, m_tParams()
{
}

CGDIPen::CGDIPen
		(
		ConstCColorRef	rColor,
		long			nWidth
		)
		: inherited()
		, m_hPen( 0 )
		, m_bStock( false )
		, m_tParams( rColor, nWidth )
{
}

/*---------------------------------------------------------------------+\

 * CGDIPen - copy constructor

\+---------------------------------------------------------------------*/
CGDIPen::CGDIPen
		(
		CGDIPenRef	r
		)
		: inherited( r )
		, m_hPen( r.m_hPen )
		, m_bStock( r.m_bStock )
		, m_tParams( r.m_tParams )
{
	r.Deselect();
	r.m_hPen = 0;
}

/*---------------------------------------------------------------------+\

 * ~CGDIPen - destructor

\+---------------------------------------------------------------------*/
CGDIPen::~CGDIPen
		(
		void
		)
{
	PenDelete();
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CGDIPenRef
		CGDIPen::operator=
		(
		CGDIPenRef	r
		)
{
	inherited::operator = ( r );

	SetParameters( r.m_tParams.oColor, r.m_tParams.nWidth );

	m_hPen = r.m_hPen;
	r.Deselect();
	r.m_hPen = 0;

	return *this;
}


bool	CGDIPen::SetParameters
		(
		ConstCColorRef oColor,
		long nWidth 
		)
{
	bool	bResult = false;

	if ( ! m_hPen )
	{
		m_tParams.oColor = oColor;
		m_tParams.nWidth = nWidth;
		m_nHash = m_tParams.Hash();

		bResult = true;
	}

	return bResult;
}

HPEN	CGDIPen::ToHPEN
		(
		void
		)
{
	if ( ! m_hPen )
		PenCreate();
	return m_hPen;
}

bool	CGDIPen::PenCreate
		(
		void 
		)
{
	bool	bResult = true;

	if ( ! m_hPen )
	{
		LOGPEN	params = {0};

		if ( m_tParams.oColor.IsNonColor()  ||  m_tParams.nWidth < 1 )
		{
			params.lopnStyle = PS_NULL;
			params.lopnColor = 0;
			m_hPen = (HPEN)::GetStockObject( NULL_PEN );
			m_bStock = true;
		}
		else
		{
			params.lopnStyle = PS_SOLID;

			unsigned	r = m_tParams.oColor.GetRed();
			unsigned	g = m_tParams.oColor.GetGreen();
			unsigned	b = m_tParams.oColor.GetBlue();
			params.lopnColor = RGB( r, g, b );

			params.lopnWidth.x = m_tParams.nWidth;
			params.lopnWidth.y = m_tParams.nWidth;

			m_hPen = ::CreatePenIndirect( &params );
		}
		if ( ! m_hPen )
			bResult = false;
	}

	return bResult;
}

bool	CGDIPen::PenDelete
		( 
		void
		)
{
	if ( m_hPen )
	{
		Deselect();
		::DeleteObject( m_hPen );
		m_hPen = 0;
	}
	return true;
}





/*=====================================================================+\
||	 protected member functions
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions
\+=====================================================================*/

/*=====================================================================+\
||				
||	 Overrides	
||				
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * Select -

\+---------------------------------------------------------------------*/
//virtual
bool	CGDIPen::Select
		(
		HDC h 
		)
{
	bool	bResult = false;

	if ( PenCreate() )
	{
		if ( ! m_hdc  &&  ! m_hPrev )
		{
			m_hdc = h;
			m_hPrev = ::SelectObject( m_hdc, m_hPen );
			if ( m_hPrev )
				bResult = true;
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * Deselect -

\+---------------------------------------------------------------------*/
//virtual
bool	CGDIPen::Deselect
		(
		void 
		)
{
	if ( m_hPen  &&  m_hPrev  &&  m_hdc )
	{
		::SelectObject( m_hdc, m_hPrev );
		m_hPrev = NULL;
		m_hdc = 0;
	}
	return true;
}



NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

