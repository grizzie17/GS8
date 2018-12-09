/*---------------------------------------------------------------------+\
|
|	CEqConstGaugeLeft.h  --  brief description of what CEqConstGaugeLeft.h is for
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
#ifndef _H_CEqConstGaugeLeft
#define _H_CEqConstGaugeLeft
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEqConstGauge.h"




namespace Yogi { namespace Gadget {
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

typedef class CEquationGaugeLeft*			CEquationGaugeLeftPtr;
typedef class CEquationGaugeLeft&			CEquationGaugeLeftRef;
typedef const class CEquationGaugeLeft&	ConstCEquationGaugeLeftRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationGaugeLeft : public VEquationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationGaugeLeft();
					CEquationGaugeLeft( CEquationGaugeLeftRef r );	// copy constructor
	virtual			~CEquationGaugeLeft();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationGaugeLeftRef	operator=( CEquationGaugeLeftRef r );		// assignment


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
}}


#endif /* _H_CEqConstGaugeLeft */
