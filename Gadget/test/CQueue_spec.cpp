#include "stdafx.h"
#include "CheckLeaks.h"

#include "igloo/igloo.h"

#include "CQueue.h"
#include "UMath.h"
#include "VDictionary.h"


using namespace igloo;

USING_NAMESPACE_GADGET


template class TQueue<long>;


Context(TQueue_template)
{

	Spec(it_should_deal_with_resizing_list)
	{
		CQueue	q;
		long	i;
		long	n;
		VDictionary::Selector	j;
		VDictionary::Selector	nIn = 0;
		VDictionary::Selector	nOut = 0;

		for ( n = 0; n < 50; ++n )
		{
			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.Push( ++nIn ), IsTrue() );
			}

			AssertThat( q.Length(), Equals(20u) );

			for ( i = 0; i < 10; ++i )
			{
				j = q.Pop();
				AssertThat( j, Equals( ++nOut ) );
			}

			AssertThat( q.Length(), Equals(10u) );

			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.Push( ++nIn ), IsTrue() );
			}

			AssertThat( q.Length(), Equals(30u) );

			for ( i = 0; i < 30; ++i )
			{
				j = q.Pop();
				AssertThat( j, Equals(++nOut) );
			}

			AssertThat( q.Length(), Equals(0u) );
		}
	}

	Spec(it_should_deal_with_existing_entries_and_drop_duplicates)
	{
		CQueue	q;
		long	i;
		long	n;
		VDictionary::Selector	j;
		VDictionary::Selector	nIn = 0;
		VDictionary::Selector	nInSave = 0;
		VDictionary::Selector	nOut = 0;

		for ( n = 0; n < 50; ++n )
		{
			nInSave = nIn;
			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.Push( ++nIn ), IsTrue() );
			}

			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.Push( ++nInSave ), IsFalse() );
			}

			AssertThat( q.Length(), Equals(20u) );

			for ( i = 0; i < 10; ++i )
			{
				j = q.Pop();
				AssertThat( j, Equals( ++nOut ) );
			}

			AssertThat( q.Length(), Equals(10u) );

			nInSave = nIn;
			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.Push( ++nIn ), IsTrue() );
			}

			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.Push( ++nInSave ), IsFalse() );
			}

			AssertThat( q.Length(), Equals(30u) );

			for ( i = 0; i < 30; ++i )
			{
				j = q.Pop();
				AssertThat( j, Equals(++nOut) );
			}

			AssertThat( q.Length(), Equals(0u) );
		}
	}

	Spec(it_should_properly_handle_already_processed_entries)
	{
		CQueue	q;

		AssertThat( q.Push( 1u ), IsTrue() );
		AssertThat( q.Push( 0u ), IsTrue() );

		AssertThat( q.Pop(), Equals(1u) );
		AssertThat( q.Pop(), Equals(0u) );

		AssertThat( q.Push( 0u ), IsTrue() );

	}

};

