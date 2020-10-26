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
#include "CCharDescriptor.h"
#include "CCharString.h"
#include "CColor.h"
#include "CDateTime.h"
#include "CUnitsOfMeasure.h"
#include "TArray.h"
#include "UFloat.h"

#include "UDeclCommon.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CVariantData*       CVariantDataPtr;
typedef class CVariantData&       CVariantDataRef;
typedef const class CVariantData& ConstCVariantDataRef;
typedef const class CVariantData* ConstCVariantDataPtr;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class COMMON_CLASS CVariantData
{
    //	class lifecycle  ----------------------------------------------------
public:
    CVariantData();
    CVariantData( ConstCVariantDataRef r );  // copy constructor
    CVariantData( double f );
    CVariantData( GFLOAT f );
    CVariantData( long i );
    CVariantData( const char* s );
    CVariantData( Yogi::Core::ConstCColorRef r );
    CVariantData( bool b );
    CVariantData( Yogi::Core::ConstCDateTimeRef t );
    CVariantData( Yogi::Core::ConstCCharDescriptorRef r );
    virtual ~CVariantData();

public:
    //	public types  -------------------------------------------------------

    typedef enum V_TYPE
    {
        T_UNDEFINED = 0,

        // Base Types

        T_BOOL,
        T_INTEGER,           // long-integer
        T_FLOAT,             // look for special handling
        T_PACKED_CHARACTER,  // must be fewer than 4 bytes
        T_STRING,            // variable length byte string
        T_COLOR,             // RGBA color value
        T_DATETIME,          // seconds since 1970-01-01
        T_ARRAY              // array of Variants


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


    ConstCVariantDataRef
    operator=( ConstCVariantDataRef r );  // assignment
    ConstCVariantDataRef
    operator=( Yogi::Core::ConstCCharDescriptorRef r );
    ConstCVariantDataRef
    operator=( Yogi::Core::ConstCCharStringRef r );

    ConstCVariantDataRef
    operator=( double fData );
    ConstCVariantDataRef
    operator=( GFLOAT fData );
    ConstCVariantDataRef
    operator=( bool bData );
    ConstCVariantDataRef
    operator=( long nData );
    ConstCVariantDataRef
    operator=( const char* sData );
    ConstCVariantDataRef
    operator=( Yogi::Core::ConstCColorRef r );
    ConstCVariantDataRef
    operator=( Yogi::Core::ConstCDateTimeRef r );

    bool
    operator==( ConstCVariantDataRef r ) const;
    bool
    operator==( Yogi::Core::ConstCCharStringRef r ) const;
    bool
    operator==( Yogi::Core::ConstCCharDescriptorRef r ) const;
    bool
    operator==( double fData ) const;
    bool
    operator==( GFLOAT fData ) const;
    bool
    operator==( bool bData ) const;
    bool
    operator==( long nData ) const;
    bool
    operator==( const char* sData ) const;
    bool
    operator==( Yogi::Core::ConstCColorRef r ) const;
    bool
    operator==( Yogi::Core::ConstCDateTimeRef r ) const;

    bool
    operator!=( ConstCVariantDataRef r ) const;
    bool
    operator!=( Yogi::Core::ConstCCharStringRef r ) const;
    bool
    operator!=( Yogi::Core::ConstCCharDescriptorRef r ) const;
    bool
    operator!=( double fData ) const;
    bool
    operator!=( GFLOAT fData ) const;
    bool
    operator!=( bool bData ) const;
    bool
    operator!=( long nData ) const;
    bool
    operator!=( const char* sData ) const;
    bool
    operator!=( Yogi::Core::ConstCColorRef r ) const;
    bool
    operator!=( Yogi::Core::ConstCDateTimeRef r ) const;

    bool
    operator<( ConstCVariantDataRef r ) const;
    bool
    operator<( Yogi::Core::ConstCCharStringRef r ) const;
    bool
    operator<( Yogi::Core::ConstCCharDescriptorRef r ) const;
    bool
    operator<( double fData ) const;
    bool
    operator<( GFLOAT fdata ) const;
    bool
    operator<( bool bData ) const;
    bool
    operator<( long nData ) const;
    bool
    operator<( Yogi::Core::ConstCColorRef r ) const;
    bool
    operator<( Yogi::Core::ConstCDateTimeRef r ) const;


    operator Yogi::Core::CCharDescriptor( void ) const;
    // //operator const CCharDescriptor* ( void );
    // //operator CCharDescriptor* ( void ) const;
    // //operator Yogi::Core::CCharDescriptorRef ( void );
    operator bool( void ) const;
    operator long( void ) const;
    operator GFLOAT( void ) const;
    // operator double( void ) const;
    operator Yogi::Core::CCharString( void ) const;
    // //operator const CCharString* ( void );
    // operator const char*( void ) const;
    operator Yogi::Core::CColor( void ) const;
    operator Yogi::Core::CDateTime( void ) const;

    bool
    GetValueBool( void ) const;
    long
    GetValueInteger( void ) const;
    unsigned long
    GetValueUnsignedInteger( void ) const;
    GFLOAT
    GetValueFloat( void ) const;
    double
    GetValueDouble( void ) const;
    GFLOAT
    GetValueFloatAsUnits( int nUnits ) const;
    const char*
    GetValueString( void ) const;
    Yogi::Core::CCharString
    GetValueCCharString( void ) const;
    Yogi::Core::CCharDescriptor
    GetValueCCharDescriptor( void ) const;
    Yogi::Core::CColor
    GetValueColor( void ) const;
    Yogi::Core::CDateTime
    GetValueDateTime( void ) const;

    bool
    EqualsVariant( ConstCVariantDataRef vData ) const;
    bool
    EqualsCCharString( Yogi::Core::ConstCCharStringRef r ) const;
    bool
    EqualsCCharDescriptor( Yogi::Core::ConstCCharDescriptorRef r ) const;
    bool
    EqualsDouble( double fData ) const;
    bool
    EqualsFloat( GFLOAT fData ) const;
    bool
    EqualsBool( bool bData ) const;
    bool
    EqualsInteger( long nData ) const;
    bool
    EqualsString( const char* sData ) const;
    bool
    EqualsColor( Yogi::Core::ConstCColorRef r ) const;
    bool
    EqualsDateTime( Yogi::Core::ConstCDateTimeRef r ) const;

    bool
    LessThanVariant( ConstCVariantDataRef r ) const;
    bool
    LessThanCCharString( Yogi::Core::ConstCCharStringRef r ) const;
    bool
    LessThanCCharDescriptor( Yogi::Core::ConstCCharDescriptorRef r ) const;
    bool
    LessThanDouble( double fData ) const;
    bool
    LessThanFloat( GFLOAT fData ) const;
    bool
    LessThanBool( bool bData ) const;
    bool
    LessThanInteger( long nData ) const;
    bool
    LessThanString( const char* sData ) const;
    bool
    LessThanColor( Yogi::Core::ConstCColorRef r ) const;
    bool
    LessThanDateTime( Yogi::Core::ConstCDateTimeRef r ) const;

    bool
    LoadCopy( ConstCVariantDataRef r );  // assignment
    bool
    LoadCharString( const char* s );
    bool
    LoadCharDescriptor( const char* s, size_t n );

    // array operations
    size_t
    ItemCount( void ) const;
    CVariantDataRef
    Item( const index_t n );
    ConstCVariantDataRef
    Item( const index_t n ) const;
    bool
    LoadItem( ConstCVariantDataRef r, const index_t n );

    ConstCVariantDataRef
    operator[]( const index_t n ) const;
    CVariantDataRef
    operator[]( const index_t n );


    V_TYPE
    GetType( void ) const;
    V_METATYPE
    GetMetaType( void ) const;
    int
    GetUnits( void ) const;
    void
    SetUnits( int nUnits );

    void
    Clear( void );  // clear all values


protected:
    //	protected types  ----------------------------------------------------

    typedef Yogi::Core::TArray<CVariantData> TVariantArray;

    //	protected functions  ------------------------------------------------

    void
    PrepareLoad( V_TYPE t );

    //	protected data  -----------------------------------------------------

    V_TYPE          m_eType;
    CUnitsOfMeasure m_tUnits;
    //V_UNITS	m_eUnits;
    union  // anonymous
    {
        bool                       m_bData;
        long                       m_nData;
        GXFLOAT                    m_fData;
        char                       m_cData[sizeof( time_t )];
        Yogi::Core::CCharStringPtr m_pString;
        Yogi::Core::COLORDATA      m_tColor;
        time_t                     m_tTime;
        TVariantArray*             m_pArray;
    };


    static Yogi::Core::CCharDescriptor g_tCharDescriptor;

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


inline CVariantDataRef
CVariantData::operator[]( const index_t n )
{
    return Item( n );
}

inline ConstCVariantDataRef
CVariantData::operator[]( const index_t n ) const
{
    return Item( n );
}


/*---------------------------------------------------------------------+\

 * operator == - equality operator

\+---------------------------------------------------------------------*/
inline bool
CVariantData::operator==( ConstCVariantDataRef r ) const
{
    return EqualsVariant( r );
}


inline bool
CVariantData::operator==( Yogi::Core::ConstCCharDescriptorRef r ) const
{
    return EqualsCCharDescriptor( r );
}


inline bool
CVariantData::operator==( Yogi::Core::ConstCCharStringRef r ) const
{
    return EqualsCCharString( r );
}


// inline
// bool	operator==
// 		(
// 		Yogi::Core::ConstCCharDescriptorRef	a,
// 		ConstCVariantDataRef	b
// 		)
// {
// 	return b.EqualsCCharDescriptor( a );
// }


inline bool
CVariantData::operator==( double fData ) const
{
    return EqualsDouble( fData );
}


inline bool
operator==( double a, ConstCVariantDataRef b )
{
    return b.EqualsDouble( a );
}


inline bool
CVariantData::operator==( GFLOAT fData ) const
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


inline bool
CVariantData::operator==( bool bData ) const
{
    return EqualsBool( bData );
}


inline bool
operator==( bool a, ConstCVariantDataRef b )
{
    return b.EqualsBool( a );
}


inline bool
CVariantData::operator==( long nData ) const
{
    return EqualsInteger( nData );
}


inline bool
operator==( long a, ConstCVariantDataRef b )
{
    return b.EqualsInteger( a );
}


inline bool
CVariantData::operator==( const char* sData ) const
{
    return EqualsString( sData );
}


inline bool
operator==( const char* a, ConstCVariantDataRef b )
{
    return b.EqualsString( a );
}


inline bool
CVariantData::operator==( Yogi::Core::ConstCColorRef r ) const
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


inline bool
CVariantData::operator==( Yogi::Core::ConstCDateTimeRef t ) const
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
inline bool
CVariantData::operator!=( ConstCVariantDataRef r ) const
{
    return ! EqualsVariant( r );
}


inline bool
CVariantData::operator!=( Yogi::Core::ConstCCharDescriptorRef r ) const
{
    return ! EqualsCCharDescriptor( r );
}


inline bool
CVariantData::operator!=( Yogi::Core::ConstCCharStringRef r ) const
{
    return ! EqualsCCharString( r );
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


inline bool
CVariantData::operator!=( double d ) const
{
    return ! EqualsDouble( d );
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


inline bool
CVariantData::operator!=( GFLOAT f ) const
{
    return ! EqualsFloat( f );
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


inline bool
CVariantData::operator!=( bool b ) const
{
    return ! EqualsBool( b );
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


inline bool
CVariantData::operator!=( long n ) const
{
    return ! EqualsInteger( n );
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


inline bool
CVariantData::operator!=( const char* s ) const
{
    return ! EqualsString( s );
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


inline bool
CVariantData::operator!=( Yogi::Core::ConstCColorRef c ) const
{
    return ! EqualsColor( c );
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


inline bool
CVariantData::operator!=( Yogi::Core::ConstCDateTimeRef t ) const
{
    return ! EqualsDateTime( t );
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

inline bool
CVariantData::operator<( ConstCVariantDataRef r ) const
{
    return LessThanVariant( r );
}


inline bool
CVariantData::operator<( Yogi::Core::ConstCCharDescriptorRef r ) const
{
    return LessThanCCharDescriptor( r );
}

inline bool
CVariantData::operator<( Yogi::Core::ConstCCharStringRef r ) const
{
    return LessThanCCharString( r );
}

inline bool
CVariantData::operator<( double d ) const
{
    return LessThanDouble( d );
}

inline bool
CVariantData::operator<( GFLOAT f ) const
{
    return LessThanDouble( f );
}

inline bool
CVariantData::operator<( bool b ) const
{
    return LessThanBool( b );
}

inline bool
CVariantData::operator<( long n ) const
{
    return LessThanInteger( n );
}


inline bool
CVariantData::operator<( Yogi::Core::ConstCColorRef r ) const
{
    return LessThanColor( r );
}

inline bool
CVariantData::operator<( Yogi::Core::ConstCDateTimeRef r ) const
{
    return LessThanDateTime( r );
}


// inline
// CVariantData::operator unsigned long
// 		(
// 		void
// 		)
// {
// 	return GetValueUnsignedInteger();
// }


// inline
// CVariantData::operator const char *
// 		(
// 		void
// 		) const
// {
// 	return GetValueString();
// }


// inline
// unsigned long
// 		CVariantData::GetValueUnsignedInteger
// 		(
// 		void
// 		) const
// {
// 	return static_cast<unsigned long>(GetValueInteger());
// }


}}  // namespace Yogi::Common


#endif /* _H_CVariantData */
