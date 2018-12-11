
#include "stdafx.h"
#include <string.h>
#include "igloo/igloo.h"

#include "CVariables.h"

using namespace igloo;

using namespace Yogi::Common;
using namespace Yogi::Core;


class MockVariable : public VVariable
{
public:
	MockVariable() {};
	~MockVariable() {};

public:

	virtual CCharString	ResolveVariable( ConstCCharDescriptorRef r ) const
	{
		if ( r == "george" )
			return CCharString( "GEORGIA" );
		else if ( r == "bob" )
			return CCharString( "ROBERT" );
		else
			return CCharString();
	};


};

Context(CVariables_class)
{
	MockVariable	m_mock;
	CVariablesPtr	m_pVars;

	void SetUp()
	{
		m_pVars = new CVariables( &m_mock );
	}

	void TearDown()
	{
		delete m_pVars;
	}

	Spec(it_should_translate_simple_variable)
	{
		CCharString	sample( "$(george)" );

		CCharString	s = m_pVars->Substitute( sample );

		AssertThat( (s == "GEORGIA"), IsTrue() );

	}

	Spec(it_should_translate_with_embedded_variable)
	{
		CCharString	sample( "some prefix $(bob) some postfix" );
		CCharString s = m_pVars->Substitute( sample );

		AssertThat( (s == "some prefix ROBERT some postfix"), IsTrue() );
	}

	Spec(it_should_not_process_a_non_existent_variable)
	{
		CCharString sample( "$(anything)" );
		CCharString	s = m_pVars->Substitute( sample );

		AssertThat( (s == "$(anything)"), IsTrue() );
	}

	Spec(it_should_ignore_malformed_variable)
	{
		CCharString	sample( "$1.0, $(abc xyz $(bob)" );
		CCharString	s = m_pVars->Substitute( sample );

		AssertThat( (s == "$1.0, $(abc xyz ROBERT"), IsTrue() );
	}

};
