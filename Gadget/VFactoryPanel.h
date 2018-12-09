/*---------------------------------------------------------------------+\
|
|	VFactoryPanel.h  --  Interface for creating CPanel(s)
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
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Rework class hierarchy for XMLLite
	19-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFactoryPanel
#define _H_VFactoryPanel
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/


#include "VFactoryComponent.h"

#include "VFactoryGauge.h"
#include "CPanel.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VFactoryPanel*		VFactoryPanelPtr;
typedef class VFactoryPanel&		VFactoryPanelRef;
typedef const class VFactoryPanel&	ConstVFactoryPanelRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VFactoryPanel : public VFactoryComponent
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VFactoryPanel(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	CPanelPtr		Make( const char* sName ) = 0;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	// return a pointer to the gauge factory
	virtual
	VFactoryGaugePtr
					FactoryGauge( void ) = 0;

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



#endif /* _H_VFactoryPanel */
