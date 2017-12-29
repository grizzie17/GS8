/*---------------------------------------------------------------------+\
|
|	CEqOpRegLoad.h  --  brief description of what CEqOpRegLoad.h is for
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
#ifndef _H_CEqOpRegLoad
#define _H_CEqOpRegLoad
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
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
NAMESPACE_GADGET_BEGIN

typedef class CEquationRegisterLoad*		CEquationRegisterLoadPtr;
typedef class CEquationRegisterLoad&		CEquationRegisterLoadRef;
typedef const class CEquationRegisterLoad&	ConstCEquationRegisterLoadRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationRegisterLoad : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationRegisterLoad();
					CEquationRegisterLoad( ConstCEquationRegisterLoadRef r );	// copy constructor
	virtual			~CEquationRegisterLoad();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationRegisterLoadRef	operator=( ConstCEquationRegisterLoadRef r );		// assignment

	void	SetRegister( int n );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	int		m_nRegister;

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


#endif /* _H_CEqOpRegLoad */

