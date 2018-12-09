/*---------------------------------------------------------------------+\
|
|	CEqConstGaugeHeight.h  --  brief description of what CEqConstGaugeHeight.h is for
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
#ifndef _H_CEqConstGaugeHeight
#define _H_CEqConstGaugeHeight
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

typedef class CEquationGaugeHeight*			CEquationGaugeHeightPtr;
typedef class CEquationGaugeHeight&			CEquationGaugeHeightRef;
typedef const class CEquationGaugeHeight&	ConstCEquationGaugeHeightRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationGaugeHeight : public VEquationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationGaugeHeight();
					CEquationGaugeHeight( CEquationGaugeHeightRef r );	// copy constructor
	virtual			~CEquationGaugeHeight();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationGaugeHeightRef	operator=( CEquationGaugeHeightRef r );		// assignment


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


#endif /* _H_CEqConstGaugeHeight */
