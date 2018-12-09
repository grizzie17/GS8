/*---------------------------------------------------------------------+\
|
|	CKeyProcessorWin.h  --  process keyboard input and call CKepMap
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
	14-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Move bezel button functions to mfcview class
	22-Oct-2009			R.Hosea			(Reviewed by: M.Rose)
		Added bezel button fcns
	26-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CKeyProcessorWin
#define _H_CKeyProcessorWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"
#if defined( OS_MSWIN )		// brackets entire file

#	include <Winuser.h>

#	include "CApplicationGauge.h"


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
typedef class CKeyProcessorWin*			CKeyProcessorWinPtr;
typedef class CKeyProcessorWin&			CKeyProcessorWinRef;
typedef const class CKeyProcessorWin&	ConstCKeyProcessorWinRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CKeyProcessorWin
{
//	class lifecycle  ----------------------------------------------------
public:
					CKeyProcessorWin();
	virtual			~CKeyProcessorWin();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	// functions that receive input from MFC
	void	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	void	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	void	OnBezelDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	void	OnBezelUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	void	SetApplication( CApplicationGaugePtr p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CApplicationGaugePtr	m_pApplication;
	unsigned char			m_aKeys[256 + 64];

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

}}


#endif	// OS_MSWIN



#endif /* _H_CKeyProcessorWin */
