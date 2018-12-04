
#include "stdafx.h"
#include <string.h>
#include <float.h>

#include "TCharDescriptor.h"

#include "igloo/igloo.h"
using namespace igloo;

USING_NAMESPACE_ROOT

Context(TCharDescriptor_template)
{
	Spec(it_should_hold_pointer_and_count)
	{
		char	sample[] = "This is a sample string";

		TCharDescriptor<char>	desc(sample);

		// make sure that we are comparing the pointer not the string
		AssertThat( (void*)desc.Pointer(), Equals((void*)sample) );
		AssertThat( desc.Length(), Equals(strlen(sample)) );
	}

	Spec(it_should_be_able_copy_to_array)
	{
		char	sample[] = "sample";
		char	target[sizeof(sample)+1];

		TCharDescriptor<char>	desc(sample);

		bool	bResult = desc.CopyTo( target, sizeof(target) );

		AssertThat( bResult, IsTrue() );
		AssertThat( strcmp(sample, target), Equals(0) );
	}

	Spec(it_should_be_able_copy_to_array_without_overflow)
	{
		char	sample[] = "sample";
		char	target[sizeof(sample)-2];

		TCharDescriptor<char>	desc(sample);

		bool	bResult = desc.CopyTo( target, sizeof(target) );

		AssertThat( bResult, IsFalse() );
	}

	Spec(it_should_parse_integer_strings)
	{
		char	sample[] = "12345";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		long	nResult = desc.ParseInt( &nCount );

		AssertThat( nCount, Equals(strlen(sample)) );
		AssertThat( nResult, Equals(12345) );
	}

	Spec(it_should_parse_hex_strings)
	{
		char	sample[] = "0x1234ACDF";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		long	nResult = desc.ParseInt( &nCount );

		AssertThat( nCount, Equals(strlen(sample)) );
		AssertThat( nResult, Equals(0x1234ACDF) );
	}

	Spec(it_should_not_parse_bad_integer_strings)
	{
		char	sample[] = "abc123";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		long	nResult = desc.ParseInt( &nCount );

		AssertThat( nCount, Equals(0u) );
		AssertThat( nResult, Equals(0) );
	}

	Spec(it_should_be_able_to_identify_equality)
	{
		char	sample1[] = "sample";
		char	sample2[] = "sample";

		TCharDescriptor<char>	t1(sample1);
		TCharDescriptor<char>	t2(sample2);

		AssertThat( (t1 == t2), IsTrue() );
	}

	Spec(it_should_parse_string_into_integer)
	{
		char	sample[] = "12345";
		size_t	nLen = strlen(sample);
		long	nValue;
		size_t	nCount;

		nValue = ParseIntT( sample, nLen, &nCount );

		AssertThat( nValue, Equals(12345) );
		AssertThat( nCount, Equals(nLen));
	}

	Spec(it_should_parse_string_into_integer_with_nonnumeric_chars_at_end)
	{
		char	sample[] = "12345abc";
		size_t	nLen = strlen(sample);
		long	nValue;
		size_t	nCount;

		nValue = ParseIntT( sample, nLen, &nCount );

		AssertThat( nValue, Equals(12345) );
		AssertThat( nCount, Equals(nLen-3));
	}

	Spec(it_should_parse_simple_float_strings)
	{
		char	sample[] = "1.5";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		GFLOAT	fResult = desc.ParseFloat( &nCount );

		AssertThat( nCount, Equals(strlen(sample)) );
		AssertThat( fResult, Equals(1.5) );
	}

	Spec(it_should_parse_simple_neg_float_strings)
	{
		char	sample[] = "-1.5";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		GFLOAT	fResult = desc.ParseFloat( &nCount );

		AssertThat( nCount, Equals(strlen(sample)) );
		AssertThat( fResult, Equals(-1.5) );
	}

	Spec(it_should_parse_exp_float_strings)
	{
		char	sample[] = "1.5e2";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		GFLOAT	fResult = desc.ParseFloat( &nCount );

		AssertThat( nCount, Equals(strlen(sample)) );
		AssertThat( fResult, Equals(1.5e2) );
	}

	Spec(it_should_parse_neg_exp_neg_float_strings)
	{
		char	sample[] = "-1.5e-2";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount;
		GFLOAT	fResult = desc.ParseFloat( &nCount );

		AssertThat( nCount, Equals(strlen(sample)) );
		AssertThat( fResult, EqualsWithDelta(-1.5e-2, FLT_EPSILON) );
	}

	Spec(it_should_parse_mant_exp_float_strings)
	{
		char	sample[] = "1e2";

		TCharDescriptor<char>	desc(sample);

		size_t	nCount2;
		GFLOAT	fResult = desc.ParseFloat( &nCount2 );

		AssertThat( nCount2, Equals(strlen(sample)) );
		AssertThat( fResult, EqualsWithDelta(1e2, FLT_EPSILON) );
	}


};

