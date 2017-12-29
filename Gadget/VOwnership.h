/*---------------------------------------------------------------------+\
|
|	VOwnership.h  --  brief description of what VOwnership.h is for
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
		Add functions for dealing with propagating the
		foreground/background context
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse.
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VOwnership
#define _H_VOwnership
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VRenderable.h"

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

typedef class VOwnership*			VOwnershipPtr;
typedef class VOwnership&			VOwnershipRef;
typedef const class VOwnership&		ConstVOwnershipRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VOwnership : public VRenderable
{
//	class lifecycle  ----------------------------------------------------
public:
					VOwnership();
					VOwnership( ConstVOwnershipRef r );
	virtual			~VOwnership();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VOwnershipRef	operator=( ConstVOwnershipRef r );

	virtual void	SetParent( VOwnershipPtr pParent );
	virtual VOwnershipPtr
					GetParent( void );

	virtual void	IncludeContext( int mask );




protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VOwnershipPtr	m_pParent;
	int				m_mChildrenContext;	// VRDR_

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		GetChildContext( void );
	virtual bool	Layout( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );

	virtual
	bool	ProcessEvent
			(
			VDictionaryPtr			pDict,
			VDictionary::Selector	vEvent
			);

	/*
		Process a Mouse click.
	*/
	virtual
	bool	ProcessMouse
			(
			VDictionaryPtr	pDict,
			CMouseLocatePtr	pMouseLocate
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
NAMESPACE_GADGET_END


#endif /* _H_VOwnership */

