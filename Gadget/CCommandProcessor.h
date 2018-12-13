/*---------------------------------------------------------------------+\
|
|	CCommandProcessor.h  --  Example command processor class
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
	18-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Changed hierarchy to make this class a reasonable base class
		for Command Processors
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for the new "Constants" dictionary page
	25-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add command to toggle which VehicleData XML processor
		that we are going to use.
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add access to the Reload function on the application
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCommandProcessor
#define _H_CCommandProcessor
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFunctionProcessor.h"
#include "CApplicationGauge.h"
#include "CDictPageVariantRead.h"
#include "VDictionary.h"

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
typedef class CCommandProcessor*		CCommandProcessorPtr;
typedef class CCommandProcessor&		CCommandProcessorRef;
typedef const class CCommandProcessor&	ConstCCommandProcessorRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCommandProcessor : public VFunctionProcessor
{
//	class lifecycle  ----------------------------------------------------
public:
					CCommandProcessor();
	virtual			~CCommandProcessor();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	//void			SetLoaderControl( bool*	pLoaderControl );

	virtual void	SetApplication( CApplicationGaugePtr p );
	virtual void	InitializeFunctions( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CApplicationGaugePtr	m_pApplication;
	//bool*					m_pLoaderControl;
	VDictionaryPagePtr		m_pPageData;
	VDictionaryPagePtr		m_pPageConstants;
	//CDictPageVariantReadPtr	m_pPageData;
	//CDictPageVariantReadPtr	m_pPageConstants;

	// functions
	VDictionary::Selector	m_cToggleLoader;

	VDictionary::Selector	m_cReloadScreens;
	VDictionary::Selector	m_cDumpDictionary;
	VDictionary::Selector	m_cBlackout;
	long					m_nBlackout;

	VDictionary::Selector	m_cBackgroundColor;
	VDictionary::Selector	m_cWindowTitle;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VFunctionProcessor
public:
	virtual bool
			ProcessRequest
			(
			VDictionary::Selector				sel,
			Yogi::Common::ConstCVariantDataRef	vData
			);


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



#endif /* _H_CCommandProcessor */
