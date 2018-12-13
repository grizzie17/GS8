/*---------------------------------------------------------------------+\
|
|	CDrawQueue.h  --  class to manage drawing parameters
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
#ifndef _H_CDrawQueue
#define _H_CDrawQueue
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDrawQueue.h"

#include "IDraw.h"
#include "VRenderable.h"
#include "TArray.h"

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

typedef class CDrawQueue*		CDrawQueuePtr;
typedef class CDrawQueue&		CDrawQueueRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDrawQueue : public VDrawQueue
{
//	class lifecycle  ----------------------------------------------------
public:
					CDrawQueue();
					CDrawQueue( CDrawQueueRef r );	// copy constructor
	virtual			~CDrawQueue();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	SetCropRectangle( float left, float top, float right, float bottom );

	virtual bool	SetPosition( float x, float y );
	virtual bool	SetShift( float x, float y );
	virtual bool	SetAxis( float x, float y );
	virtual bool	SetRotation( float fRadians );
	virtual bool	SetScale( float fScale );
	virtual bool	SetVisible( bool bVisible );

	virtual bool	AddGraphic( VRenderablePtr	pGraphic );

	virtual bool	RenderGraphics(VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	float			m_nCropLeft;
	float			m_nCropTop;
	float			m_nCropRight;
	float			m_nCropBottom;
	bool			m_bCropped;

	float			m_nXPosition;
	float			m_nYPosition;

	float			m_nXShift;
	float			m_nYShift;

	float			m_nXAxis;		// rotation point defined by position
	float			m_nYAxis;

	float			m_fRotation;	// radians 0 - 2pi

	float			m_fScale;

	bool			m_bVisible;

	Yogi::Core::TArray<VRenderablePtr>	m_aGraphics;

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


#endif /* _H_CDrawQueue */
