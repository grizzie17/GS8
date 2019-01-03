/*---------------------------------------------------------------------+\
|
|	CDrawWin.h  --  Implementation of draw object for MS-Windows
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:

		THIS FILE FOR MS-WINDOWS ONLY

|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		react to new Size function that is declared in VDraw
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add debug mode that will display dirty-rectangle
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for switchable double-backing-store option
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement double-backing-store to support the concepts of
		background & foreground data model.
	09-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix the V_MIDDLE vertical-alignment setting
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Change names of the Select/Destroy Pen/Brush/Font functions
		to avoid a conflict with MS-Windows.
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawWin
#define _H_CDrawWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UMachine.h"
#if defined( GL_GDI )		// brackets entire file
#include "VDraw.h"
#include "IDrawWin32.h"
#include "IDrawDebug.h"
#include "CGDIPen.h"
#include "CGDIBrush.h"
#include "CGDIFont.h"
#include "THash.h"

#include <ocidl.h>
#include <olectl.h>


namespace Yogi { namespace Common {
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

typedef class CDrawWin*			CDrawWinPtr;
typedef class CDrawWin&			CDrawWinRef;
typedef const class CDrawWin&	ConstCDrawWinRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDrawWin : public VXDraw,
				implements_ IDrawWin32,
				implements_ IDrawDebug
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawWin );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IDrawWin32

	virtual
	void	SetHDC
			(
			HWND	wnd,
			HDC		hDC,
			LPRECT	pRect = NULL
			);


	virtual
	void	UpdateRect
			(
			LPRECT	pRect
			);

	//	IDrawDebug

	virtual
	void	SetDoubleBackingstore
			(
			bool	b
			);

	virtual
	void	SetDisplayDirtyRectangle
			(
			bool	b
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------



protected:
//	protected types  ----------------------------------------------------

	struct XOleImage : public XImage
	{
		XOleImage() : XImage(), nmW(0), nmH(0), pPicture( 0 ) {};

		long		nmW;
		long		nmH;
		LPPICTURE	pPicture;

	protected:
		virtual ~XOleImage() { if ( pPicture ) pPicture->Release(); };
	};

	typedef THashTable<CGDIPen::Parameters, CGDIPen>		PenList;
	typedef THashTable<CGDIBrush::Parameters, CGDIBrush>	BrushList;
	typedef THashTable<CGDIFont::Parameters, CGDIFont>		FontList;

//	protected functions  ------------------------------------------------

	bool		BufferCreate( void );
	bool		BufferDestroy( void );

	bool		PenSelect( void );
	bool		PenHaloSelect( void );
	void		PenDestroy( void );

	bool		BrushSelect( void );
	bool		BrushHaloSelect( void );
	void		BrushDestroy( void );

	bool		FontSelect( void );
	bool		FontHaloSelect( void );
	void		FontDestroy( void );

	void		ResetPenBrush( void );

	void		HimetricToPixel(SIZEL* pHM, SIZEL* pPX) const;


//	protected data  -----------------------------------------------------

	EDrawContexts		m_eLastContext;
	bool				m_bDoubleBuffer;
	bool				m_bDisplayDirtyRectangle;
	Yogi::Core::CColor	m_clrDirtyRectangle;
	Yogi::Core::CColor	m_clrNone;
	Yogi::Core::CColor	m_clrBackBuffer;
	Yogi::Core::CColor	m_clrForeBuffer;
	Yogi::Core::CColor	m_clrBothBuffer;

	HDC			m_hdc;		// active DC
	HDC			m_hdcWindow;
	HDC			m_hdcApplication;
	HDC			m_hdcBackground;
	HDC			m_hdcForeground;
	HBITMAP		m_pBMApplication;
	HBITMAP		m_pBMBackground;
	HBITMAP		m_pBMForeground;
	HANDLE		m_pOldApplication;
	HANDLE		m_pOldBackground;
	HANDLE		m_pOldForeground;
	//int			m_nCX;		// width of buffer
	//int			m_nCY;		// height of buffer

	PenList			m_oPenList;
	const CGDIPen*	m_pPen;
	BrushList		m_oBrushList;
	const CGDIBrush* m_pBrush;
	FontList		m_oFontList;
	const CGDIFont*	m_pFont;
	//HPEN		m_hPen;
	//HPEN		m_hPenHalo;
	//HBRUSH		m_hBrush;
	//HBRUSH		m_hBrushHalo;
	//HFONT		m_hFont;
	//HFONT		m_hFontHalo;
	TEXTMETRIC	m_tTextMetric;
	//HGDIOBJ		m_hPenOld;
	//HGDIOBJ		m_hBrushOld;
	//HGDIOBJ		m_hFontOld;
	RECT		m_tUpdateRect;
	HRGN		m_hClipRegion;


private:

	typedef	VXDraw	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

	//	IPluginLoadConfiguration
public:
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);


	//	IDrawTmx
public:
	virtual bool	begin( void );
	virtual bool	end( void );


	//	IDraw
public:

	virtual bool	Size( long nWidth, long nHeight );
	virtual bool	BeginContext( EDrawContexts ctx );
	virtual bool	EndContext( void );
	virtual bool	SupportsContext( void );

	virtual bool	PushCropRectangle
					(
					long	nLeft,
					long	nTop,
					long	nRight,
					long	nBottom
					);
	virtual bool	PopCropRectangle( void );

	virtual bool	RefreshRectangle( void );

	virtual bool	SetUpdateRectangle
					(
					long	nLeft,
					long	nTop,
					long	nRight,
					long	nBottom
					);
	virtual bool	GetUpdateRectangle
					(
					long*	pLeft,
					long*	pTop,
					long*	pRight,
					long*	pBottom
					);


	virtual bool	LineWidth( short nWidth );
	virtual bool	LineColor( Yogi::Core::CColorRef rColor );
	virtual bool	FillColor( Yogi::Core::CColorRef rColor );
	virtual bool	HaloColor( Yogi::Core::CColorRef rColor );

	virtual bool	FontParams( const char* sFontName, GFLOAT fFontHeight );


	// --- Geometry graphics ---

	virtual bool	Line
					(
					GFLOAT	xStart,
					GFLOAT	yStart,
					GFLOAT	xEnd,
					GFLOAT	yEnd
					);


	virtual bool	Arc
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius,
					GFLOAT	fStartAngle,
					GFLOAT	fEndAngle
					);

	virtual bool	Circle
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius
					);

	virtual bool	Ellipse
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nHeight,
					GFLOAT	nWidth
					);

	virtual bool	Pie
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius,
					GFLOAT	fStartAngle,
					GFLOAT	fEndAngle
					);


	virtual bool	EndPolyline
					(
					void
					);

	virtual bool	EndPolygon
					(
					void
					);

	virtual bool	Rectangle
					(
					GFLOAT		xPosition,
					GFLOAT		yPosition,
					GFLOAT		nWidth,
					GFLOAT		nHeight,
					CORNERSTYLE	eStyle = C_SQUARE,
					GFLOAT		nCornerSize = 0.0f
					);


	virtual bool	TextString
					(
					GFLOAT			xPosition,
					GFLOAT			yPosition,
					EAlignments		eAlign,
					EVerticalAlignments	eVertAlign,
					const char*		sString,
					long			nCount = -1
					);


	virtual bool	Video
					(
					GFLOAT			xPosition,
					GFLOAT			yPosition,
					GFLOAT			nWidth,
					GFLOAT			nHeight,
					CVariantDataRef	rSource,
					EFitments		eFitment = F_FILL,
					EAlignments		eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
					EVerticalAlignments	eVertAlign = V_MIDDLE,
					bool			bMirror = false
					);

	virtual bool	Image
					(
					GFLOAT		xPosition,
					GFLOAT		yPosition,
					GFLOAT		nWidth,
					GFLOAT		nHeight,
					const char*	sSource,
					EFitments	eFitment = F_FILL,
					EAlignments	eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
					EVerticalAlignments	eVertAlign = V_MIDDLE
					);

	virtual bool	ImagePreloaded
					(
					GFLOAT		xPosition,
					GFLOAT		yPosition,
					GFLOAT		nWidth,
					GFLOAT		nHeight,
					VImagePtr	pImage,
					EFitments	eFitment = F_FILL,
					EAlignments	eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
					EVerticalAlignments	eVertAlign = V_MIDDLE
					);

	virtual bool	ImageLoadFile
					(
					const char*	sSource,
					VImagePtr*	ppImage
					);

	virtual bool	ImageRelease
					(
					VImagePtr	pImage
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


#endif	// OS_MSWIN


#endif /* _H_CDrawWin */
