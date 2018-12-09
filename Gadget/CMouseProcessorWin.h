/*---------------------------------------------------------------------+\
|
|	CMouseProcessorWin.h  --  brief description of what CMouseProcessorWin.h is for
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
		change POINT to int x, y
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Finish the implementation of MouseUp, MouseMove and
		MouseLeave operations
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMouseProcessorWin
#define _H_CMouseProcessorWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"
//#if defined( OS_MSWIN )		// brackets entire file
#	include "CApplicationGauge.h"
#	include "VMouseProcessorWin.h"

#	include "NamespaceGadget.h"
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
typedef class CMouseProcessorWin*		CMouseProcessorWinPtr;
typedef class CMouseProcessorWin&		CMouseProcessorWinRef;
typedef const class CMouseProcessorWin&	ConstCMouseProcessorWinRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CMouseProcessorWin : public VMouseProcessorWin
{
//	class lifecycle  ----------------------------------------------------
public:
					CMouseProcessorWin();
	virtual			~CMouseProcessorWin();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CApplicationGaugePtr	m_pApplication;
	int						m_nLastX;
	int						m_nLastY;
	bool					m_bMouseDown;

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

}}


//#endif	// OS_MSWIN

#endif /* _H_CMouseProcessorWin */
