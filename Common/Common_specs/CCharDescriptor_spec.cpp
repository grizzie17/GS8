//#include "stdafx.h"
#include "igloo/igloo.h"

#include <string.h>

//#include <string>

#include "CCharDescriptor.h"

using namespace igloo;

USING_NAMESPACE_COMMON

Context(CCharDescriptor_class)
{
	Spec(it_should_load_pointer_and_count)
	{
		const char	sample[] = "This is a sample string";

		CCharDescriptor	str(sample);

		// make sure that we are comparing the original string
		AssertThat((void*)str.Pointer(), Is().EqualTo((void*)sample));
		AssertThat(str.Length(), Equals(strlen(sample)));
	}

	Spec(it_should_be_able_to_identify_equality)
	{
		const char	sample1[] = "sample";
		const char	sample2[] = "sample";

		CCharDescriptor	t1(sample1);
		CCharDescriptor	t2(sample2);

		AssertThat((t1 == t2), IsTrue());
		AssertThat((t1 == sample2), IsTrue());
		AssertThat((sample1 == t1), IsTrue());
	}

	Spec(it_should_identify_the_comparitive_operators)
	{
		const char	s1[] = "abc";
		const char	s2[] = "def";

		CCharDescriptor	t1(s1);
		CCharDescriptor	t2(s2);

		AssertThat((t1 < t2), IsTrue());
		AssertThat((t1 < s2), IsTrue());
		AssertThat((s1 < t2), IsTrue());

		AssertThat((t1 <= t2), IsTrue());
		AssertThat((t1 <= s2), IsTrue());
		AssertThat((s1 <= t2), IsTrue());

		AssertThat((t2 > t1), IsTrue());
		AssertThat((t2 > s1), IsTrue());
		AssertThat((s2 > t1), IsTrue());

		AssertThat((t2 >= t1), IsTrue());
		AssertThat((t2 >= s1), IsTrue());
		AssertThat((s2 >= t1), IsTrue());

		AssertThat((t2 != t1), IsTrue());
		AssertThat((t2 != s1), IsTrue());
		AssertThat((s2 != t1), IsTrue());
	}

	Spec(it_should_compare_ignoring_case)
	{
		const char			s1[] = "sample";
		const char			s2[] = "SAMPLE";
		CCharDescriptor t1(s1);

		AssertThat(t1.CompareIgnoreCase(s2), Equals(0));
	}




};
