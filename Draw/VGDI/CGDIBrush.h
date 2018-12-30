/*---------------------------------------------------------------------+\
|
|	CGDIBrush.h  --  brief description of what CGDIBrush.h is for
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
#ifndef _H_CGDIBrush
#define _H_CGDIBrush
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "VGDI.h"
#include "CColor.h"
#include "THash.h"

#include "UDeclCommon.h"

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
typedef class CGDIBrush*			CGDIBrushPtr;
typedef class CGDIBrush&			CGDIBrushRef;
typedef const class CGDIBrush&	ConstCGDIBrushRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class DECL_CLASS CGDIBrush : public VGDI
{
//	class lifecycle  ----------------------------------------------------
public:
					CGDIBrush();
					CGDIBrush( CGDIBrushRef r );	// copy constructor
					CGDIBrush( ConstCColorRef rColor );
	virtual			~CGDIBrush();

public:
//	public types  -------------------------------------------------------

	typedef	struct Parameters
	{
		CColor	oColor;

		Parameters() : oColor() {};
		Parameters( const CColor& c ) : oColor( c ) {};
		Parameters( const Parameters& r ) : oColor( r.oColor ) {};

		Parameters&	operator = ( const Parameters& r )
		{
			oColor = r.oColor;
			return *this;
		};

		bool	operator == ( const Parameters& r )
		{
			if ( oColor != r.oColor )
				return false;
			return true;
		}

		uintmax_t	Hash( void ) const
		{
			if ( oColor.IsNonColor() )
			{
				return ~(uintmax_t)0;
			}
			else
			{
				return oColor;
			}
		}
	} Parameters;

//	public functions  ---------------------------------------------------

	CGDIBrushRef	operator=( CGDIBrushRef r );		// assignment

	bool	SetParameters( ConstCColorRef oColor );

	HBRUSH	ToHBRUSH( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool	BrushCreate( void );
	bool	BrushDelete( void );

//	protected data  -----------------------------------------------------


	HBRUSH		m_hBrush;
	Parameters	m_tParams;

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
		THashValueFromKey //<CGDIBrush::Parameters>
		(
		const CGDIBrush::Parameters&	key
		)
{
	uintmax_t	nHash = key.Hash();
	return nHash;
}


}}

#endif	// GL_GDI



#endif /* _H_CGDIBrush */
