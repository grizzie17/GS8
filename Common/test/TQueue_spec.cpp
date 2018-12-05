#include "stdafx.h"
#include "CheckLeaks.h"
//#include <stdio.h>

#include "igloo/igloo.h"

#include "TQueue.h"
#include "UMath.h"


using namespace igloo;

using namespace Yogi::Common;


template class TQueue<long>;


Context(TQueue_template)
{
	Spec(it_is_initialized_as_empty)
	{
		Leaks	k;
		{
			TQueue<long>	q;

			AssertThat( q.IsEmpty(), IsTrue() );

			long	n;

			AssertThat( q.FetchEntry(n), IsFalse() );
		}
		AssertThat( k.HasLeaks(), IsFalse() );
	}

	Spec(it_will_collect_entries)
	{
		Leaks	k;
		{
			TQueue<long>	q;

			q.AppendEntry( 1L );

			AssertThat( q.IsEmpty(), IsFalse() );

			q.AppendEntry( 2L );
			q.AppendEntry( 3L );
			q = 4L;

			AssertThat( q.Length(), Equals(4u) );

			//char*	a = new char[45];
			//AssertThat( a, IsGreaterThan((char*)0) );
		}
		AssertThat( k.HasLeaks(), IsFalse() );
	}

	Spec(it_will_allow_writing_directly_to_internal_buffer)
	{
		TQueue<long>				q;
		TQueue<long>::Enumerator	e;

		AssertThat( q.IsEmpty(), IsTrue() );

		size_t	n = q.GetWriteEnumerator( e, 4u );
		AssertThat( n, Equals( 4u ) );
		AssertThat( e.v[0].p, !Equals( (void*)0 ) );
		AssertThat( e.v[0].n, IsGreaterThan( 0u ) );

		long	j = 0;
		while ( e.MoveNext() )
		{
			*(e.Current()) = j++;
		}


		size_t	k = q.WriteAdvance( e.Length() );
		AssertThat( q.Length(), Equals( n ) );
		AssertThat( k, Equals(n) );
	}

	Spec(it_will_allow_read_direct_from_internal_buffer)
	{
		TQueue<long>				q;
		TQueue<long>::Enumerator	e;

		AssertThat( q.IsEmpty(), IsTrue() );

		long	j = 0;
		q.AppendEntry( j++ );
		q.AppendEntry( j++ );
		q.AppendEntry( j++ );
		q.AppendEntry( j++ );

		size_t	n = q.GetReadEnumerator( e );
		AssertThat( n, Equals( 4u ) );

		j = 0;
		while ( e.MoveNext() )
		{
			long*	p = e.Current();
			AssertThat( *p, Equals( j++ ) );
		}

		size_t	k = q.ReadAdvance( n );
		AssertThat( k, Equals(n) );

		AssertThat( q.Length(), Equals( 0u ) );
	}

	Spec(it_will_act_like_discrete)
	{
		TQueue<long>	q;

		AssertThat( q.IsEmpty(), IsTrue() );

		q = 1L;

		AssertThat( q.IsEmpty(), IsFalse() );

		long	n = q;

		AssertThat( q.IsEmpty(), IsTrue() );

		AssertThat( n, Equals(1) );
	}

	Spec(it_implements_a_fifo_list)
	{
		TQueue<long>	q;
		long			list[] = {1, 2, 3, 4, 5};

		q.AppendEntries( list, numberof(list) );

		AssertThat( q.Length(), Equals(numberof(list)) );

		long	n;

		for (size_t i = 0; i < numberof(list); ++i )
		{
			AssertThat( q.FetchEntry(n), IsTrue() );
			AssertThat( n, Equals(list[i]) );
		}

	}

	Spec(it_should_deal_with_resizing_list)
	{
		TQueue<long>	q;
		long	i;
		long	j;
		long	n;
		long	nIn = 0;
		long	nOut = 0;

		for ( n = 0; n < 50; ++n )
		{
			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.AppendEntry( ++nIn ), IsTrue() );
			}

			AssertThat( q.Length(), Equals(20u) );

			for ( i = 0; i < 10; ++i )
			{
				AssertThat( q.FetchEntry( j ), IsTrue() );
				AssertThat( j, Equals( ++nOut ) );
			}

			AssertThat( q.Length(), Equals(10u) );

			for ( i = 0; i < 20; ++i )
			{
				AssertThat( q.AppendEntry( ++nIn ), IsTrue() );
			}

			AssertThat( q.Length(), Equals(30u) );

			for ( i = 0; i < 30; ++i )
			{
				AssertThat( q.FetchEntry( j ), IsTrue() );
				AssertThat( j, Equals(++nOut) );
			}

			AssertThat( q.Length(), Equals(0u) );
		}
	}

	Spec(it_should_deal_with_resizing_list2)
	{
		TQueue<long>				q;
		TQueue<long>::Enumerator	e;
		long	i;
		long	n;
		size_t	m;
		long	nIn = 0;
		long	nOut = 0;

		// todo: we need to create an enumerator to use

		for ( n = 0; n < 50; ++n )
		{
			m = q.GetWriteEnumerator( e, 20 );
			AssertThat( m, Equals( 20u ) );
			while ( e.MoveNext() )
			{
				long*	p = e.Current();
				*p = ++nIn;
			}
			q.WriteAdvance( m );
			AssertThat( q.Length(), Equals(20u) );

			m = q.GetReadEnumerator( e );
			for ( i = 0; i < 10; ++i )
			{
				AssertThat( e.MoveNext(), IsTrue() );
				long*	p = e.Current();
				AssertThat( *p, Equals( ++nOut ) );
			}
			q.ReadAdvance( 10 );
			AssertThat( q.Length(), Equals(10u) );

			m = q.GetWriteEnumerator( e, 20 );
			while ( e.MoveNext() )
			{
				long*	p = e.Current();
				*p = ++nIn;
			}
			q.WriteAdvance( m );
			AssertThat( q.Length(), Equals(30u) );

			m = q.GetReadEnumerator( e );
			AssertThat( m, Equals( 30u ) );
			while ( e.MoveNext() )
			{
				long*	p = e.Current();
				AssertThat( *p, Equals(++nOut) );
			}
			q.ReadAdvance( m );
			AssertThat( q.Length(), Equals(0u) );
		}
	}
};
