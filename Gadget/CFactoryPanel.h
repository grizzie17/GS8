/*---------------------------------------------------------------------+\
|
|	CFactoryPanel.h  --  brief description of what GaugeFactory.h is for
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
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for passing the dictionary down to the Equation
		Factory so it can use it to validate the scripts.
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite Parser
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryPanel
#define _H_CFactoryPanel
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryPanel.h"

#include "NamespaceGadget.h"

#include "CFactoryEquation.h"
#include "CFactoryGauge.h"

#include "CPanel.h"


#include "CGauge.h"


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

typedef class CFactoryPanel*		CFactoryPanelPtr;
typedef class CFactoryPanel&		CFactoryPanelRef;
typedef const class CFactoryPanel&	ConstCFactoryPanelRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryPanel : public VFactoryPanel
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryPanel();
	virtual			~CFactoryPanel();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	CPanelPtr		Make( const char* sName );



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


	CGaugePtr		MakeGauge( CCharDescriptorRef rName );

	CPanelPtr		Panel( XMLIteratorPtr pIt );

	CGaugePtr		GaugeInstance( XMLIteratorPtr pIt );




//	protected data  -----------------------------------------------------

	CGaugePtr			m_pGauge;
	VFactoryGaugePtr	m_pGgFactory;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VFactoryPanel
protected:
	virtual
	VFactoryGaugePtr	FactoryGauge( void );


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


#endif /* _H_CFactoryPanel */


