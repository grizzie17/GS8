/*---------------------------------------------------------------------+\
|
|	CDrawWorkbench.cpp  --  brief description of what CDrawWorkbench.cpp is for
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
	17-Feb-2012			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CDrawWorkbench.h"
#include "VPluginFactory.h"


#include "TPointer.h"
#include "LogFile.h"

namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


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

PLUGIN_CREATE_FACTORY( CDrawWorkbench );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDrawWorkbench - constructor

\+---------------------------------------------------------------------*/
CDrawWorkbench::CDrawWorkbench
		(
		void
		)
		: inherited()
		, m_pDraw( 0 )
		, m_pApplication( 0 )
		, m_nFeed( 0 )
		, m_oVideoCache()
{
}

CDrawWorkbench::CDrawWorkbench
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_pDraw( 0 )
		, m_pApplication( 0 )
		, m_nFeed( 0 )
		, m_oVideoCache()
{
}

CDrawWorkbench::CDrawWorkbench
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_pDraw( 0 )
		, m_pApplication( 0 )
		, m_nFeed( 0 )
		, m_oVideoCache()
{
}


/*---------------------------------------------------------------------+\

 * ~CDrawWorkbench - destructor

\+---------------------------------------------------------------------*/
CDrawWorkbench::~CDrawWorkbench
		(
		void
		)
{

	THashTableEnumerator<CCharString, VImagePtr> e = m_oVideoCache.GetEnumerator();

	while ( e.MoveNext() )
	{
		VImagePtr*	ppImage = e.Current();
		if ( ppImage )
		{
			VImagePtr	pImage = *ppImage;
			pImage->Destroy();
		}
	}
	m_oChronos.PrintLog();
}

/*=====================================================================+\
||	 Interface implementation functions
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;
	return true;
}


/*=====================================================================+\
||	 public member functions
\+=====================================================================*/


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/





/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CDrawWorkbench::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDraw )
			pI = INTERFACE_THIS( IDrawPtr );
		else if ( rIID == IXID_IApplicationUser )
			pI = INTERFACE_THIS( IApplicationUserPtr );
		else
			pI = 0;
	}

	return pI;
}


#if 0 //def _DEBUG
/*---------------------------------------------------------------------+\

 * InternalAddRef -

\+---------------------------------------------------------------------*/
NRefCount
		CDrawWorkbench::InternalAddRef
		(
		void
		)
{
	NRefCount	n = inherited::InternalAddRef();
	LOCAL_PRINT( "%s: refcount=%d\n", __FUNCTION__, m_nRefCount );
	return n;
}

/*---------------------------------------------------------------------+\

 * InternalRelease -

\+---------------------------------------------------------------------*/
NRefCount
		CDrawWorkbench::InternalRelease
		(
		void
		)
{
	NRefCount	n = inherited::InternalRelease();
	LOCAL_PRINT( "%s: refcount=%d\n", __FUNCTION__, n );
	return n;
}


/*---------------------------------------------------------------------+\

 * FinalRelease -

\+---------------------------------------------------------------------*/
void	CDrawWorkbench::FinalRelease
		(
		void
		)
{
	LOCAL_PRINT( "%s\n", __FUNCTION__ );
	inherited::FinalRelease();
}

#endif // _DEBUG


/*---------------------------------------------------------------------+\

 * Load - fetch configuration parameters

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = inherited::Load( pConfig, pLib );
	if ( bResult )
	{
		NResult	nr;

		m_pDraw = static_cast<IDrawPtr>(FindExternalInterface( IXID_IDraw, &nr ));
		if ( m_pDraw )
			m_pDraw->Release();
		else
			bResult = false;
	}
	return bResult;
}




/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::begin
		(
		void
		)
{
	CHRONOS(TE_BEGIN);
	m_nFeed = 0;
	return m_pDraw->begin();
}

/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::end
		(
		void
		)
{
	CHRONOS(TE_END);
	return m_pDraw->end();
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::margin
		(
		int		nLeft,
		int		nTop,
		int		nRight,
		int		nBottom
		)
{
	return m_pDraw->margin( nLeft, nTop, nRight, nBottom );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::push
		(
		GFLOAT	xPosition,
		GFLOAT	yPosition,
		GFLOAT	xShift,
		GFLOAT	yShift,
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	rotation,
		GFLOAT	scale
		)
{
	return m_pDraw->push( xPosition, yPosition, xShift, yShift, xAxis, yAxis, rotation, scale );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::pop
		(
		void
		)
{
	return m_pDraw->pop();
}



/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Size
		(
		long	nWidth,
		long	nHeight
		)
{
	return m_pDraw->Size( nWidth, nHeight );
}


/*---------------------------------------------------------------------+\

 * BeginContext -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::BeginContext
		(
		VDraw::EDrawContexts ctx
		)
{
	CHRONOS(TE_BEGINCONTEXT);
	return m_pDraw->BeginContext( ctx );
}


/*---------------------------------------------------------------------+\

 * EndContext -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::EndContext
		(
		void
		)
{
	CHRONOS(TE_ENDCONTEXT);
	return m_pDraw->EndContext();
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
IDraw::EDrawContexts
		CDrawWorkbench::CurrentContext
		(
		void
		)
{
	return m_pDraw->CurrentContext();
}


/*---------------------------------------------------------------------+\

 * SupportsContext -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::SupportsContext
		(
		void
		)
{
	return m_pDraw->SupportsContext();
}


/*---------------------------------------------------------------------+\

 * PushCropRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::PushCropRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	return m_pDraw->PushCropRectangle( nLeft, nTop, nRight, nBottom );
}

/*---------------------------------------------------------------------+\

 * PopCropRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::PopCropRectangle
		(
		void
		)
{
	return m_pDraw->PopCropRectangle();
}


/*---------------------------------------------------------------------+\

 * RefreshRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::RefreshRectangle
		(
		void
		)
{
	return m_pDraw->RefreshRectangle();
}


/*---------------------------------------------------------------------+\

 * SetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::SetUpdateRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	return m_pDraw->SetUpdateRectangle( nLeft, nTop, nRight, nBottom );
}


/*---------------------------------------------------------------------+\

 * GetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::GetUpdateRectangle
		(
		long*	pLeft,
		long*	pTop,
		long*	pRight,
		long*	pBottom
		)
{
	return m_pDraw->GetUpdateRectangle( pLeft, pTop, pRight, pBottom );
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::DayMode
		(
		IDraw::EDayModes eMode
		)
{
	return m_pDraw->DayMode( eMode );
}



/*---------------------------------------------------------------------+\

 * LineWidth -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::LineWidth
		(
		short nWidth
		)
{
	return m_pDraw->LineWidth( nWidth );
}

/*---------------------------------------------------------------------+\

 * LineColor -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::LineColor
		(
		CColorRef rColor
		)
{
	return m_pDraw->LineColor( rColor );
}

/*---------------------------------------------------------------------+\

 * FillColor -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::FillColor
		(
		CColorRef rColor
		)
{
	return m_pDraw->FillColor( rColor );
}


/*---------------------------------------------------------------------+\

 * HaloColor -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::HaloColor
		(
		CColorRef rColor
		)
{
#if 0
	return true;
#else
	return m_pDraw->HaloColor( rColor );
#endif
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::BackgroundColor
		(
		ConstCColorRef rColor
		)
{
	return m_pDraw->BackgroundColor( rColor );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::NightColor
		(
		IDraw::ENightColorModes eMode
		)
{
	return m_pDraw->NightColor( eMode );
}



/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		)
{
	return m_pDraw->FontParams( sFontName, fFontHeight );
}



/*---------------------------------------------------------------------+\

 * Line -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Line
		(
		GFLOAT	xStart,
		GFLOAT	yStart,
		GFLOAT	xEnd,
		GFLOAT	yEnd
		)
{
	CHRONOS(TE_LINE);
	return m_pDraw->Line( xStart, yStart, xEnd, yEnd );
}


/*---------------------------------------------------------------------+\

 * Arc -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Arc
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	CHRONOS(TE_ARC);
	return m_pDraw->Arc( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );
}


/*---------------------------------------------------------------------+\

 * Circle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Circle
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius
		)
{
	CHRONOS(TE_CIRCLE);
	return m_pDraw->Circle( xAxis, yAxis, nRadius );
}

/*---------------------------------------------------------------------+\

 * Ellipse -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Ellipse
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nHeight,
		GFLOAT	nWidth
		)
{
	CHRONOS(TE_CIRCLE);
	return m_pDraw->Ellipse( xAxis, yAxis, nHeight, nWidth );
}

/*---------------------------------------------------------------------+\

 * Pie -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Pie
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	CHRONOS(TE_PIE);
	return m_pDraw->Pie( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Polygon
		(
		long		nNumPoints,
		FPointPtr	pPointList
		)
{
	return m_pDraw->Polygon( nNumPoints, pPointList );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Polyline
		(
		long		nNumPoints,
		FPointPtr	pPointList
		)
{
	return m_pDraw->Polyline( nNumPoints, pPointList );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::BeginPolyline
		(
		void
		)
{
	return m_pDraw->BeginPolyline();
}




/*---------------------------------------------------------------------+\

 * EndPolyline -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::EndPolyline
		(
		void
		)
{
	CHRONOS(TE_ENDPOLYLINE);
	return m_pDraw->EndPolyline();
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::BeginPolygon
		(
		void
		)
{
	return m_pDraw->BeginPolygon();
}




/*---------------------------------------------------------------------+\

 * EndPolygon -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::EndPolygon
		(
		void
		)
{
	CHRONOS(TE_ENDPOLYGON);
	return m_pDraw->EndPolygon();
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Polypoint
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	return m_pDraw->Polypoint( x, y );
}


/*---------------------------------------------------------------------+\

 * Rectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Rectangle
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		CORNERSTYLE	eStyle, 	//= C_SQUARE,
		GFLOAT		nCornerSize //= 0.0f
		)
{
	CHRONOS(TE_RECTANGLE);
	return m_pDraw->Rectangle( xPosition, yPosition,
							nWidth, nHeight,
							eStyle, nCornerSize );
}


/*---------------------------------------------------------------------+\

 * TextString -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::TextString
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		VDraw::EAlignments			eAlign,
		VDraw::EVerticalAlignments	eVertAlign,
		const char*	sString,
		long		nCount
		)
{
	CHRONOS(TE_TEXTSTRING);
	return m_pDraw->TextString( xPosition, yPosition, eAlign, eVertAlign, sString, nCount );
}


/*---------------------------------------------------------------------+\

 * Video -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Video
		(
		GFLOAT			xPosition,
		GFLOAT			yPosition,
		GFLOAT			nWidth,
		GFLOAT			nHeight,
		CVariantDataRef	sSource,
		EFitments		eFitment,	//= F_FILL,
		EAlignments		eAlign,		//= A_CENTER,	// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign,	// = V_MIDDLE,
		bool			bMirror		//= false
		)
{
	bool		bResult = true;
	CCharString	sImageName = sSource;

	if ( sImageName.Length() < 1L )
	{
		bResult = false;
		return bResult;
	}

	IDraw::VImagePtr	pImage = 0;
	IDraw::VImagePtr*	ppImage = 0;

	ppImage = m_oVideoCache.Find( sImageName );
	if ( ! ppImage )
	{
		bResult = ImageLoadFile( sImageName.Pointer(), &pImage );
		if ( bResult )
			m_oVideoCache.Add( sImageName.Pointer(), pImage );
	}
	else
	{
		pImage = *ppImage;
	}

	if ( pImage )
		bResult = ImagePreloaded( xPosition, yPosition, nWidth, nHeight, pImage, eFitment, eAlign, eVertAlign );
	else
		bResult = Image( xPosition, yPosition, nWidth, nHeight, sImageName.Pointer(), eFitment, eAlign, eVertAlign );

	if ( ! bResult )
	{
		LogPrint( "Problem opening %s\n", sImageName.Pointer() );
	}

	if ( bMirror )
	{
		FontParams( "sans-serif", 20.0f );
		TextString( xPosition + 5,
			yPosition + 3,
			IDraw::A_LEFT, IDraw::V_TOP,
			"MIRROR" );
	}

	++m_nFeed;
	CCharString		sFeedName;
	sFeedName.Format( "C:Video Feed %d", m_nFeed );
	VDictionaryPtr	pDict = m_pApplication->Dictionary();
	VDictionary::Selector	sel = pDict->LocateEntry( sFeedName );
	if ( sel )
	{
		pDict->PutData( sel, &sSource );
	}

	return true;

}



/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::Image
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		const char*	sSource,
		IDraw::EFitments	eFitment, // = F_Fill,
		IDraw::EAlignments	eAlign, // = A_Center,
		IDraw::EVerticalAlignments eVertAlign // = V_Middle,
		)
{
	return m_pDraw->Image( xPosition, yPosition, nWidth, nHeight, sSource, eFitment, eAlign, eVertAlign );
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::ImagePreloaded
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		IDraw::VImagePtr	pVoid,
		IDraw::EFitments	eFitment,	// = F_FILL,
		IDraw::EAlignments	eAlign,		// = A_CENTER,		// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign	// = V_MIDDLE
		)
{
	CHRONOS(TE_IMAGEPRELOADED);
	return m_pDraw->ImagePreloaded( xPosition, yPosition, nWidth, nHeight, pVoid, eFitment, eAlign, eVertAlign );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::ImageLoadFile
		(
		const char*			sSource,
		IDraw::VImagePtr*	ppImage
		)
{
	CHRONOS(TE_IMAGELOADFILE);
	bool	bResult = true;

	CCharString	sTemp = sSource;

	char	sFolder[1024] = {0};
	char	sFile[128] = {0};

	if ( ':' != sSource[1]  &&  '/' != sSource[0] )
	{
		sTemp.CopyTo( sFile, sizeof(sFile) );

		const char*	sApp = ::GetUserConfigFolder();
		::strcpy_s( sFolder, sizeof(sFolder), sApp );

		char*	t = sFolder + ::strlen(sFolder) - 1;
		if ( FOLDER_SEPARATOR_C == *t )
			::strcat_s( sFolder, sizeof(sFolder),
						"images" FOLDER_SEPARATOR_S );
		else
			::strcat_s( sFolder, sizeof(sFolder),
						FOLDER_SEPARATOR_S "images" FOLDER_SEPARATOR_S );

		::strcat_s( sFolder, sizeof(sFolder), sFile );
	}
	else
	{
		::strcpy_s( sFolder, sizeof(sFolder), sSource );
	}


	bResult = m_pDraw->ImageLoadFile( sFolder, ppImage );

	if ( ! bResult )
	{
		LogPrint( "Problem opening %s\n", sFolder );
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CDrawWorkbench::ImageRelease
		(
		IDraw::VImagePtr	pImage
		)
{
	return m_pDraw->ImageRelease( pImage );
}



}}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
