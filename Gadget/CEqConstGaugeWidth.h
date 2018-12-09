/*---------------------------------------------------------------------+\
|
|	CEqConstGaugeWidth.h  --  brief description of what CEqConstGaugeWidth.h is for
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
#ifndef _H_CEqConstGaugeWidth
#define _H_CEqConstGaugeWidth
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

typedef class CEquationGaugeWidth*			CEquationGaugeWidthPtr;
typedef class CEquationGaugeWidth&			CEquationGaugeWidthRef;
typedef const class CEquationGaugeWidth&	ConstCEquationGaugeWidthRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationGaugeWidth : public VEquationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationGaugeWidth();
					CEquationGaugeWidth( CEquationGaugeWidthRef r );	// copy constructor
	virtual			~CEquationGaugeWidth();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationGaugeWidthRef	operator=( CEquationGaugeWidthRef r );		// assignment


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


#endif /* _H_CEqConstGaugeWidth */
