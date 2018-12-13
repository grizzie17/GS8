/*---------------------------------------------------------------------+\
|
|	CGaugeText.h  --  brief description of what CGaugeText.h is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetFontName that uses descriptor to send the name instead
		of null terminated string.
	02-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CGaugeText
#define _H_CGaugeText
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"

#include "TArray.h"
#include "CGaugeString.h"
#include "CPoint.h"
#include "CCharDescriptor.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CGaugeText*		CGaugeTextPtr;
typedef class CGaugeText&		CGaugeTextRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CGaugeText : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					CGaugeText();
					CGaugeText( CGaugeTextRef r );	// copy constructor
	virtual			~CGaugeText();

public:
//	public types  -------------------------------------------------------


//	public functions  ---------------------------------------------------

	CPointValuePtr	Point( void );
	void			SetMaxLength( long n );
	void			SetFontName( const char* s );
	void			SetFontName( Yogi::Core::ConstCCharDescriptorRef r );
	void			SetFontHeight( float f );
	CResultValuePtr	FontHeight( void );
	void			SetAlign( Yogi::Common::VDraw::EAlignments e );
	void			SetVertAlign( Yogi::Common::VDraw::EVerticalAlignments e );
	void			AddString( CGaugeStringPtr pString );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CPointValuePtr			m_pPoint;		// origin of text string
	long					m_nMaxLength;	// number of characters to display
	Yogi::Core::CCharString	m_tFontName;	// name of font
	CResultValue			m_tFontHeight;
	Yogi::Common::VDraw::EAlignments	m_eAlign;
	Yogi::Common::VDraw::EVerticalAlignments
							m_eVertAlign;
	Yogi::Core::TArray<CGaugeStringPtr>
							m_aStrings;

private:
//	private types  ------------------------------------------------------

	typedef VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VGraphic-1
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );

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


#endif /* _H_CGaugeText */
