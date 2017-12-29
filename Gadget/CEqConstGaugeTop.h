/*---------------------------------------------------------------------+\
|
|	CEqConstGaugeTop.h  --  brief description of what CEqConstGaugeTop.h is for
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
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqConstGaugeTop
#define _H_CEqConstGaugeTop
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEqConstGauge.h"

#include "NamespaceGadget.h"


NAMESPACE_GADGET_BEGIN
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

typedef class CEquationGaugeTop*			CEquationGaugeTopPtr;
typedef class CEquationGaugeTop&			CEquationGaugeTopRef;
typedef const class CEquationGaugeTop&	ConstCEquationGaugeTopRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationGaugeTop : public VEquationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationGaugeTop();
					CEquationGaugeTop( CEquationGaugeTopRef r );	// copy constructor
	virtual			~CEquationGaugeTop();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationGaugeTopRef	operator=( CEquationGaugeTopRef r );		// assignment


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
	//	VEquation-1
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


#endif /* _H_CEqConstGaugeTop */

