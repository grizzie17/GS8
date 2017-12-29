/*---------------------------------------------------------------------+\
|
|	CEqOpUnitConvert.h  --  brief description of what CEqOpUnitConvert.h is for
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
	30-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqOpUnitConvert
#define _H_CEqOpUnitConvert
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEqOpBinary.h"

#include "CCharString.h"
#include "CUnitsOfMeasure.h"
#include "NamespaceGadget.h"
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
NAMESPACE_GADGET_BEGIN

typedef class CEquationOperatorUnitConvert*		CEquationOperatorUnitConvertPtr;
typedef class CEquationOperatorUnitConvert&		CEquationOperatorUnitConvertRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorUnitConvert : public VEquationOperatorBinary
{
//	class lifecycle  ----------------------------------------------------
public:
				CEquationOperatorUnitConvert();
				CEquationOperatorUnitConvert( CEquationOperatorUnitConvertRef r );	// copy constructor
	virtual		~CEquationOperatorUnitConvert();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorUnitConvertRef	operator=( CEquationOperatorUnitConvertRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CCharString		m_sUnitName;
	CUnitsOfMeasure	m_tUnits;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VEquation
public:
	virtual CVariantData	GetValue( VDictionaryPtr pDict );
	virtual VEquationPtr	Clone( void );

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

NAMESPACE_GADGET_END


#endif /* _H_CEqOpUnitConvert */

