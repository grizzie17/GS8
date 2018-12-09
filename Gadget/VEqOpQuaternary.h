/*---------------------------------------------------------------------+\
|
|	VEqOpQuaternary.h  --  brief description of what VEqOpQuaternary.h is for
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
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VEqOpQuaternary
#define _H_VEqOpQuaternary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

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
namespace Yogi { namespace Gadget {

typedef class VEquationOperatorQuaternary*			VEquationOperatorQuaternaryPtr;
typedef class VEquationOperatorQuaternary&			VEquationOperatorQuaternaryRef;
typedef const class VEquationOperatorQuaternary&	ConstVEquationOperatorQuaternaryRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VEquationOperatorQuaternary : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					VEquationOperatorQuaternary();
					VEquationOperatorQuaternary( ConstVEquationOperatorQuaternaryRef r );	// copy constructor
	virtual			~VEquationOperatorQuaternary();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VEquationOperatorQuaternaryRef	operator=( ConstVEquationOperatorQuaternaryRef r );		// assignment

	virtual CVariantData	GetValue( VDictionaryPtr pDict ) = 0;

	void		SetOperand1( VEquationPtr pOp );
	void		SetOperand2( VEquationPtr pOp );
	void		SetOperand3( VEquationPtr pOp );
	void		SetOperand4( VEquationPtr pOp );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


//	protected data  -----------------------------------------------------

	VEquationPtr	m_pOperand1;
	VEquationPtr	m_pOperand2;
	VEquationPtr	m_pOperand3;
	VEquationPtr	m_pOperand4;

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

}}

#endif /* _H_VEqOpQuaternary */
