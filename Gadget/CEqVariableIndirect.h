/*---------------------------------------------------------------------+\
|
|	CEqVariableIndirect.h  --  brief description of what VariableIndirect.h is for
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
	02-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqVariableIndirect
#define _H_CEqVariableIndirect
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEqOpUnary.h"
#include "CDictionarySelector.h"
#include "CCharDescriptor.h"

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

typedef class CEquationVariableIndirect*		CEquationVariableIndirectPtr;
typedef class CEquationVariableIndirect&		CEquationVariableIndirectRef;
typedef const class CEquationVariableIndirect&	ConstCEquationVariableIndirectRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationVariableIndirect : public VEquationOperatorUnary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationVariableIndirect();
					CEquationVariableIndirect( ConstCEquationVariableIndirectRef r );	// copy constructor
	virtual			~CEquationVariableIndirect();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationVariableIndirectRef	operator=( ConstCEquationVariableIndirectRef r );		// assignment


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool			GetSelector( VDictionaryPtr pDict );

//	protected data  -----------------------------------------------------

	CDictionarySelector	m_tSelector;

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


#endif /* _H_VariableIndirect */
