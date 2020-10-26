//=====================================================================+|
//
//!	@file	CDateTime.h
//!	@brief	encapsulate date/time
//!
//!	@note	The date/time is always stored in UTC (Zulu) zone
//
//=====================================================================+/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	30-Mar-2011			J.Griswold		(Reviewed by: xxxx)
		Add CurrentTime static function
	05-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		remove from Gauge namespace
	23-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Another adjustment to the "Parse" functions handling
		daylight-savings-time
	21-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix the "Parse" function and the Format functions to behave
		the way we expect.
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
#ifndef _H_CDateTime_Root
#define _H_CDateTime_Root
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <time.h>

#include "CCharDescriptor.h"
#include "UMachine.h"

#include "UDeclPlatform.h"

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#define FORMAT_ISODATE ( "%Y-%m-%d %H:%M:%S Z" )

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CDateTime*       CDateTimePtr;
typedef class CDateTime&       CDateTimeRef;
typedef const class CDateTime& ConstCDateTimeRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CORE_CLASS CDateTime
{
    //	class lifecycle  ----------------------------------------------------
public:
    CDateTime();
    CDateTime( ConstCDateTimeRef r );  // copy constructor
    CDateTime( int nYear, int nMon, int nDay, int nHour, int nMin, int nSec );
    CDateTime( const char* s );
    CDateTime( ConstCCharDescriptorRef r );
    CDateTime( time_t t );
    ~CDateTime();

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

    ConstCDateTimeRef
    operator=( ConstCDateTimeRef r );  // assignment
    ConstCDateTimeRef
    operator=( const time_t t );
    ConstCDateTimeRef
    operator=( const char* s );

    bool
    operator==( ConstCDateTimeRef r ) const;
    bool
    operator==( const time_t t ) const;
    bool
    operator==( const char* s ) const;

    operator time_t( void ) const;

    bool
    Parse( const char* s );
    bool
    Parse( ConstCCharDescriptorRef r );
    bool
    Load( int nYear, int nMon, int nDay, int nHour, int nMin, int nSec );

    bool
    IsBadTime( void ) const;

    time_t
    ToTime_t( void ) const;

    //bool			ToTM

    // uses the formatting of strftime
    void
    FormatGMT( char* sBuffer, size_t nBufSize, const char* sFormat );
    void
    FormatLocal( char* sBuffer, size_t nBufSize, const char* sFormat );
    void
    FormatISO( char* sBuffer, size_t nBufSize, bool bLocal = false );

    // deltas used for timezone or timezone + daylight-savings
    long
    TimezoneOffset( void );
    long
    TimeAdjustOffset( void );

    static CDateTime
    CurrentTime( void );

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    long
    ParseDate( const char* s, const char* sEnd, long* pYear, long* pMonth,
            long* pDay );
    long
    ParseTime( const char* s, const char* sEnd, long* pHour, long* pMinute,
            long* pSecond );
    long
    ParseFracSeconds( const char* s, const char* sEnd );
    long
    ParseZone( const char* s, const char* sEnd, long* pSecondsOffset );

    void
    FormatTM( char* sBuffer, size_t nBufSize, const char* sFormat,
            struct tm* pTm );


    // returns number of chracters processed
    long
    SpanNumber( const char* s, const char* sEnd, long* nValue );
    long
    SpanBlanks( const char* s, const char* sEnd );

    //	protected data  -----------------------------------------------------

    time_t m_t;

    long g_nTimezoneOffset = ~0;
    int  g_nDaylight = 0;

    const time_t g_nBadTimeValue = ~0;

private:
    //	private functions  --------------------------------------------------

    //	private data  -------------------------------------------------------

    //============================== Overrides ==============================
    // -- delete this section if this is a root class --
    //	root
    //	BaseClass-1
    //	BaseClass
};

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/


/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline ConstCDateTimeRef
CDateTime::operator=( ConstCDateTimeRef r )
{
    m_t = r.m_t;
    return *this;
}

inline ConstCDateTimeRef
CDateTime::operator=( const time_t t )
{
    m_t = t;
    return *this;
}

inline ConstCDateTimeRef
CDateTime::operator=( const char* s )
{
    Parse( s );
    return *this;
}

/*---------------------------------------------------------------------+\

 * operator== - equality

\+---------------------------------------------------------------------*/
inline bool
CDateTime::operator==( ConstCDateTimeRef r ) const
{
    return m_t == r.m_t;
}


inline bool
CDateTime::operator==( const char* s ) const
{
    CDateTime t( s );
    return m_t == t;
}


inline bool
CDateTime::operator==( const time_t t ) const
{
    return m_t == t;
}


/*---------------------------------------------------------------------+\

 * operator time_t - operator

\+---------------------------------------------------------------------*/
inline CDateTime::operator time_t( void ) const
{
    return m_t;
}


/*---------------------------------------------------------------------+\

 * ToTime_t -

\+---------------------------------------------------------------------*/
inline time_t
CDateTime::ToTime_t( void ) const
{
    return m_t;
}


inline bool
CDateTime::IsBadTime( void ) const
{
    if ( 0 == m_t || g_nBadTimeValue == m_t )
        return true;
    else
        return false;
}


}}  // namespace Yogi::Core


#endif /* _H_CDateTime */
