#include "stdafx.h"
#include "CUnitsOfMeasure.h"
#include "igloo/igloo.h"

#include "EqualsFloat.h"
#include "UMath.h"


using namespace igloo;

using namespace Yogi::Common;


Context(CUnitsOfMeasure_class)
{
	Spec(it_can_translate_strings_into_UOM_id)
	{
		CUnitsOfMeasure	u;
		u.SetUsingString( "meter" );

		AssertThat( u.GetUnits(), IsGreaterThan(0) );
	}

	Spec(it_can_be_initialized_using_name)
	{
		CUnitsOfMeasure	u("meter");
		AssertThat( u.GetUnits(), IsGreaterThan(0) );
	}

	Spec(it_can_convert_temperatures)
	{
		CUnitsOfMeasure	uF("fahrenheit");
		CUnitsOfMeasure	uC("centigrade");

		GFLOAT	f = CUnitsOfMeasure::Convert( uC, uF, 32.0f );
		AssertThat( f, EqualsFloat(0.0) );

		// -40 is the same for both C & F
		f = CUnitsOfMeasure::Convert( uC, uF, -40.0f );
		AssertThat( f, EqualsFloat(-40.0) );
	}

	Spec(it_can_convert_distances)
	{
		CUnitsOfMeasure	uKm("km");
		CUnitsOfMeasure uM("meter");
		CUnitsOfMeasure	uFt("foot");
		CUnitsOfMeasure uYd("yard");
		CUnitsOfMeasure uIn("inch");
		CUnitsOfMeasure	uMi("mile");

		GFLOAT	f = CUnitsOfMeasure::Convert( uM, uKm, 1.0f );
		AssertThat( f, EqualsFloat(1000.0f) );

		f = CUnitsOfMeasure::Convert( uKm, uM, 1000.0f );
		AssertThat( f, EqualsFloat(1.0f) );

		f = CUnitsOfMeasure::Convert( uYd, uFt, 3.0f );
		AssertThat( f, EqualsFloat(1.0f) );

		f = CUnitsOfMeasure::Convert( uMi, uFt, 5280.0f );
		AssertThat( f, EqualsFloat(1.0f) );

		f = CUnitsOfMeasure::Convert( uIn, uYd, 1.0f );
		AssertThat( f, EqualsFloat(36.0) );

	}

	Spec(it_can_convert_gallons)
	{
		CUnitsOfMeasure	uGal("gallon");
		CUnitsOfMeasure	uQt("quart");

		GFLOAT	f = CUnitsOfMeasure::Convert( uQt, uGal, 1.0f );
		AssertThat( f, EqualsFloat(4.0f) );
	}

	Spec(it_can_convert_liters)
	{
		CUnitsOfMeasure	uL("liter");
		CUnitsOfMeasure uCC("cubic centimeter");

		GFLOAT	f = CUnitsOfMeasure::Convert( uCC, uL, 1.0f );
		AssertThat( f, EqualsFloat( 1000.0f ) );
	}

	Spec(it_can_convert_liters_to_gallons)
	{
		CUnitsOfMeasure	uL("liter");
		CUnitsOfMeasure	uGal("gallon");
		CUnitsOfMeasure	uQt("quart");

		GFLOAT	f = CUnitsOfMeasure::Convert( uL, uGal, 1.0f );
		AssertThat( f, EqualsFloat( 3.7854117 ) );

		f = CUnitsOfMeasure::Convert( uQt, uL, 1.0f );
		AssertThat( f, EqualsFloat( 1.05669 ) );
	}

	Spec(it_can_convert_angles)
	{
		CUnitsOfMeasure	uRad("radian");
		CUnitsOfMeasure	uDeg("degree");
		CUnitsOfMeasure	uGrd("grad");

		GFLOAT	f = CUnitsOfMeasure::Convert( uRad, uDeg, 180.0f );
		AssertThat( f, EqualsFloat( kPI ) );

		f = CUnitsOfMeasure::Convert( uGrd, uDeg, 90.0f );
		AssertThat( f, EqualsFloat( 100.0 ) );
	}

	Spec(it_can_convert_angular_velocity)
	{
		CUnitsOfMeasure	uRPM("rpm");
		CUnitsOfMeasure	uRadS("radian per second");
		CUnitsOfMeasure	uDPS("degree per second");

		GFLOAT	f = CUnitsOfMeasure::Convert( uDPS, uRPM, 1.0f );
		AssertThat( f, EqualsFloat(360.0/60.0) );

		f = CUnitsOfMeasure::Convert( uRadS, uRPM, 1.0f );
		AssertThat( f, EqualsFloat(kPI2/60.0) );
	}

	Spec(it_can_convert_time)
	{
		CUnitsOfMeasure	uSec("second");
		CUnitsOfMeasure	uMin("minute");
		CUnitsOfMeasure	uHr("hour");
		CUnitsOfMeasure	uDay("day");
		GFLOAT	f;

		f = CUnitsOfMeasure::Convert( uSec, uMin, 1.0f );
		AssertThat( f, EqualsFloat( 60.0 ) );

		f = CUnitsOfMeasure::Convert( uMin, uHr, 1.0f );
		AssertThat( f, EqualsFloat( 60.0 ) );

		f = CUnitsOfMeasure::Convert( uHr, uDay, 1.0f );
		AssertThat( f, EqualsFloat( 24.0 ) );
	}

	Spec(it_can_convert_weights)
	{
		CUnitsOfMeasure	uKg("kilogram");
		CUnitsOfMeasure	uG("gram");
		CUnitsOfMeasure	uLB("pound");
		CUnitsOfMeasure	uOz("ounce");
		GFLOAT	f;

		f = CUnitsOfMeasure::Convert( uG, uKg, 1.0f );
		AssertThat( f, EqualsFloat(1000.0) );

		f = CUnitsOfMeasure::Convert( uOz, uLB, 1.0f );
		AssertThat( f, EqualsFloat(16.0) );

		f = CUnitsOfMeasure::Convert( uLB, uOz, 16.0f );
		AssertThat( f, EqualsFloat(1.0) );
	}

	Spec(it_can_convert_areas)
	{
		CUnitsOfMeasure	uSqM("square meter");
		CUnitsOfMeasure	uSqCm("square centimeter");
		CUnitsOfMeasure	uSqFt("square foot");
		CUnitsOfMeasure	uSqIn("square inch");
		GFLOAT	f;

		f = CUnitsOfMeasure::Convert( uSqCm, uSqM, 1.0f );
		AssertThat( f, EqualsFloat(10000.0) );

		f = CUnitsOfMeasure::Convert( uSqIn, uSqFt, 1.0f );
		AssertThat( f, EqualsFloat(12.0*12.0) );
	}
};

