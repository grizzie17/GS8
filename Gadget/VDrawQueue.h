/*---------------------------------------------------------------------+\
|
|	VDrawQueue.h  --  class to manage drawing parameters
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
	30-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VDrawQueue
#define _H_VDrawQueue
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionary.h"
#include "IDraw.h"


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

class VRenderable;
//class VDraw;

typedef class VDrawQueue*		VDrawQueuePtr;
typedef class VDrawQueue&		VDrawQueueRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VDrawQueue
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VDrawQueue(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	SetCropRectangle( float left, float top, float right, float bottom ) = 0;

	virtual bool	SetPosition( float x, float y ) = 0;
	virtual bool	SetShift( float x, float y ) = 0;
	virtual bool	SetAxis( float x, float y ) = 0;
	virtual bool	SetRotation( float fRadians ) = 0;
	virtual bool	SetScale( float fScale ) = 0;
	virtual bool	SetVisible( bool bVisible ) = 0;

	virtual bool	AddGraphic( VRenderable*	pGraphic ) = 0;

	virtual bool	RenderGraphics(VDictionaryPtr pDict, Yogi::Common::VDraw* pDraw) = 0;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

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


#endif /* _H_VDrawQueue */
