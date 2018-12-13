/*---------------------------------------------------------------------+\
|
|	CEqOpDegFromRad.h  --  brief description of what CEqOpDegFromRad.h is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	01-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqOpDegFromRad
#define _H_CEqOpDegFromRad
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEqOpUnary.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

typedef class CEquationOperatorDegreesFromRadians*			CEquationOperatorDegreesFromRadiansPtr;
typedef class CEquationOperatorDegreesFromRadians&			CEquationOperatorDegreesFromRadiansRef;
typedef const class CEquationOperatorDegreesFromRadians&	ConstCEquationOperatorDegreesFromRadiansRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorDegreesFromRadians : public VEquationOperatorUnary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorDegreesFromRadians();
					CEquationOperatorDegreesFromRadians( ConstCEquationOperatorDegreesFromRadiansRef r );	// copy constructor
	virtual			~CEquationOperatorDegreesFromRadians();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorDegreesFromRadiansRef	operator=( ConstCEquationOperatorDegreesFromRadiansRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::CUnitsOfMeasure	m_unitDegree;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VEquation
public:
	virtual Yogi::Common::CVariantData	GetValue( VDictionaryPtr pDict );
	virtual VEquationPtr				Clone( void );

	//	VEquationOperatorBinary

};

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}


#endif /* _H_CEqOpDegFromRad */
