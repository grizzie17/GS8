/*---------------------------------------------------------------------+\
|
|	VEqConstGauge.h  --  brief description of what VEqConstGauge.h is for
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
#ifndef _H_VEqConstGauge
#define _H_VEqConstGauge
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEquation.h"
#include "VPanelChild.h"

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

typedef class VEquationGauge*		VEquationGaugePtr;
typedef class VEquationGauge&		VEquationGaugeRef;
typedef const class VEquationGauge&	ConstVEquationGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VEquationGauge : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					VEquationGauge();
					VEquationGauge( VEquationGaugeRef r );	// copy constructor
	virtual			~VEquationGauge();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VEquationGaugeRef	operator=( VEquationGaugeRef r );		// assignment

	void			SetGauge( VPanelChildPtr p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VPanelChildPtr	m_pGauge;


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


#endif /* _H_VEqConstGauge */
