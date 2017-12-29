/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2009 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CFactoryPanelTester.h  --  FILE RETIRED
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
	15-Sep-2009			J.Griswold		(Reviewed by: xxxx)
		THIS FILE IS RETIRED
	19-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryPanelTester
#define _H_CFactoryPanelTester
#pragma once

#if 0	// FILE RETIRED

/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VFactoryPanel.h"
#include "VFactoryGauge.h"
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
typedef class CFactoryPanelTester*			CFactoryPanelTesterPtr;
typedef class CFactoryPanelTester&			CFactoryPanelTesterRef;
typedef const class CFactoryPanelTester&	ConstCFactoryPanelTesterRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryPanelTester : public VFactoryPanel
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryPanelTester();
	virtual			~CFactoryPanelTester();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual CPanelPtr	Make( char* sName );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	virtual VFactoryGaugePtr	FactoryGauge( void );

//	protected data  -----------------------------------------------------

	VFactoryGaugePtr	m_pFactoryGauge;

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


#endif	// FILE RETIRED


#endif /* _H_CFactoryPanelTester */

