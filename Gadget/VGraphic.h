/*---------------------------------------------------------------------+\
|
|	VGraphic.h  --  Base class from which all graphic classes are derived
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
	30-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VGraphic
#define _H_VGraphic
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VOwnership.h"
#include "CStyle.h"
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
NAMESPACE_GADGET_BEGIN


typedef class VGraphic*			VGraphicPtr;
typedef class VGraphic&			VGraphicRef;
typedef const class VGraphic&	ConstVGraphicRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VGraphic : public VOwnership
{
//	class lifecycle  ----------------------------------------------------
public:
					VGraphic();
					VGraphic( ConstVGraphicRef r );	// copy constructor
	virtual			~VGraphic();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VGraphicRef	operator=( ConstVGraphicRef r );		// assignment

	void		SetStyle( CStylePtr pStyle );
	CStylePtr	Style( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CStylePtr		m_pStyle;

private:
//	private types  ------------------------------------------------------

	typedef VOwnership	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render(VDictionaryPtr pDict, VDrawPtr pDraw);
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



NAMESPACE_GADGET_END


#endif /* _H_VGraphic */

