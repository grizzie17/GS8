/*---------------------------------------------------------------------+\
|
|	CDrawOpenGL.h  --  brief description of what CDrawOpenGL.h is for
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
	25-Jun-2013			J.Griswold
		added support for fontconfig that allows the system to find
		fonts instead of being hardcoded paths.
	08-Dec-2009			C. Cason		(Reviewed by: R.Hosea)
		Eliminated dsp_idx references
		Added color lookup table and glIndex support
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawOpenGL_Common
#define _H_CDrawOpenGL_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include "VDraw.h"

#include "UMachine.h"
#if defined( GL_OPENGL )	// brackets entire file

//#include "fonts.h"
#include "TDictionaryIndexed.h"
#include "CVariantData.h"

#	include <GL/gl.h>
#	include <GL/glu.h>

#	define	TDrawOpenGL	CDrawOpenGLBase
#	include "TDrawOpenGL.h"

#	include <ft2build.h>
#	include <FTGL/ftgl.h>
#	include <fontconfig/fontconfig.h>



namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


#define NEAR_Z        1000.0
#define FAR_Z        -1000.0


//These defines are carried over from the SM501 OpenGL implementation
#define Z_LEVEL_1 3
#define NO_OPAQUE      0
#define LITTLE_OPAQUE  1
#define MORE_OPAQUE    2
#define FULL_OPAQUE    3


//#define	FONT_GLUT	1
#define FONT_FTGL	1



/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CDrawOpenGL*			CDrawOpenGLPtr;
typedef class CDrawOpenGL&			CDrawOpenGLRef;
typedef const class CDrawOpenGL&	ConstCDrawOpenGLRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

//typedef struct
//{
//  CCharString FontName;
//  CCharString FontType;
//  GFLOAT FontHeight;
//  BitmapFontRec* FontRec;
//
//}FontData;

class CDrawOpenGL : public TDrawOpenGL
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawOpenGL );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	void	FontInitialize( void );
	//bool	ActivateStyles( void );



//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef TDrawOpenGL	inherited;

//	private functions  --------------------------------------------------

	void	ResetPenBrush(void);
	void	DestroyFont(void);
	bool	SelectFont(void);
	bool	FindFontByName( char* sFile, size_t nFile, const char* sName );
	//FontData*	BestFont(void);
	long	LocateEntry(const char* sName) const;
	//bool 	glIndex(int color, int alpha);

//	private data  -------------------------------------------------------

//        FontData*   m_hFont;
//        FontData*   m_hFontOld;
//        FontData*   m_hFontCur;
	FcConfig*		m_pFontConfig;
	//TDictionaryIndexed< CCharString, FontData*>	m_pFonts;

#ifdef FONT_FTGL
	FTGLPixmapFont*	m_pxFont;
	FTGLPixmapFont*	m_pxFontOld;
	FTGLPixmapFont*	m_pxFontCur;
#endif



//============================== Overrides ==============================

	//	VDrawTmx
public:
	virtual bool	begin( void );
	virtual bool	end( void );


	//	VDraw
public:



/*
	virtual bool	BeginContext( EDrawContexts ctx );
	virtual bool	EndContext( void );
	virtual bool	SupportsContext( void );

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
	virtual bool	LineColor( CColorRef rColor );
	virtual bool	FillColor( CColorRef rColor );
*/

	virtual bool	FontParams( const char* sFontName, GFLOAT fFontHeight );

	// --- Geometry graphics ---

	virtual bool	BeginPolygon
					(
					void
					);

	virtual bool	EndPolygon
					(
					void
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



#endif	// GL_OPENGL


#endif /* _H_CDrawOpenGL */
