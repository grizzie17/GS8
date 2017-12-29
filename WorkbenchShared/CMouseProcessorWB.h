/*---------------------------------------------------------------------+\
|
|	CMouseProcessorWB.h  --  brief description of what CMouseProcessorWB.h is for
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
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Finish the implementation of MouseUp, MouseMove and
		MouseLeave operations
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMouseProcessorWB
#define _H_CMouseProcessorWB
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CApplicationGauge.h"
#include "VMouseProcessorWin.h"
#include "CMatrix3x3.h"

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
typedef class CMouseProcessorWB*		CMouseProcessorWBPtr;
typedef class CMouseProcessorWB&		CMouseProcessorWBRef;
typedef const class CMouseProcessorWB&	ConstCMouseProcessorWBRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CMouseProcessorWB : public VMouseProcessorWin
{
//	class lifecycle  ----------------------------------------------------
public:
					CMouseProcessorWB();
	virtual			~CMouseProcessorWB();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	SetMouseProcessor( VMouseProcessorWinPtr p );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VMouseProcessorWinPtr	m_pRealProcessor;

	CApplicationGaugePtr	m_pApplication;
	CMatrix3x3				m_tFudge;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

public:
	//	VMouseProcessorWin
	virtual void	OnLButtonDown(uint_t nFlags, int x, int y);
	virtual void	OnLButtonUp(uint_t nFlags, int x, int y);
	virtual void	OnMouseMove(uint_t nFlags, int x, int y);
	virtual void	OnMouseHover(uint_t nFlags, int x, int y);
	virtual void	OnMouseLeave( void );

	virtual void	SetApplication( CApplicationGaugePtr p );

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



#endif /* _H_CMouseProcessorWB */

