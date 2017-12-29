/*---------------------------------------------------------------------+\
|
|	CPolyline.h  --  brief description of what CPolyline.h is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPolyline
#define _H_CPolyline
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPolylist.h"
#include "TArray.h"
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

typedef class CPolyline*		CPolylinePtr;
typedef class CPolyline&		CPolylineRef;
typedef const class CPolyline&	ConstCPolylineRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPolyline : public VPolylist
{
//	class lifecycle  ----------------------------------------------------
public:
					CPolyline();
					CPolyline( ConstCPolylineRef r );	// copy constructor
	virtual			~CPolyline();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CPolylineRef	operator=( ConstCPolylineRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef	VPolylist	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );

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


#endif /* _H_CPolyline */

