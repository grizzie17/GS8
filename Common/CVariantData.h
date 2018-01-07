/*---------------------------------------------------------------------+\
|
|	CVariantData.h  --  Implements Typed Variant Data
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	01-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Change the GetValueXxxxxx functions to be 'const'
	27-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Correct the handling of CColor
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support to retrieve a float value converted to specified units.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add date/time support
	21-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Fix time_t references to be compatible with GCC
	20-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Start adding support for date/time info
	02-Sep-2009			R.Hosea			(Reviewed by: M.Rose)
		Mods for gcc compatibility
	29-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		React to class hierarchy change for CCharString/CCharDescriptor
	27-Aug-2009			J.Griswold
		Fix the implmentation of the Equality and Inequality functionality
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CVariantData
#define _H_CVariantData
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharString.h"
#include "CColor.h"
#include "CDateTime.h"
#include "CUnitsOfMeasure.h"
#include "UFloat.h"
#include "TArray.h"

#include "NamespaceCommon.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMON_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CVariantData*			CVariantDataPtr;
typedef class CVariantData&			CVariantDataRef;
typedef const class CVariantData&	ConstCVariantDataRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CVariantData
{
//	class lifecycle  ----------------------------------------------------
public:
					CVariantData();
					CVariantData( ConstCVariantDataRef r );	// copy constructor
					CVariantData( double f );
					CVariantData( GFLOAT f );
					CVariantData( long i );
					CVariantData( const char* s );
					CVariantData( ConstCColorRef r );
					CVariantData( bool b );
					CVariantData( ConstCDateTimeRef t );
					CVariantData( ConstCCharDescriptorRef r );
	virtual			~CVariantData();

public:
//	public types  -------------------------------------------------------

	typedef enum V_TYPE
	{
		T_UNDEFINED = 0,

		// Base Types

		T_BOOL,
		T_INTEGER,				// long-integer
		T_FLOAT,				// look for special handling
		T_PACKED_CHARACTER,		// must be fewer than 4 bytes
		T_STRING,				// variable length byte string
		T_COLOR,				// RGBA color value
		T_DATETIME,				// seconds since 1970-01-01
		T_ARRAY					// array of Variants


	} V_TYPE;

	// metatype is derrived from the V_TYPE
	typedef enum V_METATYPE
	{
		MT_UNDEFINED = 0,
		MT_LOGICAL,
		MT_NUMERIC,
		MT_CHARACTER,
		MT_COLOR,
		MT_DATETIME,
		MT_ARRAY
	} V_METATYPE;


//	public functions  ---------------------------------------------------


	CVariantDataRef	operator=( ConstCVariantDataRef r );		// assignment
	CVariantDataRef	operator=( ConstCCharDescriptorRef r );

	CVariantDataRef operator=( const double fData );
	CVariantDataRef operator=( const GFLOAT fData );
	CVariantDataRef	operator=( const bool bData );
	CVariantDataRef	operator=( const long nData );
	CVariantDataRef operator=( const char* sData );
	CVariantDataRef	operator=( ConstCColorRef r );
	CVariantDataRef	operator=( ConstCDateTimeRef r );

	bool			operator==( ConstCVariantDataRef r ) const;
	//bool			operator==( ConstCCharStringRef r );
	bool			operator==( ConstCCharDescriptorRef r ) const;
	bool			operator==( double fData ) const;
	bool			operator==( GFLOAT fData ) const;
	bool			operator==( bool bData ) const;
	bool			operator==( long nData ) const;
	bool			operator==( const char* sData ) const;
	bool			operator==( ConstCColorRef r ) const;
	bool			operator==( ConstCDateTimeRef r ) const;

	bool			operator!=( ConstCVariantDataRef r ) const;
	//bool			operator!=( ConstCCharStringRef r );
	bool			operator!=( ConstCCharDescriptorRef r ) const;
	bool			operator!=( double fData ) const;
	bool			operator!=( GFLOAT fData ) const;
	bool			operator!=( bool bData ) const;
	bool			operator!=( long nData ) const;
	bool			operator!=( const char* sData ) const;
	bool			operator!=( ConstCColorRef r ) const;
	bool			operator!=( ConstCDateTimeRef r ) const;

	bool			operator< ( ConstCVariantDataRef r ) const;
	bool			operator< ( ConstCCharDescriptorRef r ) const;
	bool			operator< ( double fData ) const;
	bool			operator< ( GFLOAT fdata ) const;
	bool			operator< ( bool bData ) const;
	bool			operator< ( long nData ) const;
	bool			operator< ( ConstCColorRef r ) const;
	bool			operator< ( ConstCDateTimeRef r ) const;


	operator CCharDescriptor ( void );
	operator const CCharDescriptor* ( void );
	operator CCharDescriptor* ( void ) const;
	operator CCharDescriptorRef ( void );
	operator bool( void );
	operator long( void );
	operator unsigned long( void );
	operator GFLOAT( void );
	operator double( void );
	operator CCharString( void );
	//operator const CCharString* ( void );
	//operator const CCharString( void );
	operator const char*( void );
	operator CColor( void );
	operator CDateTime( void );

	bool		GetValueBool( void ) const;
	long		GetValueInteger( void ) const;
	unsigned long
				GetValueUnsignedInteger( void ) const;
	GFLOAT		GetValueFloat( void ) const;
	double		GetValueDouble( void ) const;
	GFLOAT		GetValueFloatAsUnits( int nUnits ) const;
	const char*	GetValueString( void ) const;
	CCharString	GetValueCCharString( void ) const;
	CColor		GetValueColor( void ) const;
	CDateTime	GetValueDateTime( void ) const;

	bool		EqualsVariant( ConstCVariantDataRef vData ) const;
	bool		EqualsCCharString( ConstCCharDescriptorRef r ) const;
	bool		EqualsDouble( double fData ) const;
	bool		EqualsFloat( GFLOAT fData ) const;
	bool		EqualsBool( bool bData ) const;
	bool		EqualsInteger( long nData ) const;
	bool		EqualsString( const char* sData ) const;
	bool		EqualsColor( ConstCColorRef r ) const;
	bool		EqualsDateTime( ConstCDateTimeRef r ) const;

	bool		LessThanVariant( ConstCVariantDataRef r ) const;
	bool		LessThanCCharString( ConstCCharDescriptorRef r ) const;
	bool		LessThanDouble( double fData ) const;
	bool		LessThanFloat( GFLOAT fData ) const;
	bool		LessThanBool( bool bData ) const;
	bool		LessThanInteger( long nData ) const;
	bool		LessThanString( const char* sData ) const;
	bool		LessThanColor( ConstCColorRef r ) const;
	bool		LessThanDateTime( ConstCDateTimeRef r ) const;

	bool		LoadCopy( ConstCVariantDataRef r );		// assignment
	bool		LoadCharString( const char* s );
	bool		LoadCharDescriptor( const char* s, size_t n );

	// array operations
	size_t			ItemCount( void ) const;
	CVariantDataRef	Item( const index_t n );
	ConstCVariantDataRef	Item( const index_t n ) const;
	bool			LoadItem( ConstCVariantDataRef r, const index_t n );

	ConstCVariantDataRef	operator[]( const index_t n ) const;
	CVariantDataRef			operator[]( const index_t n );


	V_TYPE		GetType( void );
	V_METATYPE	GetMetaType( void );
	int			GetUnits( void );
	void		SetUnits( int nUnits );

	void		Clear( void );		// clear all values


protected:
//	protected types  ----------------------------------------------------

	typedef TArray<CVariantData>	TVariantArray;

//	protected functions  ------------------------------------------------

	void		PrepareLoad( V_TYPE t );

//	protected data  -----------------------------------------------------

	V_TYPE	m_eType;
	CUnitsOfMeasure	m_tUnits;
	//V_UNITS	m_eUnits;
	union	// anonymous
	{
		bool			m_bData;
		long			m_nData;
		GXFLOAT			m_fData;
		char			m_cData[sizeof(time_t)];
		CCharStringPtr	m_pString;
		COLORDATA		m_tColor;
		time_t			m_tTime;
		TVariantArray*	m_pArray;
	};


	static CCharDescriptor	g_tCharDescriptor;

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


inline
CVariantDataRef
		CVariantData::operator[]
		(
		const index_t	n
		)
{
	return Item( n );
}

inline
ConstCVariantDataRef
		CVariantData::operator[]
		(
		const index_t	n
		) const
{
	return Item( n );
}


/*---------------------------------------------------------------------+\

 * operator == - equality operator

\+---------------------------------------------------------------------*/
inline
bool	CVariantData::operator==
		(
		ConstCVariantDataRef r
		) const
{
	return EqualsVariant( r );
}


inline
bool	CVariantData::operator==
		(
		ConstCCharDescriptorRef r
		) const
{
	return EqualsCCharString( r );
}


//inline
//bool	operator==
//		(
//		ConstCCharDescriptorRef	a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsCCharString( a );
//}



inline
bool	CVariantData::operator==
		(
		double fData
		) const
{
	return EqualsDouble( fData );
}


//inline
//bool	operator==
//		(
//		double					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsDouble( a );
//}



inline
bool	CVariantData::operator==
		(
		GFLOAT fData
		) const
{
	return EqualsFloat( fData );
}


//inline
//bool	operator==
//		(
//		GFLOAT					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsFloat( a );
//}



inline
bool	CVariantData::operator==
		(
		bool bData
		) const
{
	return EqualsBool( bData );
}


//inline
//bool	operator==
//		(
//		bool					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsBool( a );
//}




inline
bool	CVariantData::operator==
		(
		long nData
		) const
{
	return EqualsInteger( nData );
}


//inline
//bool	operator==
//		(
//		long					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsInteger( a );
//}




inline
bool	CVariantData::operator==
		(
		const char* sData
		) const
{
	return EqualsString( sData );
}


//inline
//bool	operator==
//		(
//		const char*				a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsString( a );
//}




inline
bool	CVariantData::operator==
		(
		ConstCColorRef r
		) const
{
	return EqualsColor( r );
}


//inline
//bool	operator==
//		(
//		ConstCColorRef			a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsColor( a );
//}




inline
bool	CVariantData::operator==
		(
		ConstCDateTimeRef	t
		) const
{
	return EqualsDateTime( t );
}



//inline
//bool	operator==
//		(
//		ConstCDateTimeRef		a,
//		ConstCVariantDataRef	b
//		)
//{
//	return b.EqualsDateTime( a );
//}




/*---------------------------------------------------------------------+\

 * operator != - inequality operator

\+---------------------------------------------------------------------*/
inline
bool	CVariantData::operator !=
		(
		ConstCVariantDataRef r
		) const
{
	return !EqualsVariant( r );
}


inline
bool	CVariantData::operator!=
		(
		ConstCCharDescriptorRef r
		) const
{
	return !EqualsCCharString( r );
}


//inline
//bool	operator!=
//		(
//		ConstCCharDescriptorRef	a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsCCharString( a );
//}


inline
bool	CVariantData::operator !=
		(
		double d
		) const
{
	return !EqualsDouble( d );
}


//inline
//bool	operator!=
//		(
//		double					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsDouble( a );
//}



inline
bool	CVariantData::operator !=
		(
		GFLOAT	f
		) const
{
	return !EqualsFloat( f );
}

//inline
//bool	operator!=
//		(
//		GFLOAT					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsFloat( a );
//}



inline
bool	CVariantData::operator !=
		(
		bool	b
		) const
{
	return !EqualsBool( b );
}

//inline
//bool	operator!=
//		(
//		bool					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsBool( a );
//}




inline
bool	CVariantData::operator !=
		(
		long	n
		) const
{
	return !EqualsInteger( n );
}

//inline
//bool	operator!=
//		(
//		long					a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsInteger( a );
//}




inline
bool	CVariantData::operator !=
		(
		const char* s
		) const
{
	return !EqualsString( s );
}

//inline
//bool	operator!=
//		(
//		const char*				a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsString( a );
//}




inline
bool	CVariantData::operator !=
		(
		ConstCColorRef c
		) const
{
	return !EqualsColor( c );
}

//inline
//bool	operator!=
//		(
//		ConstCColorRef			a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsColor( a );
//}




inline
bool	CVariantData::operator!=
		(
		ConstCDateTimeRef	t
		) const
{
	return !EqualsDateTime( t );
}


//inline
//bool	operator!=
//		(
//		ConstCDateTimeRef		a,
//		ConstCVariantDataRef	b
//		)
//{
//	return ! b.EqualsDateTime( a );
//}

inline
bool	CVariantData::operator <
		(
		ConstCVariantDataRef r
		) const
{
	return LessThanVariant( r );
}


inline
bool	CVariantData::operator <
		(
		ConstCCharDescriptorRef r
		) const
{
	return LessThanCCharString( r );
}

inline
bool	CVariantData::operator <
		(
		double	d
		) const
{
	return LessThanDouble( d );
}

inline
bool	CVariantData::operator <
		(
		GFLOAT	f
		) const
{
	return LessThanDouble( f );
}

inline
bool	CVariantData::operator <
		(
		bool	b
		) const
{
	return LessThanBool( b );
}

inline
bool	CVariantData::operator <
		(
		long	n
		) const
{
	return LessThanInteger( n );
}


inline
bool	CVariantData::operator <
		(
		ConstCColorRef	r
		) const
{
	return LessThanColor( r );
}

inline
bool	CVariantData::operator <
		(
		ConstCDateTimeRef	r
		) const
{
	return LessThanDateTime( r );
}


inline
CVariantData::operator unsigned long
		(
		void
		)
{
	return GetValueUnsignedInteger();
}


inline
unsigned long
		CVariantData::GetValueUnsignedInteger
		(
		void
		) const
{
	return static_cast<unsigned long>(GetValueInteger());
}



NAMESPACE_COMMON_END




#endif /* _H_CVariantData */
