/*---------------------------------------------------------------------+\
|
|	VEqOpBinary.h  --  brief description of what VEqOpBinary.h is for
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
	26-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Change the copy constructor to receive a type of const
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VEqOpBinary
#define _H_VEqOpBinary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEquation.h"
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

typedef class VEquationOperatorBinary*			VEquationOperatorBinaryPtr;
typedef class VEquationOperatorBinary&			VEquationOperatorBinaryRef;
typedef const class VEquationOperatorBinary&	ConstVEquationOperatorBinaryRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VEquationOperatorBinary : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					VEquationOperatorBinary();
					VEquationOperatorBinary( ConstVEquationOperatorBinaryRef r );	// copy constructor
	virtual			~VEquationOperatorBinary();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VEquationOperatorBinaryRef	operator=( VEquationOperatorBinaryRef r );		// assignment

	virtual CVariantData	GetValue(VDictionaryPtr pDict) = 0;

	void		SetLeft( VEquationPtr pLeft );
	void		SetRight( VEquationPtr pRight );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


//	protected data  -----------------------------------------------------

	VEquationPtr	m_pLeft;
	VEquationPtr	m_pRight;

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

#endif /* _H_VEqOpBinary */

