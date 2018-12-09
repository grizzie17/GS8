/*---------------------------------------------------------------------+\
|
|	CEqVariableAssign.h  --  brief description of what CEqVariableAssign.h is for
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
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetVariableName that uses descriptor to send the name instead
		of null terminated string.
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqVariableAssign
#define _H_CEqVariableAssign
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

typedef class CEquationVariableAssign*			CEquationVariableAssignPtr;
typedef class CEquationVariableAssign&			CEquationVariableAssignRef;
typedef const class CEquationVariableAssign&	ConstCEquationVariableAssignRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationVariableAssign : public VEquationOperatorUnary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationVariableAssign();
					CEquationVariableAssign( ConstCEquationVariableAssignRef r );	// copy constructor
	virtual			~CEquationVariableAssign();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationVariableAssignRef	operator=( ConstCEquationVariableAssignRef r );		// assignment

	bool			SetVariableName( const char* sVariableName );
	bool			SetVariableName( CCharDescriptorRef rVariableName );

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

}}


#endif /* _H_CEqVariableAssign */
