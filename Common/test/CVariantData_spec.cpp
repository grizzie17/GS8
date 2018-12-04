#include "stdafx.h"
#include "CVariantData.h"
#include "igloo/igloo.h"
#include "EqualsFloat.h"


using namespace igloo;

USING_NAMESPACE_COMMON

Context(CVariantData_class)
{
	Spec(it_can_hold_float_data)
	{
		CVariantData	v(1.0);

		AssertThat(v.GetType(), Equals(CVariantData::T_FLOAT) );
	}

	Spec(it_can_hold_integer_data)
	{
		CVariantData	v(1L);

		AssertThat(v.GetType(), Equals(CVariantData::T_INTEGER) );
	}

	Spec(it_can_hold_character_string_data)
	{
		CVariantData	v("string");

		AssertThat(v.GetType(), Equals(CVariantData::T_STRING) );
	}

	Spec(it_can_hold_boolean_data)
	{
		CVariantData	v(true);

		AssertThat(v.GetType(), Equals(CVariantData::T_BOOL) );
	}

	Spec(it_can_hold_color_data)
	{
		CColor	c( 255, 127, 63 );
		CVariantData	v(c);

		AssertThat(v.GetType(), Equals(CVariantData::T_COLOR) );
	}

	Spec(it_can_hold_datetime_data)
	{
		CDateTime	d("20010911T100301");
		CVariantData	v(d);

		AssertThat(v.GetType(), Equals(CVariantData::T_DATETIME) );
	}

	Spec(it_can_change_type)
	{
		CVariantData	v;
		AssertThat( v.GetType(), Equals(CVariantData::T_UNDEFINED) );

		v = 1.0f;
		AssertThat( v.GetType(), Equals(CVariantData::T_FLOAT) );

		v = 1L;
		AssertThat( v.GetType(), Equals(CVariantData::T_INTEGER) );

		v = "string";
		AssertThat( v.GetType(), Equals(CVariantData::T_STRING) );

		CDateTime	d(2000, 1, 1, 13, 0, 0);
		v = d;
		AssertThat( v.GetType(), Equals(CVariantData::T_DATETIME) );

		CColor	c("green");
		v = c;
		AssertThat( v.GetType(), Equals(CVariantData::T_COLOR) );

		v = true;
		AssertThat( v.GetType(), Equals(CVariantData::T_BOOL) );
	}

	Spec(it_can_compare_equality)
	{
		CVariantData	v(1.0f);

		AssertThat( (v == 1.0f), IsTrue() );
		AssertThat( (v == "1.0"), IsTrue() );

		v = "string";
		AssertThat( (v == "string"), IsTrue() );

		CColor	c("blue");
		v = c;
		AssertThat( (v == "blue"), IsTrue() );

		v = true;
		AssertThat( (v == true), IsTrue() );

		CDateTime	d(2000, 1, 1, 13, 0, 0 );
		v = d;
		AssertThat( (v == d), IsTrue() );

		// compare with 'undefined' which should act like zero or null
		CVariantData	u;

		v = "";
		AssertThat( (v == u), IsTrue() );
		AssertThat( (u == v), IsTrue() );
		AssertThat( (u == ""), IsTrue() );

		v = 0L;
		AssertThat( (v == u), IsTrue() );
		AssertThat( (u == v), IsTrue() );

		v = 0.0f;
		AssertThat( (v == u), IsTrue() );
		AssertThat( (u == v), IsTrue() );
	}

	Spec(it_can_compare_lessthan)
	{
		CVariantData	v1(1.0f);
		CVariantData	v2(2.0f);

		AssertThat( (v1 < v2), IsTrue() );

		CVariantData	u; // undefined

		AssertThat( (u < v1), IsTrue() );

		v1 = false;
		v2 = true;
		AssertThat( (v1 < v2), IsTrue() );
		AssertThat( (u < v2), IsTrue() );

		v1 = "abc";
		v2 = "def";
		AssertThat( (v1 < v2), IsTrue() );
		AssertThat( (u < v2), IsTrue() );
		AssertThat( (v2 < v1), IsFalse() );
		AssertThat( (v1 < u), IsFalse() );
	}

	Spec(it_can_convert_types)
	{
		CVariantData	v(1.0f);

		CCharString		s = v.GetValueCCharString();

		AssertThat( (s == "1.000000"), IsTrue() );
	}

	Spec(it_deals_correctly_with_units)
	{
		CVariantData	v(32.0);
		CUnitsOfMeasure	uF("fahrenheit");
		CUnitsOfMeasure	uC("centigrade");

		AssertThat( uF.GetUnits(), IsGreaterThan(0) );
		AssertThat( uC.GetUnits(), IsGreaterThan(0) );

		v.SetUnits( uF );

		GFLOAT	f = v.GetValueFloatAsUnits(uC);
		AssertThat( f, EqualsFloat(0.0) );
	}

};
