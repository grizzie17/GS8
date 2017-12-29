/*---------------------------------------------------------------------+\
|
|	CEqVariableAssignIndirect.h  --  brief description of what VariableIndirect.h is for
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
	27-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqVariableAssignIndirect
#define _H_CEqVariableAssignIndirect
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VEqOpBinary.h"
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
NAMESPACE_GADGET_BEGIN

typedef class CEquationVariableAssignIndirect*		CEquationVariableAssignIndirectPtr;
typedef class CEquationVariableAssignIndirect&		CEquationVariableAssignIndirectRef;
typedef const class CEquationVariableAssignIndirect&	ConstCEquationVariableAssignIndirectRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationVariableAssignIndirect : public VEquationOperatorBinary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationVariableAssignIndirect();
					CEquationVariableAssignIndirect( ConstCEquationVariableAssignIndirectRef r );	// copy constructor
	virtual			~CEquationVariableAssignIndirect();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationVariableAssignIndirectRef	operator=( ConstCEquationVariableAssignIndirectRef r );		// assignment


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
	virtual CVariantData	GetValue( VDictionaryPtr pDict );
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

NAMESPACE_GADGET_END


#endif /* _H_VariableIndirect */

