/*---------------------------------------------------------------------+\
|
|	CGDIFont.cpp  --  brief description of what CGDIFont.cpp is for
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
#include "CGDIFont.h"

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

 * CGDIFont - constructor

\+---------------------------------------------------------------------*/
CGDIFont::CGDIFont
		(
		void
		)
		: inherited()
		, m_hFont( 0 )
		, m_tParams()
{
}

CGDIFont::CGDIFont
		(
		ConstCCharDescriptorRef	rName,
		unsigned long			nHeight
		)
		: inherited()
		, m_hFont( 0 )
		, m_tParams( rName, nHeight )
{
}


CGDIFont::CGDIFont
		(
		const char*		sName,
		unsigned long	nHeight
		)
		: inherited()
		, m_hFont( 0 )
		, m_tParams( sName, nHeight )
{
}

/*---------------------------------------------------------------------+\

 * CGDIFont - copy constructor

\+---------------------------------------------------------------------*/
CGDIFont::CGDIFont
		(
		CGDIFontRef	r
		)
		: inherited( r )
		, m_hFont( r.m_hFont )
		, m_tParams( r.m_tParams )
{
	r.Deselect();
	r.m_hFont = 0;
}

/*---------------------------------------------------------------------+\

 * ~CGDIFont - destructor

\+---------------------------------------------------------------------*/
CGDIFont::~CGDIFont
		(
		void
		)
{
	FontDelete();
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CGDIFontRef
		CGDIFont::operator=
		(
		CGDIFontRef	r
		)
{
	inherited::operator = ( r );

	SetParameters( r.m_tParams.sName, r.m_tParams.nHeight );

	m_hFont = r.m_hFont;
	r.Deselect();
	r.m_hFont = 0;

	return *this;
}


bool	CGDIFont::SetParameters
		(
		ConstCCharDescriptorRef	rName,
		unsigned long			nHeight
		)
{
	bool	bResult = false;

	if ( ! m_hFont )
	{
		rName.CopyTo( m_tParams.sName, sizeof(m_tParams.sName) );
		m_tParams.nHeight = nHeight;
		m_nHash = m_tParams.Hash();

		bResult = true;
	}

	return bResult;
}

bool	CGDIFont::SetParameters
		(
		const char*		sName,
		unsigned long	nHeight
		)
{
	bool	bResult = false;

	if ( ! m_hFont )
	{
		strcpy_s( m_tParams.sName, sizeof(m_tParams.sName), sName );
		m_tParams.nHeight = nHeight;
		m_nHash = m_tParams.Hash();

		bResult = true;
	}

	return bResult;
}

HFONT	CGDIFont::ToHFONT
		(
		void
		)
{
	if ( ! m_hFont )
		FontCreate();
	return m_hFont;
}

bool	CGDIFont::FontCreate
		(
		void 
		)
{
	bool	bResult = true;

	if ( ! m_hFont )
	{
#if defined( OS_MSWIN_WCE )
		LOGFONT		f = {0};

		f.lfHeight = m_tParams.nHeight;
		TArrayPointer<WCHAR> wsFont = ::WideStringFromString( m_tParams.sName );
		::wcscpy_s( f.lfFaceName, sizeof(f.lfFaceName), wsFont );

		m_hFont = CreateFontIndirectW( &f );
#else
		LOGFONTA	f = {0};

		f.lfHeight = (LONG)m_tParams.nHeight;
		strcpy_s( f.lfFaceName, sizeof(f.lfFaceName), m_tParams.sName );

		m_hFont = ::CreateFontIndirectA( &f );
#endif
		if ( ! m_hFont )
			bResult = false;
	}

	return bResult;
}

bool	CGDIFont::FontDelete
		( 
		void
		)
{
	if ( m_hFont )
	{
		Deselect();
		::DeleteObject( m_hFont );
		m_hFont = 0;
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
bool	CGDIFont::Select
		(
		HDC h 
		)
{
	bool	bResult = false;

	if ( FontCreate() )
	{
		if ( ! m_hdc  &&  ! m_hPrev )
		{
			m_hdc = h;
			m_hPrev = ::SelectObject( m_hdc, m_hFont );
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
bool	CGDIFont::Deselect
		(
		void 
		)
{
	if ( m_hFont  &&  m_hPrev  &&  m_hdc )
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

