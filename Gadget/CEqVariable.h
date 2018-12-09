/*---------------------------------------------------------------------+\
|
|	CEqVariable.h  --  brief description of what CEqVariable.h is for
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
#ifndef _H_CEqVariable
#define _H_CEqVariable
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEquation.h"
#include "CDictionarySelector.h"
#include "CUnitsOfMeasure.h"

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

typedef class CEquationVariable*		CEquationVariablePtr;
typedef class CEquationVariable&		CEquationVariableRef;
typedef const class CEquationVariable&	ConstCEquationVariableRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationVariable : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationVariable();
					CEquationVariable( ConstCEquationVariableRef r );	// copy constructor
	virtual			~CEquationVariable();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationVariableRef	operator=( ConstCEquationVariableRef r );		// assignment

	bool			SetVariableName( const char* sVariableName );
	void			SetDesiredUoM( ConstCUnitsOfMeasureRef cUoM );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool			GetSelector( VDictionaryPtr pDict );

//	protected data  -----------------------------------------------------

	CDictionarySelector	m_tSelector;
	CUnitsOfMeasure		m_tUoM;

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


#endif /* _H_CEqVariable */
