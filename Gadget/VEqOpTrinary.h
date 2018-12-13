/*---------------------------------------------------------------------+\
|
|	VEqOpTrinary.h  --  brief description of what VEqOpTrinary.h is for
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
#ifndef _H_VEqOpTrinary
#define _H_VEqOpTrinary
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

typedef class VEquationOperatorTrinary*		VEquationOperatorTrinaryPtr;
typedef class VEquationOperatorTrinary&		VEquationOperatorTrinaryRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VEquationOperatorTrinary : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
			VEquationOperatorTrinary();
			VEquationOperatorTrinary( VEquationOperatorTrinaryRef r );	// copy constructor
	virtual	~VEquationOperatorTrinary();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VEquationOperatorTrinaryRef	operator=( VEquationOperatorTrinaryRef r );		// assignment

	virtual Yogi::Common::CVariantData	GetValue(VDictionaryPtr pDict) = 0;

	void		SetControl( VEquationPtr pControl );
	void		SetLeft( VEquationPtr pLeft );
	void		SetRight( VEquationPtr pRight );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


//	protected data  -----------------------------------------------------

	VEquationPtr	m_pControl;
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

}}

#endif /* _H_VEqOpTrinary */
