//#include "stdafx.h"

#include <string.h>

//#include <string>

#include "CCharString.h"

#include "igloo/igloo.h"
using namespace igloo;

using namespace Yogi::Core;

Context(CCharString_class)
{
	Spec(it_should_load_pointer_and_count)
	{
		const char	sample[] = "This is a sample string";

		CCharString	str(sample);

		// make sure that we are comparing the pointer not the string
		AssertThat( (void*)str.Pointer(), Is().Not().EqualTo((void*)sample) );
		AssertThat( str.Length(), Equals(strlen(sample)) );
	}

	Spec(it_should_be_able_to_identify_equality)
	{
		const char	sample1[] = "sample";
		const char	sample2[] = "sample";

		CCharString	t1(sample1);
		CCharString	t2(sample2);

		AssertThat( (t1 == t2), IsTrue() );
		AssertThat( (t1 == sample2), IsTrue() );
		AssertThat( (sample1 == t1), IsTrue() );
	}

	Spec(it_should_identify_the_comparitive_operators)
	{
		const char	s1[] = "abc";
		const char	s2[] = "def";

		CCharString	t1( s1 );
		CCharString	t2( s2 );

		AssertThat( (t1 < t2), IsTrue() );
		AssertThat( (t1 < s2), IsTrue() );
		AssertThat( (s1 < t2), IsTrue() );

		AssertThat( (t1 <= t2), IsTrue() );
		AssertThat( (t1 <= s2), IsTrue() );
		AssertThat( (s1 <= t2), IsTrue() );

		AssertThat( (t2 > t1), IsTrue() );
		AssertThat( (t2 > s1), IsTrue() );
		AssertThat( (s2 > t1), IsTrue() );

		AssertThat( (t2 >= t1), IsTrue() );
		AssertThat( (t2 >= s1), IsTrue() );
		AssertThat( (s2 >= t1), IsTrue() );

		AssertThat( (t2 != t1), IsTrue() );
		AssertThat( (t2 != s1), IsTrue() );
		AssertThat( (s2 != t1), IsTrue() );
	}

	Spec(it_should_compare_ignoring_case)
	{
		const char	s1[] = "sample";
		CCharString t1("SAMPLE");

		AssertThat( t1.CompareIgnoreCase(s1), Equals(0) );
	}

	Spec(it_should_allow_appending_strings)
	{
		CCharString	t1("Sample");
		t1.Append("String");

		AssertThat( t1.Pointer(), Equals("SampleString"));
	}

	Spec(it_should_allow_appending_strings_via_operator)
	{
		CCharString	t1("Sample");
		t1 += "String";

		AssertThat( t1.Pointer(), Equals("SampleString"));
	}

	Spec(allow_loading_using_formatted_strings)
	{
		CCharString	t1;
		t1.Format("Data = %ld", 123);

		AssertThat( t1.Pointer(), Equals("Data = 123"));
	}

	Spec(allow_appending_strings_using_formatted_strings)
	{
		CCharString t1("Data:");
		t1.AppendFormat(" %ld", 123);

		AssertThat( t1.Pointer(), Equals("Data: 123"));
	}

	Spec(allow_acting_like_descriptor)
	{
		CCharString	t1("string");
		CCharDescriptor	d1 = t1;

		// notice that d1 is actually pointing to t1's data
		AssertThat( (void*)t1.Pointer(), Equals((void*)d1.Pointer()));
	}

	Spec(support_case_conversion)
	{
		CCharString t1("Sample");

		t1.ConvertUppercase();
		AssertThat( (t1 == "SAMPLE"), IsTrue() );

		t1.ConvertLowercase();
		AssertThat( (t1 == "sample"), IsTrue() );
	}
};
