
#include "stdafx.h"
#include "igloo/igloo.h"

#include "ISupports.h"
#include "VSupports.h"
#include "TComPointer.h"

using namespace igloo;

using namespace Yogi::Common;
using namespace Yogi::Core;

extern const IXID	IXID_IGeorge;


const IXID	IXID_IGeorge( "BCG::Common::IGeorge" );

interface_ IGeorge : public ISupports
{
	virtual NRefCount GetRefCount() = 0;
};

class XCom : implements_ IGeorge
{
	NRefCount	m_nRefCount;

public:

	XCom() : m_nRefCount(0) {}

	virtual void* QueryInterface(ConstIXIDRef rIID, NResultPtr pResult = 0)
	{
		ISupportsPtr	p(0);
		if ( rIID == IXID_ISupports )
			p = INTERFACE_THIS( ISupports* );
		else if ( rIID == IXID_IGeorge )
			p = INTERFACE_THIS( IGeorge* );
		if ( p )
		{
			p->AddRef();
		}

		return p;
	}

	virtual NRefCount AddRef( void )
	{
		if ( m_nRefCount < 0 )
			m_nRefCount = 1;
		else
			++m_nRefCount;
		return m_nRefCount;
	}

	virtual NRefCount Release( void )
	{
		NRefCount	n = 0;

		if ( 0 < m_nRefCount )
			n = --m_nRefCount;

		if ( n < 1 )
		{
			delete this;
		}

		return n;
	}

	virtual NRefCount GetRefCount( void )
	{
		return m_nRefCount;
	}
protected:
	virtual ~XCom(){};
};

Context(TComPointer_template)
{


	Spec(it_should_support_initialization_via_contructor)
	{
		TIP(IGeorge)	p = new XCom;

		AssertThat( p->GetRefCount(), Equals(1u) );

		{
			TIP(IGeorge) p2 = p;

			AssertThat( p->GetRefCount(), Equals(2u) );
		}

		AssertThat( p->GetRefCount(), Equals(1u) );
	}

};

