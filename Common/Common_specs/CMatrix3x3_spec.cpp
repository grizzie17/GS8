
#include "stdafx.h"
#include "CMatrix3x3.h"

#include "igloo/igloo.h"

#include "EqualsFloat.h"


using namespace igloo;

USING_NAMESPACE_COMMON

Context(CMatrix3x3_class)
{
	Spec(default_init_should_be_identity)
	{
		CMatrix3x3	m;

		GFLOAT	m1, m2, m3,
				m4, m5, m6,
				m7, m8, m9;

		m.Get( &m1, &m2, &m3,
				&m4, &m5, &m6,
				&m7, &m8, &m9 );

		AssertThat( m1, EqualsFloat(1.0f));
		AssertThat( m5, EqualsFloat(1.0f));
		AssertThat( m9, EqualsFloat(1.0f));

		AssertThat( m2, EqualsFloat(0.0f));
		AssertThat( m3, EqualsFloat(0.0f));
		AssertThat( m4, EqualsFloat(0.0f));
		AssertThat( m6, EqualsFloat(0.0f));
		AssertThat( m7, EqualsFloat(0.0f));
		AssertThat( m8, EqualsFloat(0.0f));
	}

	Spec(it_can_tell_if_its_identity)
	{
		CMatrix3x3	m;

		AssertThat( m.IsIdentity(), IsTrue() );
	}

	Spec(it_should_be_able_to_compare_equality)
	{
		CMatrix3x3	m1(	1.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						5.0f, 3.0f, 1.0f );

		CMatrix3x3	m2( m1 );

		AssertThat( (m1 == m2), IsTrue() );

		m2.SelfRotate( 3.14f * 0.25f );

		AssertThat( (m1 != m2), IsTrue() );
	}

	Spec(it_can_apply_translation)
	{
		CMatrix3x3	m1;
		CMatrix3x3	m2(	1.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						5.0f, 3.0f, 1.0f );

		m1.SelfTranslate( 5.0f, 3.0f );

		AssertThat( m1, Equals(m2) );
	}

	Spec(it_can_apply_rotation)
	{
		CMatrix3x3	m1;

		const float	r = 3.14f * 0.25f;	// 45 degrees
		float	fSin = sinf( r );
		float	fCos = cosf( r );
		CMatrix3x3	m2(	fCos, -fSin, 0.0f,
						fSin, fCos, 0.0f,
						0.0f, 0.0f, 1.0f );

		m1.SelfRotate( r );

		AssertThat( m1, Equals(m2) );
	}

	Spec(it_can_tell_if_its_affine)
	{
		CMatrix3x3	m;

		m *= CMatrix3x3::_Rotate(3.14f*0.5f);
		m *= CMatrix3x3::_Translate( 5.0f, 3.0f );

		AssertThat( m.IsAffine(), IsTrue() );

		m = m.Transpose();

		AssertThat( m.IsAffine(), IsFalse() );
	}

	Spec(it_should_allow_assignment)
	{
		CMatrix3x3	m1(	1.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						5.0f, 3.0f, 1.0f );

		CMatrix3x3	m2;

		m2 = m1;

		AssertThat( m2, Equals(m1));
	}

	Spec(it_should_apply_scale)
	{
		CMatrix3x3	m1;

		m1.SelfScale( 2.0f, 2.0f );

		CMatrix3x3	m2(	2.0f, 0.0f, 0.0f,
						0.0f, 2.0f, 0.0f,
						0.0f, 0.0f, 1.0f );

		AssertThat( m1, Equals(m2) );
	}

	Spec(it_can_perform_transformations_on_points)
	{
		CMatrix3x3	m1(	1.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						5.0f, 3.0f, 1.0f );
		GFLOAT	x = 0.0f;
		GFLOAT	y = 0.0f;

		GFLOAT	x1;
		GFLOAT	y1;

		m1.Transform( x1, y1, x, y );

		AssertThat( x1, EqualsFloat(5.0f) );
		AssertThat( y1, EqualsFloat(3.0f) );

	}


};
