/*---------------------------------------------------------------------+\
|
|	CEqOpFormatString.cpp  --  brief description of what CEqOpFormatString.cpp is for
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
	27-Oct-2009			M.Rose			(Reviewed by: R.Hosea)
		Fix g++ compile error, remove :: operator from sprintf_s
	21-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add some new special date/time format tags.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support the date/time type
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	30-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Change 'GetValue' to use a 'const char*' to fetch the
		operand if it was being formatted as a string.
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <stdio.h>
#include "UPlatform.h"
#include "UPlatformString.h"
#include "CEqOpFormatString.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
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

 * CEquationOperatorFormatString - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorFormatString::CEquationOperatorFormatString
		(
		void
		)
		: VEquationOperatorUnary(),
		m_sFormat()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorFormatString - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorFormatString::CEquationOperatorFormatString
		(
		ConstCEquationOperatorFormatStringRef	r
		)
		: VEquationOperatorUnary( r ),
		m_sFormat( r.m_sFormat )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorFormatString - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorFormatString::~CEquationOperatorFormatString
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
CEquationOperatorFormatStringRef
		CEquationOperatorFormatString::operator=
		(
		ConstCEquationOperatorFormatStringRef	r
		)
{
	VEquationOperatorUnary::operator = ( r );

	m_sFormat = r.m_sFormat;
	return *this;
}

/*---------------------------------------------------------------------+\

 * SetFormat -

\+---------------------------------------------------------------------*/
void	CEquationOperatorFormatString::SetFormat
		(
		const char *s
		)
{
	m_sFormat = s;
}


/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

CVariantData
		CEquationOperatorFormatString::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );
	char			sOut[512];

	size_t			n = m_sFormat.Length();
	if ( 0 < n )
	{
		const char*	sf = m_sFormat.Pointer();
		char		c = *(sf + n - 1);		// get last character

		switch ( c )
		{
		case 'd':
		case 'i':
		case 'n':
		case 'o':
		case 'u':
		case 'x':
		case 'X':
			{
				long	i = vOperand;
				sprintf_s( sOut, sizeof(sOut), m_sFormat.Pointer(), i );
			}
			break;
		case 'f':
			{
				GFLOAT	f = vOperand;
				sprintf_s( sOut, sizeof(sOut), m_sFormat.Pointer(), (float)f );
			}
			break;
		case 's':
			{
				if ( CVariantData::T_STRING == vOperand.GetType() )
				{
					CCharDescriptor	sd = vOperand;
					sprintf_s( sOut, sizeof(sOut), m_sFormat.Pointer(), sd );
				}
				else
				{
					CCharString	s = vOperand;
					const char*	p = s.Pointer();
					sprintf_s( sOut, sizeof(sOut), m_sFormat.Pointer(), p );
				}
			}
			break;
		case 't':
			{
				CDateTime t = vOperand;
				t.FormatISO( sOut, sizeof(sOut), false );
			}
			break;
		case 'T':
			{
				CDateTime t = vOperand;
				t.FormatISO( sOut, sizeof(sOut), true );
			}
			break;
		default:
			if ( CVariantData::T_DATETIME == vOperand.GetType() )
			{
				CDateTime t = vOperand;
				t.FormatGMT( sOut, sizeof(sOut), m_sFormat.Pointer() );
			}
			else
			{
				::strcpy_s( sOut, sizeof(sOut), vOperand.GetValueString() );
			}
			break;
		}
	}
	else
	{
		::strcpy_s( sOut, sizeof(sOut), vOperand.GetValueString() );
	}

	vResult = sOut;


	return vResult;
}

//END_OVERRUN_WARNING

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
		CEquationOperatorFormatString::Clone
		(
		void
		)
{
	return new CEquationOperatorFormatString( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
