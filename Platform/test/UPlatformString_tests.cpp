
#include "UPlatformIO.h"
#include "UPlatformString.h"

#include <stdexcept>
#include <string>


#include "iggy.h"


#define Equals( s ) ( s )

// #include "igloo/igloo.h"
// using namespace igloo;


Context( UPlatformString_spec ) {
Spec( should_copy_a_string )
{
    const char source[] = "This is a sample string";
    char       target[128];

    errno_t e = strcpy_s( target, sizeof( target ), source );

    AssertThat( e, Equals( 0 ) );
}

//	Spec(should_reject_string_overflow)
//	{
//		const char source[] = "This is a sample string";
//		char target[10] = {0};
//
//		errno_t	e;
//
//		//AssertThrows(std::string, (e = strcpy_s( target, sizeof(target)-2, source )));
//		//Assert::That(LastException<std::string>().c_str(), Is().Containing("too small"));
//#if defined( _MSC_VER )
//		__try
//		{
//			errno_t	e = strcpy_s(target, sizeof(target), source);
//		}
//		__except (EXCEPTION_CONTINUE_EXECUTION)
//		{
//		}
//#else
//		try
//		{
//			errno_t e = strcpy_s(target, sizeof(target), source);
//		}
//		catch (...)
//		{
//		}
//#endif
//
//		AssertThat( e, !Equals( 0 ) );
//		AssertThat( target[sizeof(target)-1], Equals(0) );
//	}

Spec( function_memcpy_s )
{
    const int source[] = { 1, 2, 3, 4 };
    int       target[20];

    errno_t e = memcpy_s( target, sizeof( target ), source, sizeof( source ) );

    AssertThat( e, Equals( 0 ) );
}

Spec( function_sprintf_s_that_fits )
{
    char target[40];

    errno_t e = sprintf_s( target, sizeof( target ), "----%ld----", 1234L );

    AssertThat( e, Equals( 12 ) );
    AssertThatStrEq( target, Equals( "----1234----" ) );
}

//	Spec(function_sprintf_s_overflow)
//	{
//		char target[4];
//		errno_t	e = 0;
//
//		AssertThrows(std::string, (e = sprintf_s( target, sizeof(target), "----%ld----", 1234L )));
//
//		Assert::That(LastException<std::string>().c_str(), Is().Containing("too small"));
//
//		AssertThat( e, Equals(0) );
//		AssertThat( errno, IsLessThan(0) );
//	}

// memmove_s( t, tc, s, sc )
// strcat_s( t, tc, s )
// strset_s( t, tc, v )
// strerror_s( t, tc, v )

};  // Context(UPlatformString_spec)
