/*---------------------------------------------------------------------+\
|
|	CEqOpAdd.h  --  brief description of what CEqOpAdd.h is for
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
#ifndef _H_CEqOpAdd
#define _H_CEqOpAdd
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

typedef class CEquationOperatorAdd*		CEquationOperatorAddPtr;
typedef class CEquationOperatorAdd&		CEquationOperatorAddRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorAdd : public VEquationOperatorBinary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorAdd();
					CEquationOperatorAdd( CEquationOperatorAddRef r );	// copy constructor
	virtual			~CEquationOperatorAdd();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorAddRef	operator=( CEquationOperatorAddRef r );		// assignment

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


#endif /* _H_CEqOpAdd */
