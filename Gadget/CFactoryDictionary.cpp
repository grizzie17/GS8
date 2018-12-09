/*---------------------------------------------------------------------+\
|
|	CFactoryDictionary.cpp  --  brief description of what CFactoryDictionary.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
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
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CFactoryDictionary.h"

#include "CDictionary.h"
#include "CDictPageEvents.h"
#include "CDictPageFunctions.h"
#include "CDictHandlerTime.h"
#include "CDictPageSystem.h"
#include "CDictPageT.h"
#include "CDictPageLazyLoad.h"
#include "CDictPageConfigWrapper.h"

#include "CApplicationGauge.h"
#include "CFactoryDictActive.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Local defines / constants
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Local Type Definitions
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Private Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Public Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	 Code
||
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictAppHdlrBase -

\+---------------------------------------------------------------------*/

class CDictAppHdlrBase : public VDictPageHandler
{
//	class lifecycle  ----------------------------------------------------
public:
	CDictAppHdlrBase() : VDictPageHandler(), m_pApp( 0 ){};
	CDictAppHdlrBase( CApplicationGaugePtr p ) : VDictPageHandler(), m_pApp( p ){}
	virtual			~CDictAppHdlrBase(){};

	void			SetApplication( CApplicationGaugePtr p )
	{
		m_pApp = p;
	}

protected:

	CApplicationGaugePtr	m_pApp;

//============================== Overrides ==============================
	//	VDictPageHandler
public:
	virtual bool			BeginCalculate( CDictPageSystemPtr pPage );
	virtual bool			EndCalculate( CDictPageSystemPtr pPage );
	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage );
	virtual bool			PutData( CDictPageSystemPtr pPage, CVariantDataPtr pData );

};

bool	CDictAppHdlrBase::BeginCalculate
		(
		CDictPageSystemPtr //pPage
		)
{
	return false;
}

bool	CDictAppHdlrBase::EndCalculate
		(
		CDictPageSystemPtr //pPage
		)
{
	return false;
}


CVariantDataPtr
		CDictAppHdlrBase::GetData
		(
		CDictPageSystemPtr //pPage
		)
{
	return &m_tData;
}


bool	CDictAppHdlrBase::PutData
		(
		CDictPageSystemPtr,
		CVariantDataPtr
		)
{
	return false;	// no public put data allowed
}


class CDictAppHdlr_Screen_Width : public CDictAppHdlrBase
{
public:
	CDictAppHdlr_Screen_Width() : CDictAppHdlrBase(){}
	CDictAppHdlr_Screen_Width( CApplicationGaugePtr p ) : CDictAppHdlrBase( p ){}
	virtual ~CDictAppHdlr_Screen_Width(){}

	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage )
	{
		int		w;
		int		h;
		m_pApp->GetClientSize( &w, &h );
		//m_pApp->Screen()->GetSize( 0, w, h );
		m_tData = long(w);
		return CDictAppHdlrBase::GetData( pPage );
	}
};

class CDictAppHdlr_Screen_Height : public CDictAppHdlrBase
{
public:
	CDictAppHdlr_Screen_Height() : CDictAppHdlrBase(){}
	CDictAppHdlr_Screen_Height( CApplicationGaugePtr p ) : CDictAppHdlrBase( p ){}
	virtual ~CDictAppHdlr_Screen_Height(){}

	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage )
	{
		int		w;
		int		h;
		m_pApp->GetClientSize( &w, &h );
		//m_pApp->Screen()->GetSize( 0, w, h );
		m_tData = long(h);
		return CDictAppHdlrBase::GetData( pPage );
	}
};


/*=====================================================================+\
||	 class lifecycle functions
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CFactoryDictionary - constructor

\+---------------------------------------------------------------------*/
CFactoryDictionary::CFactoryDictionary
		(
		void
		)
{
}

/*---------------------------------------------------------------------+\

 * CFactoryDictionary - copy constructor

\+---------------------------------------------------------------------*/
CFactoryDictionary::CFactoryDictionary
		(
		ConstCFactoryDictionaryRef	//r
		)
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CFactoryDictionary - destructor

\+---------------------------------------------------------------------*/
CFactoryDictionary::~CFactoryDictionary
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CFactoryDictionaryRef
		CFactoryDictionary::operator=
		(
		ConstCFactoryDictionaryRef	//r
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}



/*---------------------------------------------------------------------+\

 * Make - Make the dictionary

\+---------------------------------------------------------------------*/
VDictionaryPageServerPtr
		CFactoryDictionary::Make
		(
		CApplicationGaugePtr	pApp,
		const char*				tSettings
		)
{
	CDictionaryPtr	pDict = new CDictionary;
	if ( pDict )
	{
		CCharString		sSettings = tSettings;
		CFactoryDictActive	aPage;

		aPage.SetVariableIF( pApp->Configuration() );

		if ( aPage.Make( sSettings.Pointer() ) )
		{
			CDictPageTPtr	pTesting = new CDictPageT;
			pDict->SetDictionaryPage( 'T', pTesting );

			CDictPageActivePtr		pActive = aPage.GetPageActive();
			CDictPageVariantReadPtr	pBase = aPage.GetPageBase();
			CDictPageAlertsPtr		pNotify = aPage.GetPageNotify();
			if ( pActive )
			{
				m_pDictPageActive = pActive;
				pDict->SetDictionaryPage( 'A', pActive );
				pTesting->SetPageActive( pActive );
			}
			if ( pBase )
			{
				pDict->SetDictionaryPage( 'B', pBase );
				pTesting->SetPageBase( pBase );
			}
			if ( pNotify )
			{
				m_pDictPageNotify = pNotify;
				pDict->SetDictionaryPage( 'N', pNotify );
			}
		}

		m_pDictPageCommands = new CDictPageCommands;
		if ( m_pDictPageCommands )
		{
			//m_pDictPageCommands->SetCommandQueue( m_pCommandQueue );
			pDict->SetDictionaryPage( 'C', m_pDictPageCommands );
		}

		m_pDictPageFunctions = new CDictPageFunctions;
		if ( m_pDictPageFunctions )
		{
			//m_pDictPageFunctions->SetFunctionProcessor( m_pFunctionProcessor );
			pDict->SetDictionaryPage( 'F', m_pDictPageFunctions );
		}


		m_pDictPageData = new CDictPageVariantRead;
		if ( m_pDictPageData )
			pDict->SetDictionaryPage( 'D', m_pDictPageData );

		m_pDictPageConstants = new CDictPageVariantRead;
		if ( m_pDictPageConstants )
			pDict->SetDictionaryPage( 'K', m_pDictPageConstants );

		m_pDictPageEvents = new CDictPageEvents;
		if ( m_pDictPageEvents )
		{
			//m_pDictPageEvents->SetEventQueue( EventQueue() );
			pDict->SetDictionaryPage( 'E', m_pDictPageEvents );
		}

		m_pDictPageInput = new CDictPageVariantRead;
		if ( m_pDictPageInput )
		{
			CVariantData	v;
			pDict->SetDictionaryPage( 'M', m_pDictPageInput );
			pDict->SetDictionaryPage( 'I', m_pDictPageInput );
			v = 0L;
			m_pDictPageInput->AddEntry( "X", v );
			m_pDictPageInput->AddAlias( CCharDescriptor("X"), CCharDescriptor("Mouse X") );
			m_pDictPageInput->AddEntry( "Y", v );
			m_pDictPageInput->AddAlias( CCharDescriptor("Y"), CCharDescriptor("Mouse Y") );
			m_pDictPageInput->AddEntry( "Event", v );
			m_pDictPageInput->AddAlias( CCharDescriptor( "Event"), CCharDescriptor("Mouse Event") );

			m_pDictPageInput->AddEntry( "Key Code", v );
			m_pDictPageInput->AddEntry( "Key Modifier", v );
			m_pDictPageInput->AddEntry( "Key State", v );
		}

		CDictPageSystemPtr pPageSys = new CDictPageSystem;
		if ( pPageSys )
		{
			VDictPageHandlerPtr	pHndlr;
			pHndlr = new CDictTime_Milli;
			if ( pHndlr )
				pPageSys->AddEntryPageHandler( "MILLI", pHndlr );
			pHndlr = new CDictTime_Absolute_Time;
			if ( pHndlr )
				pPageSys->AddEntryPageHandler( "ABSOLUTE TIME", pHndlr );
			pHndlr = new CDictTime_Absolute_Time;
			if ( pHndlr )
				pPageSys->AddEntryPageHandler( "ZULU TIME", pHndlr );
			pHndlr = new CDictAppHdlr_Screen_Width( pApp );
			if ( pHndlr )
				pPageSys->AddEntryPageHandler( "SCREEN WIDTH", pHndlr );
			pHndlr = new CDictAppHdlr_Screen_Height( pApp );
			if ( pHndlr )
				pPageSys->AddEntryPageHandler( "SCREEN HEIGHT", pHndlr );
			pDict->SetDictionaryPage( 'S', pPageSys );
		}

		CDictPageConfigWrapperPtr	pCfgWrapper;
		pCfgWrapper = new CDictPageConfigWrapper;
		if ( pCfgWrapper )
		{
			BEGIN_IGNORE_WARNING(4946)	// suppress warning: cast between related classes
			pCfgWrapper->SetConfiguration( reinterpret_cast<CConfigurationPtr>(pApp->Configuration()) );
			END_IGNORE_WARNING
			pDict->SetDictionaryPage( 'P', pCfgWrapper );
		}

		CDictPageLazyLoadPtr	pLazy;
		pLazy = new CDictPageLazyLoad;
		if ( pLazy )
			pDict->SetDictionaryPage( 'U', pLazy );


	}

	return pDict;
}


/*---------------------------------------------------------------------+\

 * DictPageActive - 'A' page

\+---------------------------------------------------------------------*/
CDictPageActivePtr
		CFactoryDictionary::DictPageActive
		(
		void
		)
{
	return m_pDictPageActive;
}

/*---------------------------------------------------------------------+\

 * DictPageFunctions - 'C' page

\+---------------------------------------------------------------------*/
CDictPageCommandsPtr
		CFactoryDictionary::DictPageCommands
		(
		void
		)
{
	return m_pDictPageCommands;
}


/*---------------------------------------------------------------------+\

 * DictPageEventss - 'E' page

\+---------------------------------------------------------------------*/
CDictPageEventsPtr
		CFactoryDictionary::DictPageEvents
		(
		void
		)
{
	return m_pDictPageEvents;
}


/*---------------------------------------------------------------------+\

 * DictPageFunctions - 'F' page

\+---------------------------------------------------------------------*/
CDictPageFunctionsPtr
		CFactoryDictionary::DictPageFunctions
		(
		void
		)
{
	return m_pDictPageFunctions;
}


/*---------------------------------------------------------------------+\

 * DictPageData - 'D' page

\+---------------------------------------------------------------------*/
CDictPageVariantReadPtr
		CFactoryDictionary::DictPageData
		(
		void
		)
{
	return m_pDictPageData;
}


/*---------------------------------------------------------------------+\

 * DictPageInput - 'I' page

\+---------------------------------------------------------------------*/
CDictPageVariantReadPtr
		CFactoryDictionary::DictPageInput
		(
		void
		)
{
	return m_pDictPageInput;
}



/*---------------------------------------------------------------------+\

 * DictPageConstants - 'K' page

\+---------------------------------------------------------------------*/
CDictPageVariantReadPtr
		CFactoryDictionary::DictPageConstants
		(
		void
		)
{
	return m_pDictPageConstants;
}



/*---------------------------------------------------------------------+\

 * DictPageNotify - 'N' page

\+---------------------------------------------------------------------*/
CDictPageAlertsPtr
		CFactoryDictionary::DictPageNotify
		(
		void
		)
{
	return m_pDictPageNotify;
}



/*=====================================================================+\
||	 protected member functions
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions
\+=====================================================================*/

/*=====================================================================+\
||
||	 Overrides
||
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
