/*---------------------------------------------------------------------+\
|
|	CFactoryEquation.cpp  --  Build equation objects from string
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
	06-Jul-2011			J.Griswold		(Reviewed by: xxxx)
		Fixed a long-standing memory leak concerning filling in
		CEqFormatString.SetFormat. A temporary object was not being
		deleted
	29-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Fixed memory leak that occured when we encountered
		an error condition in the script from an unrecognized
		dictionary variable name.
	26-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add "assignindirect" operator
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Add 'colorname' as an alias for the 'color' operator
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Allow meaningful error messages to be returned to the caller
	02-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fix a problem where color values were not being correctly
		generated for numeric values.
		Add better support for dealing with 'units'.
		Add radian to degree (rddg) function.
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix a problem where we might run-off the end of memory
		if we did not correctly balance the quotes.
	14-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for inline comments within equations
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add new operators for dealing with color
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	30-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Very nice optimization that recognizes when an operator
		is acting on constants and as a result the result will be
		a constant.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		If a variable is identified as a constant value (locked)
		generate a 'constant' node instead of a 'variable'.
		Change behavior so we will mark the equation as bad if the
		'variable' does not exist in the dictionary.
	18-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		New operator 'near'
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Actually test the register numbers and properly fail if
		one was specified that does not exist.
	02-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add "indirect" operator
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Compiler warning resolution for GCC++
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for special constant types that are read directly
		from the gauge or other object
	02-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix for parsing Hexidecimal numbers.  We were not correctly
		dealing with the leading "0x".  I honestly don't understand
		why this wasn't caught earlier.
	07-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <ctype.h>
#include <stdlib.h>

#include "CFactoryEquation.h"

#include "UPlatform.h"
#include "UPlatformString.h"
#include "CUnitsOfMeasure.h"

#include "CEqConstant.h"
#include "CEqConstGaugeHeight.h"
#include "CEqConstGaugeLeft.h"
#include "CEqConstGaugeTop.h"
#include "CEqConstGaugeWidth.h"
#include "CEqOpAbs.h"
#include "CEqOpAdd.h"
#include "CEqOpAnd.h"
#include "CEqOpBitAnd.h"
#include "CEqOpBitOr.h"
#include "CEqOpBoth.h"
#include "CEqOpCase.h"
#include "CEqOpCeil.h"
#include "CEqOpColorname.h"
#include "CEqOpDecrement.h"
#include "CEqOpDegFromRad.h"
#include "CEqOpDegreeNorm.h"
#include "CEqOpDivide.h"
#include "CEqOpEqual.h"
#include "CEqOpFind.h"
#include "CEqOpFloor.h"
#include "CEqOpFormatString.h"
#include "CEqOpGreaterOrEqual.h"
#include "CEqOpGreaterThan.h"
#include "CEqOpIncrement.h"
#include "CEqOpLessOrEqual.h"
#include "CEqOpLessThan.h"
#include "CEqOpMax.h"
#include "CEqOpMin.h"
#include "CEqOpModulo.h"
#include "CEqOpMultiply.h"
#include "CEqOpNear.h"
#include "CEqOpNegate.h"
#include "CEqOpNot.h"
#include "CEqOpNotEqual.h"
#include "CEqOpOr.h"
#include "CEqOpQuestion.h"
#include "CEqOpRadFromDeg.h"
#include "CEqOpRadianNorm.h"
#include "CEqOpRange.h"
#include "CEqOpRegLoad.h"
#include "CEqOpRegStore.h"
#include "CEqOpRGB.h"
#include "CEqOpRGBA.h"
#include "CEqOpSquare.h"
#include "CEqOpStrCat.h"
#include "CEqOpSubStr.h"
#include "CEqOpSubtract.h"
#include "CEqOpUnitAbbrev.h"
#include "CEqOpUnitConvert.h"
#include "CEqOpUnitName.h"
#include "CEqOpUnitPlural.h"
#include "CEqVariable.h"
#include "CEqVariableAssign.h"
#include "CEqVariableAssignCond.h"
#include "CEqVariableAssignIndirect.h"
#include "CEqVariableIndirect.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/

bool	StringEquiv
		(
		const char*	s1,
		const char*	s2,
		int		n2
		)
{
	bool	bResult = true;
	const char*	s2End = s2 + n2;

	while ( s2 < s2End )
	{
		if ( ::tolower( *s1 ) != ::tolower( *s2 ) )
		{
			bResult = false;
			break;
		}
		s1++;
		s2++;
	}
	if ( *s1 )
		bResult = false;

	return bResult;
}



class CTNumber : public VFactoryEquationToken
{
public:
	virtual VEquationPtr
			MakeToken
			(
			EquationTokenType*	pTokenType,		// OUT
			CFactoryEquation::MapToken* pMap,
			const char*			sToken,
			int					n,
			CFactoryEquationPtr pFactory
			)
	{
		VEquationPtr	pEq = 0;
		if ( 1 == n )
		{
			switch ( *sToken )
			{
			case '*':	// dummy label
				break;
			default:
				break;
			}
		}
		else
		{
			if ( StringEquiv( "pi", sToken, n )
					||  StringEquiv( "pi2", sToken, n ) )
				pEq = pFactory->EqFromNumber( pMap->sValue, ::strlen(pMap->sValue) );
		}
		*pTokenType = T_CONSTANT;
		return pEq;
	}
};

class CTOpUnary : public VFactoryEquationToken
{
public:
	virtual VEquationPtr
			MakeToken
			(
			EquationTokenType*	pTokenType,		// OUT
			CFactoryEquation::MapToken* ,
			const char*			sToken,
			int					n,
			CFactoryEquationPtr pFactory
			)
	{
		VEquationPtr		pEq = 0;
		EquationTokenType	eType = T_UNDEFINED;
		VEquationOperatorUnaryPtr	pEqU = 0;
		if ( 1 == n )
		{
			switch ( *sToken )
			{
			case '!':
				pEqU = new CEquationOperatorNot;
				break;
			case '@':
				pEqU = new CEquationVariableIndirect;
				eType = T_OPERATOR;
			default:
				break;
			}
		}
		else
		{
			if ( StringEquiv( "/-/", sToken, n )
					||	StringEquiv( "neg", sToken, n ) )
				pEqU = new CEquationOperatorNegate;
			else if ( StringEquiv( "NOT", sToken, n ) )
				pEqU = new CEquationOperatorNot;
			else if ( StringEquiv( "ceil", sToken, n ) )
				pEqU = new CEquationOperatorCeil;
			else if ( StringEquiv( "flr", sToken, n )
					||	StringEquiv( "floor", sToken, n ) )
				pEqU = new CEquationOperatorFloor;
			else if ( StringEquiv( "near", sToken, n ) )
				pEqU = new CEquationOperatorNear;
			else if ( StringEquiv( "dgrd", sToken, n ) )
				pEqU = new CEquationOperatorRadiansFromDegrees;
			else if ( StringEquiv( "rddg", sToken, n ) )
				pEqU = new CEquationOperatorDegreesFromRadians;
			else if ( StringEquiv( "sqr", sToken, n )
					||	StringEquiv( "square", sToken, n ) )
				pEqU = new CEquationOperatorSquare;
			else if ( StringEquiv( "++", sToken, n ) )
				pEqU = new CEquationOperatorIncrement;
			else if ( StringEquiv( "--", sToken, n ) )
				pEqU = new CEquationOperatorDecrement;
			else if ( StringEquiv( "abs", sToken, n ) )
				pEqU = new CEquationOperatorAbs;
			else if ( StringEquiv( "dnor", sToken, n ) )
				pEqU = new CEquationOperatorDegreeNorm;
			else if ( StringEquiv( "rnor", sToken, n ) )
				pEqU = new CEquationOperatorRadianNorm;
			else if ( StringEquiv( "colorname", sToken, n )
					||	StringEquiv( "color", sToken, n ) )
				pEqU = new CEquationOperatorColorname;
			else if ( StringEquiv( "unitabbrev", sToken, n ) )
				pEqU = new CEquationOperatorUnitAbbrev;
			else if ( StringEquiv( "unitname", sToken, n ) )
				pEqU = new CEquationOperatorUnitName;
			else if ( StringEquiv( "unitplural", sToken, n ) )
				pEqU = new CEquationOperatorUnitPlural;
			else if ( StringEquiv( "ind", sToken, n )
					||	StringEquiv( "indirect", sToken, n ) )
			{
				pEqU = new CEquationVariableIndirect;
				eType = T_OPERATOR;
			}

		}
		if ( pEqU )
		{
			EquationTokenType	e;
			VEquationPtr	pOperand = pFactory->Pop( &e );
			if ( pOperand )
			{
				pEqU->SetOperand( pOperand );

				if ( T_UNDEFINED == eType
					&&	T_CONSTANT == e )
				{
					CEquationConstantPtr	pConst = new CEquationConstant;
					if ( pConst )
					{
						CVariantData	v = pEqU->GetValue( 0 );
						pConst->SetValue( v );
						pEq = pConst;
						eType = T_CONSTANT;
						delete pEqU;
					}
					else
					{
						pEq = pEqU;
					}
				}
				else
				{
					eType = T_OPERATOR;
					pEq = pEqU;
				}
			}
			else
			{
				delete pEqU;
				eType = T_UNDEFINED;
			}
		}
		*pTokenType = eType;
		return pEq;
	}
};


class CTOpBinary : public VFactoryEquationToken
{
public:
	virtual VEquationPtr
			MakeToken
			(
			EquationTokenType*	pTokenType,		// OUT
			CFactoryEquation::MapToken* ,
			const char*			sToken,
			int					n,
			CFactoryEquationPtr pFactory
			)
	{
		VEquationPtr		pEq = 0;
		EquationTokenType	eType = T_UNDEFINED;
		VEquationOperatorBinaryPtr	pEqB = 0;
		if ( 1 == n )
		{
			switch( *sToken )
			{
			case '+':
				pEqB = new CEquationOperatorAdd;
				break;
			case '-':
				pEqB = new CEquationOperatorSubtract;
				break;
			case '*':
				pEqB = new CEquationOperatorMultiply;
				break;
			case '/':
				pEqB = new CEquationOperatorDivide;
				break;
			case '%':
				pEqB = new CEquationOperatorModulo;
				break;
			case '&':
				pEqB = new CEquationOperatorBitAnd;
				break;
			case '|':
				pEqB = new CEquationOperatorBitOr;
				break;
			case '<':
				pEqB = new CEquationOperatorLessThan;
				break;
			case '>':
				pEqB = new CEquationOperatorGreaterThan;
				break;
			default:
				break;
			}
		}
		else
		{
			if ( StringEquiv( "==", sToken, n )
					||	StringEquiv( "EQ", sToken, n ) )
				pEqB = new CEquationOperatorEqual;
			else if ( StringEquiv( "!=", sToken, n )
					||	StringEquiv( "NE", sToken, n ) )
				pEqB = new CEquationOperatorNotEqual;
			else if ( StringEquiv( "&lt;", sToken, n )
					||	StringEquiv( "LT", sToken, n ) )
				pEqB = new CEquationOperatorLessThan;
			else if ( StringEquiv( "&gt;", sToken, n )
					||	StringEquiv( "GT", sToken, n ) )
				pEqB = new CEquationOperatorGreaterThan;
			else if ( StringEquiv( "<=", sToken, n )
					||	StringEquiv( "&lt;=", sToken, n )
					||	StringEquiv( "&le;", sToken, n )
					||	StringEquiv( "LE", sToken, n ) )
				pEqB = new CEquationOperatorLessOrEqual;
			else if ( StringEquiv( ">=", sToken, n )
					||	StringEquiv( "&gt;=", sToken, n )
					||	StringEquiv( "&ge;", sToken, n )
					||	StringEquiv( "GE", sToken, n ) )
				pEqB = new CEquationOperatorGreaterOrEqual;
			else if ( StringEquiv( "&&", sToken, n )
					||	StringEquiv( "&amp;&amp;", sToken, n )
					||	StringEquiv( "AND", sToken, n ) )
				pEqB = new CEquationOperatorAnd;
			else if ( StringEquiv( "||", sToken, n )
					||	StringEquiv( "OR", sToken, n ) )
				pEqB = new CEquationOperatorOr;
			else if ( StringEquiv( "&", sToken, n )
					||	StringEquiv( "&amp;", sToken, n )
					||	StringEquiv( "BITAND", sToken, n ) )
				pEqB = new CEquationOperatorBitAnd;
			else if ( StringEquiv( "|", sToken, n )
					||	StringEquiv( "BITOR", sToken, n ) )
				pEqB = new CEquationOperatorBitAnd;
			else if ( StringEquiv( "max", sToken, n ) )
				pEqB = new CEquationOperatorMax;
			else if ( StringEquiv( "min", sToken, n ) )
				pEqB = new CEquationOperatorMin;
			else if ( StringEquiv( "scat", sToken, n )
					||	StringEquiv( "strcat", sToken, n ) )
				pEqB = new CEquationOperatorStrCat;
			else if ( StringEquiv( "unitcnv", sToken, n ) )
				pEqB = new CEquationOperatorUnitConvert;
			else if ( StringEquiv( "both", sToken, n ) )
			{
				pEqB = new CEquationOperatorBoth;
				eType = T_OPERATOR;
			}
			else if ( StringEquiv( "asnind", sToken, n )
					||	StringEquiv( "indasn", sToken, n )
					||	StringEquiv( "assignindirect", sToken, n )
					||	StringEquiv( "indirectassign", sToken, n )
					||	StringEquiv( "=@", sToken, n )
					||	StringEquiv( "@=", sToken, n ) )
			{
				pEqB = new CEquationVariableAssignIndirect;
				eType = T_OPERATOR;
			}
			else if ( StringEquiv( "subtract", sToken, n ) )
			{
				pEqB = new CEquationOperatorSubtract;
			}
		}
		if ( pEqB )
		{
			EquationTokenType	eRight;
			EquationTokenType	eLeft;
			VEquationPtr pRight = pFactory->Pop( &eRight );
			VEquationPtr pLeft = pFactory->Pop( &eLeft );
			pEqB->SetLeft( pLeft );
			pEqB->SetRight( pRight );

			if ( (T_CONSTANT == eRight
					&&	T_CONSTANT == eLeft)
					&&	T_UNDEFINED == eType )
			{
				CEquationConstantPtr	pConst = new CEquationConstant;
				if ( pConst )
				{
					CVariantData	v = pEqB->GetValue( 0 );
					pConst->SetValue( v );
					pEq = pConst;
					eType = T_CONSTANT;
					delete pEqB;
				}
				else
				{
					pEq = pEqB;
					eType = T_OPERATOR;
				}
			}
			else
			{
				pEq = pEqB;
				eType = T_OPERATOR;
			}
		}
		*pTokenType = eType;
		return pEq;
	}
};


class CTOpTrinary : public VFactoryEquationToken
{
public:
	virtual VEquationPtr
			MakeToken
			(
			EquationTokenType*	pTokenType,		// OUT
			CFactoryEquation::MapToken* ,
			const char*			sToken,
			int					n,
			CFactoryEquationPtr pFactory
			)
	{
		VEquationPtr		pEq = 0;
		EquationTokenType	eType = T_UNDEFINED;
		VEquationOperatorTrinaryPtr	pEqT = 0;
		if ( 1 == n )
		{
			switch ( *sToken )
			{
			case '?':
				pEqT = new CEquationOperatorQuestion;
				break;
			default:
				break;
			}
		}
		else
		{
			if ( StringEquiv( "rng", sToken, n )
					||	StringEquiv( "range", sToken, n ) )
				pEqT = new CEquationOperatorRange;
			else if ( StringEquiv( "rgb", sToken, n ) )
				pEqT = new CEquationOperatorRGB;
			else if ( StringEquiv( "substr", sToken, n ) )
				pEqT = new CEquationOperatorSubStr;
		}
		if ( pEqT )
		{
			EquationTokenType	eControl;
			EquationTokenType	eRight;
			EquationTokenType	eLeft;
			VEquationPtr pControl = pFactory->Pop( &eControl );
			VEquationPtr pRight = pFactory->Pop( &eRight );
			VEquationPtr pLeft = pFactory->Pop( &eLeft );
			pEqT->SetControl( pControl );
			pEqT->SetLeft( pLeft );
			pEqT->SetRight( pRight );

			if ( T_CONSTANT == eControl
					&&	T_CONSTANT == eRight
					&&	T_CONSTANT == eLeft )
			{
				CEquationConstantPtr	pConst;
				CVariantData			v;

				v = pEqT->GetValue( 0 );
				pConst = new CEquationConstant;
				pConst->SetValue( v );
				pEq = pConst;
				eType = T_CONSTANT;
				delete pEqT;

			}
			else
			{
				pEq = pEqT;
				eType = T_OPERATOR;
			}
		}
		*pTokenType = eType;
		return pEq;
	}
};

class CTOpQuaternary : public VFactoryEquationToken
{
public:
	virtual VEquationPtr
			MakeToken
			(
			EquationTokenType*	pTokenType,		// OUT
			CFactoryEquation::MapToken* ,
			const char*			sToken,
			int					n,
			CFactoryEquationPtr pFactory
			)
	{
		VEquationPtr		pEq = 0;
		EquationTokenType	eType = T_UNDEFINED;
		VEquationOperatorQuaternaryPtr	pEqT = 0;
		if ( 1 == n )
		{
			switch ( *sToken )
			{
			case '_':	// dummy
				pEqT = 0;
				break;
			default:
				break;
			}
		}
		else
		{
			if ( StringEquiv( "rgba", sToken, n ) )
				pEqT = new CEquationOperatorRGBA;
		}
		if ( pEqT )
		{
			EquationTokenType	eOp1;
			EquationTokenType	eOp2;
			EquationTokenType	eOp3;
			EquationTokenType	eOp4;
			VEquationPtr	pOp1 = pFactory->Pop( &eOp1 );
			VEquationPtr	pOp2 = pFactory->Pop( &eOp2 );
			VEquationPtr	pOp3 = pFactory->Pop( &eOp3 );
			VEquationPtr	pOp4 = pFactory->Pop( &eOp4 );

			pEqT->SetOperand1( pOp1 );
			pEqT->SetOperand2( pOp2 );
			pEqT->SetOperand3( pOp3 );
			pEqT->SetOperand4( pOp4 );

			if ( T_CONSTANT == eOp1
					&&	T_CONSTANT == eOp2
					&&	T_CONSTANT == eOp3
					&&	T_CONSTANT == eOp4 )
			{
				CEquationConstantPtr	pConst;
				CVariantData			v;

				v = pEqT->GetValue( 0 );
				pConst = new CEquationConstant;
				pConst->SetValue( v );
				pEq = pConst;
				eType = T_CONSTANT;
				delete pEqT;

			}
			else
			{
				pEq = pEqT;
				eType = T_OPERATOR;
			}
		}
		*pTokenType = eType;
		return pEq;
	}
};

class CTOpSpecial : public VFactoryEquationToken
{
public:
	virtual VEquationPtr
			MakeToken
			(
			EquationTokenType*	pTokenType,		// OUT
			CFactoryEquation::MapToken* ,
			const char*			sToken,
			int					n,
			CFactoryEquationPtr pFactory
			)
	{
		VEquationPtr		pEq = 0;
		EquationTokenType	eType = T_UNDEFINED;
		if ( 1 == n )
		{
			switch ( *sToken )
			{
			case '*':
				// dummy entry
				break;
			default:
				break;
			}
		}
		else
		{
			if ( StringEquiv( "case", sToken, n ) )
			{
				EquationTokenType	e;
				CEquationOperatorCasePtr pEqCase = new CEquationOperatorCase;
				VEquationPtr	pOperand = pFactory->Pop( &e );
				VEquationPtr	pCount = pFactory->Pop( &e );
				pEqCase->SetOperand( pOperand );
				CVariantData v = pCount->GetValue( 0 );
				long	i = v;
				//long	i = pCount->GetValue( 0 );
				delete pCount;
				VEquationPtr	p;
				while( 0 < i )
				{
					p = pFactory->Pop( &e );
					if ( p )
						pEqCase->AppendItem( p );
					--i;
				}

				eType = T_OPERATOR;
				pEq = pEqCase;
			}
			else if ( StringEquiv( "find", sToken, n ) )
			{
				EquationTokenType	e;
				CEquationOperatorFindPtr pEqFind = new CEquationOperatorFind;
				VEquationPtr	pOperand = pFactory->Pop( &e );
				VEquationPtr	pCount = pFactory->Pop( &e );
				pEqFind->SetOperand( pOperand );
				CVariantData v = pCount->GetValue( 0 );
				long	i = v;
				//long	i = pCount->GetValue( 0 );
				delete pCount;
				VEquationPtr	p;
				while( 0 < i )
				{
					p = pFactory->Pop( &e );
					if ( p )
						pEqFind->AppendItem( p );
					--i;
				}

				eType = T_OPERATOR;
				pEq = pEqFind;
			}
			else if ( StringEquiv( "format", sToken, n ) )
			{
				EquationTokenType	e;
				CEquationOperatorFormatStringPtr	pEqFmt = new CEquationOperatorFormatString;
				VEquationPtr	pFormat = pFactory->Pop( &e );
				if ( T_CONSTANT == e )
				{
					VEquationPtr	pOperand = pFactory->Pop( &e );
					CVariantData	v = pFormat->GetValue( 0 );
					CCharString		sFmt = v;
					pEqFmt->SetFormat( sFmt.Pointer() );
					pEqFmt->SetOperand( pOperand );
					if ( T_CONSTANT == e )
					{
						CEquationConstantPtr	pConst;
						CVariantData			v2;

						v2 = pEqFmt->GetValue( 0 );
						pConst = new CEquationConstant;
						pConst->SetValue( v2 );
						pEq = pConst;
						eType = T_CONSTANT;
						delete pEqFmt;
					}
					else
					{
						pEq = pEqFmt;
						eType = T_OPERATOR;
					}
				}
				if ( pFormat )
					delete pFormat;

			}
			else if ( StringEquiv( "true", sToken, n ) )
			{
				CEquationConstantPtr	pC = new CEquationConstant;
				pC->SetValue( CVariantData( true ) );
				pEq = pC;
				eType = T_CONSTANT;
			}
			else if ( StringEquiv( "false", sToken, n ) )
			{
				CEquationConstantPtr	pC = new CEquationConstant;
				pC->SetValue( CVariantData( false ) );
				pEq = pC;
				eType = T_CONSTANT;
			}
			else if ( StringEquiv( "height", sToken, n ) )
			{
				CEquationGaugeHeightPtr	pC = new CEquationGaugeHeight;
				pC->SetGauge( pFactory->GetGauge() );
				pEq = pC;
				eType = T_VARIABLE;
			}
			else if ( StringEquiv( "width", sToken, n ) )
			{
				CEquationGaugeWidthPtr	pC = new CEquationGaugeWidth;
				pC->SetGauge( pFactory->GetGauge() );
				pEq = pC;
				eType = T_VARIABLE;
			}
			else if ( StringEquiv( "left", sToken, n ) )
			{
				CEquationGaugeLeftPtr	pC = new CEquationGaugeLeft;
				pC->SetGauge( pFactory->GetGauge() );
				pEq = pC;
				eType = T_VARIABLE;
			}
			else if ( StringEquiv( "top", sToken, n ) )
			{
				CEquationGaugeTopPtr	pC = new CEquationGaugeTop;
				pC->SetGauge( pFactory->GetGauge() );
				pEq = pC;
				eType = T_VARIABLE;
			}
		}
		*pTokenType = eType;
		return pEq;
	}
};





/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/

CTNumber		g_Number;
CTOpUnary		g_OpUnary;
CTOpBinary		g_OpBinary;
CTOpTrinary		g_OpTrinary;
CTOpQuaternary	g_OpQuaternary;
CTOpSpecial		g_OpSpecial;

//	token,	factory,	value(string)
CFactoryEquation::MapToken
g_aMapToken[]
= {
	// Common Operators
	{"+",	&g_OpBinary,	0 },
	{"-",	&g_OpBinary,	0 },
	{"/",	&g_OpBinary,	0 },
	{"*",	&g_OpBinary,	0 },
	{"%",	&g_OpBinary,	0 },		// modulo
	{"/-/",	&g_OpUnary,		"-" },		// unary negate
	{"neg",	&g_OpUnary,		"-" },		// unary negate
	{"++",	&g_OpUnary,		0 },
	{"--",	&g_OpUnary,		0 },
	{"subtract",	&g_OpBinary,	0 },

	// Bitwise Operators
	{"&",	&g_OpBinary,	0 },		// BITAND
	{"&amp;",&g_OpBinary,	0 },		//
	{"BITAND",&g_OpBinary,	0 },
	{"|",	&g_OpBinary,	0 },		// BITOR
	{"BITOR",&g_OpBinary,	0 },

	// Comparison Operators
	{"==",	&g_OpBinary,	0 },		// equal
	{"EQ",	&g_OpBinary,	0 },
	{"!=",	&g_OpBinary,	0 },		// not equal
	{"NE",	&g_OpBinary,	0 },
	{">",	&g_OpBinary,	0 },		// greater than
	{"&gt;",&g_OpBinary,	0 },
	{"GT",	&g_OpBinary,	0 },
	{"<",	&g_OpBinary,	0 },		// less than
	{"&lt;",&g_OpBinary,	0 },
	{"LT",	&g_OpBinary,	0 },
	{">=",	&g_OpBinary,	0 },		// greater or equal
	{"&gt;=",&g_OpBinary,	0 },
	{"&ge;",&g_OpBinary,	0 },
	{"GE",	&g_OpBinary,	0 },
	{"<=",	&g_OpBinary,	0 },		// less or equal
	{"&lt;=",&g_OpBinary,	0 },
	{"&le;",&g_OpBinary,	0 },
	{"LE",	&g_OpBinary,	0 },
	{"?",	&g_OpTrinary,	0 },		// (A B C ?) returns A if C is true, otherwise B is returned

	// Logical Operators
	{"!",	&g_OpUnary,		0 },
	{"NOT",	&g_OpUnary,		0 },
	{"&&",	&g_OpBinary,	0 },
	{"&amp;&amp;",&g_OpBinary, 0 },
	{"AND",	&g_OpBinary,	0 },
	{"||",	&g_OpBinary,	0 },
	{"OR",	&g_OpBinary,	0 },
	{"rng",	&g_OpTrinary,	0 },		// (A B C rng) returns true if A <= C <= B
	{"range",&g_OpTrinary,	0 },
	{"case",&g_OpSpecial,	0 },		// (50 40 30 20 10 5 A case) returns 20 if int(A) is 1
	{"find",&g_OpSpecial,	0 },		// (50 40 30 20 10 5 A find) returns 1 if A is 20

	{"abs",	&g_OpUnary,		0 },
	{"max",	&g_OpBinary,	0 },
	{"min",	&g_OpBinary,	0 },
	{"flr",	&g_OpUnary,		0 },
	{"floor",&g_OpUnary,	0 },
	{"ceil",&g_OpUnary,		0 },
	{"near",&g_OpUnary,		0 },		// nearest integer (rounds)
//	{"int",	&g_OpUnary,		0 },
	{"dgrd",&g_OpUnary,		0 },		// converts degrees to radians
	{"rddg",&g_OpUnary,		0 },		// converts radians to degrees
	{"dnor",&g_OpUnary,		0 },		// normalize degrees to 0 to 360
	{"rnor",&g_OpUnary,		0 },		// normalize radians to 0 to pi2
//	{"lg",	&g_OpUnary,		0 },		// logarithm to base 10
//	{"ln",	&g_OpUnary,		0 },		// Natural logarithm
//	{"sin",	&g_OpUnary,		0 },		// sine
//	{"asin",&g_OpUnary,		0 },		// arc sine
//	{"cos",	&g_OpUnary,		0 },		// cosine
//	{"acos",&g_OpUnary,		0 },		// arc cosine
//	{"tg",	&g_OpUnary,		0 },		// tangent
//	{"tan",	&g_OpUnary,		0 },		// tangent
//	{"atg",	&g_OpUnary,		0 },		// arc tangent
//	{"atan",&g_OpUnary,		0 },		// arc tangent
//	{"ctg",	&g_OpUnary,		0 },		// cotangent
	{"sqr",	&g_OpUnary,		0 },		// square
	{"square",&g_OpUnary,	0 },
//	{"sqrt",&g_OpUnary,		0 },		// square root
//	{"pow",	&g_OpBinary,	0 },		// (2 5 pow) is 32
//	{"^",	&g_OpBinary,	0 },		// pow

	// dictionary operators
	{"ind",	&g_OpUnary,		0 },		// indirect for a variable
	{"indirect",&g_OpUnary,	0 },
	{"@",	&g_OpUnary,		0 },
	{"asnind",	&g_OpBinary,0 },		// indirect assign for a variable
	{"indasn",	&g_OpBinary,0 },
	{"assignindirect",&g_OpBinary,0 },
	{"indirectassign",&g_OpBinary,0 },
	{"=@",	&g_OpBinary,	0 },
	{"@=",	&g_OpBinary,	0 },

	// String Operators
//	{"lc",	&g_OpUnary,		0 },		// lowercase
//	{"lcase",&g_OpUnary,	0 },
//	{"uc",	&g_OpUnary,		0 },		// uppercase
//	{"ucase",&g_OpUnary,	0 },
	{"scat",&g_OpBinary,	0 },		// string concatenation
	{"strcat",&g_OpBinary,	0 },		// string concatenation
//	{"scmp",&g_OpBinary,	0 },		// string compare
//	{"scmpi",&g_OpBinary,	0 },		// string compare ignoring case
	{"format",&g_OpSpecial,	0 },		// string format
	{"substr",&g_OpTrinary,	0 },		//	3 2 '12345678' substr	// = '34'

	{"rgb",	&g_OpTrinary,	0 },		// 255 255 0 rgb //  makes yellow
	{"rgba",&g_OpQuaternary,0 },		// red green blue alpha
	{"color",&g_OpUnary,	0 },		// 'red' color
	{"colorname",&g_OpUnary,0 },		// 'red' colorname

	{"unitcnv",&g_OpBinary,	0 },		// operand 'unitname' unitcnv
	{"unitname",&g_OpUnary,	0 },		// unit-name of input operand
	{"unitplural",&g_OpUnary,0 },		// plural unit-name of input operand
	{"unitabbrev",&g_OpUnary,0 },		// abbrev unit-name of input operand

	{"both",&g_OpBinary,	0 },		// assure both operands are processed

	{"width",&g_OpSpecial,	0 },
	{"height",&g_OpSpecial,	0 },
	{"left",&g_OpSpecial,	0 },
	{"top",&g_OpSpecial,	0 },
	{"true",&g_OpSpecial,	0 },
	{"false",&g_OpSpecial,	0 },
	{"pi",	&g_Number,		"3.141592654"},
	{"pi2",	&g_Number,		"6.283185308"}
};

CFactoryEquation::MapToken*
CFactoryEquation::g_pMap = &g_aMapToken[0];
long	CFactoryEquation::g_nMap = sizeof(g_aMapToken) / sizeof(CFactoryEquation::MapToken);



char	kBlanks[]
= {
	0x09,	// tab
	0x0A,	// linefeed
	0x0D,	// carriage return
	0x20,	// space

	0x00
};


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

 * CFactoryEquation - constructor

\+---------------------------------------------------------------------*/
CFactoryEquation::CFactoryEquation
		(
		void
		)
		: m_eTarget( E_UNDEFINED ),
		m_nStack( 0 ),
		m_bGVariables( false ),
		m_pGauge( 0 ),
		m_pDictionary( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CFactoryEquation - destructor

\+---------------------------------------------------------------------*/
CFactoryEquation::~CFactoryEquation
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * MakeEquation -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::MakeEquation
		(
		FEquationTargets eTarget,
		const char*	sString,
		int			nLength
		)
{
	VEquationPtr	pEquation = 0;

	if ( nLength < 0 )
		nLength = int(::strlen(sString));

	m_eTarget = eTarget;
	m_nStack = 0;
	m_bGVariables = false;
	m_bConstant = false;
	m_bError = false;
	m_sErrorString[0] = 0;
	m_sString = (char*)sString;
	m_nString = nLength;
	m_sToken = 0;
	m_nToken = 0;

	m_bConstant = false;
	m_nNodeCount = 0;

	const char*	s = sString;
	const char*	sEnd = s + nLength;
	size_t		n;
	MapToken*	pMapToken = 0;
	VFactoryEquationToken*	pEqFactory = 0;

	VEquationPtr		pEq = 0;
	EquationTokenType	eType = T_UNDEFINED;


	s = SkipBlanks( s );
	while ( s < sEnd  &&  ! m_bError )
	{
		// handle special case tokens
		if ( '\'' == *s  ||  '"' == *s )	// string literal (might be treated as color based on eTarget)
		{
			n = (size_t)TokenString( s, sEnd );
			if ( 0 < n )
			{
				pEq = EqFromString( s, n );
				if ( pEq )
				{
					s += n;
					Push( pEq, T_CONSTANT );
				}
				else
				{
					CCharString		sError( "Problem with string - ");
					CCharDescriptor	sToken( s, n );
					sError += sToken;
					SetError( sError.Pointer() );
				}
			}
			else
			{
				++s;
			}
		}
		else if ( '(' == *s )				// variable name
		{
			n = (size_t)TokenVariable( s, sEnd );
			if ( 0 < n )
			{
				pEq = EqFromVariable( &eType, s, n );
				if ( pEq )
				{
					s += n;
					Push( pEq, eType );
				}
				else
				{
					CCharString		sError( "Problem with variable - ");
					CCharDescriptor	sToken( s, n );
					sError += sToken;
					SetError( sError.Pointer() );
				}

			}
			else
			{
				++s;
				SetError( "Malformed Variable" );
			}
		}
		else if ( StringEquiv( "/*", s, 2 )
				||	StringEquiv( "//", s, 2 ) )
		{
			n = (size_t)TokenComment( s, sEnd );
			if ( 0 < n )
				s += n;
			else
				SetError( "unrecognized comment in script" );
		}
		else
		{
			n = (size_t)TokenNonBlank( s, sEnd );
			if ( 0 < n )
			{
				pMapToken = FindMapEntry( s, (int)n );
				if ( pMapToken )
				{
					pEqFactory = pMapToken->pFactory;
					pEq = pEqFactory->MakeToken( &eType, pMapToken, s, (int)n, this );
					if ( pEq )
					{
						s += n;
						++m_nNodeCount;
						Push( pEq, eType );
					}
					else
					{
						CCharString		sError( "Problem with script token - ");
						CCharDescriptor	sToken( s, n );
						sError += sToken;
						SetError( sError.Pointer() );
					}
				}
				else if ( TokenRegister( s, n ) )
				{
					pEq = EqFromRegister( s, n );
					if ( pEq )
					{
						s += n;
						Push( pEq, T_VARIABLE );
					}
					else
					{
						CCharString		sError( "Bad or unrecognized Register - ");
						CCharDescriptor	sToken( s, n );
						sError += sToken;
						SetError( sError.Pointer() );
					}
				}
				else if ( TokenNumberInteger( s, n ) )
				{
					pEq = EqFromNumberInteger( s, n );
					if ( pEq )
					{
						s += n;
						Push( pEq, T_CONSTANT );
					}
					else
					{
						CCharString		sError( "Problem with integer constant - ");
						CCharDescriptor	sToken( s, n );
						sError += sToken;
						SetError( sError.Pointer() );
					}
				}
				else if ( TokenNumberFloat( s, n ) )
				{
					pEq = EqFromNumberFloat( s, n );
					if ( pEq )
					{
						s += n;
						Push( pEq, T_CONSTANT );
					}
					else
					{
						CCharString		sError( "Problem with floating point constant - ");
						CCharDescriptor	sToken( s, n );
						sError += sToken;
						SetError( sError.Pointer() );
					}
				}
				else if ( TokenNumberHex( s, n ) )
				{
					pEq = EqFromNumberHex( s, n );
					if ( pEq )
					{
						s += n;
						Push( pEq, T_CONSTANT );
					}
					else
					{
						CCharString		sError( "Problem with Hex constant - ");
						CCharDescriptor	sToken( s, n );
						sError += sToken;
						SetError( sError.Pointer() );
					}
				}
				else
				{
					CCharString		sError( "Unexpected or unrecognized token in script - ");
					CCharDescriptor	sToken( s, n );
					sError += sToken;
					SetError( sError.Pointer() );
				}
			}
			else
			{
				// we have a serious problem
				SetError( "Unidentified error in script" );
				break;
			}
		}
		s = SkipBlanks( s );
	}

	if ( E_COLOR == eTarget )
	{
		if ( 0 < m_nStack )
		{
			pMapToken = FindMapEntry( "color", 5 );
			if ( pMapToken )
			{
				pEqFactory = pMapToken->pFactory;
				pEq = pEqFactory->MakeToken( &eType, pMapToken, "color", 5, this );
				if ( pEq )
				{
					Push( pEq, eType );
				}
				else
				{
					CCharString		sError( "Problem with script token - [color]");
					SetError( sError.Pointer() );
				}
			}
		}
	}

	if ( 1 == m_nStack )
	{
		pEquation = Pop( &eType );
		if ( eType == T_CONSTANT )
			m_bConstant = true;
	}
	else
	{

		SetError( "Unbalanced equation" );
		// we have a problem the stack should only have one entry
		while ( 0 != (pEquation = Pop( &eType )) )
			delete pEquation;
		pEquation = 0;

	}
	if ( m_bError )
	{
		if ( pEquation )
			delete pEquation;
		pEquation = 0;
		SetError( "Unspecified Error" );
	}

	m_pGauge = 0;


	return pEquation;
}


/*---------------------------------------------------------------------+\

 * Push -

\+---------------------------------------------------------------------*/
void	CFactoryEquation::Push
		(
		VEquationPtr		p,
		EquationTokenType	eType
		)
{
	m_aStack[m_nStack].pNode = p;
	m_aStack[m_nStack++].eType = eType;
	//LogPrint( "%d> %d\n", m_nStack, eType);
}

/*---------------------------------------------------------------------+\

 * Pop -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::Pop
		(
		EquationTokenType*	pType
		)
{
	VEquationPtr	p = 0;
	if ( 0 < m_nStack )
	{
		--m_nStack;
		p = m_aStack[m_nStack].pNode;
		*pType = m_aStack[m_nStack].eType;
		m_aStack[m_nStack].pNode = 0;
		//LogPrint( "%d< %d\n", m_nStack, m_aStack[m_nStack].eType );
	}
	else
	{
		*pType = T_UNDEFINED;
		//CCharString		sError( "Not enough operands for operator in script - ");
		//CCharDescriptor	sToken( m_sString, m_nString );
		//sError.AppendFormat( "(%d) :: ", m_nNodeCount );
		//sError += sToken;
		//SetError( sError );
		SetError( "Not enough operands for operator in script" );
	}
	return p;
}


/*---------------------------------------------------------------------+\

 * SetDictionary -

\+---------------------------------------------------------------------*/
void	CFactoryEquation::SetDictionary
		(
		VDictionaryPtr	pDict
		)
{
	m_pDictionary = pDict;
}


/*---------------------------------------------------------------------+\

 * HasGVariables -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::HasGVariables
		(
		void
		)
{
	return m_bGVariables;
}


/*---------------------------------------------------------------------+\

 * IsConstant -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::IsConstant
		(
		void
		)
{
	bool	bResult = false;
	if ( m_bConstant )
	{
		if ( 1 == m_nNodeCount )
			bResult = true;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * SetError -

\+---------------------------------------------------------------------*/
void	CFactoryEquation::SetError
		(
		const char*	s
		)
{
	m_bError = true;
	if ( ! m_sErrorString[0] )
		::strcpy_s( m_sErrorString, sizeof(m_sErrorString), s );
}


/*---------------------------------------------------------------------+\

 * GetError -

\+---------------------------------------------------------------------*/
char*	CFactoryEquation::GetError
		(
		void
		)
{
	if ( m_bError )
		return m_sErrorString;
	else
		return 0;
}



/*---------------------------------------------------------------------+\

 * SetGauge -

\+---------------------------------------------------------------------*/
void	CFactoryEquation::SetGauge
		(
		VPanelChildPtr p
		)
{
	m_pGauge = p;
}

/*---------------------------------------------------------------------+\

 * GetGauge -

\+---------------------------------------------------------------------*/
VPanelChildPtr
		CFactoryEquation::GetGauge
		(
		void
		)
{
	return m_pGauge;
}


/*---------------------------------------------------------------------+\

 * EqFromNumber -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::EqFromNumber
		(
		const char*	s,
		size_t		n
		)
{
	VEquationPtr	pEq = 0;

	if ( TokenNumberHex( s, n ) )
		pEq = EqFromNumberHex( s, n );
	else if ( TokenNumberInteger( s, n ) )
		pEq = EqFromNumberInteger( s, n );
	else if ( TokenNumberFloat( s, n ) )
		pEq = EqFromNumberFloat( s, n );

	return pEq;
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * EqFromString -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::EqFromString
		(
		const char*	s,
		size_t		n
		)
{
	VEquationPtr	pEq = 0;

	//if ( E_COLOR == m_eTarget )
	//{
	//	CColor	tColor;
	//	if ( ! FindColorEntry( s+1, n-2, &tColor ) )
	//	{
	//		tColor.SetRGB( 0x01, 0xEE, 0x99 );
	//		SetError( "unrecognized color name in script" );
	//	}
	//	CEquationConstantPtr	pEqColor = new CEquationConstant;
	//	m_bConstant = true;
	//	CVariantData			v;
	//	v = tColor;
	//	pEqColor->SetValue( v );
	//	pEq = pEqColor;
	//}
	if ( ! pEq )
	{
		char	c = *s;
		char*	sOut = new char[n+1];
		char*	t = sOut;
		const char*	sEnd = s + n - 1;		// subtract one to remove ending quote

		++s;
		while ( s < sEnd )
		{
			if ( '\'' == *s  &&  c == *(s+1) )
				++s;
			else
				*t++ = *s;
			++s;
		}
		*t = 0;

		CEquationConstantPtr	pEqStr = new CEquationConstant;
		m_bConstant = true;
		CVariantData		v = sOut;
		delete [] sOut;
		pEqStr->SetValue( v );
		pEq = pEqStr;
	}
	++m_nNodeCount;

	return pEq;
}


/*---------------------------------------------------------------------+\

 * EqFromVariable -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

VEquationPtr
		CFactoryEquation::EqFromVariable
		(
		EquationTokenType*	pType,		// OUT
		const char*			s,
		size_t				n
		)
{
	VEquationPtr		pEq = 0;
	EquationTokenType	eType = T_VARIABLE;
	if ( '(' == *s  &&  ')' == *(s+n-1) )
	{
		size_t	i = n;
		char*	t = new char[n+1];
		const char*	sEnd = s + n - 1;
		int		nVariableMetadata;
		char	sTemp[128];
		++s;

		const char*	ss = SkipBlanks( s );
		char		cAsn = 0;

		cAsn = *ss;
		if ( '&' == *ss )
		{
			if ( 0 == ::strncmp( "&gt;", ss, 4 ) )
			{
				cAsn = '>';
				ss += 3;
			}
		}

		if ( '>' == cAsn  ||  '=' == cAsn  ||  '?' == cAsn )
		{
			++ss;
			ss = SkipBlanks( ss );
			n = static_cast<size_t>(sEnd - ss);
			strncpy_s( t, i, ss, n );
			t[n] = 0;

			nVariableMetadata = VariableValid( t );
			if ( 1 == nVariableMetadata )
			{
				CEquationVariableAssignPtr	pAsn;
				switch ( cAsn )
				{
				case '?':
					pAsn = new CEquationVariableAssignConditional;
					break;
				case '>':
				case '=':
				default:
					pAsn = new CEquationVariableAssign;
					break;
				}
				EquationTokenType	eType2;
				pEq = Pop( &eType2 );

				pAsn->SetVariableName( t );
				pAsn->SetOperand( pEq );

				pEq = pAsn;

				if ( 'G' == *t )
					m_bGVariables = true;
			}
			else
			{
				sprintf_s( sTemp, sizeof(sTemp),
						"Unrecognized variable name (%s) in script", t );
				SetError( sTemp );
			}
		}
		else
		{
			n = static_cast<size_t>(sEnd - ss);
			strncpy_s( t, i, ss, n );
			t[n] = 0;

			CEquationVariablePtr	pVar = new CEquationVariable;

			char*	c = ::strrchr( t, ',' );
			if ( c )
			{
				CUnitsOfMeasure	uom;
				uom.SetUsingString( c+1 );
				if ( uom )
				{
					pVar->SetDesiredUoM( uom );
					*c = 0;
				}
			}


			pVar->SetVariableName( t );

			nVariableMetadata = VariableValid( t );
			if ( nVariableMetadata )
			{
				if ( 1 == nVariableMetadata )
				{
					pEq = pVar;
				}
				else	// constant value
				{
					CVariantData	v;
					if ( m_pDictionary )
					{
						v = pVar->GetValue( m_pDictionary );
						delete pVar;

						CEquationConstantPtr	pConst = new CEquationConstant;
						pConst->SetValue( v );
						pEq = pConst;
						m_bConstant = true;
						eType = T_CONSTANT;
					}
					else
					{
						pEq = pVar;
					}
				}
			}
			else
			{
				delete pVar;
				sprintf_s( sTemp, sizeof(sTemp),
						"Unrecognized variable name (%s) in script", t );
				SetError( sTemp );
			}

		}

		delete [] t;
	}
	if ( pEq )
		++m_nNodeCount;
	*pType = eType;
	return pEq;
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * VariableValid -

\+---------------------------------------------------------------------*/
int		CFactoryEquation::VariableValid
		(
		char*	sName
		)
{
	int		nResult = 1;
	if ( m_pDictionary )
	{
		if ( 'G' == *sName  &&  ':' == *(sName+1) )
		{
			nResult = 1;
		}
		else
		{
			nResult = 0;
			VDictionary::Selector nSel = m_pDictionary->LocateEntry( sName );
			if ( nSel )
			{
				nResult = 1;
				if ( m_pDictionary->IsDataLocked( nSel ) )
					nResult = -1;
			}
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * EqFromNumberHex -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::EqFromNumberHex
		(
		const char*	s,
		size_t		n
		)
{
	CEquationConstantPtr	pEq = 0;
	const char*				sEnd = s + n;
	long					nValue = 0;
	char					c;
	if ( '0' == *s  &&  'x' == ::tolower( *(s+1) ) )
		s += 2;
	while ( s < sEnd )
	{
		nValue *= 16;
		c = static_cast<char>(::toupper( *s ));
		if ( '0' <= c  &&  c <= '9' )
			nValue += c - '0';
		else if ( 'A' <= c &&  c <= 'F' )
			nValue += c - 'A' + 10;
		++s;
	}
	pEq = new CEquationConstant;
	m_bConstant = true;
	CVariantData	v;
	//if ( E_COLOR == m_eTarget )
	//{
	//	CColor	c;
	//	c.SetColorLong( nValue );
	//	v = c;
	//}
	//else
	//{
		v = nValue;
	//}
	pEq->SetValue( v );
	++m_nNodeCount;
	return pEq;
}


/*---------------------------------------------------------------------+\

 * EqFromNumberInteger -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::EqFromNumberInteger
		(
		const char*	s,
		size_t		n
		)
{
	CEquationConstantPtr	pEq = 0;
	const char*				sEnd = s + n;
	long					nSign = 1;
	long					nValue = 0;
	if ( '-' == *s )
	{
		nSign = -1;
		++s;
	}
	while ( s < sEnd )
	{
		nValue *= 10;
		nValue += (*s) - '0';
		++s;
	}
	nValue *= nSign;
	pEq = new CEquationConstant;
	m_bConstant = true;
	CVariantData v;
	v = nValue;
	pEq->SetValue( v );
	++m_nNodeCount;
	return pEq;
}

/*---------------------------------------------------------------------+\

 * EqFromNumberFloat -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::EqFromNumberFloat
		(
		const char*	s,
		size_t		n
		)
{
	CEquationConstantPtr	pEq = 0;
	size_t			i;
	GFLOAT			f = ParseFloatT<char>( s, n, &i );

	pEq = new CEquationConstant;
	m_bConstant = true;
	CVariantData	v;
	v = f;
	pEq->SetValue( v );
	++m_nNodeCount;
	return pEq;
}


/*---------------------------------------------------------------------+\

 * EqFromRegister -

\+---------------------------------------------------------------------*/
VEquationPtr
		CFactoryEquation::EqFromRegister
		(
		const char*	s,
		size_t		n
		)
{
	VEquationPtr	pEq = 0;
	const char*		sEnd = s + n;
	const char*		sK = s;
	int				nValue = 0;

	++s;
	while ( s < sEnd )
	{
		nValue *= 10;
		nValue += (*s) - '0';
		++s;
	}
	if ( nValue < 16 )
	{
		if ( 's' == *sK )
		{
			EquationTokenType	eType;
			CEquationOperatorRegisterStorePtr	pStore = new CEquationOperatorRegisterStore;
			pStore->SetRegister( nValue );
			pEq = Pop( &eType );
			pStore->SetOperand( pEq );
			pEq = pStore;
		}
		else if ( 'l' == *sK  ||  'r' == *sK )
		{
			CEquationRegisterLoadPtr	pStore = new CEquationRegisterLoad;
			pStore->SetRegister( nValue );
			pEq = pStore;
		}
	}
	++m_nNodeCount;
	return pEq;
}





/*---------------------------------------------------------------------+\

 * IsBlank -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::IsBlank
		(
		char	c
		)
{
	if ( c < 0x21 )
		return true;
	else
		return false;
}

/*---------------------------------------------------------------------+\

 * SkipBlanks -

\+---------------------------------------------------------------------*/
const char*
		CFactoryEquation::SkipBlanks
		(
		const char*	s
		)
{
	while ( *s )
	{
		if ( ! IsBlank( *s ) )
			break;
		++s;
	}
	return s;
}

/*---------------------------------------------------------------------+\

 * TokenNonBlank -

\+---------------------------------------------------------------------*/
int		CFactoryEquation::TokenNonBlank
		(
		const char*	s,
		const char*	sEnd
		)
{
	const char*	sBegin = s;

	while ( s < sEnd  &&  *s )
	{
		if ( IsBlank( *s ) )
			break;
		++s;
	}
	return int(s - sBegin);

}

/*---------------------------------------------------------------------+\

 * TokenComment -

\+---------------------------------------------------------------------*/
int		CFactoryEquation::TokenComment
		(
		const char*	s,
		const char*	sEnd
		)
{
	const char*	sBegin = s;

	if ( '/' == *s  &&  '*' == *(s+1) )
	{
		s += 2;
		while ( s < sEnd )
		{
			if ( '*' == *s  &&  '/' == *(s+1) )
			{
				s += 2;
				break;
			}
			++s;
		}
	}
	else if ( '/' == *s  &&  '/' == *(s+1) )
	{
		s += 2;
		while ( s < sEnd )
		{
			if ( '\r' == *s  ||  '\n' == *s )
				break;
			++s;
		}
	}

	return int(s - sBegin);
}

/*---------------------------------------------------------------------+\

 * TokenString -

\+---------------------------------------------------------------------*/
int		CFactoryEquation::TokenString
		(
		const char*	s,
		const char*	sEnd
		)
{
	const char*	sBegin = s;
	char	c = *s;
	if ( '\'' == c  ||  '"' == c )
	{
		++s;
		while ( s < sEnd )
		{
			if ( '\\' == *s  &&  c == *(s+1) )
			{
				++s;
			}
			else if ( c == *s )
			{
				++s;	// step past final quote
				break;
			}
			++s;
		}
		if ( c == *(s-1) )
		{
			return int(s - sBegin);
		}
		else
		{
			SetError( "unbalanced quotes in script" );
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


/*---------------------------------------------------------------------+\

 * TokenNumberHex -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::TokenNumberHex
		(
		const char*	s,
		size_t		n
		)
{
	bool	bResult = false;

	if ( 2 < n )
	{
		bResult = true;
		const char*	sEnd = s + n;
		char	c;
		if ( '0' == *s  &&  'x' == ::tolower( *(s+1) ) )
			s += 2;
		while ( s < sEnd )
		{
			c = static_cast<char>(::tolower( *s ));
			if ( ! (
					('0' <= c  &&  c <='9')
						||  ('a' <= c  &&  c <= 'f')
					))
				bResult = false;
			++s;
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * TokenNumberInteger -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::TokenNumberInteger
		(
		const char*	s,
		size_t		n
		)
{
	bool	bResult = false;

	if ( 0 < n )
	{
		bResult = true;
		const char*	sEnd = s + n;
		if ( '-' == *s  &&  1 < n )
			++s;

		while ( s < sEnd )
		{
			if ( *s < '0'  ||  '9' < *s )
				bResult = false;
			++s;
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * TokenNumberFloat -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::TokenNumberFloat
		(
		const char*	s,
		size_t		n
		)
{
	bool	bResult = false;
	if ( 1 < n )
	{
		bResult = true;
		const char*	sEnd = s + n;
		int		nState = 0;

		while ( s < sEnd )
		{
			switch ( nState )
			{
			case 0:		// just starting (only thing here is to prefix with sign)
				if ( '-' == *s )
				{
					if ( (sEnd-s) < 2 )
						bResult = false;
					++s;
				}
				nState = 1;
				break;
			case 1:
				if ( '.' == *s )
				{
					++s;
					nState = 2;
				}
				else if ( 'f' == ::tolower( *s ) )
				{
					++s;
					nState = 3;
				}
				else
				{
					if ( *s < '0'  ||  '9' < *s )
						bResult = false;
					++s;
				}
				break;
			case 2:
				if ( 'f' == ::tolower( *s ) )
				{
					++s;
					nState = 3;
				}
				else
				{
					if ( *s < '0'  ||  '9' < *s )
						bResult = false;
					++s;
				}
				break;
			case 3:
				if ( '-' == *s )
				{
					if ( (sEnd-s) < 2 )
						bResult = false;
					++s;
				}
				nState = 4;
				break;
			case 4:
				if ( *s < '0'  ||  '9' < *s )
					bResult = false;
				++s;
				break;
			default:
				++s;
				bResult = false;
				break;
			}
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * TokenRegister -

\+---------------------------------------------------------------------*/
bool	CFactoryEquation::TokenRegister
		(
		const char*	s,
		size_t		n
		)
{
	bool	bResult = false;
	if ( 1 < n )
	{
		if ( 's' == *s  ||  'l' == *s  ||  'r' == *s )
		{
			bResult = TokenNumberInteger( s+1, n-1 );
		}
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * TokenVariable -

\+---------------------------------------------------------------------*/
int		CFactoryEquation::TokenVariable
		(
		const char*	s,
		const char*	sEnd
		)
{
	const char*	sBegin = s;

	if ( '(' == *s )
	{
		++s;
		while ( s < sEnd )
		{
			if ( ')' == *s )
			{
				++s;
				break;
			}
			++s;
		}
		if ( ')' == *(s-1) )
		{
			return int(s - sBegin);
		}
		else
		{
			SetError( "Malformed variable in script" );
			return 0;
		}
	}
	else
	{
		return 0;
	}

}

/*---------------------------------------------------------------------+\

 * FindMapEntry -

\+---------------------------------------------------------------------*/
CFactoryEquation::MapToken*
		CFactoryEquation::FindMapEntry
		(
		const char*	sToken,
		int		nToken
		)
{
	MapToken*	pResult = 0;

	MapToken*	p = g_pMap;
	MapToken*	pEnd = p + g_nMap;

	while ( p < pEnd )
	{
		if ( StringEquiv( p->sToken, sToken, nToken ) )
		{
			pResult = p;
			break;
		}
		++p;
	}

	return pResult;
}

/*---------------------------------------------------------------------+\

 * FindColorEntry -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
bool	CFactoryEquation::FindColorEntry
		(
		const char*	sToken,
		size_t		nToken,
		CColorPtr	pColor
		)
{
	char			sName[128];
	const size_t	kLenName = sizeof(sName);

	strncpy_s( sName, sizeof(sName), sToken, nToken );
	sName[nToken < kLenName ? nToken : kLenName-1] = 0;
	CColor	c = CColor::ColorFromName( sName );
	*pColor = c;
	if ( c.IsNonColor() )
		return false;
	else
		return true;
}
//END_OVERRUN_WARNING

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
