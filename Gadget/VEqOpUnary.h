/*---------------------------------------------------------------------+\
|
|	VEqOpUnary.h  --  brief description of what VEqOpUnary.h is for
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
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VEqOpUnary
#define _H_VEqOpUnary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VEquation.h"
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

typedef class VEquationOperatorUnary*		VEquationOperatorUnaryPtr;
typedef class VEquationOperatorUnary&		VEquationOperatorUnaryRef;
typedef const class VEquationOperatorUnary&	ConstVEquationOperatorUnaryRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VEquationOperatorUnary : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
				VEquationOperatorUnary();
				VEquationOperatorUnary( ConstVEquationOperatorUnaryRef r );	// copy constructor
	virtual		~VEquationOperatorUnary();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VEquationOperatorUnaryRef	operator=( ConstVEquationOperatorUnaryRef r );		// assignment

	virtual CVariantData	
				GetValue( VDictionaryPtr pDict ) = 0;

	void		SetOperand( VEquationPtr pOperand );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


//	protected data  -----------------------------------------------------

	VEquationPtr	m_pOperand;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VEquation-1
	//	VEquation

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

#endif /* _H_VEqOpUnary */

