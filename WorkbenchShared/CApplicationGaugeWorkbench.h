/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWorkbench.h  --  brief description of what CApplicationGaugeWorkbench.h is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
#include <afxwin.h>
#include "CDrawWinWorkbench.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CApplicationGaugeWorkbench*			CApplicationGaugeWorkbenchPtr;
typedef class CApplicationGaugeWorkbench&			CApplicationGaugeWorkbenchRef;
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
					CApplicationGaugeWorkbench( ConstCApplicationGaugeWorkbenchRef r );	// copy constructor
	virtual			~CApplicationGaugeWorkbench();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CApplicationGaugeWorkbenchRef	operator=( ConstCApplicationGaugeWorkbenchRef r );		// assignment

	CDrawWinPtr		DrawWin( void );

	void			SetCView( CView* p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CView*	m_pCView;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	CApplicationGauge
public:
	virtual bool		OnDraw( void );

	virtual bool		WindowTitle( ConstCCharDescriptorRef rChar );

protected:
	virtual VDrawPtr	MakeDraw( void );
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

NAMESPACE_GADGET_END


#endif	//	OS_MSWIN

#endif /* _H_CApplicationGaugeWorkbench */
