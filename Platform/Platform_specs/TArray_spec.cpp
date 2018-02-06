#include "stdafx.h"
#include "TArray.h"
#include "igloo/igloo.h"


using namespace igloo;

USING_NAMESPACE_ROOT

Context(TArray_template)
{
	Spec(it_should_initialize_as_empty)
	{
		TArray<long>	a;

		AssertThat( a.Length(), Equals(0u) );
	}

	Spec(the_enumerator_should_behave_with_an_empty_array)
	{
		TArray<long>	a;
		TArrayEnumerator<long>	e = a.GetEnumerator();

		AssertThat( e.MoveNext(), IsFalse() );
	}

	Spec(it_can_hold_items)
	{
		TArray<long>	a;

		a[0] = 0;
		a[1] = 1;
		a[2] = 2;

		AssertThat( a.Length(), Equals(3u) );

		AssertThat( a[0], Equals(0) );
		AssertThat( a[1], Equals(1) );
		AssertThat( a[2], Equals(2) );
	}

	Spec(it_can_sort_items)
	{
		TArray<long>	a;

		a[0] = 2;
		a[1] = 1;
		a[2] = 3;

		a.Sort();

		AssertThat( a[0], Equals(1) );
		AssertThat( a[1], Equals(2) );
		AssertThat( a[2], Equals(3) );
	}

	Spec(it_can_allocate_space_when_needed)
	{
		TArray<long>	a;

		AssertThat( a.Length(), Equals(0u) );

		long*	p = a.PointItem(5);

		AssertThat( (void*)p, !Equals((void*)NULL) );
		AssertThat( a.Length(), Equals(6u) );
	}

	Spec(it_can_determine_if_already_allocated)
	{
		TArray<long>	a;

		long*	p = a.PointArray(3);

		AssertThat( (void*)p, Equals((void*)NULL) );
	}

	Spec(it_can_clear_its_memory)
	{
		TArray<long>	a;
		a[0] = 1;
		a[1] = 2;
		a[2] = 3;
		a[3] = 4;

		AssertThat( a.Length(), Equals(4u) );

		a.Clear();

		AssertThat( a.Length(), Equals(0u) );
	}

};
