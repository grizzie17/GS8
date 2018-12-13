/*---------------------------------------------------------------------+\
|
|	CGauge.h  --  Collection of renderable objects
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CGauge
#define _H_CGauge
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPanelChild.h"


#include "VDictionaryPage.h"
#include "VAction.h"
#include "CMouseAreaList.h"
#include "TArray.h"
#include "TPointer.h"
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
namespace Yogi { namespace Gadget {

typedef class CGauge*		CGaugePtr;
typedef class CGauge&		CGaugeRef;
typedef const class CGauge&	ConstCGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CGauge : public VPanelChild
{
//	class lifecycle  ----------------------------------------------------
public:
					CGauge();
					CGauge( CGaugeRef r );	// copy constructor
	virtual			~CGauge();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CGaugeRef	operator=( CGaugeRef r );

	bool		AddRenderable( VRenderablePtr p );

	bool		AllocateLocalData( void );

	CMouseAreaListPtr	MouseAreaList( void );



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VDictionaryPagePtr		m_pLocalData;

	Yogi::Core::TArray<VRenderablePtr>	m_aList;

	//VActionPtr			m_pAction;	// declared in VControl
	CMouseAreaListPtr		m_pMouseAreaList;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );
	virtual int		GetChildContext( void );

	//	VControl
public:
	virtual bool	ProcessEvent( VDictionaryPtr pDict, VDictionary::Selector vEvent );
	virtual bool	ProcessMouse( VDictionaryPtr pDict, CMouseLocatePtr pMouseLocate );


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

#endif /* _H_CGauge */
