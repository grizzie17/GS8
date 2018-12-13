/*---------------------------------------------------------------------+\
|
|	CElement.h  --  brief description of what CElement.h is for
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
#ifndef _H_CElement
#define _H_CElement
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VElement.h"

#include "TArray.h"
#include "CVisible.h"

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


typedef class CElement*		CElementPtr;
typedef class CElement&		CElementRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CElement : public VElement
{
//	class lifecycle  ----------------------------------------------------
public:
					CElement();
					CElement( CElementRef r );	// copy constructor
	virtual			~CElement();

public:
//	public types  -------------------------------------------------------

	typedef enum EContext
	{
		CTX_UNDETERMINED = -1,
		CTX_FOREGROUND = 0,
		CTX_BACKGROUND,
		CTX_APPLICATION,
		CTX_GROUP
	} EContext;

//	public functions  ---------------------------------------------------

	CElementRef	operator=( CElementRef r );		// assignment


	bool		AddRenderable( VRenderablePtr p );

	bool		SetVisible( CVisiblePtr p );

	void		SetContext( EContext ctx );
	EContext	Context( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Core::TArray<VRenderablePtr>	m_aList;
	CVisiblePtr				m_pVisible;
	EContext				m_eContext;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// VOwnership
public:
	virtual int		GetChildContext( void );


	// VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render(VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw);
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );


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

#endif /* _H_CElement */
