#include "TDictionaryIndexed.h"
#include "CCharString.h"
#include "igloo/igloo.h"


using namespace igloo;

USING_NAMESPACE_COMMON

Context(TDictionaryIndexed_template)
{
	Spec(it_should_initialize_as_empty)
	{
		TDictionaryIndexed<CCharString,long>	a;

		AssertThat( a.Length(), Equals(0u) );
	}

	Spec(the_enumerator_should_behave_with_an_empty_array)
	{
		TDictionaryIndexed<CCharString,long>	a;
		TDictionaryIndexedEnumerator<CCharString,long>	e = a.GetEnumerator();

		AssertThat( e.MoveNext(), IsFalse() );
	}

	Spec(it_can_hold_items)
	{
		TDictionaryIndexed<CCharString,long>	a;

		a.Add(CCharString("a"), 0);
		a.Add(CCharString("b"), 1);
		a.Add(CCharString("c"), 2);


		AssertThat( a.Length(), Equals(3u) );

		AssertThat( *a.Find(CCharString("a")), Equals(0))
		AssertThat( *a.Find(CCharString("b")), Equals(1))
		AssertThat( *a.Find(CCharString("c")), Equals(2))
	}


};
