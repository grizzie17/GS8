/*---------------------------------------------------------------------+\
|
|	CEqOpCeil.h  --  brief description of what CEqOpCeil.h is for
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
#ifndef _H_CEqOpCeil
#define _H_CEqOpCeil
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

typedef class CEquationOperatorCeil*			CEquationOperatorCeilPtr;
typedef class CEquationOperatorCeil&			CEquationOperatorCeilRef;
typedef const class CEquationOperatorCeil&	ConstCEquationOperatorCeilRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorCeil : public VEquationOperatorUnary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorCeil();
					CEquationOperatorCeil( ConstCEquationOperatorCeilRef r );	// copy constructor
	virtual			~CEquationOperatorCeil();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorCeilRef	operator=( ConstCEquationOperatorCeilRef r );		// assignment

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


#endif /* _H_CEqOpCeil */
