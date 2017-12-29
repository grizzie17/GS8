/*---------------------------------------------------------------------+\
|
|	CEqOpColorname.h  --  brief description of what CEqOpColorname.h is for
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
	13-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqOpColorname
#define _H_CEqOpColorname
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEqOpUnary.h"

#include "NamespaceGadget.h"
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

typedef class CEquationOperatorColorname*		CEquationOperatorColornamePtr;
typedef class CEquationOperatorColorname&		CEquationOperatorColornameRef;
typedef const class CEquationOperatorColorname&	ConstCEquationOperatorColornameRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorColorname : public VEquationOperatorUnary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorColorname();
					CEquationOperatorColorname( ConstCEquationOperatorColornameRef r );	// copy constructor
	virtual			~CEquationOperatorColorname();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorColornameRef	operator=( ConstCEquationOperatorColornameRef r );		// assignment

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
	virtual CVariantData	GetValue( VDictionaryPtr pDict );
	virtual VEquationPtr	Clone( void );

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

NAMESPACE_GADGET_END


#endif /* _H_CEqOpColorname */

