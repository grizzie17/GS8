/*---------------------------------------------------------------------+\
|
|	CApplicationGauge.cpp  --  Main Application entry point
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
	11-Dec-2018			J.Griswold
		Migrate to correctly using namespaces.
	01-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Fixed a problem where when we process ReloadScreen it would
		distort the views based on the amount specified in the
		left and right margins.
	23-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the new SetPosition()
	08-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Change SetMouseTransform function to deal with the new
		IMouseTransform interface
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for dictionary entries for keyboard events
		'Key Code', 'Key Modifier', 'Key State'
		Fix the call to AddAlias for the 'I:' dictionary page
	27-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add GetUserID function
	20-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add SetMouseTransform function
	22-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fix a problem that caused a bad display on a panel switch
		until the first calculate happened after the panel switch
	22-Mar-2010         P.Hogan         (Reviewed by: M.Rose)
		Implemented dirty rectangle graphics updating
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Deal with the new mouse hover capability.
		Support the ability to specify the background color at runtime.
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'.
	01-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Add the "M" page support for the mouse-events
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for MouseDown, MouseUp, and MouseMove
	19-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		New function to "send" a gauge event
	12-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fix the startup events and cleanup event processing
	10-Jan-2010			J.Griswold		(Reviewed by: M.Rose) [1]
		Add new Blackout feature that will cripple the display
		of data until reenabled.
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix call to VDraw::Size()
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		React to new abstract base class for the configuration.
		Add new function to dump the contents of the dictionary.
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for new dictionary page that hosts constants
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changes to support foreground/background (double-buffer) drawing.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add CalculateNow function that will always calculate
		Also make sure that we reset the Notify page on data timeout
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Move stale-data calculation to its own function that will
		be called via a timer.
	13-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Optimization in the Calculate function so we don't check to
		see if our input stream has gone stale so frequently.
	02-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for "Active" Dictionary timeout
	31-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Handle resetting the "Active" dictionary page when we are
		not receiving Vehicle data.
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add Startup Event processing
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add functionality to force a Maximum elapsed time between
		calculates
	25-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix a problem where EventQueueProcess resulted in clearing
		the dirty flag on the dictionary.
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to create the dictionary before the screen is created
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Support KeyEventMaps on the Screen object in addition to
		the active panel.
		Also fix the Reload function so that it works!
	29-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		React to class hierarchy change for CCharString/CCharDescriptor
	27-Aug-2009			J.Griswold
		Add support for the new CConfiguration class
		Add support for reload of XML screen/panels/gauges
		Allow designation of screen (XML) name for load
	26-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <limits.h>

#include "CApplicationGauge.h"
#include "UPlatformString.h"

#include "CFactoryScreen.h"
#include "CFactoryDictionary.h"
#include "CFactoryConfiguration.h"
#include "CFactoryExternalXML.h"
#include "CFactoryPlugin.h"
#include "IApplicationUser.h"
#include "IPluginLibrary.h"
#include "CDictionary.h"

using namespace Yogi::Core;
using namespace Yogi::Common;

namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CApplicationGauge - constructor

\+---------------------------------------------------------------------*/
CApplicationGauge::CApplicationGauge
		(
		void
		)
		: m_sScreenName( "default" )
		, m_nTimeLastCalculate( 0 )
		, m_nMaximumCalculateTime( 1000 )
		, m_nMaximumUpdateTime( 1000*10 )
		, m_mDirty( VRDR_CALCULATE_NONE )
		, m_bBlackout( false )
		, m_nMarginLeft( 0 )
		, m_nMarginTop( 0 )
		, m_nMarginRight( 0 )
		, m_nMarginBottom( 0 )
		, m_nScreenWidth( 0 )
		, m_nScreenHeight( 0 )
		, m_nClientWidth( 0 )
		, m_nClientHeight( 0 )
		, m_bMouseDown( false )
		, m_nDictMouseX( 0 )
		, m_nDictMouseY( 0 )
		, m_nDictMouseEvent( 0 )
		, m_pMouseTransform( 0 )
		, m_sUserID()
		, m_nUserID( 0 )
		, m_pDraw( 0 )
		, m_pDictionary( 0 )
		, m_pEventQueue( 0 )
		, m_pCommandQueue( 0 )
		, m_pCommandProcessor( 0 )
		, m_pFunctionProcessor( 0 )
		, m_pScreen( 0 )
		, m_pMouseLocate( 0 )
		, m_pConfiguration( 0 )
		, m_pDictPageActive( 0 )
		, m_pDictPageCommands( 0 )
		, m_pDictPageData( 0 )
		, m_pDictPageFunctions( 0 )
		, m_pDictPageConstants( 0 )
		, m_pDictPageInput( 0 )
		, m_pDictPageNotify( 0 )
		, m_tCOMObjects()
		, m_tObjects()
		, m_pFactoryExternalXML( 0 )
{
	ResetDirtyRectangle();
	m_sUserID = "";
}


/*---------------------------------------------------------------------+\

 * ~CApplicationGauge - destructor

\+---------------------------------------------------------------------*/
CApplicationGauge::~CApplicationGauge
		(
		void
		)
{

	m_pScreen.Destroy();

	if ( m_pDraw )
		m_pDraw->Release();

	if ( m_pMouseTransform )
		m_pMouseTransform->Release();

	if ( m_pFactoryExternalXML )
		m_pFactoryExternalXML->Release();

	THashTableEnumerator<Yogi::Core::CCharString, Yogi::Common::ISupportsPtr>	tEnum = m_tCOMObjects.GetEnumerator();
	while ( tEnum.MoveNext() )
	{
		ISupportsPtr	pSup = tEnum.Value();
		if ( pSup )
			pSup->Release();
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetScreenName -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::SetScreenName
		(
		const char*	sName
		)
{
	m_sScreenName = sName;
	return true;
}


/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Initialize1
		(
		void
		)
{
	bool			bResult = false;
	Yogi::Common::CVariantDataPtr	pv;

	do	// sequence
	{
		if ( ! m_pConfiguration )
		{
			m_pConfiguration = MakeConfiguration();
			if ( ! m_pConfiguration )
				break;
		}

		m_bBlackout = false;

		m_pEventQueue = new CQueue;
		m_pEventQueue->SetBlockSize( 16 );
		m_pCommandQueue = new CQueue;

		m_pDictionary = MakeDictionary();
		if ( ! m_pDictionary )
			break;

		m_pDraw = MakeDraw();
		if ( ! m_pDraw )
			break;

		pv = m_pConfiguration->GetEntry( "Screen" );
		if ( pv )
			m_sScreenName = (CCharDescriptorRef)*pv;

		pv = m_pConfiguration->GetEntry( "Active Dictionary Timeout" );
		if ( pv )
		{
			GFLOAT	f = *pv;
			//if ( GFLOAT_0 < f )
			{
				Yogi::Common::CUnitsOfMeasure	u;
				u.SetUsingName( "millisecond" );
				f = pv->GetValueFloatAsUnits( u );
				m_nMaximumUpdateTime = static_cast<long>(f);
			}
		}



		bResult = true;
	} sequence;	// end sequence

	return bResult;
}

/*---------------------------------------------------------------------+\

 * Initialize2 -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Initialize2
		(
		void
		)
{
	bool	bResult = false;

	do	// sequence
	{
		if ( ! m_pDictionary )
		{
			if ( ! Initialize1() )
				break;
		}

		if ( m_pDictPageConstants )
		{
			CDictPageVariantReadPtr(m_pDictPageConstants)->LockData( true );
		}


		m_pScreen = MakeScreen();
		if ( ! m_pScreen )
			break;

		StartupProcess();

		m_pScreen->Layout( m_pDictionary );

		m_pDictionary->SetDirty( true );
		m_mDirty = (VRDR_CALCULATE_FOREGROUND
					| VRDR_CALCULATE_BACKGROUND
					| VRDR_CALCULATE_APPLICATION
					| VRDR_CALCULATE_UNDETERMINED
					| VRDR_CALCULATE_LAYOUT);
		m_nDirtyLeft = 0;
		m_nDirtyTop = 0;
		m_nDirtyRight = LONG_MAX;
		m_nDirtyBottom = LONG_MAX;

		m_pMouseLocate = new CMouseLocate;

		bResult = true;
	} sequence;	// end sequence

	return bResult;
}


/*---------------------------------------------------------------------+\

 * ReloadScreen -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::ReloadScreen
		(
		void
		)
{
	if ( m_pScreen )
		delete m_pScreen;

	m_pScreen = 0;
	m_pScreen = MakeScreen();
	m_pScreen->Calculate( m_pDictionary );
	Size( m_nScreenWidth, m_nScreenHeight );
	m_mDirty = VRDR_CALCULATE_FOREGROUND
			| VRDR_CALCULATE_BACKGROUND
			| VRDR_CALCULATE_APPLICATION
			| VRDR_CALCULATE_LAYOUT;
	m_nDirtyLeft = 0;
	m_nDirtyTop = 0;
	m_nDirtyRight = m_nScreenWidth;
	m_nDirtyBottom = m_nScreenHeight;
	return m_pScreen != 0;
}


/*---------------------------------------------------------------------+\

 * Blackout -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Blackout
		(
		bool	b
		)
{
	bool	bResult = false;

	if ( b != m_bBlackout )
	{
		m_bBlackout = b;
		m_mDirty = (VRDR_CALCULATE_FOREGROUND
					| VRDR_CALCULATE_BACKGROUND
					| VRDR_CALCULATE_APPLICATION
					| VRDR_CALCULATE_UNDETERMINED
					| VRDR_CALCULATE_LAYOUT);
		m_nDirtyLeft = 0;
		m_nDirtyTop = 0;
		m_nDirtyRight = m_nScreenWidth;
		m_nDirtyBottom = m_nScreenHeight;
		bResult = true;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * BackgroundColor -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::BackgroundColor
		(
		Yogi::Core::ConstCColorRef rColor
		)
{
	bool	bResult = false;

	if ( m_pDraw )
	{
		if ( m_pDraw->BackgroundColor( rColor ) )
		{
			m_mDirty = (VRDR_CALCULATE_FOREGROUND
						| VRDR_CALCULATE_BACKGROUND
						| VRDR_CALCULATE_APPLICATION
						| VRDR_CALCULATE_UNDETERMINED
						| VRDR_CALCULATE_LAYOUT);
			m_nDirtyLeft = LONG_MIN;
			m_nDirtyTop = LONG_MIN;
			m_nDirtyRight = LONG_MAX;
			m_nDirtyBottom = LONG_MAX;
			bResult = true;
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * WindowTitle -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::WindowTitle
		(
		Yogi::Core::ConstCCharDescriptorRef	//rChar
		)
{
	return false;
}



/*---------------------------------------------------------------------+\

 * SetDraw -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::SetDraw
		(
		Yogi::Common::VDrawPtr p
		)
{
	if ( m_pDraw )
		m_pDraw->Release();
	m_pDraw = p;
}

/*---------------------------------------------------------------------+\

 * Draw -

\+---------------------------------------------------------------------*/
Yogi::Common::VDrawPtr
		CApplicationGauge::Draw
		(
		void
		)
{
	if ( ! m_pDraw )
		m_pDraw = MakeDraw();
	return m_pDraw;
}


/*---------------------------------------------------------------------+\

 * Configuration -

\+---------------------------------------------------------------------*/
Yogi::Common::VConfigurationPtr
		CApplicationGauge::Configuration
		(
		void
		)
{
	if ( ! m_pConfiguration )
		m_pConfiguration = MakeConfiguration();
	return m_pConfiguration;
}


/*---------------------------------------------------------------------+\

 * DumpDictionary -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

void	CApplicationGauge::DumpDictionary
		(
		void
		)
{
	VDictionaryPtr	pDict = Dictionary();
	Yogi::Core::TPointer<VDictionaryEnumerator>
					pEnum = pDict->GetEnumerator();
	char			sTemp[1024];
	const char*		sFolder = GetApplicationFolder();
	char			sFolderSep[2] = { FOLDER_SEPARATOR, 0 };

	if ( sFolder )
	{
		::strcpy_s( sTemp, sizeof(sTemp), sFolder );
		::strcat_s( sTemp, sizeof(sTemp), sFolderSep );
		::strcat_s( sTemp, sizeof(sTemp), "DictionaryDump.txt" );
		if ( pEnum )
		{
			FILE*			pf;

			if ( 0 == ::fopen_s( &pf, sTemp, "w" ) )
			{
				char			cPage;
				long			nID;
				Yogi::Core::CColor			color;
				Yogi::Common::CVariantData	v;
				Yogi::Core::CCharString		sKey;
				Yogi::Core::CCharString		sv;
				Yogi::Common::CVariantData::V_TYPE	vt;
				int				nUnits;
				const char*		sUnitName;
				char			sUnitDummy[] = "undefined";
				char			sTypeBOOLEAN[] = "BOOLEAN";
				char			sTypeINTEGER[] = "INTEGER";
				char			sTypeFLOAT[] = "FLOAT";
				char			sTypeSTRING[] = "TEXT";
				char			sTypeCOLOR[] = "COLOR";
				char			sTypeDATETIME[] = "DATETIME";
				char			sTypeUNDEFINED[] = "undefined";
				char*			sType;
				Yogi::Core::CDateTime		dt;
				char			sData[80];

				while ( pEnum->MoveNext() )
				{
					cPage = pEnum->Page();
					v = pEnum->Value();
					sKey = pEnum->Key();
					nID = pEnum->ID();

					vt = v.GetType();
					nUnits = v.GetUnits();

					sUnitName = CUnitsOfMeasure::NameFromUnits( nUnits );
					if ( ! sUnitName )
						sUnitName = sUnitDummy;

					switch ( vt )
					{
					case CVariantData::T_BOOL:
						sType = sTypeBOOLEAN;
						if ( v.GetValueBool() )
							sprintf_s( sData, sizeof(sData), "%s", "True" );
						else
							sprintf_s( sData, sizeof(sData), "%s", "False" );
						break;
					case CVariantData::T_COLOR:
						sType = sTypeCOLOR;
						color = v.GetValueColor();
						sprintf_s( sData, sizeof(sData),
							"r=%2x g=%2x b=%2x a=%2x",
							color.GetRed(), color.GetGreen(), color.GetBlue(),
							color.GetAlpha() );
						break;
					case CVariantData::T_DATETIME:
						sType = sTypeDATETIME;
						dt = v.GetValueDateTime();
						dt.FormatISO( sData, sizeof(sData) );
						break;
					case CVariantData::T_FLOAT:
						sType = sTypeFLOAT;
						sprintf_s( sData, sizeof(sData), "%5.4f", v.GetValueFloat() );
						break;
					case CVariantData::T_INTEGER:
						sType = sTypeINTEGER;
						sprintf_s( sData, sizeof(sData), "%ld", v.GetValueInteger() );
						break;
					case CVariantData::T_STRING:
						sType = sTypeSTRING;
						sv = v.GetValueCCharString();
						sv.CopyTo( sData, sizeof(sData) );
						break;
					case CVariantData::T_UNDEFINED:
					default:
						sType = sTypeUNDEFINED;
						sv = v.GetValueCCharString();
						sv.CopyTo( sData, sizeof(sData) );
						break;
					}

					sv = v.GetValueCCharString();

					::fprintf( pf, "%c\t%s\t%ld\t%s\t%s\t%s\n",
							cPage, sKey.Pointer(), nID, sType, sUnitName, sData );
				}
				::fclose( pf );
			}
		}
	}
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * Dictionary -

\+---------------------------------------------------------------------*/
VDictionaryPtr
		CApplicationGauge::Dictionary
		(
		void
		)
{
	if ( ! m_pDictionary )
		m_pDictionary = MakeDictionary();
	return m_pDictionary;
}



/*---------------------------------------------------------------------+\

 * DictPageActive - 'A' page

\+---------------------------------------------------------------------*/
//CDictPageActivePtr
VDictionaryPagePtr
		CApplicationGauge::DictPageActive
		(
		void
		)
{
	return m_pDictPageActive;
}

/*---------------------------------------------------------------------+\

 * DictPageFunctions - 'C' page

\+---------------------------------------------------------------------*/
//CDictPageCommandsPtr
VDictionaryPagePtr
		CApplicationGauge::DictPageCommands
		(
		void
		)
{
	return m_pDictPageCommands;
}


/*---------------------------------------------------------------------+\

 * DictPageFunctions - 'F' page

\+---------------------------------------------------------------------*/
//CDictPageFunctionsPtr
VDictionaryPagePtr
		CApplicationGauge::DictPageFunctions
		(
		void
		)
{
	return m_pDictPageFunctions;
}


/*---------------------------------------------------------------------+\

 * DictPageData - 'D' page

\+---------------------------------------------------------------------*/
//CDictPageVariantReadPtr
VDictionaryPagePtr
		CApplicationGauge::DictPageData
		(
		void
		)
{
	return m_pDictPageData;
}


/*---------------------------------------------------------------------+\

 * DictPageConstants - 'K' page

\+---------------------------------------------------------------------*/
//CDictPageVariantReadPtr
VDictionaryPagePtr
		CApplicationGauge::DictPageConstants
		(
		void
		)
{
	return m_pDictPageConstants;
}



/*---------------------------------------------------------------------+\

 * DictPageNotify - 'N' page

\+---------------------------------------------------------------------*/
//CDictPageAlertsPtr
VDictionaryPagePtr
		CApplicationGauge::DictPageNotify
		(
		void
		)
{
	return m_pDictPageNotify;
}



/*---------------------------------------------------------------------+\

 * EventQueue -

\+---------------------------------------------------------------------*/
CQueuePtr
		CApplicationGauge::EventQueue
		(
		void
		)
{
	if ( ! m_pEventQueue )
		m_pEventQueue = new CQueue;
	return m_pEventQueue;
}



/*---------------------------------------------------------------------+\

 * Screen -

\+---------------------------------------------------------------------*/
CScreenPtr
		CApplicationGauge::Screen
		(
		void
		)
{
	if ( ! m_pScreen )
		m_pScreen = MakeScreen();
	return m_pScreen;
}

/*---------------------------------------------------------------------+\

 * GetUserID -

\+---------------------------------------------------------------------*/
Yogi::Core::ConstCCharStringRef
		CApplicationGauge::GetUserID
		(
		void
		)
{
	return m_sUserID;
}
long	CApplicationGauge::GetUserIDNumber
		(
		void
		)
{
	return m_nUserID;
}


/*---------------------------------------------------------------------+\

 * SetFunctionProcessor -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::SetFunctionProcessor
		(
		VFunctionProcessorPtr p
		)
{
	m_pFunctionProcessor = p;
}


/*---------------------------------------------------------------------+\

 * SetFunctionProcessor -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::SetCommandProcessor
		(
		VFunctionProcessorPtr p
		)
{
	m_pCommandProcessor = p;
}


/*---------------------------------------------------------------------+\

 * SetMaximumTimeElapsedToCalculate -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::SetMaximumTimeElapsedToCalculate
		(
		long	n
		)
{
	m_nMaximumCalculateTime = n;
}


/*---------------------------------------------------------------------+\

 * OnDraw -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnDraw
		(
		void
		)
{
	if ( m_pDraw  &&  m_pScreen )
	{
		bool	bNeedsRedraw = false;
		long	w = 0;
		long	h = 0;

		m_pScreen->GetSize( 0, w, h );
		m_pDraw->Size( w, h );

		m_pDraw->margin( m_nMarginLeft, m_nMarginTop,
						m_nMarginRight, m_nMarginBottom );
		if ( ! IsDisplayDirty() )
		{
			bNeedsRedraw = ! m_pDraw->RefreshRectangle();
		}
		else
		{
			bNeedsRedraw = true;
		}

		if ( bNeedsRedraw  ||  0 != m_mDirty )
		{
			m_pDraw->begin();
			m_pDraw->SetUpdateRectangle( m_nDirtyLeft, m_nDirtyTop,
										m_nDirtyRight, m_nDirtyBottom );
			if ( m_pDraw->SupportsContext() )
			{
				if ( 0 != (m_mDirty & (VRDR_CALCULATE_APPLICATION
										| VRDR_CALCULATE_LAYOUT) ) )
				{
					m_pDraw->BeginContext( VDraw::CTX_APPLICATION );
					if ( ! m_bBlackout )
						m_pScreen->Render( m_pDictionary, m_pDraw );
					m_pDraw->EndContext();
				}
				if ( 0 != (m_mDirty & (VRDR_CALCULATE_BACKGROUND
										| VRDR_CALCULATE_APPLICATION
										| VRDR_CALCULATE_LAYOUT)) )
				{
					m_pDraw->BeginContext( VDraw::CTX_BACKGROUND );
					if ( ! m_bBlackout )
						m_pScreen->Render( m_pDictionary, m_pDraw );
					m_pDraw->EndContext();
				}
				if ( 0 != (m_mDirty & (VRDR_CALCULATE_FOREGROUND
										| VRDR_CALCULATE_BACKGROUND
										| VRDR_CALCULATE_APPLICATION
										| VRDR_CALCULATE_UNDETERMINED
										| VRDR_CALCULATE_LAYOUT)) )
				{
					m_pDraw->BeginContext( VDraw::CTX_FOREGROUND );
					if ( ! m_bBlackout )
						m_pScreen->Render( m_pDictionary, m_pDraw );
					m_pDraw->EndContext();
				}
			}
			else
			{
				if ( ! m_bBlackout )
					m_pScreen->Render( m_pDictionary, m_pDraw );
			}
			m_pDraw->end();
		}
		m_mDirty = VRDR_CALCULATE_NONE;
		ResetDirtyRectangle();
		return true;
	}
	else
	{
		return false;
	}
}



/*---------------------------------------------------------------------+\

 * EventQueueProcess -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::EventQueueProcess
		(
		void
		)
{
	if ( m_pScreen )
	{
		bool	bDirty = m_pDictionary->IsDirty();

		while ( ! m_pEventQueue->IsEmpty() )
		{
			VDictionary::Selector tEvent = m_pEventQueue->Pop();
			m_pScreen->ProcessEvent( m_pDictionary, tEvent );
			bDirty = m_pDictionary->IsDirty()  ||  bDirty;
		}
		if ( bDirty )
			m_pDictionary->SetDirty();
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * FunctionQueueProcess -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::FunctionQueueProcess
		(
		void
		)
{
	bool					bResult = false;
	Yogi::Common::CVariantDataPtr			pv;
	VDictionary::Selector	tFunc;

	if ( m_pScreen )
	{
		while ( ! m_pCommandQueue->IsEmpty() )
		{
			tFunc = m_pCommandQueue->Pop();
			pv = m_pDictionary->GetData( tFunc );
			bResult = m_pCommandProcessor->ProcessRequest( tFunc, *pv );
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * StartupProcess -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::StartupProcess
		(
		void
		)
{
	bool					bResult = true;
	Yogi::Common::CVariantDataPtr		pv;
	Yogi::Core::CCharDescriptor			tValue;
	VDictionary::Selector	nSel;

	nSel = m_pDictionary->LocateEntry( "E:INITIALIZE" );
	bResult = EventQueue()->Push( nSel );

	pv = m_pConfiguration->GetEntry( "Startup Events" );
	if ( pv )
	{
		Yogi::Common::CVariantData	v = *pv;
		Yogi::Core::CCharString		t;
		Yogi::Core::CCharString		s = v;
		const char*	p = s.Pointer();
		const char*	pTok = 0;
		const char*	pEnd = p + s.Length();
		while ( p < pEnd )
		{
			p += ::strspn( p, " \r\n\t" );
			pTok = ::strpbrk( p, ";\r\n" );
			if ( pTok )
			{
				t = Yogi::Core::CCharDescriptor( p, (size_t)(pTok - p) );
				p = pTok + 1;
			}
			else
			{
				t = Yogi::Core::CCharDescriptor( p, (size_t)(pEnd - p) );
				p = pEnd;
			}

			if ( 0 < t.Length() )
			{
				nSel = m_pDictionary->LocateEntry( t );
				bResult = EventQueue()->Push( nSel );
			}
		}
	}
	else
	{
		nSel = m_pDictionary->LocateEntry( "E:UNITS IMPERIAL" );
		bResult = EventQueue()->Push( nSel );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ResetDirtyRectangle -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::ResetDirtyRectangle
		(
		void
		)
{
	m_nDirtyLeft = LONG_MAX;
	m_nDirtyTop = LONG_MAX;
	m_nDirtyRight = LONG_MIN;
	m_nDirtyBottom = LONG_MIN;
}


/*---------------------------------------------------------------------+\

 * GrowDirtyRectangle -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::GrowDirtyRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	if ( nLeft < m_nDirtyLeft )
		m_nDirtyLeft = nLeft;
	if ( nTop < m_nDirtyTop )
		m_nDirtyTop = nTop;
	if ( m_nDirtyRight < nRight )
		m_nDirtyRight = nRight;
	if ( m_nDirtyBottom < nBottom )
		m_nDirtyBottom = nBottom;
}


/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Calculate
		(
		void
		)
{
	bool	bResult = false;
	int		mCalcResult = VRDR_CALCULATE_NONE;
	if ( m_pScreen )
	{
		m_pDictionary->ClearMilliseconds();
		long	nMilli = m_pDictionary->GetMilliseconds();
		int		nLoops = 0;

		if ( m_pDictionary->IsDirty()
			||  m_nMaximumCalculateTime < (nMilli - m_nTimeLastCalculate) )
		{
			do
			{

				EventQueueProcess();
				FunctionQueueProcess();

				long	nLeft = LONG_MAX;
				long	nTop = LONG_MAX;
				long	nRight = LONG_MIN;
				long	nBottom = LONG_MIN;
				mCalcResult = m_pScreen->CalculateDirtyRectangle
										(
										m_pDictionary,
										&nLeft, &nTop,
										&nRight, &nBottom
										);
				m_mDirty |= mCalcResult;
				if ( mCalcResult )
				{
					bResult = true;
					GrowDirtyRectangle( nLeft, nTop, nRight, nBottom );
				}
				if ( 0 != (VRDR_CALCULATE_LAYOUT & m_mDirty) )
				{
					bResult = m_pScreen->Layout( m_pDictionary ) || bResult;
					m_mDirty &= ~VRDR_CALCULATE_LAYOUT;
					m_mDirty |= VRDR_CALCULATE_BACKGROUND
								| VRDR_CALCULATE_FOREGROUND
								| VRDR_CALCULATE_APPLICATION;
					m_nDirtyLeft = 0;
					m_nDirtyTop = 0;
					m_nDirtyRight = LONG_MAX;
					m_nDirtyBottom = LONG_MAX;
					m_pDictionary->SetDirty( true );
				}
				m_nTimeLastCalculate = nMilli;

				EventQueueProcess();
				FunctionQueueProcess();

			} while ( m_pDictionary->IsDirty()
						&&  ++nLoops < 30 );
		}

		if ( m_mDirty )
			bResult = true;

	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * CalculateNow -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::CalculateNow
		(
		void
		)
{
	bool	bResult = false;
	int		mCalcResult = VRDR_CALCULATE_NONE;
	if ( m_pScreen )
	{
		m_pDictionary->ClearMilliseconds();
		long	nMilli = m_pDictionary->GetMilliseconds();
		int		nLoops = 0;

		do
		{
			EventQueueProcess();
			FunctionQueueProcess();


			long	nLeft = LONG_MAX;
			long	nTop = LONG_MAX;
			long	nRight = LONG_MIN;
			long	nBottom = LONG_MIN;
			mCalcResult = m_pScreen->CalculateDirtyRectangle
								(
								m_pDictionary,
								&nLeft, &nTop,
								&nRight, &nBottom
								);
			m_mDirty |= mCalcResult;
			if ( mCalcResult )
			{
				bResult = true;
				GrowDirtyRectangle( nLeft, nTop, nRight, nBottom );
			}
			if ( 0 != (VRDR_CALCULATE_LAYOUT & m_mDirty) )
			{
				bResult = m_pScreen->Layout( m_pDictionary ) || bResult;
				m_mDirty &= ~VRDR_CALCULATE_LAYOUT;
				m_mDirty |= VRDR_CALCULATE_BACKGROUND
							| VRDR_CALCULATE_FOREGROUND
							| VRDR_CALCULATE_APPLICATION;
				m_nDirtyLeft = 0;
				m_nDirtyTop = 0;
				m_nDirtyRight = LONG_MAX;
				m_nDirtyBottom = LONG_MAX;
				m_pDictionary->SetDirty( true );
			}
			m_nTimeLastCalculate = nMilli;

			EventQueueProcess();
			FunctionQueueProcess();

		} while ( m_pDictionary->IsDirty()  &&  ++nLoops < 30 );

		if ( m_mDirty )
			bResult = true;
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * StaleData -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::StaleData
		(
		void
		)
{
	bool	bResult = false;

	if ( 0 < m_nMaximumUpdateTime )
	{
		m_pDictionary->ClearMilliseconds();
		long	nMilli = m_pDictionary->GetMilliseconds();

		if ( m_pDictPageActive )
		{
			if ( CDictPageActivePtr(m_pDictPageActive)->LastUpdate() + m_nMaximumUpdateTime < nMilli )
			{
				CDictPageActivePtr(m_pDictPageActive)->ResetAllEntries();
				CDictPageAlertsPtr(m_pDictPageNotify)->ResetAllEntries();
				bResult = true;
			}
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Position -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Position
		(
		int		x,
		int		y
		)
{
	m_nMarginLeft = x;
	m_nMarginTop = y;
	m_nMarginRight = x;
	m_nMarginBottom = y;

	m_nClientWidth = m_nScreenWidth - m_nMarginLeft - m_nMarginRight;
	m_nClientHeight = m_nScreenHeight - m_nMarginTop - m_nMarginBottom;
	return true;
}


/*---------------------------------------------------------------------+\

 * Margin -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Margin
		(
		int		nLeft,
		int		nTop,
		int		nRight,
		int		nBottom
		)
{
	m_nMarginLeft = nLeft;
	m_nMarginTop = nTop;
	m_nMarginRight = nRight;
	m_nMarginBottom = nBottom;

	m_nClientWidth = m_nScreenWidth - m_nMarginLeft - m_nMarginRight;
	m_nClientHeight = m_nScreenHeight - m_nMarginTop - m_nMarginBottom;
	return true;
}


/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::Size
		(
		int		x,
		int		y
		)
{
	bool	bResult = false;
	if ( 0 < x  &&  0 < y )
	{
		m_nScreenWidth = x;
		m_nScreenHeight = y;

		m_nClientWidth = m_nScreenWidth - m_nMarginLeft - m_nMarginRight;
		m_nClientHeight = m_nScreenHeight - m_nMarginTop - m_nMarginBottom;

		if ( m_pDraw )
			m_pDraw->Size( x, y );

		if ( m_pScreen )
		{
			if ( m_pScreen->SetSize( m_nClientWidth, m_nClientHeight ) )
			{

				m_mDirty |= VRDR_CALCULATE_LAYOUT
						| VRDR_CALCULATE_APPLICATION
						| VRDR_CALCULATE_BACKGROUND;
				bResult = CalculateNow();
				m_mDirty |= VRDR_CALCULATE_LAYOUT
						| VRDR_CALCULATE_BACKGROUND
						| VRDR_CALCULATE_FOREGROUND
						| VRDR_CALCULATE_APPLICATION;
			}
		}

		if ( m_pDictionary )
			m_pDictionary->SetDirty();

		if ( m_pMouseTransform )
			m_pMouseTransform->SetSize( x, y );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetClientSize -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::GetClientSize
		(
		int*	pWidth,
		int*	pHeight
		)
{
	if ( pWidth  &&  pHeight )
	{
		*pWidth = m_nClientWidth;
		*pHeight = m_nClientHeight;
		return true;
	}
	else
	{
		return false;
	}
}





/*---------------------------------------------------------------------+\

 * OnKeyDown -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnKeyDown
		(
		int nKeyCode,
		int mModifiers
		)
{
	bool			bResult = false;
	CKeyEventMapPtr	pMap = 0;

	if ( m_pScreen )
	{
		Yogi::Common::CVariantData	v;
		bool	bDirty = m_pDictionary->IsDirty();

		v = long(nKeyCode);
		m_pDictPageInput->UpdateEntry( m_nDictKeyCode, v );
		v = long(mModifiers);
		m_pDictPageInput->UpdateEntry( m_nDictKeyModifier, v );
		v = true;
		m_pDictPageInput->UpdateEntry( m_nDictKeyState, v );

		m_pDictionary->SetDirty( bDirty );

		pMap = m_pScreen->PanelKeyEventMap();
		if ( pMap )
			bResult = pMap->OnKeyDown( m_pDictionary, nKeyCode, mModifiers );
		pMap = m_pScreen->KeyEventMap();
		if ( pMap )
			bResult = pMap->OnKeyDown( m_pDictionary, nKeyCode, mModifiers );

	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * OnKeyRepeat -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnKeyRepeat
		(
		int nKeyCode,
		int mModifiers
		)
{
	bool			bResult = false;
	CKeyEventMapPtr	pMap = 0;

	if ( m_pScreen )
	{
		Yogi::Common::CVariantData	v;
		bool	bDirty = m_pDictionary->IsDirty();

		v = long(nKeyCode);
		m_pDictPageInput->UpdateEntry( m_nDictKeyCode, v );
		v = long(mModifiers);
		m_pDictPageInput->UpdateEntry( m_nDictKeyModifier, v );
		v = true;
		m_pDictPageInput->UpdateEntry( m_nDictKeyState, v );

		m_pDictionary->SetDirty( bDirty );


		pMap = m_pScreen->KeyEventMap();
		if ( pMap )
		{
			bResult = pMap->OnKeyRepeat( m_pDictionary, nKeyCode, mModifiers );
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * OnKeyUp -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnKeyUp
		(
		int nKeyCode,
		int mModifiers
		)
{
	bool			bResult = false;
	CKeyEventMapPtr	pMap = 0;

	if ( m_pScreen )
	{
		Yogi::Common::CVariantData	v;
		bool	bDirty = m_pDictionary->IsDirty();

		v = long(nKeyCode);
		m_pDictPageInput->UpdateEntry( m_nDictKeyCode, v );
		v = long(mModifiers);
		m_pDictPageInput->UpdateEntry( m_nDictKeyModifier, v );
		v = false;
		m_pDictPageInput->UpdateEntry( m_nDictKeyState, v );

		m_pDictionary->SetDirty( bDirty );


		pMap = m_pScreen->PanelKeyEventMap();
		if ( pMap )
			bResult = pMap->OnKeyUp( m_pDictionary, nKeyCode, mModifiers );
		pMap = m_pScreen->KeyEventMap();
		if ( pMap )
			bResult = pMap->OnKeyUp( m_pDictionary, nKeyCode, mModifiers );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * HandleMouse -

\+---------------------------------------------------------------------*/
void	CApplicationGauge::HandleMouse
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	Yogi::Common::CVariantData	v;
	GFLOAT	dx;
	GFLOAT	dy;

	if ( m_pMouseTransform )
	{
		m_pMouseTransform->Transform( &dx, &dy, x, y );
	}
	else
	{
		dx = x;
		dy = y;
	}

	m_nMouseX = dx;
	m_nMouseY = dy;

	v = m_nMouseX;
	m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseX, v );
	v = m_nMouseY;
	m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseY, v );
}




/*---------------------------------------------------------------------+\

 * OnMouseDown -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnMouseDown
		(
		int	,	//nButtonCode,
		uint_t,	//mModifiers,
		GFLOAT	x,
		GFLOAT	y
		)
{
	bool	bResult = false;
	if ( m_pScreen  &&  m_pMouseLocate )
	{
		Yogi::Common::CVariantData	v;
		bool	bDirty = m_pDictionary->IsDirty();

		HandleMouse( x, y );


		m_pMouseLocate->begin();
		m_pMouseLocate->SetAction( CMouseLocate::M_DOWN );
		m_pMouseLocate->SetPoint( m_nMouseX, m_nMouseY );
		m_bMouseDown = true;
		v = "Down";
		m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseEvent, v );


		bResult = m_pScreen->ProcessMouse( m_pDictionary, m_pMouseLocate );
		m_pMouseLocate->end();

		if ( bDirty )
			m_pDictionary->SetDirty();
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * OnMouseUp -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnMouseUp
		(
		int,	//nButtonCode,
		uint_t,	//mModifiers,
		GFLOAT	x,
		GFLOAT	y
		)
{
	bool	bResult = false;
	if ( m_pScreen  &&  m_pMouseLocate )
	{
		Yogi::Common::CVariantData	v;
		bool	bDirty = m_pDictionary->IsDirty();

		HandleMouse( x, y );

		m_pMouseLocate->begin();
		m_pMouseLocate->SetAction( CMouseLocate::M_UP );
		m_pMouseLocate->SetPoint( m_nMouseX, m_nMouseY );
		m_bMouseDown = false;
		v = "Up";
		m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseEvent, v );

		bResult = m_pScreen->ProcessMouse( m_pDictionary, m_pMouseLocate );
		m_pMouseLocate->end();

		if ( bDirty )
			m_pDictionary->SetDirty();
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * OnMouseMove -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnMouseMove
		(
		int,	//nButtonCode,
		uint_t,	//mModifiers,
		GFLOAT	x,
		GFLOAT	y
		)
{
	bool	bResult = false;
	if ( m_pScreen  &&  m_pMouseLocate  &&  m_bMouseDown )
	{
		GFLOAT	dx;
		GFLOAT	dy;

		if ( m_pMouseTransform )
		{
			m_pMouseTransform->Transform( &dx, &dy, x, y );
		}
		else
		{
			dx = x;
			dy = y;
		}


		if ( m_nMouseX != dx  ||  m_nMouseY != dy )
		{
			Yogi::Common::CVariantData	v;
			bool	bDirty = m_pDictionary->IsDirty();

			m_pMouseLocate->begin();
			m_pMouseLocate->SetAction( CMouseLocate::M_MOVE );
			m_pMouseLocate->SetPoint( GFLOAT(dx), GFLOAT(dy) );
			m_nMouseX = GFLOAT(dx);
			m_nMouseY = GFLOAT(dy);
			v = m_nMouseX;
			m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseX, v );
			v = m_nMouseY;
			m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseY, v );
			v = "Drag";
			m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseEvent, v );

			bResult = m_pScreen->ProcessMouse( m_pDictionary, m_pMouseLocate );
			m_pMouseLocate->end();

			if ( bDirty )
				m_pDictionary->SetDirty();

		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * OnMouseHover -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::OnMouseHover
		(
		int,	//nButtonCode,
		uint_t,	//mModifiers,
		GFLOAT	x,
		GFLOAT	y
		)
{
	bool	bResult = false;
	if ( m_pScreen  &&  m_pMouseLocate  &&  !m_bMouseDown )
	{
		GFLOAT	dx = x;
		GFLOAT	dy = y;

		if ( m_pMouseTransform )
		{
			m_pMouseTransform->Transform( &dx, &dy, x, y );
		}
		else
		{
			dx = x;
			dy = y;
		}

		if ( m_nMouseX != dx  ||  m_nMouseY != dy )
		{
			Yogi::Common::CVariantData	v;
			bool	bDirty = m_pDictionary->IsDirty();


			m_pMouseLocate->begin();
			m_pMouseLocate->SetAction( CMouseLocate::M_HOVER );
			m_pMouseLocate->SetPoint( GFLOAT(dx), GFLOAT(dy) );
			m_nMouseX = GFLOAT(dx);
			m_nMouseY = GFLOAT(dy);
			v = m_nMouseX;
			m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseX, v );
			v = m_nMouseY;
			m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseY, v );
			v = "Hover";
			m_pDictPageInput->UpdateEntry( (unsigned long)m_nDictMouseEvent, v );

			bResult = m_pScreen->ProcessMouse( m_pDictionary, m_pMouseLocate );
			m_pMouseLocate->end();

			if ( bDirty )
				m_pDictionary->SetDirty();

		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * SetMouseTransform -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::SetMouseTransform
		(
		Yogi::Common::ISupportsPtr	p
		)
{
	bool				bResult = false;
	IMouseTransformPtr	pOld = m_pMouseTransform;	// protect from reassign

	if ( p )
	{
		m_pMouseTransform = QI_( p, IMouseTransform );
		if ( m_pMouseTransform )
		{
			bResult = true;
			m_pMouseTransform->SetSize( m_nScreenWidth, m_nScreenHeight );
		}
	}
	else
	{
		m_pMouseTransform = 0;
		bResult = true;
	}
	if ( pOld )
		pOld->Release();

	return bResult;
}



/*---------------------------------------------------------------------+\

 * RegisterCOMObject -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::RegisterCOMObject
		(
		const char*		sKey,
		Yogi::Common::ISupportsPtr	p
		)
{
	bool								bResult = false;
	Yogi::Core::CCharString				tKey( sKey );
	const Yogi::Common::ISupportsPtr*	hSup;

	hSup = m_tCOMObjects.Find( tKey );
	if ( ! hSup )
	{
		bResult = m_tCOMObjects.Add( tKey, p );
		if ( bResult )
			p->AddRef();
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * FindCOMObject -

\+---------------------------------------------------------------------*/
ISupportsPtr
		CApplicationGauge::FindCOMObject
		(
		const char*	sKey
		)
{
	Yogi::Common::ISupportsPtr			pSup = 0;
	const Yogi::Common::ISupportsPtr*	hSup = 0;
	Yogi::Core::CCharString				tKey( sKey );

	hSup = m_tCOMObjects.Find( tKey );
	if ( hSup )
	{
		pSup = *hSup;
		pSup->AddRef();
	}


	return pSup;
}


/*---------------------------------------------------------------------+\

 * QueryCOMObject -

\+---------------------------------------------------------------------*/
ISupportsPtr
		CApplicationGauge::QueryCOMObject
		(
		ConstIXIDRef	rIXID
		)
{
	ISupportsPtr	pIf = 0;
	THashTableEnumerator<CCharString, ISupportsPtr>	tEnum = m_tCOMObjects.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		ISupportsPtr	pSup = tEnum.Value();
		if ( pSup )
		{
			pIf = (ISupportsPtr)pSup->QueryInterface( rIXID );
			if ( pIf )
				break;
		}
	}

	return pIf;
}



/*---------------------------------------------------------------------+\

 * RegisterObject -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::RegisterObject
		(
		const char*	sKey,
		VObjectPtr	p
		)
{
	bool				bResult = false;
	CCharString			tKey( sKey );
	const VObjectPtr*	h;

	h = m_tObjects.Find( tKey );
	if ( ! h )
	{
		bResult = m_tObjects.Add( tKey, p );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * FindObject -

\+---------------------------------------------------------------------*/
VObjectPtr
		CApplicationGauge::FindObject
		(
		const char*	sKey
		)
{
	VObjectPtr			p = 0;
	const VObjectPtr*	h = 0;
	CCharString			tKey( sKey );

	h = m_tObjects.Find( tKey );
	if ( h )
	{
		p = *h;
	}


	return p;
}





/*---------------------------------------------------------------------+\

 * SendEvent -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::SendEvent
		(
		const char*				sEventName,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;

	if ( m_pDictionary )
	{
		CCharString	tEvent;
		VDictionary::Selector	nSel;

		tEvent = "E:";
		tEvent += sEventName;

		nSel = m_pDictionary->LocateEntry( tEvent );
		if ( nSel )
		{
			CVariantData	v = rData;
			bResult = m_pDictionary->PutData( nSel, &v );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * PostCalculateNeeded -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::PostCalculateNeeded
		(
		void
		)
{
	// needs to be overridden
	return true;
}



/*---------------------------------------------------------------------+\

 * IsDisplayDirty -

\+---------------------------------------------------------------------*/
bool	CApplicationGauge::IsDisplayDirty
		(
		void
		)
{
	if ( m_mDirty )
		return true;

	if ( m_nDirtyLeft < m_nDirtyRight
		&&	m_nDirtyTop < m_nDirtyBottom )
		return true;

	return false;
}


/*---------------------------------------------------------------------+\

 * GetDirtyRectangle -

\+---------------------------------------------------------------------*/
bool CApplicationGauge::GetDirtyRectangle
		(
		long* pLeft,
		long* pTop,
		long* pRight,
		long* pBottom
		)
{
	bool bResult = IsDisplayDirty();
	if( bResult )
	{
		*pLeft = umax( m_nDirtyLeft, 0L );
		*pTop = umax( m_nDirtyTop, 0L );
		*pRight = umin( m_nDirtyRight, m_nScreenWidth );
		*pBottom = umin( m_nDirtyBottom, m_nScreenHeight );
	}
	return bResult;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * MakeDraw -

\+---------------------------------------------------------------------*/
VDrawPtr
		CApplicationGauge::MakeDraw
		(
		void
		)
{
	IDrawPtr			pIDraw = 0;
	ISupportsPtr		pI = FindCOMObject( "PluginLibrary" );
	if ( pI )
	{
		IPluginLibraryPtr	pIPluginLibrary = QI_( pI, IPluginLibrary );

		pI->Release();

		if ( pIPluginLibrary )
		{
			CCharString	sDrawName = m_pConfiguration->GetEntryAsString( "Draw Object", "default" );

			pIPluginLibrary->SetBaseFolder( GetApplicationFolder() );

			ISupportsArray*	aSup;

			CFactoryPlugin	plug;
			plug.SetRelativePath( "plugins/drawobjs" );
			plug.SetVariableIF( m_pConfiguration );
			aSup = plug.Make( sDrawName.Pointer(), pIPluginLibrary );

			if ( aSup )
			{
				if ( 1 == aSup->Length() )
				{
					pI = *aSup->PointArray();
					pIDraw = QI_( pI, IDraw );

					IApplicationUserPtr	pApp = QI_( pIDraw, IApplicationUser );
					if ( pApp )
					{
						pApp->SetApplication( this );
						pApp->Release();
					}
					pI->Release();
				}
				delete aSup;
			}
			pIPluginLibrary->Release();
		}
	}

	return pIDraw;
}



/*---------------------------------------------------------------------+\

 * MakeDictionary -

\+---------------------------------------------------------------------*/
VDictionaryPageServerPtr
		CApplicationGauge::MakeDictionary
		(
		void
		)
{
	VDictionaryPageServerPtr	pDict;
	CFactoryDictionary			factory;

	CCharString		sSettings;
	CCharString		sSettingsPath = "dictionary/";
	CVariantDataPtr	pv = m_pConfiguration->GetEntry( "Dictionary Settings" );
	if ( pv )
		sSettings = (CCharDescriptorRef)*pv;
	else
		sSettings = "Settings";
	sSettingsPath += sSettings;

	pDict = factory.Make( this, sSettingsPath.Pointer() );

	if ( pDict )
	{
		m_pDictPageActive = factory.DictPageActive();
		m_pDictPageNotify = factory.DictPageNotify();
		m_pDictPageData = factory.DictPageData();
		m_pDictPageConstants = factory.DictPageConstants();

		CDictPageCommandsPtr pDictPageCommands = factory.DictPageCommands();
		if ( pDictPageCommands )
		{
			pDictPageCommands->SetCommandQueue( m_pCommandQueue );
			m_pDictPageCommands = pDictPageCommands;
		}

		CDictPageFunctionsPtr pDictPageFunctions = factory.DictPageFunctions();
		if ( pDictPageFunctions )
		{
			pDictPageFunctions->SetFunctionProcessor( m_pFunctionProcessor );
			m_pDictPageFunctions = pDictPageFunctions;
		}


		CDictPageEventsPtr	pPageEvt = factory.DictPageEvents();
		if ( pPageEvt )
			pPageEvt->SetEventQueue( EventQueue() );

		CDictPageVariantReadPtr pDictPageInput = factory.DictPageInput();
		if ( pDictPageInput )
		{
			m_nDictMouseX = pDictPageInput->LocateEntry( CCharString("X") );
			m_nDictMouseY = pDictPageInput->LocateEntry( CCharString("Y") );
			m_nDictMouseEvent = pDictPageInput->LocateEntry( CCharString("Event") );

			m_nDictKeyCode = (unsigned long)pDictPageInput->LocateEntry( CCharString( "Key Code" ) );
			m_nDictKeyModifier = (unsigned long)pDictPageInput->LocateEntry( CCharString( "Key Modifier" ) );
			m_nDictKeyState = (unsigned long)pDictPageInput->LocateEntry( CCharString( "Key State" ) );

			m_pDictPageInput = pDictPageInput;
		}

		m_pDictionary = pDict;

	}

	return pDict;
}


/*---------------------------------------------------------------------+\

 * MakeScreen -

\+---------------------------------------------------------------------*/
CScreenPtr
		CApplicationGauge::MakeScreen
		(
		void
		)
{
	CFactoryScreen				factoryScreen;
	Yogi::Common::ISupportsPtr	pExt;

	if ( ! m_pFactoryExternalXML )
	{
		m_pFactoryExternalXML = NEW_OBJECT( CFactoryExternalXML );
	}

	pExt = m_pFactoryExternalXML;
	if ( pExt )
	{
		IApplicationUserPtr	pAppUser = QI_( pExt, IApplicationUser );
		if ( pAppUser )
		{
			pAppUser->SetApplication( this );
			pAppUser->Release();
		}

		factoryScreen.SetExternalXMLIF( pExt );
	}

	factoryScreen.SetRelativePath( "screens" );
	factoryScreen.SetDictionary( m_pDictionary );
	factoryScreen.SetVariableIF( m_pDictionary->GetVariableIF() );
	CScreenPtr pScreen = factoryScreen.Make( m_sScreenName.Pointer() );


	return pScreen;
}


/*---------------------------------------------------------------------+\

 * MakeConfiguration -

\+---------------------------------------------------------------------*/
VConfigurationPtr
		CApplicationGauge::MakeConfiguration
		(
		void
		)
{
	CCharString	sName( "configuration" );
	CFactoryConfiguration	factory;
	factory.SetRelativePath( "dictionary" );
	VConfigurationPtr	pConfig = factory.Make( sName.Pointer() );

	return pConfig;
}



/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
