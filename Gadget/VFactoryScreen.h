/*---------------------------------------------------------------------+\
|
|	VFactoryScreen.h  --  Interface for creating CPanel(s)
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change class hierarchy to support XMLLite parser
	19-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFactoryScreen
#define _H_VFactoryScreen
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VFactoryComponent.h"
#include "VFactoryPanel.h"
#include "CScreen.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VFactoryScreen*		VFactoryScreenPtr;
typedef class VFactoryScreen&		VFactoryScreenRef;
typedef const class VFactoryScreen&	ConstVFactoryScreenRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VFactoryScreen : public VFactoryComponent
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VFactoryScreen(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual CScreenPtr	Make( const char* sName ) = 0;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	// return a pointer to the gauge factory
	virtual VFactoryPanelPtr
						FactoryPanel( void ) = 0;

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

NAMESPACE_GADGET_END



#endif /* _H_VFactoryScreen */

