/*---------------------------------------------------------------------+\
|
|	CGDIPen.h  --  brief description of what CGDIPen.h is for
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
	29-Jun-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CGDIPen
#define _H_CGDIPen
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "VGDI.h"
#include "CColor.h"
#include "THash.h"

#if defined( GL_GDI )

namespace Yogi { namespace Common {
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
typedef class CGDIPen*			CGDIPenPtr;
typedef class CGDIPen&			CGDIPenRef;
typedef const class CGDIPen&	ConstCGDIPenRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class CGDIPen : public VGDI
{
//	class lifecycle  ----------------------------------------------------
public:
					CGDIPen();
					CGDIPen( CGDIPenRef r );	// copy constructor
					CGDIPen( ConstCColorRef rColor, long nWidth );
	virtual			~CGDIPen();

public:
//	public types  -------------------------------------------------------

	typedef	struct Parameters
	{
		CColor	oColor;
		long	nWidth;

		Parameters() : oColor(), nWidth(0) {};
		Parameters( const CColor& c, long n ) : oColor( c ), nWidth( n ) {};
		Parameters( const Parameters& r ) : oColor( r.oColor ), nWidth( r.nWidth ) {};

		Parameters&	operator = ( const Parameters& r )
		{
			oColor = r.oColor;
			nWidth = r.nWidth;
			return *this;
		};

		bool	operator == ( const Parameters& r )
		{
			if ( oColor != r.oColor )
				return false;
			if ( nWidth != r.nWidth )
				return false;
			return true;
		}

		uintmax_t	Hash( void ) const
		{
			if ( oColor.IsNonColor() )
			{
				return 0x00FFFFULL | ((uintmax_t)nWidth << 16);
			}
			else
			{
				unsigned	r = oColor.GetRed();
				unsigned	g = oColor.GetGreen();
				unsigned	b = oColor.GetBlue();

				return (r >> 3)
					| ((g >> 3) << 5)
					| ((b >> 3) << 10)
					| (nWidth << 16);
			}
		}
	} Parameters;

//	public functions  ---------------------------------------------------

	CGDIPenRef	operator=( CGDIPenRef r );		// assignment

	bool	SetParameters( ConstCColorRef oColor, long nWidth );

	HPEN	ToHPEN( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool	PenCreate( void );
	bool	PenDelete( void );

//	protected data  -----------------------------------------------------


	HPEN		m_hPen;
	bool		m_bStock;
	Parameters	m_tParams;
	//CColor	m_oColor;
	//long	m_nWidth;

private:
//	private types  ------------------------------------------------------

	typedef	VGDI	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

// VGDI
public:

	virtual
	bool	Select( HDC h );

	virtual
	bool	Deselect( void );


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

//template<>
inline
uintmax_t
		THashValueFromKey //<CGDIPen::Parameters>
		(
		const CGDIPen::Parameters&	key
		)
{
	uintmax_t	nHash = key.Hash();
	return nHash;
}


}}

#endif	// GL_GDI



#endif /* _H_CGDIPen */
