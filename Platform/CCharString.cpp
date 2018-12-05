/*---------------------------------------------------------------------+\
|
|	CCharString.cpp  --  Encapsulate a simple character string
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
	02-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Fixed a problem in AppendStringData that would allow a
		potential data overrun if a char-descriptor was passed in
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Use safer ClearString function to consistently delete the data
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Protect from null pointer in the Append function
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Disable warnings from MSVC++ regarding compatibility compiles
		as they relate to variable argument lists.
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	01-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add "AppendFormat" which formats a string (printf style) and
		then appends it to the existing string.
	29-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Split class to create a base class TCharDescriptor
	27-Aug-2009			J.Griswold
		Add support for new Format method that operates as a printf
		type functionality for loading the string.
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
//#include <string.h>
//#include <sys/types.h>
#include <stdarg.h>
#include <stdexcept>

#include "CCharString.h"
#include "TCharDescriptor.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformString.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Core {

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

 * CCharString - constructor

\+---------------------------------------------------------------------*/
CCharString::CCharString
		(
		)
		: inherited()
{
}

/*---------------------------------------------------------------------+\

 * CCharString - copy constructor

\+---------------------------------------------------------------------*/
CCharString::CCharString
		(
		ConstCCharStringRef	r
		)
		: inherited( r )
{
	//LoadCCharString( r );
}


/*---------------------------------------------------------------------+\

 * CCharString - copy constructor

\+---------------------------------------------------------------------*/
CCharString::CCharString
		(
		ConstCCharDescriptorRef r
		)
		: inherited()
{
	LoadCCharDescriptor( r );
}


/*---------------------------------------------------------------------+\

 * CCharString - load string constructor

\+---------------------------------------------------------------------*/
CCharString::CCharString
		(
		const char*	s
		)
		: inherited( s )
{
}

/*---------------------------------------------------------------------+\

 * CCharString - load string constructor

\+---------------------------------------------------------------------*/
CCharString::CCharString
		(
		const char*	s,
		size_t		n
		)
		: inherited()
{
	LoadStringData( s, (index_t)n );
}

/*---------------------------------------------------------------------+\

 * CCharString - load string constructor

\+---------------------------------------------------------------------*/
CCharString::CCharString
		(
		const std::string&	r
		) : inherited( r )
{
}

/*---------------------------------------------------------------------+\

 * ~CCharString - destructor

\+---------------------------------------------------------------------*/
CCharString::~CCharString
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/





/*---------------------------------------------------------------------+\

 * Append -

\+---------------------------------------------------------------------*/
bool	CCharString::Append
		(
		const char*	s
		)
{
	if ( s )
		return AppendStringData( s, (index_t)(::strlen( s )) );
	else
		return true;
}

/*---------------------------------------------------------------------+\

 * Append -

\+---------------------------------------------------------------------*/
bool	CCharString::Append
		(
		ConstCCharStringRef r
		)
{
	return AppendStringData( r.c_str(), (index_t)r.length() );
}


/*---------------------------------------------------------------------+\

 * Append -

\+---------------------------------------------------------------------*/
bool	CCharString::Append
		(
		ConstCCharDescriptorRef	r
		)
{
	return AppendStringData( r.Pointer(), (index_t)r.Length() );
}

/*---------------------------------------------------------------------+\

 * Append -

\+---------------------------------------------------------------------*/
bool	CCharString::Append
		(
		float	f
		)
{
	return AppendFormat( "%i", (int)f );
}



//	Disable the warning message from Microsoft C++ regarding their
//	new multi-language cross compiler format regarding variable
//	presence arguments.

BEGIN_IGNORE_WARNING( 4793 )

/*---------------------------------------------------------------------+\

 * AppendFormat - Process a "printf" like format string

\+---------------------------------------------------------------------*/
bool	CCharString::AppendFormat
		(
		const char*	sFormat,
		...
		)
{
	va_list	vargs;
	char	sTemp[128];
	va_start( vargs, sFormat );
	::vsnprintf_s( sTemp, sizeof(sTemp), sizeof(sTemp), sFormat, vargs );
	va_end( vargs );
	return Append( sTemp );
}


/*---------------------------------------------------------------------+\

 * Format - Process a "printf" like format string

\+---------------------------------------------------------------------*/
CCharStringRef
		CCharString::Format
		(
		const char*	sFormat,
		...
		)
{
	va_list	vargs;
	char	sTemp[128];
	va_start( vargs, sFormat );
	::vsnprintf_s( sTemp, sizeof(sTemp), sizeof(sTemp), sFormat, vargs );
	va_end( vargs );
	LoadStringData( sTemp );
	return *this;
}

END_IGNORE_WARNING






/*---------------------------------------------------------------------+\

 * ClearString -

\+---------------------------------------------------------------------*/
void	CCharString::ClearString
		(
		void
		)
{
	clear();
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * LoadCCharString -

\+---------------------------------------------------------------------*/
bool	CCharString::LoadCCharString
		(
		ConstCCharStringRef	r
		)
{
	bool	bResult = true;
	this->assign( r );
	// if ( this != &r )	// protect against self assignment
	// {
	// 	bResult = LoadStringData( r.m_s, (index_t)r.m_n );
	// }
	return bResult;
}


/*---------------------------------------------------------------------+\

 * LoadCCharDescriptor -

\+---------------------------------------------------------------------*/
bool	CCharString::LoadCCharDescriptor
		(
		ConstCCharDescriptorRef r
		)
{
	return LoadStringData( r.Pointer(), (index_t)r.Length() );
}



/*---------------------------------------------------------------------+\

 * LoadStringData -

\+---------------------------------------------------------------------*/
bool	CCharString::LoadStringData
		(
		const char*	s,
		index_t		nLen
		)
{
	bool	bResult = true;
	//if ( !m_s  ||  m_s != s )		// protect against self assignment
	//{
		if ( ValidAddr( s ) )
		{
			size_t	n;
			if ( nLen < 0 )
				n = ::strlen( s );
			else
				n = (size_t)nLen;
			if ( 0 < n )
			{
				this->assign( s, n );
			}
			else
			{
				ClearString();
			}
		}
		else
		{
			ClearString();
		}
	//}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * AppendStringData -

\+---------------------------------------------------------------------*/
bool	CCharString::AppendStringData
		(
		const char*	s,
		index_t		n
		)
{
//	bool	bResult = false;
	// size_t	nNew = n + m_n;
	// char*	pNew = new char[nNew + 1];

	this->append( s, n );
	// ::strncpy_s( pNew, nNew+1, m_s, m_n );
	// ::strncpy_s( pNew+m_n, (size_t)n+1, s, (size_t)n );

	// ClearString();
	// m_s = pNew;
	// m_n = nNew;

	return true;
}

/*---------------------------------------------------------------------+\

 * ValidAddr -

\+---------------------------------------------------------------------*/
bool	CCharString::ValidAddr
		(
		const char*	s
		)
{
	bool	bResult = false;
#if defined( _MSC_VER )
	__try
	{
		if ( s )
			bResult = true;
	}
	__except (EXCEPTION_ACCESS_VIOLATION)
	{
		;
	}
#else
	try
	{
		if ( s )
			bResult = true;
	}
	catch ( ... )
	{
		;
	}
#endif

	return bResult;
}

char	CCharString::AtIndex
		(
		index_t n
		) const
{
	if ( n < index_t(length()) )
		return *(c_str() + n);
	else
		return 0;
}

/*---------------------------------------------------------------------+\

 * Hash -

\+---------------------------------------------------------------------*/
uintmax_t
		CCharString::Hash
		(
		void
		) const
{
	CCharDescriptor s( c_str(), length() );

	return s.Hash();
}


bool	CCharString::CopyTo
		(
		char*	t,
		size_t	tc
		) const
{
	CCharDescriptor	s( c_str(), length() );
	return s.CopyTo( t, tc );
}


bool	CCharString::ConcatenateTo
		(
		char*	t,
		size_t	tc
		) const
{
	CCharDescriptor	s( c_str(), length() );
	return s.ConcatenateTo( t, tc );
}

int		CCharString::Compare
		(
		const char*	t
		) const
{
	CCharDescriptor	s( c_str(), length() );
	return s.Compare( t );
}

int		CCharString::Compare
		(
		const char*	t,
		size_t		tc
		) const
{
	CCharDescriptor	s( c_str(), length() );
	return s.Compare( t, tc );
}

int		CCharString::Compare
		(
		ConstCCharDescriptorRef	r
		) const
{
	return Compare( r.Pointer(), r.Length() );
}

int		CCharString::Compare
		(
		ConstCCharStringRef	r
		) const
{
	return Compare( r.c_str(), r.length() );
}

int		CCharString::Compare
		(
		const std::string&	r
		) const
{
	return Compare( r.c_str(), r.length() );
}

int		CCharString::CompareIgnoreCase
		(
		ConstCCharStringRef r
		) const
{
	return CompareIgnoreCase( r.c_str(), r.length() );
}

int		CCharString::CompareIgnoreCase
		(
		ConstCCharDescriptorRef	r
		) const
{
	return CompareIgnoreCase( r.Pointer(), r.Length() );
}

int		CCharString::CompareIgnoreCase
		(
		const char*	s,
		size_t		sc
		) const
{
	const CCharDescriptor	t( c_str(), length() );
	return t.CompareIgnoreCase( s, sc );
}

int		CCharString::CompareIgnoreCase
		(
		const char*	s
		) const
{
	const CCharDescriptor	t( c_str(), length() );
	return t.CompareIgnoreCase( s );
}

// int		CCharString::CompareIgnoreCase
// 		(
// 		const std::string&	r
// 		)
// {
// 	return CompareIgnoreCase( r.c_str(), r.length() );
// }

void	CCharString::ConvertUppercase
		(
		void
		)
{
	CCharDescriptor s( c_str(), length() );
	s.ConvertUppercase();
}


void	CCharString::ConvertLowercase
		(
		void
		)
{
	CCharDescriptor	s( c_str(), length() );
	s.ConvertLowercase();
}


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

