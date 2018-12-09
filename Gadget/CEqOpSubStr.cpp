/*---------------------------------------------------------------------+\
|
|	CEqOpSubStr.cpp  --  brief description of what CEqOpSubStr.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	24-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpSubStr.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
//USING_NAMESPACE_COMMON
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CEquationOperatorSubStr - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorSubStr::CEquationOperatorSubStr
		(
		void
		)
		: VEquationOperatorTrinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorSubStr - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorSubStr::CEquationOperatorSubStr
		(
		CEquationOperatorSubStrRef	r
		)
		: VEquationOperatorTrinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorSubStr - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorSubStr::~CEquationOperatorSubStr
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CEquationOperatorSubStrRef
		CEquationOperatorSubStr::operator=
		(
		CEquationOperatorSubStrRef	r
		)
{
	VEquationOperatorTrinary::operator =( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorSubStr::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CCharString		sResult;
	CVariantData	vControl( m_pControl->GetValue( pDict ) );
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	long			nStart = vLeft;
	long			nCount = vRight;
	CCharString		sStr = vControl;

	size_t			nLen = sStr.Length();

	if ( 0 < nLen )
	{
		if ( size_t(nStart) < nLen )
		{
			long	n = nStart + nCount;
			if ( long(nLen) < n )
				nCount = long(nLen - nStart);
		}
		sResult.LoadStringData( sStr.Pointer( nStart ), nCount );
	}

	return CVariantData( sResult );
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationOperatorSubStr::Clone
		(
		void
		)
{
	return new CEquationOperatorSubStr( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
