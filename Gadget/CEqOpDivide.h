/*---------------------------------------------------------------------+\
|
|	CEqOpDivide.h  --  brief description of what CEqOpDivide.h is for
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
	22-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqOpDivide
#define _H_CEqOpDivide
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEqOpBinary.h"
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

typedef class CEquationOperatorDivide*		CEquationOperatorDividePtr;
typedef class CEquationOperatorDivide&		CEquationOperatorDivideRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorDivide : public VEquationOperatorBinary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorDivide();
					CEquationOperatorDivide( CEquationOperatorDivideRef r );	// copy constructor
	virtual			~CEquationOperatorDivide();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorDivideRef	operator=( CEquationOperatorDivideRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

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


#endif /* _H_CEqOpDivide */
