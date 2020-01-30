
#include "CCharDescriptor.h"
#define BOOST_TEST_MODULE CCharDescriptorTest
#include <boost/test/unit_test.hpp>

using namespace Yogi::Core;

// BOOST_AUTO_TEST_SUITE( CCharDescriptor_class )


BOOST_AUTO_TEST_CASE( it_should_load_pointer_and_count )
{
	const char	sample[] = "This is a sample string";

	CCharDescriptor	str( sample, sizeof(sample)-1 );

	// make sure that we are comparing the original string
	BOOST_CHECK_EQUAL( (void*)str.Pointer(), (void*)sample );
	BOOST_CHECK_EQUAL( str.Length(), strlen(sample) );

}

// BOOST_AUTO_TEST_SUITE_END()
