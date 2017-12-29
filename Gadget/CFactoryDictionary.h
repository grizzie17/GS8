/*---------------------------------------------------------------------+\
|
|	CFactoryDictionary.h  --  brief description of what CFactoryDictionary.h is for
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
	11-Jan-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryDictionary
#define _H_CFactoryDictionary
#pragma once
/*---------------------------------------------------------------------+\
|						
|	Include Files		
|						
\+---------------------------------------------------------------------*/

#include "CApplicationGauge.h"
#include "VDictionaryPageServer.h"
#include "CDictPageSystem.h"
#include "CDictPageActive.h"
#include "CDictPageCommands.h"
#include "CDictPageFunctions.h"
#include "CDictPageVariantRead.h"
#include "CDictPageAlerts.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|						
|	Defines				
|						
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|						
|	Type Definitions	
|						
\+---------------------------------------------------------------------*/
typedef class CFactoryDictionary*		CFactoryDictionaryPtr;
typedef class CFactoryDictionary&		CFactoryDictionaryRef;
typedef const class CFactoryDictionary&	ConstCFactoryDictionaryRef;
/*---------------------------------------------------------------------+\
|						
|	Class Definitions	
|						
\+---------------------------------------------------------------------*/

class CFactoryDictionary
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryDictionary();
	virtual			~CFactoryDictionary();

private:
	// hide functions
					CFactoryDictionary( ConstCFactoryDictionaryRef r );	// copy constructor
	CFactoryDictionaryRef	operator=( ConstCFactoryDictionaryRef r );		// assignment

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VDictionaryPageServerPtr	Make( CApplicationGaugePtr pApp, const char* sSettings );

	VDictionaryPtr			Dictionary( void );
	CDictPageActivePtr		DictPageActive( void );		// A - Active Page
	CDictPageCommandsPtr	DictPageCommands( void );	// C - Command Page
	CDictPageEventsPtr		DictPageEvents( void );
	CDictPageFunctionsPtr	DictPageFunctions( void );	// F - Function Page
	CDictPageVariantReadPtr	DictPageData( void );		// D - Data Response Page
	CDictPageVariantReadPtr	DictPageConstants( void );	// K - Constants (usually tied to "D:")
	CDictPageVariantReadPtr	DictPageInput( void );		// I - Input
	CDictPageAlertsPtr		DictPageNotify( void );		// N - Notifications

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CDictPageActivePtr		m_pDictPageActive;			// A - Active Page
	CDictPageCommandsPtr	m_pDictPageCommands;		// C - Command Page
	CDictPageVariantReadPtr	m_pDictPageData;			// D - Data Response Page
	CDictPageEventsPtr		m_pDictPageEvents;			// E - Events page
	CDictPageFunctionsPtr	m_pDictPageFunctions;		// F - Command Page
	CDictPageVariantReadPtr	m_pDictPageConstants;		// K - Constants
	CDictPageVariantReadPtr	m_pDictPageInput;			// I - Page
	CDictPageAlertsPtr		m_pDictPageNotify;			// N - Notifications

private:
//	private types  ------------------------------------------------------


//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};

/*---------------------------------------------------------------------+\
|						
|	External Variables	
|						
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||						
||	Function Prototypes	
||						
\+=====================================================================*/
/*=====================================================================+\
||						
||	Inline Functions	
||						
\+=====================================================================*/

NAMESPACE_GADGET_END



#endif /* _H_CFactoryDictionary */

