//=====================================================================+|
//
//!	@file	CColor.h
//!	@brief	Class to represent color values
//
//=====================================================================+/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
	02-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		add new function that will accept a color-long value
		that represents its data in 0x00RRGGBB
	19-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add an enumerator for the colors
		Add new HSLfromRGB function that will give back a
		hue, saturation, lumen representation of the color
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Major change to CColor so that we can handle alpha-channel
		Platform specific code should no longer be included.
	05-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		remove from Gauge namespace
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ErrorColor static function that produces a really uggggly
		color to use in those cases that we want to highlight a problem.
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ColorFromName that uses descriptor to send the name instead
		of null terminated string.
	28-Jul-2009			J.Griswold
		Removed old ColorIndex table and supporting functions.
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CColor_Root
#define _H_CColor_Root
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharDescriptor.h"
#include "TEnumerator.h"
#include "UDeclPlatform.h"

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

// deal with internal representation which stores the values as
//	0xAABBGGRR
#define	COLORDATA_V_RED		0	// Shift value
#define COLORDATA_V_GREEN	8
#define	COLORDATA_V_BLUE	16
#define	COLORDATA_V_ALPHA	24

#define	COLORDATA_M_RED		0x000000FF		// low order byte
#define	COLORDATA_M_GREEN	0x0000FF00
#define COLORDATA_M_BLUE	0x00FF0000
#define	COLORDATA_M_ALPHA	0xFF000000

#define	COLORDATA_M_RGB		(COLORDATA_M_RED | COLORDATA_M_GREEN | COLORDATA_M_BLUE)

// these values are used when dealing with an input longword
//	where the values are ordered in memory as 0x00RRGGBB
#define COLORLONG_V_ALPHA	24
#define COLORLONG_V_RED		16
#define COLORLONG_V_GREEN	8
#define	COLORLONG_V_BLUE	0
#define COLORLONG_M_ALPHA	0xFF000000
#define	COLORLONG_M_RED		0x00FF0000
#define	COLORLONG_M_GREEN	0x0000FF00
#define	COLORLONG_M_BLUE	0x000000FF



/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

// ColorData
typedef unsigned long	COLORDATA;

typedef struct RGBColorWord
{
	unsigned short	red;
	unsigned short	green;
	unsigned short	blue;
} RGBColorWord;
typedef RGBColorWord*		RGBColorWordPtr;
typedef RGBColorWord&		RGBColorWordRef;
typedef const RGBColorWord&	ConstRGBColorWordRef;



typedef struct RGBColorByte
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
} RGBColorByte;
typedef	RGBColorByte*		RGBColorBytePtr;
typedef	RGBColorByte&		RGBColorByteRef;
typedef	const RGBColorByte&	ConstRGBColorByteRef;

// this struct is used to enumerate the named colors
typedef struct ColorName
{
	const char*		sName;
	RGBColorByte	value;
} ColorName;


typedef struct RGBAColorByte
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;		// degree of translucency
} RGBAColorByte;
typedef	RGBAColorByte*		RGBAColorBytePtr;
typedef	RGBAColorByte&		RGBAColorByteRef;
typedef	const RGBAColorByte&	ConstRGBAColorByteRef;


typedef struct HSVColorFloat
{
	float	hue;
	float	saturation;
	float	value;
} HSVColorFloat;
typedef HSVColorFloat*		HSVColorFloatPtr;


typedef struct HSLColorByte
{
	unsigned char	hue;
	unsigned char	saturation;
	unsigned char	light;
	unsigned char	pad;
} HSLColorByte;
typedef HSLColorByte*	HSLColorBytePtr;


//class CColor;				// forward reference
//class CColorEnumerator;		// forward reference


typedef class CColor*		CColorPtr;
typedef class CColor&		CColorRef;
typedef const class CColor&	ConstCColorRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CColorEnumerator : public TEnumerator<const ColorName>
{
public:
			CColorEnumerator( void );
	virtual	~CColorEnumerator( void );

public:
	virtual bool				MoveNext( void );
	virtual void				Reset( void );
	virtual	const ColorName*	Current( void );

protected:
	const ColorName*	m_pBegin;
	const ColorName*	m_pEnd;
	const ColorName*	m_pCurrent;

};



class CColor
{
//	class lifecycle  ----------------------------------------------------
public:
			CColor();
			CColor( ConstCColorRef r );	// copy constructor
			CColor( unsigned int r, unsigned int g, unsigned int b );
			CColor( unsigned int r, unsigned int g, unsigned int b, unsigned int a );
			CColor( ConstRGBColorByteRef a );
			CColor( ConstRGBAColorByteRef a );
			CColor( const COLORDATA& a );
			CColor( const char* sName );
			CColor( const char* sName, unsigned int a );
	virtual	~CColor();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	/**
	 * SetRGB - assign based on Red, Green, Blue values
	 *
	 * r,g,b are assumed to be byte values
	 *
	 * this function will set the alpha to zero
	 */
	void		SetRGB
				(
				unsigned int r,		///< [in] Red	0..255
				unsigned int g,		///< [in] Green
				unsigned int b		///< [in] Blue
				);

	/**
	 * 	SetRGBA - indentify R,G,B values with the alpha value
	 *
	 * 	all values are assumed to be byte values (0..255)
	 */
	void		SetRGBA
				(
				unsigned int r,
				unsigned int g,
				unsigned int b,
				unsigned int a		///< [in] Alpha
				);

	/**
	 * 	SetAlpha - set/modify the alpha value
	 */
	void		SetAlpha
				(
				unsigned int a
				);

	/**
	 * 	SetColorLong - set the color value based on the COLORLONG convention
	 *
	 * 	value is treated as AARRGGBB - AA-Alpha, RR-Red, GG-Green, BB-Blue
	 */
	void		SetColorLong
				(
				long n		// please note this is not the same as COLORDATA
				);

	/**
	 * 	GetValue
	 */
	unsigned int	GetRed( void ) const;	///@return red component of color
	unsigned int	GetGreen( void ) const;	///@return green component of color
	unsigned int	GetBlue( void ) const;	///@return blue component of color
	unsigned int	GetAlpha( void ) const;	///@return alpha component of color

	void		SetColorByte( ConstRGBColorByteRef a );
	void		SetColorByte( ConstRGBAColorByteRef a );
	COLORDATA	GetData( void ) const;
	void		SetData( const COLORDATA& a );
	void		SetData( const char* sName );
	void		SetNonColor( bool b );
	bool		IsNonColor( void ) const;

	CColorRef	operator=( ConstCColorRef r );		// assignment
	CColorRef	operator=( const COLORDATA& r );
	CColorRef	operator=( ConstRGBColorByteRef r );
	CColorRef	operator=( ConstRGBAColorByteRef r );
	CColorRef	operator=( const char* sName );
				operator COLORDATA( void ) const;
				operator RGBColorByte( void );
				operator RGBAColorByte( void );

	bool		Equals( const CColor& r ) const;
	bool		Equals( const COLORDATA& cr ) const;
	bool		operator==( const CColor& r ) const;
	bool		operator==( const COLORDATA& r ) const;
	bool		operator!=( const CColor& r ) const;
	bool		operator!=( const COLORDATA& r ) const;

	static CColor	ColorFromName( const char* sName );
	static CColor	ColorFromName( ConstCCharDescriptorRef rName );
	static CColor	ColorFromNameAlpha( const char* sName, unsigned int alpha );
	static CColor	ColorFromNameAlpha( ConstCCharDescriptorRef rName, unsigned int alpha );
	static CColor	BackgroundColor( void );
	static CColor	ErrorColor( void );

	static void		HSVfromRGB( HSVColorFloatPtr pHSV, RGBColorBytePtr pRGB );
	static void		RGBfromHSV( RGBColorBytePtr pRGB, HSVColorFloatPtr pHSV );
	static void		HSLfromRGB( HSLColorBytePtr pHSL, RGBColorBytePtr pRGB );
	static CColorEnumerator
					GetEnumerator( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	COLORDATA	m_tColor;

	static CColor	g_tErrorColor;

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

/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
inline COLORDATA
		CColor::GetData
		(
		void
		) const
{
	return m_tColor;
}

/*---------------------------------------------------------------------+\

 * SetData -

\+---------------------------------------------------------------------*/
inline void
		CColor::SetData
		(
		const COLORDATA &a
		)
{
	m_tColor = a;
}


/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline CColorRef
		CColor::operator =
		(
		ConstCColorRef r
		)
{
	m_tColor = r.m_tColor;
	return *this;
}

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline CColorRef
		CColor::operator =
		(
		const COLORDATA&	r
		)
{
	SetData( r );
	return *this;
}



/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline CColorRef
		CColor::operator =
		(
		ConstRGBColorByteRef r
		)
{
	SetColorByte( r );
	return *this;
}

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline CColorRef
		CColor::operator=
		(
		const char*	sName
		)
{
	SetData( sName );
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator COLORDATA -

\+---------------------------------------------------------------------*/
inline 	CColor::operator COLORDATA
		(
		void
		) const
{
	return m_tColor;
}


inline
bool	CColor::operator==
		(
		const CColor&	r
		) const
{
	return Equals( r );
}


inline
bool	CColor::operator==
		(
		const COLORDATA&	r
		) const
{
	return Equals( r );
}


inline
bool	CColor::operator!=
		(
		const CColor&	r
		) const
{
	return ! Equals( r );
}

inline
bool	CColor::operator!=
		(
		const COLORDATA&	r
		) const
{
	return ! Equals( r );
}

inline
bool	operator==
		(
		const COLORDATA&	a,
		const CColor&		b
		)
{
	return b.Equals( a );
}


inline
bool	operator!=
		(
		const COLORDATA&	a,
		const CColor&		b
		)
{
	return ! b.Equals( a );
}


/*---------------------------------------------------------------------+\

 * GetRed -

\+---------------------------------------------------------------------*/
inline
unsigned int
		CColor::GetRed
		(
		void
		) const
{
	return (m_tColor & COLORDATA_M_RED) >> COLORDATA_V_RED;
}

/*---------------------------------------------------------------------+\

 * GetGreen -

\+---------------------------------------------------------------------*/
inline
unsigned int
		CColor::GetGreen
		(
		void
		) const
{
	return (m_tColor & COLORDATA_M_GREEN) >> COLORDATA_V_GREEN;
}

/*---------------------------------------------------------------------+\

 * GetBlue -

\+---------------------------------------------------------------------*/
inline
unsigned int
		CColor::GetBlue
		(
		void
		) const
{
	return (m_tColor & COLORDATA_M_BLUE) >> COLORDATA_V_BLUE;
}


/*---------------------------------------------------------------------+\

 * GetAlpha -

\+---------------------------------------------------------------------*/
inline
unsigned int
		CColor::GetAlpha
		(
		void
		) const
{
	return (m_tColor & COLORDATA_M_ALPHA) >> COLORDATA_V_ALPHA;
}




}}



#endif /* _H_CColor */
