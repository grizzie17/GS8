/*---------------------------------------------------------------------+\
|
|	VControlEventMap.h  --  brief description of what VControlEventMap.h is for
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
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VControlEventMap
#define _H_VControlEventMap
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VControl.h"
#include "TPointer.h"
#include "CKeyEventMap.h"


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

typedef class VControlEventMap*			VControlEventMapPtr;
typedef TPointer<VControlEventMap>		VControlEventMapAutoPtr;
typedef class VControlEventMap&			VControlEventMapRef;
typedef const class VControlEventMap&	ConstVControlEventMapRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VControlEventMap : public VControl
{
//	class lifecycle  ----------------------------------------------------
public:
					VControlEventMap();
					VControlEventMap( VControlEventMapRef r );	// copy constructor
	virtual			~VControlEventMap();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VControlEventMapRef		operator=( VControlEventMapRef r );		// assignment

	void			SetKeyEventMap( CKeyEventMapPtr p );
	CKeyEventMapPtr	KeyEventMap( void );


	virtual int		CalculateDirtyRectangle
					(
					VDictionaryPtr	pDict,
					long*	pLeft,
					long*	pTop,
					long*	pRight,
					long*	pBottom
					);



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TPointer<CKeyEventMap>	m_pKeyEventMap;

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
NAMESPACE_GADGET_END


#endif /* _H_VControlEventMap */

