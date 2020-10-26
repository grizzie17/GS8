
#include "gtest/gtest.h"
#include <string.h>

#include "CVariables.h"

#include "iggy.h"

// #include "igloo/igloo.h"
// using namespace igloo;

using namespace Yogi::Common;
using namespace Yogi::Core;


class MockVariable : public VVariable
{
public:
    MockVariable() {};
    ~MockVariable() {};

public:
    virtual CCharString
    ResolveVariable( ConstCCharDescriptorRef r ) override
    {
        if ( r == "george" )
            return CCharString( "GEORGIA" );
        else if ( r == "bob" )
            return CCharString( "ROBERT" );
        else
            return CCharString();
    };
};


class MyFixture : public ::testing::Test
{
protected:
    virtual void
    SetUp() override
    {
        inherited::SetUp();
        m_pVars = new CVariables( &m_mock );
    }

    virtual void
    TearDown() override
    {
        delete m_pVars;
        m_pVars = nullptr;
        inherited::TearDown();
    }

    MockVariable  m_mock;
    CVariablesPtr m_pVars;

private:
    typedef ::testing::Test inherited;
};

TEST_F( MyFixture, it_should_translate_simple_variable )
{
    CCharString sample( "$(george)" );

    CCharString s = m_pVars->Substitute( sample );

    ASSERT_TRUE( s == "GEORGIA" );
}

TEST_F( MyFixture, it_should_translate_with_embedded_variable )
{
    CCharString sample( "some prefix $(bob) some postfix" );
    CCharString s = m_pVars->Substitute( sample );

    ASSERT_TRUE( s == "some prefix ROBERT some postfix" );
}

TEST_F( MyFixture, it_should_not_process_a_non_existent_variable )
{
    CCharString sample( "$(anything)" );
    CCharString s = m_pVars->Substitute( sample );

    ASSERT_TRUE( s == "$(anything)" );
}


TEST_F( MyFixture, it_should_ignore_malformed_variable )
{
    CCharString sample( "$1.0, $(abc xyz $(bob)" );
    CCharString s = m_pVars->Substitute( sample );

    ASSERT_TRUE( s == "$1.0, $(abc xyz ROBERT" );
}
