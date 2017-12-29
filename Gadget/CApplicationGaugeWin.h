/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWin.h  --  brief description of what CApplicationGaugeWin.h is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changes to support foreground/background (double-buffer) drawing.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Dispose of unnecessary functions
	05-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CApplicationGaugeWin
#define _H_CApplicationGaugeWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CApplicationGauge.h"

#include "UMachine.h"
#if defined( OS_MSWIN )
//#include "CDrawWin.h"
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
typedef class CApplicationGaugeWin*			CApplicationGaugeWinPtr;
typedef class CApplicationGaugeWin&			CApplicationGaugeWinRef;
typedef const class CApplicationGaugeWin&	ConstCApplicationGaugeWinRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CApplicationGaugeWin : public CApplicationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CApplicationGaugeWin();
					CApplicationGaugeWin( ConstCApplicationGaugeWinRef r );	// copy constructor
	virtual			~CApplicationGaugeWin();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CApplicationGaugeWinRef	operator=( ConstCApplicationGaugeWinRef r );		// assignment

	//CDrawWinPtr		DrawWin( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef CApplicationGauge	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	CApplicationGauge
public:
	virtual bool		OnDraw( void );

protected:
	virtual VDrawPtr	MakeDraw( void );

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


#endif	//	OS_MSWIN

#endif /* _H_CApplicationGaugeWin */

