/*---------------------------------------------------------------------+\
|
|	VRenderable.h  --  Identify renderable behaviors for components
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:

		All methods/functions of the VRendable interface accept
		a pointer to the Dictionary as their first argument.

|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
		Add constants that we can use to identify our fore/background
		context.
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VRenderable
#define _H_VRenderable
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionary.h"
#include "IDraw.h"
#include "VDrawQueue.h"
#include "CMouseLocate.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#define VRDR_CALCULATE_NONE			0		// no change
#define VRDR_CALCULATE_FOREGROUND	0x01	// foreground graphics redraw
#define VRDR_CALCULATE_BACKGROUND	0x02	// background graphics redraw
#define VRDR_CALCULATE_APPLICATION	0x04	// special layer
#define	VRDR_CALCULATE_LAYOUT		0x08	// relayout redraw everything
#define	VRDR_CALCULATE_UNDETERMINED	0x10	// undetermined change
											//	parent object should define scope
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class VRenderable*			VRenderablePtr;
typedef class VRenderable&			VRenderableRef;
typedef const class VRenderable&	ConstVRenderableRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VRenderable
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VRenderable(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	/*
		Calculate - compute values according to dictionary

		This function computes the new values (if any) that
		are derived from the dictionary.  If the new value
		affects the display the function returns a bitmask
		as defined by the VRDR_CALCULATE_* values
	*/
	virtual
	int		Calculate
			(
			VDictionaryPtr pDict
			) = 0;

	/*
		Layout - compute position and size values
	*/
	virtual
	bool	Layout
			(
			VDictionaryPtr	//pDict
			)
			{ return false; };


	/*
		PreRender - collect transformations and objects for
		the subsequent render call.  The Render function is
		actually called from the DrawQueue object
	*/
	virtual
	bool	PreRender
			(
			VDictionaryPtr	pDict,
			VDrawQueuePtr	pQueue
			) = 0;

	/*
		Render - output information to Draw object
	*/
	virtual
	bool	Render
			(
			VDictionaryPtr			pDict,
			Yogi::Common::VDrawPtr	pDraw
			) = 0;


	/*
		GetSize - get the effective size of the object
	*/
	virtual
	bool	GetSize
			(
			VDictionaryPtr	pDict,
			long&			rnWidth,
			long&			rnHeight
			) = 0;


	/*
		IsDisplayed - determine if the object is to be displayed
	*/
	virtual
	bool	IsDisplayed
			(
			VDictionaryPtr	pDict
			) = 0;



	/*
		Process an event request.  Part of processing the event
		may be simply handing it down to a lower level.
	*/
	virtual
	bool	ProcessEvent
			(
			VDictionaryPtr			pDict,
			VDictionary::Selector	vEvent
			) = 0;

	/*
		Process a Mouse click.
	*/
	virtual
	bool	ProcessMouse
			(
			VDictionaryPtr	pDict,
			CMouseLocatePtr	pMouseLocate
			) = 0;

	virtual
	int		GetChildContext
			(
			void
			)
	{
		return 0;
	}


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

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

#endif /* _H_VRenderable */
