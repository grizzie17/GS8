/*---------------------------------------------------------------------+\
|
|	CVariables.cpp  --  brief description of what CVariables.cpp is for
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CVariables.h"

NAMESPACE_COMMON_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * CVariables - constructor

\+---------------------------------------------------------------------*/
CVariables::CVariables
		(
		void
		)
		: m_pVariable( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CVariables - constructor

\+---------------------------------------------------------------------*/
CVariables::CVariables
		(
		VVariablePtr	pVariable
		)
		: m_pVariable( pVariable )
{
}

/*---------------------------------------------------------------------+\

 * ~CVariables - destructor

\+---------------------------------------------------------------------*/
CVariables::~CVariables
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * Substitute -

\+---------------------------------------------------------------------*/
NAMESPACE_ROOT_PREFIX CCharString
		CVariables::Substitute
		(
		NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef	rSource
		)
{
	NAMESPACE_ROOT_PREFIX CCharString	sNew;
	const char*	p = rSource.Pointer();
	const char*	pEnd = p + rSource.Length();
	long		n;

	while ( p < pEnd )
	{
		if ( '$' == *p )
		{
			n = SpanVariable( p, pEnd );
			if ( 0 < n )
			{
				NAMESPACE_ROOT_PREFIX CCharString	s;
				s = ProcessVariable( NAMESPACE_ROOT_PREFIX CCharDescriptor( p, (size_t)n ) );
				if ( 0 < s.Length() )
				{
					sNew += s;
				}
				else
				{
					//sNew += CCharDescriptor( p, n );
					sNew += "$";
					n = 1;
				}
			}
			else
			{
				sNew += "$";
				n = 1;
			}

		}
		else
		{
			n = SpanConstant( p, pEnd );
			sNew += NAMESPACE_ROOT_PREFIX CCharDescriptor( p, (size_t)n );
		}
		p += n;
	}
	return sNew;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * SpanConstant -

\+---------------------------------------------------------------------*/
long	CVariables::SpanConstant
		(
		const char*	pStart,
		const char*	pEnd
		)
{
	const char*	p = pStart;

	while ( p < pEnd )
	{
		if ( '$' == *p )
			break;
		++p;
	}

	return long(p - pStart);
}


/*---------------------------------------------------------------------+\

 * SpanVariable -

\+---------------------------------------------------------------------*/
long	CVariables::SpanVariable
		(
		const char*	pStart,
		const char*	pEnd
		)
{
	const char*	p = pStart;

	if ( '$' == *p )
	{
		if ( '(' == *(p+1) )
		{
			p += 2;
			while ( p < pEnd )
			{
				if ( ')' == *p )
					break;
				++p;
			}

			if ( ')' == *p )
				++p;
			else
				p = pStart;
		}
	}

	return long(p - pStart);
}


/*---------------------------------------------------------------------+\

 * ProcessVariable -

\+---------------------------------------------------------------------*/
NAMESPACE_ROOT_PREFIX CCharString
		CVariables::ProcessVariable
		(
		NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef rVar
		)
{
	const char*	p = rVar.Pointer() + 2;		// get past $(
	size_t		n = rVar.Length() - 3;

	NAMESPACE_ROOT_PREFIX CCharString	s;

	s = m_pVariable->ResolveVariable( NAMESPACE_ROOT_PREFIX CCharDescriptor( p, n ) );
	return Substitute( s );
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

