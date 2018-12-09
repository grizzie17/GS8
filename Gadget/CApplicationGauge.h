/*---------------------------------------------------------------------+\
|
|	CApplicationGauge.h  --  Main application
|
|	Purpose:
|
|		This is the glue that allows the platform dependent application
|		to hook into the gauge application.
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
	23-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the new SetPosition()
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for dictionary entries for keyboard events
		'Key Code', 'Key Modifier', 'Key State'
	27-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add GetUserID function
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for MouseHover
		Add support for setting BackgroundColor during runtime
	22-Feb-2010			Min Li			(Reviewed by: M.Rose)
		Atlas mouse code added
	01-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Add the "M" page support for the mouse-events
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Finish the implementation of MouseUp, MouseMove and
		MouseLeave operations
	19-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		New function to "send" a gauge event
	10-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add new Blackout feature that will cripple the display
		of data until reenabled.
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
		Break Initialize into two functions so we can make sure
		that the dictionary is full populated before calling
		Initialize2 which parses the screen, panel and gauge XML.
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Move stale-data calculation to its own function that will
		be called via a timer.
	31-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Handle resetting the "Active" dictionary page when we are
		not receiving Vehicle data.
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add Startup Event processing
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add functionality to force a Maximum elapsed time between
		calculates
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Notification/Alerts
	27-Aug-2009			J.Griswold
		Add support for the new CConfiguration class
		Add support for reload of XML screen/panels/gauges
		Allow designation of screen (XML) name for load
	26-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CApplicationGauge
#define _H_CApplicationGauge
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UFloat.h"
#include "CQueue.h"
#include "TPointer.h"
#include "TComPointer.h"

#include "CScreen.h"
#include "IDraw.h"
#include "VDictionaryPageServer.h"
#include "VDictionaryPage.h"
#include "CMouseLocate.h"
#include "VFunctionProcessor.h"
#include "CConfiguration.h"
//#include "CMatrix3x3d.h"
//#include "CMatrix3x3.h"
#include "IMouseTransform.h"
//#include "IPluginLibrary.h"
#include "THash.h"
#include "VObject.h"



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
typedef class CApplicationGauge*		CApplicationGaugePtr;
typedef class CApplicationGauge&		CApplicationGaugeRef;
typedef const class CApplicationGauge&	ConstCApplicationGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CApplicationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CApplicationGauge();
	virtual			~CApplicationGauge();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	SetScreenName( const char* sName );

	// call Initialize1
	//	then call any functions that need to
	//	add entries into the Dictionary and
	//	then call Initialize2
	virtual bool	Initialize1( void );
	virtual bool	Initialize2( void );

	// command service functions
	virtual	bool	ReloadScreen( void );
	virtual bool	Blackout( bool b );
	virtual bool	BackgroundColor( Yogi::Core::ConstCColorRef rColor );
	virtual bool	WindowTitle(Yogi::Core::ConstCCharDescriptorRef rChar );
	virtual bool	PostCalculateNeeded( void );

	void			SetDraw( VDrawPtr p );
	VDrawPtr		Draw( void );
	virtual CQueuePtr	EventQueue( void );
	CScreenPtr		Screen( void );

	virtual
	Yogi::Core::ConstCCharStringRef		GetUserID( void );
	virtual
	long					GetUserIDNumber( void );

	virtual NAMESPACE_COMMON_PREFIX VConfigurationPtr		Configuration( void );

	virtual void					DumpDictionary( void );
	virtual VDictionaryPtr			Dictionary( void );
	virtual VDictionaryPagePtr		DictPageActive( void );		// A - Active Page
	virtual VDictionaryPagePtr		DictPageCommands( void );	// C - Command Page
	virtual VDictionaryPagePtr		DictPageFunctions( void );	// F - Function Page
	virtual VDictionaryPagePtr		DictPageData( void );		// D - Data Response Page
	virtual VDictionaryPagePtr		DictPageConstants( void );	// K - Constants (usually tied to "D:")
	virtual VDictionaryPagePtr		DictPageNotify( void );		// N - Notifications

	void			SetFunctionProcessor( VFunctionProcessorPtr p );
	void			SetCommandProcessor( VFunctionProcessorPtr p );
	void			SetMaximumTimeElapsedToCalculate( long n );

	// events
	virtual bool	OnDraw( void );
	virtual bool	Calculate( void );
	virtual bool	CalculateNow( void );
	virtual bool	StaleData( void );

	virtual bool	Position( int x, int y );
	virtual bool	Margin( int nLeft, int nTop, int nRight, int nBottom );
	virtual bool	Size( int x, int y );	// window/screen re/size
	virtual bool	GetClientSize( int* pWidth, int* pHeight );

	virtual bool	RegisterCOMObject( const char* sKey, NAMESPACE_COMMON_PREFIX ISupportsPtr p );
	virtual NAMESPACE_COMMON_PREFIX ISupportsPtr
					FindCOMObject( const char* sKey );
	virtual NAMESPACE_COMMON_PREFIX ISupportsPtr
					QueryCOMObject( NAMESPACE_COMMON_PREFIX ConstIXIDRef r );

	virtual bool	RegisterObject( const char* sKey, NAMESPACE_COMMON_PREFIX VObjectPtr p );
	virtual NAMESPACE_COMMON_PREFIX VObjectPtr
					FindObject( const char* sKey );


	bool			IsDisplayDirty( void );
	bool			GetDirtyRectangle( long* pLeft, long* pTop, long* pRight, long* pBottom );


	// functions for dealing with key input
	bool			OnKeyDown( int nKeyCode, int mModifiers );
	bool			OnKeyRepeat( int nKeyCode, int mModifiers );
	bool			OnKeyUp( int nKeyCode, int mModifiers );

	// functions for dealing with mouse input
	bool			OnMouseDown( int nButtonCode, uint_t mModifiers, GFLOAT x, GFLOAT y );
	bool			OnMouseUp( int nButtonCode, uint_t mModifiers, GFLOAT x, GFLOAT y );
	bool			OnMouseMove( int nButtonCode, uint_t mModifiers, GFLOAT x, GFLOAT y );
	bool			OnMouseHover( int nButtonCode, uint_t mModifiers, GFLOAT x, GFLOAT y );
	bool			SetMouseTransform( NAMESPACE_COMMON_PREFIX ISupportsPtr p );


	virtual bool	SendEvent( const char* sEventName, ConstCVariantDataRef rData );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool			FunctionQueueProcess( void );
	bool			EventQueueProcess( void );
	bool			StartupProcess( void );

	void			ResetDirtyRectangle( void );
	void			GrowDirtyRectangle
					(
					long	nLeft,
					long	nTop,
					long	nRight,
					long	nBottom
					);

	void			HandleMouse( GFLOAT x, GFLOAT y );

	virtual VDrawPtr					MakeDraw( void );
	virtual VDictionaryPageServerPtr	MakeDictionary( void );
	virtual CScreenPtr					MakeScreen( void );
	virtual NAMESPACE_COMMON_PREFIX VConfigurationPtr			MakeConfiguration( void );

//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString		m_sScreenName;
	long					m_nTimeLastCalculate;
	long					m_nMaximumCalculateTime;
	long					m_nMaximumUpdateTime;
	int						m_mDirty;	// mask specifying last calculate dirty
	long					m_nDirtyLeft;
	long					m_nDirtyTop;
	long					m_nDirtyRight;
	long					m_nDirtyBottom;
	bool					m_bBlackout;		// don't display

	long					m_nMarginLeft;
	long					m_nMarginTop;
	long					m_nMarginRight;
	long					m_nMarginBottom;

	long					m_nScreenWidth;
	long					m_nScreenHeight;

	long					m_nClientWidth;
	long					m_nClientHeight;

	bool					m_bMouseDown;
	GFLOAT					m_nMouseX;
	GFLOAT					m_nMouseY;
	long					m_nDictMouseX;
	long					m_nDictMouseY;
	long					m_nDictMouseEvent;
	IMouseTransformPtr		m_pMouseTransform;

	unsigned long			m_nDictKeyCode;			// last key-code
	unsigned long			m_nDictKeyModifier;
	unsigned long			m_nDictKeyState;		// down, up


	Yogi::Core::CCharString	m_sUserID;
	long					m_nUserID;

	IDrawPtr						m_pDraw;
	Yogi::Core::TPointer<VDictionaryPageServer>	m_pDictionary;
	Yogi::Core::TPointer<CQueue>				m_pEventQueue;
	Yogi::Core::TPointer<CQueue>				m_pCommandQueue;
	VFunctionProcessorPtr			m_pCommandProcessor;
	VFunctionProcessorPtr			m_pFunctionProcessor;
	Yogi::Core::TPointer<CScreen>				m_pScreen;
	Yogi::Core::TPointer<CMouseLocate>			m_pMouseLocate;
	Yogi::Core::TPointer<NAMESPACE_COMMON_PREFIX VConfiguration>		m_pConfiguration;

	VDictionaryPagePtr		m_pDictPageActive;			// A - Active Page
	VDictionaryPagePtr		m_pDictPageCommands;		// C - Command Page
	VDictionaryPagePtr		m_pDictPageData;			// D - Data Response Page
	VDictionaryPagePtr		m_pDictPageFunctions;		// F - Command Page
	VDictionaryPagePtr		m_pDictPageConstants;		// K - Constants
	VDictionaryPagePtr		m_pDictPageInput;			// I - Page
	VDictionaryPagePtr		m_pDictPageNotify;			// N - Notifications

	THashTable<Yogi::Core::CCharString, NAMESPACE_COMMON_PREFIX ISupportsPtr>	m_tCOMObjects;
	THashTable<Yogi::Core::CCharString, NAMESPACE_COMMON_PREFIX VObjectPtr>		m_tObjects;

	NAMESPACE_COMMON_PREFIX ISupportsPtr	m_pFactoryExternalXML;

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



#endif /* _H_CApplicationGauge */
