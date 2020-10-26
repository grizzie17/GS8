#include "iggy.h"

#include <vector>


#include "CDateTime.h"

// #include "igloo/igloo.h"
// using namespace igloo;
using namespace Yogi::Core;


Describe( CDateTime_class ) {
It( Initialized_via_numeric_date_list )
{
    CDateTime obj( 2001, 9, 11, 10, 30, 00 );
    AssertThatGT( obj.ToTime_t(), ( 0 ) );
}
};  // Describe(CDateTime_class)

Context( CDateTimeInitialization ) {
CDateTime oBaseline;

Spec( Initialized_via_numeric_date_list )
{
    CDateTime obj( 2001, 9, 11, 10, 30, 00 );
    AssertThatGT( obj.ToTime_t(), ( 0 ) );
}

Spec( ShouldLoadDates )
{
    CDateTime o;
    bool      b = o.Load( 2000, 1, 1, 13, 0, 30 );
    AssertThat( b, IsTrue() );
}

Spec( LoadDatesViaContructor )
{
    CDateTime o( 2000, 1, 1, 13, 0, 30 );
    CDateTime r;

    bool b = r.Load( 2000, 1, 1, 13, 0, 30 );
    AssertThat( b, IsTrue() );
    time_t ot = o;
    time_t rt = r;
    AssertThat( ot, ( rt ) );
}

Spec( ShouldRejectBadDates )
{
    CDateTime o;
    bool      b = o.Load( 2000, 13, 32, 25, 70, 70 );
    AssertThat( b, IsFalse() );
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
Spec( ParsingDateString )
{
    CDateTime o;
    bool      b = o.Parse( "2000-01-01 13:00:30 " );
    AssertThat( b, IsTrue() );
}

Spec( ParsingDateString2 )
{
    CDateTime o;
    bool      b = o.Parse( "20000101T130030" );
    AssertThat( b, IsTrue() );
}

Spec( ParsingDateString3 )
{
    CDateTime o;
    bool      b = o.Parse( "200101T130030" );
    AssertThat( b, IsFalse() );
}

Spec( ParseDateStringFailure )
{
    CDateTime o;
    bool      b = o.Parse( "2000-13-32 26:00:30" );
    AssertThat( b, IsFalse() );

    //Feb 31 should be a problem
    b = o.Parse( "2000-02-31 12:00:00" );
    AssertThat( b, IsFalse() );
}

};  // Context(CDateTimeInitialization)


Context( CDateTimeOperation ) {
Spec( CompareEquality )
{
    CDateTime d1( "20010101T120000" );
    CDateTime d2( "2001-01-01 12:00:00" );

    AssertThat( d1 == d2, IsTrue() );
    AssertThat( d1 == "20010101T120000", IsTrue() );
}
};  // Context(CDateTimeOperation)
