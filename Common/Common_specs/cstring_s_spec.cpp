#include "igloo/igloo.h"

#include <string.h>


using namespace igloo;


Context(cstring_s)
{
	Spec(should_define_STDC_SECURE_LIB)
	{
#		if defined( __STDC_SECURE_LIB__ )
#			if defined( _MSC_VER )
				AssertThat( __STDC_SECURE_LIB__, IsGreaterThan(200410L) );
#			else
				AssertThat( __STDC_SECURE_LIB__, IsGreaterThan(201101L) );
#			endif
#		endif
	}
	
};
