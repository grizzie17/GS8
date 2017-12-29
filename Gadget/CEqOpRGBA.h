/*---------------------------------------------------------------------+\
|
|	CEqOpRGBA.h  --  Color from Red, Green, Blue, Alpha
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
#ifndef _H_CEqOpRGBA
#define _H_CEqOpRGBA
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEqOpQuaternary.h"

#include "TArray.h"
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

typedef class CEquationOperatorRGBA*		CEquationOperatorRGBAPtr;
typedef class CEquationOperatorRGBA&		CEquationOperatorRGBARef;
typedef const class CEquationOperatorRGBA&	ConstCEquationOperatorRGBARef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorRGBA : public VEquationOperatorQuaternary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorRGBA();
					CEquationOperatorRGBA( ConstCEquationOperatorRGBARef r );	// copy constructor
	virtual			~CEquationOperatorRGBA();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorRGBARef	operator=( ConstCEquationOperatorRGBARef r );		// assignment


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


#endif /* _H_CEqOpRGBA */

