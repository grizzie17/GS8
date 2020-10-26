/*---------------------------------------------------------------------+\
|
|	UPlatformTime.h  --  brief description of what UPlatformTime.h is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	14-Dec-2011			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UPlatformTime
#define _H_UPlatformTime
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"
#include "UTypes.h"
#if defined( OS_MSWIN )
#    include <windows.h>
//#	include <w32api/synchapi.h>
#elif defined( OS_LINUX )
#    include <sys/time.h>
#endif

#include <time.h>

#include "UDeclPlatform.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#if defined( OS_MSWIN )

#    if defined( usleep )
#        undef usleep
#    endif
#    define usleep( n ) Sleep( ( n ) / 1000 )

#endif

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
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

CORE_API( long ) milliseconds( void );


#if defined( OS_MSWIN_WCE )

time_t
time( time_t* t );

clock_t
clock( void );

struct tm*
localtime( const time_t* clock );

struct tm*
gmtime( const time_t* clock );

time_t
mktime( struct tm* t );


size_t
strftime( char* const s, const size_t maxsize, const char* format,
        const struct tm* const t );


time_t
w32_filetime_to_time_t( FILETIME* ft );


#endif


#if defined( OS_LINUX ) || defined( OS_MSWIN_WCE ) || defined( OS_MACINTOSH ) \
        || defined( __MSYS__ ) || defined( __GNUC__ )

errno_t
gmtime_s( struct tm* ptm, const time_t* pTime );

errno_t
localtime_s( struct tm* ptm, const time_t* pTime );

time_t
mkgmtime( struct tm* const tmp );

#endif


/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/


inline errno_t
millisleep( unsigned long nMilliseconds )
{
#if defined( OS_MSWIN )
    Sleep( nMilliseconds );
    return 0;
#elif defined( OS_LINUX )
    struct timespec tTime;
    struct timespec tRemain;
    const long      kOneMilli = 1000000;

    tTime.tv_sec = nMilliseconds / 1000;
    tTime.tv_nsec = ( nMilliseconds % 1000 ) * kOneMilli;
    return nanosleep( &tTime, &tRemain );
#else
    return usleep( nMilliseconds * 1000 );
#endif
}


#endif /* _H_UPlatformTime */
