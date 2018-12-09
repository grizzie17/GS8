#include "stdafx.h"
#include "CheckLeaks.h"

#include "CVariantData.h"
#include "TPointer.h"
#include "CEqConstant.h"
#include "CEqOpAbs.h"
#include "CEqOpAdd.h"
#include "CEqOpAnd.h"
#include "CEqOpDecrement.h"
#include "CEqOpIncrement.h"
#include "CEqOpDivide.h"

#include "igloo/igloo.h"
//#include "EqualsFloat.h"

using namespace igloo;

using namespace Yogi::Gadget;

class MockDictionary : public VDictionary
{
public:
	virtual void			BeginCalculate( void ) {};
	virtual void			EndCalculate( void ) {};


	virtual Selector		LocateEntry( ConstCCharStringRef rName ) { return 0; };
	virtual Selector		LocateEntry( const char* sName )
	{
		CCharString	s(sName);
		return LocateEntry( s );
	};

	virtual CVariantDataPtr	GetData( Selector nSel ) { return 0;};
	virtual bool			PutData( Selector nSel, CVariantDataPtr pData ) {return false;};

	virtual bool			IsDataLocked( Selector nSel ) { return false; };


	virtual	bool			PushDictionaryPage( VDictionaryPage* pDict ) {return false;};
	virtual bool			PopDictionaryPage( void ) {return false;};


	virtual bool			IsDirty( void ) {return false;};
	virtual long			GetMilliseconds( void ) {return 0;};

	// type is returned as an integer letter
	virtual int				GetType( void ) {return 0;};	// return type of dictionary


	virtual VDictionaryEnumerator*
		GetEnumerator( void ) {return 0;};
	virtual VDictionaryEnumerator*
		GetPageEnumerator( char cPageID ) {return 0;};

	virtual VVariablePtr	GetVariableIF( void ) {return 0;};

};

Context(CEqConstant_class)
{
	MockDictionary		dict;

	Spec(it_contains_a_constant)
	{
		CVariantData		v(1.0f);
		CEquationConstant	eq;

		eq.SetValue(v);

		CVariantData	x;

		x = eq.GetValue( &dict );

		AssertThat( (v == x), IsTrue() );
	}

	Spec(it_can_be_cloned)
	{
		CVariantData		v(1.0f);
		CEquationConstant	eq;

		eq.SetValue(v);

		TPointer<VEquation>	p = eq.Clone();
		AssertThat( (void*)p, Is().GreaterThan((void*)0) );

		CVariantData	x;

		x = p->GetValue( &dict );
		AssertThat( (v == x), IsTrue() );
	}
};

Context(CEqOpAbs_class)
{
	MockDictionary	dict;

	Spec(it_will_force_absolute_value_on_floats)
	{
		Leaks	k;
		{
			CVariantData			v(-2.0f);
			CEquationConstantPtr	pC = new CEquationConstant;
			TPointer<CEquationOperatorAbs>	pEq = new CEquationOperatorAbs;

			pC->SetValue(v);

			pEq->SetOperand( pC );

			CVariantData	x;

			x = pEq->GetValue( &dict );

			AssertThat( (x == 2.0f), IsTrue() );
		}
		AssertThat( k.HasLeaks(), IsFalse() );
	}

	Spec(it_will_force_absolute_value_on_ints)
	{
		CVariantData			v(-3L);
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorAbs>	pEq = new CEquationOperatorAbs;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x;

		x = pEq->GetValue( &dict );

		AssertThat( (x == 3L), IsTrue() );
	}

	Spec(it_will_ignore_nonnumeric_operands)
	{
		CVariantData			v("string");
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorAbs>	pEq = new CEquationOperatorAbs;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x;

		x = pEq->GetValue( &dict );

		AssertThat( (x == "string"), IsTrue() );
	}
};

Context(CEqOpAdd_class)
{
	MockDictionary	dict;

	Spec(it_will_add_two_numbers)
	{
		CVariantData	v1(1.0f);
		CVariantData	v2(2.0f);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorAdd>	pEq = new CEquationOperatorAdd;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x;

		x = pEq->GetValue( &dict );

		AssertThat( (x == 3.0f), IsTrue() );

	}

	Spec(it_will_concatenate_two_strings)
	{
		Leaks	k;
		{
			CVariantData	v1("one string");
			CVariantData	v2("second string");

			CEquationConstantPtr	pC1 = new CEquationConstant;
			CEquationConstantPtr	pC2 = new CEquationConstant;

			pC1->SetValue(v1);
			pC2->SetValue(v2);

			TPointer<CEquationOperatorAdd>	pEq = new CEquationOperatorAdd;

			pEq->SetLeft(pC1);
			pEq->SetRight(pC2);

			CVariantData	x;

			x = pEq->GetValue( &dict );

			AssertThat( (x == "one stringsecond string"), IsTrue() );
		}
		AssertThat( k.HasLeaks(), IsFalse() );
	}

	Spec(it_will_concatenate_a_number_onto_a_string)
	{
		CVariantData	v1("one string ");
		CVariantData	v2(2L);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorAdd>	pEq = new CEquationOperatorAdd;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x;

		x = pEq->GetValue( &dict );

		AssertThat( (x == "one string 2"), IsTrue() );
	}
};

Context(CEqOpAnd_class)
{
	MockDictionary	dict;

	Spec(it_will_succeed_for_two_true_operands)
	{
		CVariantData	v1(true);
		CVariantData	v2(true);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorAnd>	pEq = new CEquationOperatorAnd;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x = pEq->GetValue( &dict );

		bool	b = x;

		AssertThat( b, IsTrue() );

	}

	Spec(it_will_fail_for_one_true_one_false_operands)
	{
		CVariantData	v1(true);
		CVariantData	v2(false);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorAnd>	pEq = new CEquationOperatorAnd;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x = pEq->GetValue( &dict );

		bool	b = x;

		AssertThat( b, IsFalse() );
	}

	Spec(it_will_fail_for_two_false_operands)
	{
		CVariantData	v1(false);
		CVariantData	v2(false);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorAnd>	pEq = new CEquationOperatorAnd;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x = pEq->GetValue( &dict );

		bool	b = x;

		AssertThat( b, IsFalse() );
	}

};

Context(CEqOpDecrement_class)
{
	MockDictionary	dict;

	Spec(it_will_decrement_value_on_floats)
	{
		CVariantData			v(2.0f);
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorDecrement>	pEq = new CEquationOperatorDecrement;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x = pEq->GetValue( &dict );

		AssertThat( (x == 1.0f), IsTrue() );
	}

	Spec(it_will_decrement_value_on_ints)
	{
		CVariantData			v(2L);
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorDecrement>	pEq = new CEquationOperatorDecrement;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x = pEq->GetValue( &dict );

		AssertThat( (x == 1L), IsTrue() );
	}

	Spec(it_will_ignore_other_types)
	{
		CVariantData			v("string");
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorAbs>	pEq = new CEquationOperatorAbs;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x = pEq->GetValue( &dict );

		AssertThat( (x == "string"), IsTrue() );
	}

};

Context(CEqOpIncrement_class)
{
	MockDictionary	dict;

	Spec(it_will_increment_value_on_floats)
	{
		CVariantData			v(2.0f);
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorIncrement>	pEq = new CEquationOperatorIncrement;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x = pEq->GetValue( &dict );

		AssertThat( (x == 3.0f), IsTrue() );
	}

	Spec(it_will_increment_value_on_ints)
	{
		CVariantData			v(2L);
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorIncrement>	pEq = new CEquationOperatorIncrement;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x = pEq->GetValue( &dict );

		AssertThat( (x == 3L), IsTrue() );
	}

	Spec(it_will_ignore_other_types)
	{
		CVariantData			v("string");
		CEquationConstantPtr	pC = new CEquationConstant;
		TPointer<CEquationOperatorIncrement>	pEq = new CEquationOperatorIncrement;

		pC->SetValue(v);

		pEq->SetOperand( pC );

		CVariantData	x = pEq->GetValue( &dict );

		AssertThat( (x == "string"), IsTrue() );
	}

};



Context(CEqOpDivide_class)
{
	MockDictionary	dict;

	Spec(it_will_divide_two_numbers)
	{
		CVariantData	v1(100.0f);
		CVariantData	v2(20.0f);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorDivide>	pEq = new CEquationOperatorDivide;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x = pEq->GetValue( &dict );

		GFLOAT	f = x;

		AssertThat( f, Equals(5.0) );

	}

	Spec(it_will_be_graceful_about_zero_denominator)
	{
		CVariantData	v1(100.0f);
		CVariantData	v2(0.0f);

		CEquationConstantPtr	pC1 = new CEquationConstant;
		CEquationConstantPtr	pC2 = new CEquationConstant;

		pC1->SetValue(v1);
		pC2->SetValue(v2);

		TPointer<CEquationOperatorDivide>	pEq = new CEquationOperatorDivide;

		pEq->SetLeft(pC1);
		pEq->SetRight(pC2);

		CVariantData	x = pEq->GetValue( &dict );

		GFLOAT	f = x;

		AssertThat( f, Equals(0.0) );
	}


};
