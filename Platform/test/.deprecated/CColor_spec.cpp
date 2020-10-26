#include "stdafx.h"

#include "CColor.h"

#include "igloo/igloo.h"
using namespace igloo;

using namespace Yogi::Core;

Context(CColor_class)
{
	Spec(it_should_initialize_to_noncolor)
	{
		CColor	t;

		AssertThat( t.IsNonColor(), IsTrue() );
	}

	Spec(enumeration_of_named_colors_should_be_allowed)
	{
		CColorEnumerator	e = CColor::GetEnumerator();

		while ( e.MoveNext() )
		{
			const ColorName*	p = e.Current();

			CColor	c = CColor::ColorFromName(p->sName);
			AssertThat( c.IsNonColor(), IsFalse() );
		}
	}

	Spec(it_supports_getting_its_components)
	{
		CColor	c( 200, 100, 50 );

		AssertThat( c.GetRed(), Equals(200U) );
		AssertThat( c.GetGreen(), Equals(100U) );
		AssertThat( c.GetBlue(), Equals(50U) );
	}

	Spec(it_supports_copy)
	{
		CColor	c1( 200, 100, 50 );
		CColor	c2;

		c2 = c1;

		AssertThat( c2.GetRed(), Equals(200u) );
		AssertThat( c2.GetGreen(), Equals(100u) );
		AssertThat( c2.GetBlue(), Equals(50u) );
	}

	Spec(it_supports_equality_comparison)
	{
		CColor	c1( 200, 100, 50 );
		CColor	c2( c1 );

		AssertThat( (c2 == c1), IsTrue() );

		c2 = CColor( 10, 10, 10 );

		AssertThat( (c2 != c1), IsTrue() );
	}

	Spec(it_can_return_its_value)
	{
		CColor		c( 0xFF, 0xCC, 0x33 );

		COLORDATA	d = c;

		AssertThat( d, Equals(0x0033CCFFu) );
	}

	COLORDATA	colorArg( COLORDATA c )
	{
		return c;
	}

	Spec(it_can_offer_its_value_as_an_argument)
	{
		CColor		c( 0xFF, 0xCC, 0x33 );

		COLORDATA	d = colorArg(c);

		AssertThat( d, Equals(0x0033CCFFu) );
	}

};

