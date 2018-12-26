/*---------------------------------------------------------------------+\
|
|	CGDIFont.h  --  brief description of what CGDIFont.h is for
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
#ifndef _H_CGDIFont
#define _H_CGDIFont
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"

#include "VGDI.h"
#include "CColor.h"
#include "CCharString.h"
#include "THash.h"

#include "UDeclSpec.h"

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
typedef class CGDIFont*			CGDIFontPtr;
typedef class CGDIFont&			CGDIFontRef;
typedef const class CGDIFont&	ConstCGDIFontRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class DECL_CLASS CGDIFont : public VGDI
{
//	class lifecycle  ----------------------------------------------------
public:
					CGDIFont();
					CGDIFont( CGDIFontRef r );	// copy constructor
					CGDIFont( ConstCCharDescriptorRef rName, unsigned long nHeight );
					CGDIFont( const char* sName, unsigned long nHeight );
	virtual			~CGDIFont();

public:
//	public types  -------------------------------------------------------

	typedef	struct Parameters
	{
		char			sName[32];
		unsigned long	nHeight;

		Parameters() : nHeight( 0 ) { sName[0] = 0; };
		Parameters( ConstCCharDescriptorRef rName, unsigned long n ) : nHeight( n ) { rName.CopyTo( sName, sizeof(sName) ); };
		Parameters( const char* s, unsigned long n ) : nHeight( n ) { ::strcpy_s( sName, sizeof(sName), s ); };
		Parameters( const Parameters& r ) : nHeight( r.nHeight ) { ::strcpy_s( sName, sizeof(sName), r.sName ); };

		Parameters&	operator = ( const Parameters& r )
		{
			::strcpy_s( sName, sizeof(sName), r.sName );
			//sName = r.sName;
			nHeight = r.nHeight;
			return *this;
		};

		bool	operator == ( const Parameters& r )
		{
			if ( 0 != ::strcmp( sName, r.sName ) )
				return false;
			if ( nHeight != r.nHeight )
				return false;
			return true;
		}

		uintmax_t	Hash( void ) const
		{
			CCharDescriptor	dName( sName );
			return dName.Hash() + nHeight;
		}
	} Parameters;

//	public functions  ---------------------------------------------------

	CGDIFontRef	operator=( CGDIFontRef r );		// assignment

	bool	SetParameters( ConstCCharDescriptorRef rName, unsigned long nHeight );
	bool	SetParameters( const char* sName, unsigned long nHeight );

	HFONT	ToHFONT( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool	FontCreate( void );
	bool	FontDelete( void );

//	protected data  -----------------------------------------------------


	HFONT		m_hFont;
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
		THashValueFromKey //<CGDIFont::Parameters>
		(
		const CGDIFont::Parameters&	key
		)
{
	uintmax_t	nHash = key.Hash();
	return nHash;
}


}}

#endif	// GL_GDI



#endif /* _H_CGDIFont */
