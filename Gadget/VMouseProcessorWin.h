/*---------------------------------------------------------------------+\
|
|	VMouseProcessorWin.h  --  brief description of what VMouseProcessorWin.h is for
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
	13-Mar-2013			J.Griswold
		Change POINT references to int x, y
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Finish the implementation of MouseUp, MouseMove and 
		MouseLeave operations
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VMouseProcessorWin
#define _H_VMouseProcessorWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"
#include "UTypes.h"

#include "CApplicationGauge.h"

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
typedef class VMouseProcessorWin*		VMouseProcessorWinPtr;
typedef class VMouseProcessorWin&		VMouseProcessorWinRef;
typedef const class VMouseProcessorWin&	ConstVMouseProcessorWinRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VMouseProcessorWin
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VMouseProcessorWin(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual void	OnLButtonDown(uint_t nFlags, int x, int y) = 0;
	virtual void	OnLButtonUp(uint_t nFlags, int x, int y) = 0;
	virtual void	OnMouseMove(uint_t nFlags, int x, int y) = 0;
	virtual void	OnMouseHover(uint_t nFlags, int x, int y) = 0;
	virtual void	OnMouseLeave( void ) = 0;

	virtual void	SetApplication( CApplicationGaugePtr p ) = 0;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


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



#endif /* _H_VMouseProcessorWin */

