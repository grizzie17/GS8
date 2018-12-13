/*---------------------------------------------------------------------+\
|
|	CEqOpIncrement.h  --  brief description of what CEqOpIncrement.h is for
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
#ifndef _H_CEqOpIncrement
#define _H_CEqOpIncrement
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

typedef class CEquationOperatorIncrement*		CEquationOperatorIncrementPtr;
typedef class CEquationOperatorIncrement&		CEquationOperatorIncrementRef;
typedef const class CEquationOperatorIncrement&	ConstCEquationOperatorIncrementRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorIncrement : public VEquationOperatorUnary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorIncrement();
					CEquationOperatorIncrement( ConstCEquationOperatorIncrementRef r );	// copy constructor
	virtual			~CEquationOperatorIncrement();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorIncrementRef	operator=( ConstCEquationOperatorIncrementRef r );		// assignment

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


#endif /* _H_CEqOpIncrement */
