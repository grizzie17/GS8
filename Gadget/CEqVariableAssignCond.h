/*---------------------------------------------------------------------+\
|
|	CEqVariableAssignCond.h  --  brief description of what CEqVariableAssignCond.h is for
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
#ifndef _H_CEqVariableAssignCond
#define _H_CEqVariableAssignCond
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "CEqVariableAssign.h"
#include "CDictionarySelector.h"

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

typedef class CEquationVariableAssignConditional*		CEquationVariableAssignConditionalPtr;
typedef class CEquationVariableAssignConditional&		CEquationVariableAssignConditionalRef;
typedef const class CEquationVariableAssignConditional&	ConstCEquationVariableAssignConditionalRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationVariableAssignConditional : public CEquationVariableAssign
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationVariableAssignConditional();
					CEquationVariableAssignConditional( ConstCEquationVariableAssignConditionalRef r );	// copy constructor
	virtual			~CEquationVariableAssignConditional();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationVariableAssignConditionalRef	operator=( ConstCEquationVariableAssignConditionalRef r );		// assignment


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VEquation
public:
	virtual Yogi::Common::CVariantData	GetValue( VDictionaryPtr pDict );
	virtual VEquationPtr	Clone( void );

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


#endif /* _H_CEqVariableAssignCond */
