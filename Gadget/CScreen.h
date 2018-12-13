/*---------------------------------------------------------------------+\
|
|	CScreen.h  --  brief description of what CScreen.h is for
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
	12-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Optimize the handling of the active panel
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	13-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		React to hierarchy change to VControlKeyEventMap
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CScreen
#define _H_CScreen
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VControlEventMap.h"

#include "TArray.h"
#include "TDictionaryIndexed.h"
#include "CPanel.h"
#include "CResultValue.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CKeyEventMap.h"
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

typedef class CScreen*			CScreenPtr;
typedef class CScreen&			CScreenRef;
typedef const class CScreen&	ConstCScreenRef;


typedef Yogi::Common::TDictionaryIndexedEnumerator< Yogi::Core::CCharString, CPanelPtr >	CPanelEnumerator;


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CScreen : public VControlEventMap
{
//	class lifecycle  ----------------------------------------------------
public:
				CScreen();
	virtual		~CScreen();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CScreenRef	operator=( CScreenRef r );		// assignment

	bool		AddPanel( CPanelPtr	p, const char* sName );
	CPanelEnumerator
				GetEnumerator( void );

	bool		SetActivePanelEquation( VEquationPtr p );
	bool		SetSize( int x, int y );
	bool		Layout( VDictionaryPtr pDict );

	CKeyEventMapPtr	PanelKeyEventMap( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	//CResultValuePtr		m_pActivePanelSelector;
	CResultValue		m_vActivePanel;
	CPanelPtr			m_pActivePanel;
	Yogi::Common::TDictionaryIndexed< Yogi::Core::CCharString, CPanelPtr >	m_tPanelList;

	long				m_nWidth;
	long				m_nHeight;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );

	//	VControl
public:
	virtual bool	ProcessEvent( VDictionaryPtr pDict, VDictionary::Selector vEvent );
	virtual bool	ProcessMouse( VDictionaryPtr pDict, CMouseLocatePtr pMouseLocate );


	//	VControlEventMap
public:
	virtual int		CalculateDirtyRectangle
					(
					VDictionaryPtr	pDict,
					long*	pLeft,
					long*	pTop,
					long*	pRight,
					long*	pBottom
					);


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


#endif /* _H_CScreen */
