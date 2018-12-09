/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWorkbench.h  --  brief description of what CApplicationGaugeWorkbench.h is for
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
	26-Jan-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for setting the window title
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
#ifndef _H_CApplicationGaugeWorkbench
#define _H_CApplicationGaugeWorkbench
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CApplicationGauge.h"

#include "UMachine.h"
#if defined( OS_MSWIN )
//#include <afxwin.h>
//#include "CDrawWin.h"
//#include "CDrawWinWorkbenchCE.h"

#include "VPostCalculate.h"


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
typedef class CApplicationGaugeWorkbench*		CApplicationGaugeWorkbenchPtr;
typedef class CApplicationGaugeWorkbench&		CApplicationGaugeWorkbenchRef;
typedef const class CApplicationGaugeWorkbench&	ConstCApplicationGaugeWorkbenchRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CApplicationGaugeWorkbench : public CApplicationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CApplicationGaugeWorkbench();
	virtual			~CApplicationGaugeWorkbench();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	//CDrawWinDDPtr	DrawWin( void );

	void			SetVPostCalculate( VPostCalculate* p );
	void			SetConfiguration( VConfigurationPtr p );

protected:
//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VPostCalculate*		m_pDialog;

private:
//	protected types  ----------------------------------------------------

	typedef	CApplicationGauge	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	CApplicationGauge
public:

	virtual bool		WindowTitle( ConstCCharDescriptorRef rChar );
	virtual bool		PostCalculateNeeded( void );

protected:
	virtual VConfigurationPtr
						MakeConfiguration( void );

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


#endif	//	OS_MSWIN

#endif /* _H_CApplicationGaugeWorkbench */
