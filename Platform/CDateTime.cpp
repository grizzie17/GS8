/*---------------------------------------------------------------------+\
|
|	CDateTime.cpp  --  encapsulate date/time
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
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	30-Mar-2011			J.Griswold		(Reviewed by: xxxx)
		Add CurrentTime static function
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	22-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		utilize new ParseDecDigits function in SpanNumber
	05-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		remove from Gauge namespace
	23-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Another adjustment to the "Parse" functions handling
		daylight-savings-time
	21-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix the "Parse" function and the Format functions to behave
		the way we expect.
		Also fix the overall handling of UTC date/time.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for loading the date value from an ISO standard
		formatted date/time string
	21-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add accessor functions
	20-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for formatting date/time info
	14-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <time.h>
//#include <sys/types.h>
//#include <sys/timeb.h>

#include "CDateTime.h"

#include "UPlatform.h"
#include "UPlatformTime.h"
#include "UPlatformString.h"
//#if defined( OS_MSWIN )
//#include <crtdefs.h>
//#endif
NAMESPACE_ROOT_BEGIN
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
long	CDateTime::g_nTimezoneOffset = ~0;
int		CDateTime::g_nDaylight = 0;
time_t	CDateTime::g_nBadTimeValue = ~0;

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
#if defined( OS_MSWIN )

time_t	time_tFromSystemTime
		(
		SYSTEMTIME*	pSystemTime
		)
{
	LARGE_INTEGER jan1970FT = {0};
	LARGE_INTEGER utcFT = {0};

	jan1970FT.QuadPart = 116444736000000000LL; // january 1st 1970
	if ( SystemTimeToFileTime(pSystemTime, (FILETIME*)&utcFT) )
	{
		time_t utcDosTime = (utcFT.QuadPart - jan1970FT.QuadPart)/10000000;

		return (time_t)utcDosTime;
	}
	else
	{
		return 0;
	}

}


void Time_tToSystemTime(time_t dosTime, SYSTEMTIME *systemTime)
{

	LARGE_INTEGER jan1970FT = {0};

	jan1970FT.QuadPart = 116444736000000000LL; // january 1st 1970

	LARGE_INTEGER utcFT = {0};

	utcFT.QuadPart = ((LONGLONG)dosTime)*10000000 + jan1970FT.QuadPart;


	FileTimeToSystemTime((FILETIME*)&utcFT, systemTime);

}

#endif

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDateTime - constructor

\+---------------------------------------------------------------------*/
CDateTime::CDateTime
		(
		void
		)
		: m_t( 0 )
{
}

CDateTime::CDateTime
		(
		int	nYear,
		int	nMon,
		int	nDay,
		int	nHour,
		int	nMin,
		int	nSec
		)
		: m_t( 0 )
{
	Load( nYear, nMon, nDay, nHour, nMin, nSec );
}

CDateTime::CDateTime
		(
		const char*	s
		)
{
	Parse( s );
}

/*---------------------------------------------------------------------+\

 * CDateTime - copy constructor

\+---------------------------------------------------------------------*/
CDateTime::CDateTime
		(
		ConstCDateTimeRef	r
		)
		: m_t( r.m_t )
{
}


/*---------------------------------------------------------------------+\

 * CDateTime - copy constructor

\+---------------------------------------------------------------------*/
CDateTime::CDateTime
		(
		time_t t
		)
		: m_t( t )
{
}


/*---------------------------------------------------------------------+\

 * ~CDateTime - destructor

\+---------------------------------------------------------------------*/
CDateTime::~CDateTime
		(
		void
		)
{
	m_t = 0;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Parse -

\+---------------------------------------------------------------------*/
bool	CDateTime::Parse
		(
		const char*	s
		)
{
	NAMESPACE_COMMON_PREFIX CCharDescriptor	tString( s, strlen(s) );
	return Parse( tString );
}


/*---------------------------------------------------------------------+\

 * Parse - handle ISO standard date/time strings

		Handles dates of the form:
			YYYY-MM-DD['T']hh:mm[:ss][(+/-)hh[:mm]]
			YYYYMMDD['T']hhmm[ss][(+/-)hh[mm]]

			Where:
				YYYY is a four digit year
				MM is a two digit month
				DD is a two digit day of the month
				T is the literal 'T' or a space (the standard uses the T)
				hh is a two digit twenty four hour relative hours
				mm is a two digit minutes within the hour
				ss is a two digit seconds
				+hh:mm or -hh:mm is a time-zone offset (or 'Z' for zero)

\+---------------------------------------------------------------------*/
bool	CDateTime::Parse
		(
		NAMESPACE_COMMON_PREFIX CCharDescriptorRef r
		)
{
	bool	bResult = false;
	long	nYear = 0;
	long	nMonth = 0;
	long	nDay = 0;
	long	nHour = 0;
	long	nMinute = 0;
	long	nSecond = 0;
	long	nTZ = 0;

	const char*	s = r.Pointer();
	const char*	sEnd = s + r.Length();

	long	n;

	do	// sequence
	{
		s += SpanBlanks( s, sEnd );

		n = ParseDate( s, sEnd, &nYear, &nMonth, &nDay );
		if ( n < 8 )
			break;
		s += n;


		s += SpanBlanks( s, sEnd );

		if ( 'T' == *s )
			++s;

		s += SpanBlanks( s, sEnd );

		n = ParseTime( s, sEnd, &nHour, &nMinute, &nSecond );
		if ( n < 4 )
			break;
		s += n;

		s += SpanBlanks( s, sEnd );

		n = ParseZone( s, sEnd, &nTZ );
		s += n;

		if ( s < sEnd )
			break;

		bResult = Load( nYear, nMonth, nDay, nHour, nMinute, nSecond );
		if ( bResult )
			m_t += nTZ;


	} sequence;	// end sequence

	return bResult;
}


/*---------------------------------------------------------------------+\

 * ParseDate -

\+---------------------------------------------------------------------*/
long	CDateTime::ParseDate
		(
		const char*	s,
		const char*	sEnd,
		long*		pYear,
		long*		pMonth,
		long*		pDay
		)
{
	long	nResult = 0;
	long	nYear = 0;
	long	nMonth = 0;
	long	nDay = 0;
	long	n;
	const char*	sStart = s;

	do	// sequence
	{
		s += SpanBlanks( s, sEnd );

		n = SpanNumber( s, sEnd, &nYear );
		if ( n < 4 )
		{
			break;
		}
		else if ( 8 == n )		// form of date that is YYYYMMDD
		{
			SpanNumber( s, s+4, &nYear );
			SpanNumber( s+4, s+4+2, &nMonth );
			SpanNumber( s+4+2, s+4+2+2, &nDay );
			s += n;
		}
		else
		{
			s += n;

			if ( '-' != *s )
				break;
			++s;

			n = SpanNumber( s, sEnd, &nMonth );
			if ( n < 1 )
				break;
			s += n;

			if ( '-' != *s )
				break;
			++s;

			n = SpanNumber( s, sEnd, &nDay );
			if ( n < 1 )
				break;
			s += n;
		}

		if ( nYear < 1970 )
			break;

		if ( nMonth < 1  ||  12 < nMonth )
			break;

		if ( nDay < 1  ||  31 < nDay )
			break;

		*pYear = nYear;
		*pMonth = nMonth;
		*pDay = nDay;

		nResult = long(s - sStart);

	} sequence;	// end sequence


	return nResult;
}


/*---------------------------------------------------------------------+\

 * ParseTime -

\+---------------------------------------------------------------------*/
long	CDateTime::ParseTime
		(
		const char*	s,
		const char*	sEnd,
		long*		pHour,
		long*		pMinute,
		long*		pSecond
		)
{
	long	nResult = 0;
	long	nHour = 0;
	long	nMinute = 0;
	long	nSecond = 0;
	long	n;
	const char*	sStart = s;


	do	// sequence
	{
		n = SpanNumber( s, sEnd, &nHour );
		if ( 2 < n )
		{
			SpanNumber( s, s+2, &nHour );
			if ( 6 == n )	// HHMMSS
			{
				SpanNumber( s+2, s+2+2, &nMinute );
				SpanNumber( s+2+2, s+n, &nSecond );
				s += n;

				// this handles the optional fractional second
				//	it should be noted that we ignore the result
				s += ParseFracSeconds( s, sEnd );
			}
			else if ( 4 == n )	// HHMM
			{
				SpanNumber( s+2, s+2+2, &nMinute );
				s += n;
			}
			else
			{
				break;
			}
		}
		else
		{
			if ( n < 1 )
				break;
			s += n;

			if ( ':' != *s )
				break;
			++s;

			n = SpanNumber( s, sEnd, &nMinute );
			if ( n < 1 )
				break;
			s += n;

			if ( ':' == *s )
			{
				++s;
				n = SpanNumber( s, sEnd, &nSecond );
				if ( n < 1 )
					break;
				s += n;

				// this handles the optional fractional second
				//	it should be noted that we ignore the result
				s += ParseFracSeconds( s, sEnd );
			}
		}

		if ( nHour < 0  ||  23 < nHour )
			break;

		if ( nMinute < 0  ||  59 < nMinute )
			break;

		if ( nSecond < 0  ||  59  < nSecond )
			break;

		*pHour = nHour;
		*pMinute = nMinute;
		*pSecond = nSecond;

		nResult = long(s - sStart);

	} sequence;	// end sequence

	return nResult;
}


/*---------------------------------------------------------------------+\

 * ParseFracSeconds -

\+---------------------------------------------------------------------*/
long	CDateTime::ParseFracSeconds
		(
		const char*	s,
		const char*	sEnd
		)
{
	long		nResult = 0;
	long		nFrac = 0;
	long		n = 0;
	const char*	sStart = s;

	do	// sequence
	{
		if ( '.' != *s )
			break;
		++s;

		n = SpanNumber( s, sEnd, &nFrac );
		if ( n < 1 )
			break;
		s += n;

		nResult = long(s - sStart);

	} sequence;	// end

	return nResult;
}

/*---------------------------------------------------------------------+\

 * ParseZone -

\+---------------------------------------------------------------------*/
long	CDateTime::ParseZone
		(
		const char*	s,
		const char*	sEnd,
		long*		pSecondsOffset
		)
{
	long	nResult = 0;
	long	nOffset = 0;
	long	nDST = 0;
	long	nHour = 0;
	long	nMinute = 0;
	long	nSecond = 0;
	long	nSign = 1;
	long	n;
	const char*	sStart = s;

	do	// sequence
	{
		if ( 'Z' == *s  ||  'z' == *s )
		{
			nOffset = 0;
			++s;
		}
		else
		{
			if ( '+' == *s )
			{
				++s;
			}
			else if ( '-' == *s )
			{
				++s;
				nSign = -1;
			}
			else
			{
				break;
			}

			n = ParseTime( s, sEnd, &nHour, &nMinute, &nSecond );
			if ( n < 4 )
			{
				n = SpanNumber( s, sEnd, &nHour );
				if ( n < 1 )
					break;

				s += n;

				nMinute = 0;
				nSecond = 0;
			}
			else
			{
				s += n;
			}

			s+= SpanBlanks( s, sEnd );

			// handle non-standard definition of daylight-savings-time
			if ( 3 <= (s - sStart) )
			{
				if ( 0 == ::strncmp( s, "DST", 3 ) )
				{
					nDST = 60 * 60;
					s += 3;
				}
			}


			nOffset = nHour * 60 * 60 + nMinute * 60 + nSecond - nDST;
			nOffset *= nSign;
		}

		*pSecondsOffset = nOffset;

		nResult = long(s - sStart);


	} sequence;	// end sequence


	return nResult;
}

/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CDateTime::Load
		(
		int	nYear,
		int nMon,
		int nDay,
		int nHour,
		int nMin,
		int nSec
		)
{
	bool	bResult = false;
#if defined( OS_MSWIN )

	SYSTEMTIME	s = {0};

	s.wYear = WORD(nYear);
	s.wMonth = WORD(nMon);
	s.wDay = WORD(nDay);
	s.wHour = WORD(nHour);
	s.wMinute = WORD(nMin);
	s.wSecond = WORD(nSec);

	m_t = time_tFromSystemTime( &s );

#elif defined( OS_LINUX )

	if ( -1 < nHour  &&  nHour < 24
		&&	-1 < nMin  &&  nMin < 60
		&&	-1 < nSec  &&  nSec < 60
		&&  0 < nDay  &&  nDay < 32
		&&	0 < nMon  &&  nMon < 13
		&&	1970 < nYear
		)
	{
		struct tm	t = {0};

		t.tm_hour = nHour % 24;
		t.tm_isdst = 0;
		t.tm_mday = nDay;
		t.tm_mon = nMon - 1;
		t.tm_min = nMin % 60;
		t.tm_sec = nSec % 60;
		t.tm_wday = 0;
		t.tm_yday = 0;
		t.tm_year = nYear - 1900;

		m_t = mkgmtime( &t );
		if ( -1 == m_t )
			m_t = 0;
	}
	else
	{
		m_t = 0;
	}

#else
	m_t = 0;
#endif
	if ( 0 != m_t )
		bResult = true;

	return bResult;
}


/*---------------------------------------------------------------------+\

 * FormatLocal -

\+---------------------------------------------------------------------*/
void	CDateTime::FormatLocal
		(
		char*		sBuffer,
		size_t		nBufSize,
		const char*	sFormat
		)
{
	struct tm	tTm = {0};

	time_t		t = m_t - TimeAdjustOffset();

	// localtime_s
	if ( 0 == gmtime_s( &tTm, &t ) )
	{
		FormatTM( sBuffer, nBufSize, sFormat, &tTm );
	}
}


/*---------------------------------------------------------------------+\

 * FormatGMT -

\+---------------------------------------------------------------------*/
void	CDateTime::FormatGMT
		(
		char*		sBuffer,
		size_t		nBufSize,
		const char*	sFormat
		)
{
	struct tm	tTm = {0};

	if ( 0 == gmtime_s( &tTm, &m_t ) )
	{
		FormatTM( sBuffer, nBufSize, sFormat, &tTm );
	}
}


/*---------------------------------------------------------------------+\

 * FormatISO -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
void	CDateTime::FormatISO
		(
		char*	sBuffer,
		size_t	nBufSize,
		bool	bLocal
		)
{
	long	nOffset = TimezoneOffset();

	if ( bLocal  &&  0 != nOffset )
	{
		char	sTemp[80];
		char	sDST[8] = {0};
		long	nHour;
		long	nMinute;
		char	cSign = '-';

		if ( nOffset < 0 )
		{
			cSign = '+';
			nOffset *= -1;
		}

		if ( TimezoneOffset()  !=  TimeAdjustOffset() )
			::strcpy_s( sDST, sizeof(sDST), " DST" );

		nHour = nOffset / (60*60);
		nOffset -= nHour * 60 * 60;
		nMinute = nOffset / 60;
		FormatLocal( sTemp, sizeof(sTemp), "%Y-%m-%d %H:%M:%S" );
		sprintf_s( sBuffer, nBufSize, "%s %c%02ld:%02ld%s",
								sTemp, cSign, nHour, nMinute, sDST );
	}
	else
	{
		FormatGMT( sBuffer, nBufSize, FORMAT_ISODATE );
	}
}
//END_OVERRUN_WARNING



/*---------------------------------------------------------------------+\

 * TimezoneOffset -

\+---------------------------------------------------------------------*/
long	CDateTime::TimezoneOffset
		(
		void
		)
{
	if ( ~0 == g_nTimezoneOffset )
	{
#if defined( OS_MSWIN )

		TIME_ZONE_INFORMATION	tzi;

		::GetTimeZoneInformation( &tzi );

		g_nTimezoneOffset = tzi.StandardBias * 60;
		if ( tzi.Bias == tzi.StandardBias )
			g_nDaylight = 0;
		else
			g_nDaylight = (tzi.DaylightBias - tzi.StandardBias) * 60;

		//::_tzset();

		//long	nOfs;
		//_get_timezone( &nOfs );
		//int		nDaylight;
		//_get_daylight( &nDaylight );
		//g_nTimezoneOffset = nOfs;
		//g_nDaylight = nDaylight ? 60*60 : 0;

#elif defined( OS_LINUX )

		::tzset();
		g_nTimezoneOffset = timezone;
		g_nDaylight = daylight ? 60*60 : 0;

#else
		g_nTimezoneOffset = 0;
#endif
	}

	return g_nTimezoneOffset;
}


/*---------------------------------------------------------------------+\

 * TimeAdjustOffset -

\+---------------------------------------------------------------------*/
long	CDateTime::TimeAdjustOffset
		(
		void
		)
{
	long	nOffset = TimezoneOffset();

	nOffset -= g_nDaylight;

	return nOffset;
}



/*---------------------------------------------------------------------+\

 * CurrentTime -

\+---------------------------------------------------------------------*/
CDateTime
		CDateTime::CurrentTime
		(
		void
		)
{
	time_t	t;
#if defined( OS_MSWIN )
	SYSTEMTIME	s = {0};

	::GetSystemTime( &s );
	t = time_tFromSystemTime( &s );
#else
	t = time( 0 );
#endif
	return CDateTime( t );
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * FormatTM -

\+---------------------------------------------------------------------*/
void	CDateTime::FormatTM
		(
		char*		sBuffer,
		size_t		nBufSize,
		const char*	sFormat,
		struct tm*	pTm
		)
{
	strftime( sBuffer, nBufSize, sFormat, pTm );
}



/*---------------------------------------------------------------------+\

 * SpanNumber -

\+---------------------------------------------------------------------*/
long	CDateTime::SpanNumber
		(
		const char*	s,
		const char*	sEnd,
		long*		pNumber
		)
{
	size_t		nResult = 0;
	long		nValue = 0;

	nValue = ParseDecDigits( s, (size_t)(sEnd - s), &nResult );

	if ( pNumber )
		*pNumber = nValue;

	return (long)nResult;
}

/*---------------------------------------------------------------------+\

 * SpanBlanks -

\+---------------------------------------------------------------------*/
long	CDateTime::SpanBlanks
		(
		const char*	s,
		const char*	sEnd
		)
{
	const char*	sStart = s;
	while ( s < sEnd )
	{
		if ( 0x0020 < *s )
			break;
		++s;
	}
	return long(s - sStart);
}






/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


NAMESPACE_ROOT_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

