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
#ifndef _H_CApplicationGaugeWorkbenchWin
#define _H_CApplicationGaugeWorkbenchWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CApplicationGauge.h"
#include "VConfiguration.h"

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
typedef class CApplicationGaugeWorkbenchWin*		CApplicationGaugeWorkbenchWinPtr;
typedef class CApplicationGaugeWorkbenchWin&		CApplicationGaugeWorkbenchWinRef;
typedef const class CApplicationGaugeWorkbenchWin&	ConstCApplicationGaugeWorkbenchWinRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CApplicationGaugeWorkbenchWin : public CApplicationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
			CApplicationGaugeWorkbenchWin();
	virtual	~CApplicationGaugeWorkbenchWin();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	//CDrawWinDDPtr	DrawWin( void )
	//void	SetCView( CView* p );


	void	SetVPostCalculate( VPostCalculate* p );
	void	SetConfiguration( Yogi::Common::VConfigurationPtr p );

protected:
//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VPostCalculate*		m_pDialog;
	//CView*	m_pCView;

private:
//	protected types  ----------------------------------------------------

	typedef	CApplicationGauge	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	CApplicationGauge
public:

	virtual bool	WindowTitle( Yogi::Core::ConstCCharDescriptorRef rChar );
	virtual bool	PostCalculateNeeded( void );

protected:
	virtual 
	Yogi::Common::VConfigurationPtr
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
