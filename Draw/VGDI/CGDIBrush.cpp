/*---------------------------------------------------------------------+\
|
|	CGDIBrush.cpp  --  brief description of what CGDIBrush.cpp is for
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
#include "CGDIBrush.h"

using namespace Yogi::Core;
namespace Yogi { namespace Common {
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

 * CGDIBrush - constructor

\+---------------------------------------------------------------------*/
CGDIBrush::CGDIBrush
		(
		void
		)
		: inherited()
		, m_hBrush( 0 )
		, m_tParams()
{
}

CGDIBrush::CGDIBrush
		(
		ConstCColorRef	rColor
		)
		: inherited()
		, m_hBrush( 0 )
		, m_tParams( rColor )
{
}

/*---------------------------------------------------------------------+\

 * CGDIBrush - copy constructor

\+---------------------------------------------------------------------*/
CGDIBrush::CGDIBrush
		(
		CGDIBrushRef	r
		)
		: inherited( r )
		, m_hBrush( r.m_hBrush )
		, m_tParams( r.m_tParams )
{
	r.Deselect();
	r.m_hBrush = 0;
}

/*---------------------------------------------------------------------+\

 * ~CGDIBrush - destructor

\+---------------------------------------------------------------------*/
CGDIBrush::~CGDIBrush
		(
		void
		)
{
	BrushDelete();
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CGDIBrushRef
		CGDIBrush::operator=
		(
		CGDIBrushRef	r
		)
{
	inherited::operator = ( r );

	SetParameters( r.m_tParams.oColor );

	m_hBrush = r.m_hBrush;
	r.Deselect();
	r.m_hBrush = 0;

	return *this;
}


bool	CGDIBrush::SetParameters
		(
		ConstCColorRef oColor
		)
{
	bool	bResult = false;

	if ( ! m_hBrush )
	{
		m_tParams.oColor = oColor;
		m_nHash = m_tParams.Hash();

		bResult = true;
	}

	return bResult;
}

HBRUSH	CGDIBrush::ToHBRUSH
		(
		void
		)
{
	if ( ! m_hBrush )
		BrushCreate();
	return m_hBrush;
}

bool	CGDIBrush::BrushCreate
		(
		void
		)
{
	bool	bResult = true;

	if ( ! m_hBrush )
	{
		LOGBRUSH	brush = {0};

		if ( m_tParams.oColor.IsNonColor()  )
		{
			brush.lbStyle = BS_NULL;
			brush.lbColor = 0;
			m_hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
		else
		{
			brush.lbStyle = BS_SOLID;

			unsigned	r = m_tParams.oColor.GetRed();
			unsigned	g = m_tParams.oColor.GetGreen();
			unsigned	b = m_tParams.oColor.GetBlue();
			brush.lbColor = RGB( r, g, b );
			brush.lbHatch = static_cast<ULONG_PTR>(~0);
			m_hBrush = ::CreateBrushIndirect( &brush );
		}
		if ( ! m_hBrush )
			bResult = false;
	}

	return bResult;
}

bool	CGDIBrush::BrushDelete
		(
		void
		)
{
	if ( m_hBrush )
	{
		Deselect();
		::DeleteObject( m_hBrush );
		m_hBrush = 0;
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
bool	CGDIBrush::Select
		(
		HDC h
		)
{
	bool	bResult = false;

	if ( BrushCreate() )
	{
		if ( ! m_hdc  &&  ! m_hPrev )
		{
			m_hdc = h;
			m_hPrev = ::SelectObject( m_hdc, m_hBrush );
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
bool	CGDIBrush::Deselect
		(
		void
		)
{
	if ( m_hBrush  &&  m_hPrev  &&  m_hdc )
	{
		::SelectObject( m_hdc, m_hPrev );
		m_hPrev = NULL;
		m_hdc = 0;
	}
	return true;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
