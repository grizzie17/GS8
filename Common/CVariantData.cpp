/*---------------------------------------------------------------------+\
|
|	CVariantData.cpp  --  Class to contain variable data
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
	01-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Change the GetValueXxxxxx functions to be 'const'
	21-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Lots of 'adjustments' in the way we handle string data,
		especially with regard to comparison with no string
		data types.
	13-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a compiler warning regarding floating point conversion.
		Also fixed a potential crash.
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a memory access problem
	27-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Correct the handling of CColor
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Assigning dates or strings was wiping out the units
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix the compare of two "bool" values.
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support to retrieve a float value converted to specified units.
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Rework GetValueCCharString to support some level of conversion
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add date/time support
	21-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Fix time_t references to be compatible with GCC
	20-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Start adding support for date/time info
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	03-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Fix for clearing the data when we are dealing with assignment
		of string vs non-string data.
	02-Sep-2009			R.Hosea			(Reviewed by: M.Rose)
		Mods for gcc compatibility
	29-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		React to class hierarchy change for CCharString/CCharDescriptor
	27-Aug-2009			J.Griswold
		Fix the implementation of the Equality and Inequality functionality
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "CVariantData.h"

NAMESPACE_COMMON_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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
NAMESPACE_ROOT_PREFIX CCharDescriptor	CVariantData::g_tCharDescriptor;
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CVariantData - constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		void
		)
		: m_eType( T_UNDEFINED ),
		m_tUnits( 0 ),
		m_pString( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CVariantData - copy constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		ConstCVariantDataRef	r
		)
		: m_eType( T_UNDEFINED ),
		m_tUnits( 0 ),
		m_pString( 0 )
{
	LoadCopy( r );
}


/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		const char *s
		)
		: m_eType( T_UNDEFINED ),
		m_tUnits( 0 ),
		m_pString( 0 )
{
	LoadCharString( s );
}


/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		GFLOAT	f
		)
		: m_eType( T_FLOAT ),
		m_tUnits( 0 ),
		m_fData( GXFLOAT_CAST(f) )
{
}

/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		double	f
		)
		: m_eType( T_FLOAT ),
		m_tUnits( 0 ),
		m_fData( GXFLOAT_CAST(GFLOAT(f)) )
{
}

/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		long	i
		)
		: m_eType( T_INTEGER ),
		m_tUnits( 0 ),
		m_nData( i )
{
}

/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		ConstCColorRef	r
		)
		: m_eType( T_COLOR ),
		m_tUnits( 0 ),
		m_tColor( r )
{
}

/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		bool	b
		)
		: m_eType( T_BOOL ),
		m_tUnits( 0 ),
		m_bData( b )
{
}


/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		ConstCDateTimeRef	r
		)
		: m_eType( T_DATETIME ),
		m_tUnits( 0 ),
		m_tTime( r.ToTime_t() )
{
}


/*---------------------------------------------------------------------+\

 * CVariantData - conversion constructor

\+---------------------------------------------------------------------*/
CVariantData::CVariantData
		(
		NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef r
		)
		: m_eType( T_UNDEFINED ),
		m_tUnits( 0 ),
		m_pString( 0 )
{
	LoadCharDescriptor( r.Pointer(), r.Length() );
}


/*---------------------------------------------------------------------+\

 * ~CVariantData - destructor

\+---------------------------------------------------------------------*/
CVariantData::~CVariantData
		(
		void
		)
{
	if ( T_STRING == m_eType )
		delete m_pString;
	else if ( T_ARRAY == m_eType )
		delete m_pArray;
}






/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/






/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		ConstCVariantDataRef	r
		)
{
	if ( this != &r )	// protect against self assignment
	{
		//PrepareLoad( r.m_eType );
		if ( ! LoadCopy( r ) )
			throw -1;
	}

	return *this;
}


/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef r
		)
{
	LoadCharDescriptor( r.Pointer(), r.Length() );
	return *this;
}


/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		const bool b
		)
{
	PrepareLoad( T_BOOL );

	m_bData = b;
	m_eType = T_BOOL;
	m_tUnits = 0;
	return *this;
}


/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		const long n
		)
{
	PrepareLoad( T_INTEGER );

	m_nData = n;
	m_eType = T_INTEGER;
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		const double fData
		)
{
	PrepareLoad( T_FLOAT );

	GFLOAT	f = static_cast<float>(fData);
	m_fData = GXFLOAT_CAST(f);
	m_eType = T_FLOAT;
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		const GFLOAT f
		)
{
	PrepareLoad( T_FLOAT );

	m_fData = GXFLOAT_CAST(f);
	m_eType = T_FLOAT;
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		const char*	s
		)
{
	LoadCharString( s );
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		ConstCColorRef	r
		)
{
	PrepareLoad( T_COLOR );

	m_tColor = r.GetData();
	m_eType = T_COLOR;
	m_tUnits = 0;
	return *this;
}


/*---------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::operator =
		(
		ConstCDateTimeRef	r
		)
{
	PrepareLoad( T_DATETIME );

	m_tTime = r;
	m_eType = T_DATETIME;
	//m_tUnits = 0;
	return *this;
}



/*---------------------------------------------------------------------+\

 * operator bool -

\+---------------------------------------------------------------------*/
CVariantData::operator bool
		(
		void
		)
{
	return GetValueBool();
}


/*---------------------------------------------------------------------+\

 * operator long -

\+---------------------------------------------------------------------*/
CVariantData::operator long
		(
		void
		)
{
	return GetValueInteger();
}

/*---------------------------------------------------------------------+\

 * operator float -

\+---------------------------------------------------------------------*/
CVariantData::operator GFLOAT
		(
		void
		)
{
	return GetValueFloat();
}

/*---------------------------------------------------------------------+\

 * operator double -

\+---------------------------------------------------------------------*/
CVariantData::operator double
		(
		void
		)
{
	return GetValueDouble();
}


/*---------------------------------------------------------------------+\

 * operator char* -

\+---------------------------------------------------------------------*/
CVariantData::operator const char*
		(
		void
		)
{
	return GetValueString();
}


/*---------------------------------------------------------------------+\

 * operator CCharString -

\+---------------------------------------------------------------------*/
CVariantData::operator NAMESPACE_ROOT_PREFIX CCharString
		(
		void
		)
{
	return GetValueCCharString();
}



/*---------------------------------------------------------------------+\

 * operator CCharDescriptor -

\+---------------------------------------------------------------------*/
CVariantData::operator CCharDescriptor
		(
		void
		)
{
	if ( T_STRING == m_eType )
	{
		if ( m_pString )
			return NAMESPACE_ROOT_PREFIX CCharDescriptor( m_pString->Pointer(), m_pString->Length() );
		else
			return NAMESPACE_ROOT_PREFIX CCharDescriptor();
	}
	else if ( T_PACKED_CHARACTER == m_eType )
	{
		size_t	n = ::strlen( m_cData );
		if ( 0 < n )
			return NAMESPACE_ROOT_PREFIX CCharDescriptor( m_cData, n );
		else
			return NAMESPACE_ROOT_PREFIX CCharDescriptor();
	}
	else
	{
		return NAMESPACE_ROOT_PREFIX CCharDescriptor();
	}
}


/*---------------------------------------------------------------------+\

 * operator const CCharDescriptorPtr -

\+---------------------------------------------------------------------*/
CVariantData::operator const NAMESPACE_ROOT_PREFIX CCharDescriptor*
		(
		void
		)
{
	if ( T_STRING == m_eType )
		return m_pString;
	else
		return 0;
}


/*---------------------------------------------------------------------+\

 * operator CCharDescriptorPtr -

\+---------------------------------------------------------------------*/
CVariantData::operator NAMESPACE_ROOT_PREFIX CCharDescriptor*
		(
		void
		) const
{
	if ( T_STRING == m_eType )
		return m_pString;
	else
		return 0;
}


/*---------------------------------------------------------------------+\

 * operator CCharDescriptorRef -

\+---------------------------------------------------------------------*/
CVariantData::operator NAMESPACE_ROOT_PREFIX CCharDescriptorRef
		(
		void
		)
{
	if ( T_STRING == m_eType )
	{
		if ( m_pString )
			return *m_pString;
		else
			return g_tCharDescriptor;
	}
	else
	{
		return g_tCharDescriptor;
	}
}



/*---------------------------------------------------------------------+\

 * operator CColor -

\+---------------------------------------------------------------------*/
CVariantData::operator CColor
		(
		void
		)
{
	CColor	c;
	c = m_tColor;
	return c;
}


/*---------------------------------------------------------------------+\

 * operator CDateTime -

\+---------------------------------------------------------------------*/
CVariantData::operator CDateTime
		(
		void
		)
{
	return GetValueDateTime();
}


/*---------------------------------------------------------------------+\

 * GetValueBool -

\+---------------------------------------------------------------------*/
bool	CVariantData::GetValueBool
		(
		void
		) const
{
	switch ( m_eType )
	{
	case T_BOOL:
		return m_bData;
	case T_INTEGER:
		return m_nData != 0;
	case T_FLOAT:
		return m_fData != 0;
	case T_DATETIME:
		return m_tTime != 0;
	case T_STRING:
		if ( m_pString )
		{
			char	c = m_pString->AtIndex(0);
			switch ( c )
			{
			case 't':
			case 'T':
			case '1':
			case 'y':
			case 'Y':
				return true;
			default:
				return false;
			}
		}
		else
		{
			return false;
		}
	case T_PACKED_CHARACTER:
		if ( m_pString )
		{
			char	c = m_cData[0];
			switch ( c )
			{
			case 't':
			case 'T':
			case '1':
			case 'y':
			case 'Y':
				return true;
			default:
				return false;
			}
		}
		else
		{
			return false;
		}
	case T_ARRAY:
		{

		}
	default:
		return false;
	}
	//return false;
}

/*---------------------------------------------------------------------+\

 * GetValueInteger -

\+---------------------------------------------------------------------*/
long	CVariantData::GetValueInteger
		(
		void
		) const
{
	switch ( m_eType )
	{
	case T_BOOL:
		return m_bData ? 1 : 0;
	case T_INTEGER:
		return m_nData;
	case T_FLOAT:
		return static_cast<long>( floorf( GFLOAT_CAST(m_fData) ) );
	case T_COLOR:
		return static_cast<long>( m_tColor );
	case T_DATETIME:
		return static_cast<long>( m_tTime );
	case T_STRING:
		{
			long	n = 0;
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					size_t	nCount;
					n = m_pString->ParseInt( &nCount );
					if ( nCount != m_pString->Length() )
						n = 0;
				}
			}
			return n;
		}
	case T_PACKED_CHARACTER:
		{
			long	n = 0;
			size_t	i = ::strlen( m_cData );
			if ( 0 < i )
			{
				size_t	nCount;
				n = ParseInt( m_cData, (size_t)i, &nCount );
				if ( nCount != i )
					n = 0;
			}
			return n;
		}
	default:
		return 0;
	}
}

/*---------------------------------------------------------------------+\

 * GetValueFloat -

\+---------------------------------------------------------------------*/
GFLOAT	CVariantData::GetValueFloat
		(
		void
		) const
{
	switch ( m_eType )
	{
	case T_BOOL:
		return GFLOAT( m_bData ? GFLOAT_1 : GFLOAT_0 );
	case T_INTEGER:
		return GFLOAT( m_nData );
		break;
	case T_FLOAT:
		return GFLOAT_CAST( m_fData );
		break;
	case T_STRING:
		{
			GFLOAT	f = GFLOAT_0;
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					size_t	nCount;
					f = m_pString->ParseFloat( &nCount );
					if ( nCount != m_pString->Length() )
						f = GFLOAT_0;
				}
			}
			return f;
		}
		break;
	case T_PACKED_CHARACTER:
		{
			GFLOAT	f = GFLOAT_0;
			size_t	n = ::strlen( m_cData );
			if ( 0 < n )
			{
				size_t	nCount;
				f = ParseFloat( m_cData, n, &nCount );
				if ( n != nCount )
					f = GFLOAT_0;
			}
			return f;
		}
	default:
		return GFLOAT_0;
		break;
	}
}


/*---------------------------------------------------------------------+\

 * GetValueFloatAsUnits -

\+---------------------------------------------------------------------*/
GFLOAT	CVariantData::GetValueFloatAsUnits
		(
		int		nUnits
		) const
{
	GFLOAT	f = GetValueFloat();
	int		u = m_tUnits.GetUnits();

	if ( 0 < u )
	{
		if ( u != nUnits )
			return CUnitsOfMeasure::Convert( nUnits, u, f );
		else
			return f;
	}
	else
	{
		return f;
	}
}


/*---------------------------------------------------------------------+\

 * GetValueDouble -

\+---------------------------------------------------------------------*/
double	CVariantData::GetValueDouble
		(
		void
		) const
{
	return GetValueFloat();
}

/*---------------------------------------------------------------------+\

 * GetValueString -

\+---------------------------------------------------------------------*/
const char*
		CVariantData::GetValueString
		(
		void
		) const
{
	switch ( m_eType )
	{
	case T_STRING:
		if ( m_pString )
			return m_pString->Pointer();
		else
			return 0;
	default:
		return 0;
	}
}



/*---------------------------------------------------------------------+\

 * EqualsVariant - equality operator

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsVariant
		(
		ConstCVariantDataRef r
		) const
{
	if ( m_tUnits != r.m_tUnits )
		return false;
	if ( m_eType == r.m_eType )
	{
		switch ( m_eType )
		{
		case T_STRING:
			return 0 == m_pString->Compare( *r.m_pString );
			break;
		case T_INTEGER:
		case T_PACKED_CHARACTER:
			return m_nData == r.m_nData;
			break;
		case T_BOOL:
			return m_bData == r.m_bData;
			break;
		case T_FLOAT:
			return m_fData == r.m_fData;
			break;
		case T_COLOR:
			return m_tColor == r.m_tColor;
			break;
		case T_DATETIME:
			return m_tTime == r.m_tTime;
			break;
		case T_UNDEFINED:
			return m_nData == r.m_nData;
			break;
		default:
			return false;
			break;
		}
	}
	else
	{
		switch ( r.m_eType )
		{
		case T_STRING:
			return EqualsCCharString( *r.m_pString );
			break;
		case T_INTEGER:
			return EqualsInteger( r.m_nData );
			break;
		case T_BOOL:
			return EqualsBool( r.m_bData );
			break;
		case T_FLOAT:
			return EqualsFloat( r.m_fData );
			break;
		case T_COLOR:
			return EqualsColor( r.m_tColor );
			break;
		case T_DATETIME:
			return EqualsDateTime( r.m_tTime );
			break;
		case T_UNDEFINED:
			switch ( m_eType )
			{
			case T_STRING:
				{
					CCharDescriptor	s;
					return EqualsCCharString( s );
				}
			case T_INTEGER:
				return EqualsInteger( 0L );
			case T_BOOL:
				return EqualsBool( false );
			case T_FLOAT:
				return EqualsFloat( 0.0f );
			case T_COLOR:
				{
					CColor	c;
					return EqualsColor( c );
				}
			case T_DATETIME:
				{
					CDateTime	d;
					return EqualsDateTime( d );
				}
			default:
				return false;
			}
			break;
		default:
			return false;
			break;
		}
	}
}

bool	CVariantData::LessThanVariant
		(
		ConstCVariantDataRef r
		) const
{
	if ( m_eType == r.m_eType )
	{
		switch ( m_eType )
		{
		case T_FLOAT:
			return m_fData < r.m_fData;
		case T_INTEGER:
			return m_nData < r.m_nData;
		case T_STRING:
			if ( m_pString  &&  r.m_pString )
			{
				return *m_pString < *r.m_pString;
			}
			else if ( m_pString )
			{
				return false;
			}
			else if ( r.m_pString )
			{
				return true;
			}
			else
			{
				return false;
			}
		case T_DATETIME:
			return m_tTime < r.m_tTime;
		case T_COLOR:
			return m_tColor < r.m_tColor;
		case T_PACKED_CHARACTER:
			return m_nData < r.m_nData;
		case T_BOOL:
			if ( !m_bData  &&  r.m_bData )
				return true;
			else
				return false;
		default:
			return false;
		}
	}
	else
	{
		switch ( r.m_eType )
		{
		case T_STRING:
			return LessThanCCharString( *r.m_pString );
			break;
		case T_INTEGER:
			return LessThanInteger( r.m_nData );
			break;
		case T_BOOL:
			return LessThanBool( r.m_bData );
			break;
		case T_FLOAT:
			return LessThanFloat( r.m_fData );
			break;
		case T_COLOR:
			return LessThanColor( r.m_tColor );
			break;
		case T_DATETIME:
			return LessThanDateTime( r.m_tTime );
			break;
		default:
			return false;
			break;
		}
	}
}

/*---------------------------------------------------------------------+\

 * EqualsDouble - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsDouble
		(
		double fData
		) const
{
	switch ( m_eType )
	{
	case T_FLOAT:
		return m_fData == GXFLOAT_CAST(GFLOAT(fData));
		break;
	case T_INTEGER:
		return double(m_nData) == fData;
		break;
	case T_STRING:
		{
			GFLOAT	d = GFLOAT_MAX;
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					size_t	nCount;
					d = m_pString->ParseFloat( &nCount );
					if ( nCount != m_pString->Length() )
						d = GFLOAT_MAX;
				}
			}
			return d == fData;
		}
		break;
	case T_UNDEFINED:
		return 0.0 == fData;
		break;
	default:
		return false;
		break;
	}
}

/*---------------------------------------------------------------------+\

 * EqualsFloat - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsFloat
		(
		GFLOAT fData
		) const
{
	switch ( m_eType )
	{
	case T_FLOAT:
		return m_fData == GXFLOAT_CAST(fData);
		break;
	case T_INTEGER:
		return GFLOAT(m_nData) == fData;
		break;
	case T_STRING:
		{
			GFLOAT	d = GFLOAT_MAX;
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					size_t	nCount;
					d = m_pString->ParseFloat( &nCount );
					if ( nCount != m_pString->Length() )
						d = GFLOAT_MAX;
				}
			}
			return d == fData;
		}
		break;
	case T_UNDEFINED:
		return 0.0f == fData;
		break;
	default:
		return false;
		break;
	}
}

bool	CVariantData::LessThanFloat
		(
		GFLOAT fData
		) const
{
	switch ( m_eType )
	{
	case T_FLOAT:
		return m_fData < GXFLOAT_CAST(fData);
		break;
	case T_INTEGER:
		return GFLOAT(m_nData) < fData;
		break;
	case T_STRING:
		{
			GFLOAT	d = GFLOAT_MAX;
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					size_t	nCount;
					d = m_pString->ParseFloat( &nCount );
					if ( nCount != m_pString->Length() )
						d = GFLOAT_MAX;
				}
			}
			return d < fData;
		}
		break;
	case T_UNDEFINED:
		return (0.0f < fData);
		break;
	default:
		return false;
		break;
	}
}

/*---------------------------------------------------------------------+\

 * EqualsBool - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsBool
		(
		bool bData
		) const
{
	switch ( m_eType )
	{
	case T_BOOL:
		return m_bData == bData;
		break;
	case T_INTEGER:
		return (m_nData ? true : false) == bData;
		break;
	case T_FLOAT:
		return (GFLOAT_EPSILON < ::fabsf(GFLOAT_CAST(m_fData)) ? true : false) == bData;
		break;
	case T_STRING:
		{
			bool	b = false;
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					switch ( ::toupper(*(m_pString->Pointer())) )
					{
					case 'T':
					case 'Y':
					case '1':
						b = true;
						break;
					}
				}
			}
			return b == bData;
		}
		break;
	case T_UNDEFINED:
		return false == bData;
		break;
	default:
		return false;
		break;
	}
}

bool	CVariantData::LessThanBool
		(
		bool bData
		) const
{
	bool	b = false;

	switch ( m_eType )
	{
	case T_BOOL:
		b = m_bData;
		break;
	case T_INTEGER:
		b = (m_nData ? true : false);
		break;
	case T_FLOAT:
		b = (GFLOAT_EPSILON < ::fabsf(GFLOAT_CAST(m_fData)) ? true : false);
		break;
	case T_STRING:
		{
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					switch ( ::toupper(m_pString->AtIndex(0)) )
					{
					case 'T':
					case 'Y':
					case '1':
						b = true;
						break;
					}
				}
			}
		}
		break;
	default:
		b = false;
		break;
	}
	if ( !b  &&  bData )
		return true;
	else
		return false;
}

/*---------------------------------------------------------------------+\

 * EqualsInteger - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsInteger
		(
		long nData
		) const
{
	switch ( m_eType )
	{
	case T_INTEGER:
		return m_nData == nData;
		break;
	case T_FLOAT:
		return long(GFLOAT_CAST(m_fData)) == nData;
		break;
	case T_STRING:
		{
			long	d = 0;
			if ( m_pString )
			{
				size_t	nLen = m_pString->Length();
				if ( 0 < nLen )
				{
					size_t	nCount;
					d = NAMESPACE_ROOT_PREFIX ParseInt( m_pString->Pointer(), nLen, &nCount );
					if ( nCount != nLen )
						d = ~nData;
				}
			}
			return d == nData;
		}
		break;
	case T_UNDEFINED:
		return 0 == nData;
		break;
	default:
		return false;
		break;
	}
}

bool	CVariantData::LessThanInteger
		(
		long nData
		) const
{
	switch ( m_eType )
	{
	case T_INTEGER:
		return m_nData < nData;
		break;
	case T_FLOAT:
		return long(GFLOAT_CAST(m_fData)) < nData;
		break;
	case T_STRING:
		{
			long	d = 0;
			if ( m_pString )
			{
				size_t	nLen = m_pString->Length();
				if ( 0 < nLen )
				{
					size_t	nCount;
					d = NAMESPACE_ROOT_PREFIX ParseInt( m_pString->Pointer(), nLen, &nCount );
					if ( nCount != nLen )
						d = ~nData;
				}
			}
			return d < nData;
		}
		break;
	case T_UNDEFINED:
		return 0 < nData;
		break;
	default:
		return false;
		break;
	}
}

/*---------------------------------------------------------------------+\

 * EqualsString - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsString
		(
		const char* sData
		) const
{
	if ( sData )
	{
		NAMESPACE_ROOT_PREFIX CCharDescriptor	tData( sData );
		return EqualsCCharString( tData );
	}
	else
	{
		return false;
	}
}


bool	CVariantData::LessThanString
		(
		const char* sData
		) const
{
	if ( sData )
	{
		NAMESPACE_ROOT_PREFIX CCharDescriptor	tData( sData );
		return LessThanCCharString( tData );
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * EqualsCCharString - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsCCharString
		(
		NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef r
		) const
{
	switch ( m_eType )
	{
	case T_STRING:
		if ( m_pString )
			return 0 == m_pString->Compare( r );
		else
			return false;
		break;
	case T_INTEGER:
		{
			if ( 0 < r.Length() )
			{
				long	n;
				size_t	nCount;
				n = r.ParseInt( &nCount );
				if ( nCount != r.Length() )
					return false;
				else
					return m_nData == n;
			}
			else
			{
				return false;
			}
		}
		break;
	case T_BOOL:
		{
			bool	b = false;
			if ( 0 < r.Length() )
			{
				switch ( ::toupper( r.AtIndex(0) ) )
				{
				case 'T':
				case 'Y':
				case '1':
					b = true;
				}
			}
			return m_bData == b;
		}
		break;
	case T_FLOAT:
		{
			if ( 0 < r.Length() )
			{
				GFLOAT	d;
				size_t	nCount;
				d = r.ParseFloat( &nCount );
				if ( nCount != r.Length() )
					return false;
				else
					return m_fData == GXFLOAT_CAST(d);
			}
			else
			{
				return false;
			}
		}
		break;
	case T_DATETIME:
		{
			CDateTime	t;
			t.Parse( r.Pointer() );
			return t == m_tTime;
		}
		break;
	case T_COLOR:
		{
			CColor	c;
			c = CColor::ColorFromName( r.Pointer() );
			return c == m_tColor;
		}
		break;
	case T_UNDEFINED:
		{
			if ( r.Length() < 1 )
				return true;
			else
				return false;
		}
		break;
	default:
		return false;
		break;
	}
}

bool	CVariantData::LessThanCCharString
		(
		NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef r
		) const
{
	switch ( m_eType )
	{
	case T_STRING:
		if ( m_pString )
			return *m_pString < r;
		else
			return false;
		break;
	case T_INTEGER:
		{
			if ( 0 < r.Length() )
			{
				long	n;
				size_t	nCount;
				n = r.ParseInt( &nCount );
				if ( nCount != r.Length() )
					return false;
				else
					return m_nData < n;
			}
			else
			{
				return false;
			}
		}
		break;
	case T_BOOL:
		{
			bool	b = false;
			if ( 0 < r.Length() )
			{
				switch ( ::toupper( r.AtIndex(0) ) )
				{
				case 'T':
				case 'Y':
				case '1':
					b = true;
				}
			}
			return (!m_bData && b) ? true : false;
		}
		break;
	case T_FLOAT:
		{
			if ( 0 < r.Length() )
			{
				GFLOAT	d;
				size_t	nCount;
				d = r.ParseFloat( &nCount );
				if ( nCount != r.Length() )
					return false;
				else
					return m_fData < GXFLOAT_CAST(d);
			}
			else
			{
				return false;
			}
		}
		break;
	case T_DATETIME:
		{
			CDateTime	t;
			t.Parse( r.Pointer() );
			return t < m_tTime;
		}
		break;
	case T_COLOR:
		{
			CColor	c;
			c = CColor::ColorFromName( r.Pointer() );
			return c > m_tColor;
		}
		break;
	case T_UNDEFINED:
		{
			if ( 0 < r.Length() )
				return true;
			else
				return false;
		}
		break;
	default:
		return false;
		break;
	}
}

/*---------------------------------------------------------------------+\

 * EqualsColor - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsColor
		(
		ConstCColorRef r
		) const
{
	switch ( m_eType )
	{
	case T_COLOR:
		{
			//CColor	c = r;
			return m_tColor == r;
		}
		break;
	case T_INTEGER:
		{
			CColor	c;
			c.SetColorLong( m_nData );
			return c == r;
		}
		break;
	case T_STRING:
		{
			if ( m_pString )
			{
				if ( 0 < m_pString->Length() )
				{
					CColor	c = CColor::ColorFromName( *m_pString );
					return c == r;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		break;
	default:
		return false;
		break;
	}
}

bool	CVariantData::LessThanColor
		(
		ConstCColorRef //r
		) const
{
	return false;
}


/*---------------------------------------------------------------------+\

 * EqualsDateTime - Equality

\+---------------------------------------------------------------------*/
bool	CVariantData::EqualsDateTime
		(
		ConstCDateTimeRef	t
		) const
{
	switch ( m_eType )
	{
	case T_DATETIME:
		return m_tTime == t;
		break;
	default:
		return false;
		break;
	}
}


bool	CVariantData::LessThanDateTime
		(
		ConstCDateTimeRef	t
		) const
{
	switch ( m_eType )
	{
	case T_DATETIME:
		return m_tTime < t;
		break;
	default:
		return false;
		break;
	}
}


/*---------------------------------------------------------------------+\

 * GetValueCCharString -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

NAMESPACE_ROOT_PREFIX CCharString
		CVariantData::GetValueCCharString
		(
		void
		) const
{
	switch ( m_eType )
	{
	case T_STRING:
		if ( m_pString )
			return *m_pString;
		else
			return NAMESPACE_ROOT_PREFIX CCharString( "" );
		break;
	case T_INTEGER:
		{
			NAMESPACE_ROOT_PREFIX CCharString	s;
			s.Format( "%d", m_nData );
			return s;
		}
		break;
	case T_FLOAT:
		{
			NAMESPACE_ROOT_PREFIX CCharString	s;
			s.Format( "%f", (float)GFLOAT_CAST(m_fData) );
			return s;
		}
		break;
	case T_DATETIME:
		{
			char		sTemp[80];
			CDateTime	t( m_tTime );
			t.FormatISO( sTemp, sizeof(sTemp) );
			return CCharString( sTemp );
		}
		break;
	case T_ARRAY:
		{
			if ( m_pArray )
				return Item( 0 ).GetValueCCharString();
			else
				return CCharString( "" );
		}
	default:
		return NAMESPACE_ROOT_PREFIX CCharString( "" );
		break;
	}
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * GetValueColor -

\+---------------------------------------------------------------------*/
CColor
		CVariantData::GetValueColor
		(
		void
		) const
{
	CColor	c;
	switch ( m_eType )
	{
	case T_COLOR:
		c.SetData( m_tColor );
		break;
	case T_INTEGER:
		c.SetColorLong( m_nData );
		break;
	case T_STRING:
		if ( m_pString )
			c = CColor::ColorFromName( *m_pString );
		else
			c.SetNonColor( true );
		break;
	case T_ARRAY:
		if ( m_pArray )
			c = Item(0).GetValueColor();
		else
			c.SetNonColor( true );
		break;
	default:
		c.SetNonColor( true );
		break;
	}
	return c;
}


/*---------------------------------------------------------------------+\

 * GetValueDateTime -

\+---------------------------------------------------------------------*/
CDateTime
		CVariantData::GetValueDateTime
		(
		void
		) const
{
	switch ( m_eType )
	{
	case T_DATETIME:
		return CDateTime( m_tTime );
	case T_INTEGER:
		return CDateTime( m_nData );
	case T_STRING:
		{
			CDateTime	t;
			if ( 0 < m_pString->Length() )
				t.Parse( *m_pString );
			return t;
		}
	case T_ARRAY:
		{
			if ( m_pArray )
				return Item( 0 ).GetValueDateTime();
			else
				return CDateTime();
		}
	default:
		return CDateTime();
	}
}

/*---------------------------------------------------------------------+\

 * GetType -

\+---------------------------------------------------------------------*/
CVariantData::V_TYPE
		CVariantData::GetType
		(
		void
		)
{
	return m_eType;
}

/*---------------------------------------------------------------------+\

 * GetMetaType -

\+---------------------------------------------------------------------*/
CVariantData::V_METATYPE
		CVariantData::GetMetaType
		(
		void
		)
{
	switch ( m_eType )
	{
	case T_UNDEFINED:
		return MT_UNDEFINED;
	case T_BOOL:
		return MT_LOGICAL;
	case T_INTEGER:
	case T_FLOAT:
		return MT_NUMERIC;
	case T_PACKED_CHARACTER:
	case T_STRING:
		return MT_CHARACTER;
	case T_COLOR:
		return MT_COLOR;
	case T_DATETIME:
		return MT_DATETIME;
	case T_ARRAY:
		return MT_ARRAY;
	default:
		return MT_UNDEFINED;
	}
}


/*---------------------------------------------------------------------+\

 * GetUnits -

\+---------------------------------------------------------------------*/
int		CVariantData::GetUnits
		(
		void
		)
{
	return m_tUnits.GetUnits();
}

/*---------------------------------------------------------------------+\

 * SetUnits -

\+---------------------------------------------------------------------*/
void	CVariantData::SetUnits
		(
		int	eUnits
		)
{
	m_tUnits = CUnitsOfMeasure(eUnits);
}



/*---------------------------------------------------------------------+\

 * Clear -

\+---------------------------------------------------------------------*/
void	CVariantData::Clear
		(
		void
		)
{
	if ( T_STRING == m_eType )
	{
		if ( m_pString )
			delete m_pString;

	}
	else if ( T_ARRAY == m_eType )
	{
		if ( m_pArray )
			delete m_pArray;
	}

	m_eType = T_UNDEFINED;
	m_bData = false;
	m_nData = 0;
	m_fData = 0;
	m_pString = 0;
	m_tColor = 0;
	m_tTime = 0;
	m_pArray = 0;
}




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/





/*---------------------------------------------------------------------+\

 * LoadCopy -

\+---------------------------------------------------------------------*/
bool	CVariantData::LoadCopy
		(
		ConstCVariantDataRef	r
		)
{
	bool	bResult = true;
	//int		n = 0;

	PrepareLoad( r.m_eType );

	switch ( r.m_eType )
	{
	case T_BOOL:
		m_bData = r.m_bData;
		break;
	case T_INTEGER:
		m_nData = r.m_nData;
		break;
	case T_FLOAT:
		m_fData = r.m_fData;
		break;
	case T_STRING:
		if ( m_pString )
		{
			m_pString->LoadCCharString( *r.m_pString );
		}
		else
		{
			m_pString = new NAMESPACE_ROOT_PREFIX CCharString( *r.m_pString );
		}
		break;
	case T_COLOR:
		m_tColor = r.m_tColor;
		break;
	case T_DATETIME:
		m_tTime = r.m_tTime;
		break;
	case T_ARRAY:
		{
			if ( m_pArray )
			{
				*m_pArray = *r.m_pArray;
			}
			else
			{
				m_pArray = new TVariantArray( *r.m_pArray );
			}
		}
		break;
	default:
		m_nData = r.m_nData;
		break;
	}
	m_eType = r.m_eType;
	m_tUnits = r.m_tUnits;
	return bResult;
}


/*---------------------------------------------------------------------+\

 * LoadCharString -

\+---------------------------------------------------------------------*/
bool	CVariantData::LoadCharString
		(
		const char*	s
		)
{
	bool	bResult = true;

	PrepareLoad( T_STRING );

	if ( m_eType != T_STRING )
	{
		m_pString = new NAMESPACE_ROOT_PREFIX CCharString( s );
		if ( ! m_pString )
			bResult = false;
	}
	else
	{
		if ( ! m_pString )
			m_pString = new NAMESPACE_ROOT_PREFIX CCharString( s );
		else
			m_pString->LoadStringData( s );
	}
	m_eType = T_STRING;
	//m_tUnits = 0;
	return bResult;
}


/*---------------------------------------------------------------------+\

 * LoadCharDescriptor -

\+---------------------------------------------------------------------*/
bool	CVariantData::LoadCharDescriptor
		(
		const char*	s,
		size_t		n
		)
{
	bool	bResult = true;

	PrepareLoad( T_STRING );

	if ( m_eType != T_STRING )
	{
		m_pString = new CCharString( s, n );
		if ( ! m_pString )
			bResult = false;
	}
	else
	{
		if ( ! m_pString )
			m_pString = new NAMESPACE_ROOT_PREFIX CCharString( s, n );
		else
			m_pString->LoadStringData( s, (index_t)n );
	}
	m_eType = T_STRING;
	//m_tUnits = 0;
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ItemCount -

\+---------------------------------------------------------------------*/
size_t	CVariantData::ItemCount
		(
		void
		) const
{
	if ( T_ARRAY == m_eType )
	{
		if ( m_pArray )
			return m_pArray->Length();
		else
			return 0;
	}
	else
	{
		return 0;
	}
}


/*---------------------------------------------------------------------+\

 * Item -

\+---------------------------------------------------------------------*/
CVariantDataRef
		CVariantData::Item
		(
		const index_t n
		)
{
	if ( T_ARRAY == m_eType )
	{
		if ( m_pArray )
		{
			CVariantDataPtr	p = m_pArray->PointArray( n );
			if ( p )
				return *p;
		}
	}
	return *this;
}


/*---------------------------------------------------------------------+\

 * Item -

\+---------------------------------------------------------------------*/
ConstCVariantDataRef
		CVariantData::Item
		(
		const index_t n
		) const
{
	if ( T_ARRAY == m_eType )
	{
		if ( m_pArray )
		{
			CVariantDataPtr	p = m_pArray->PointArray( n );
			if ( p )
				return *p;
		}
	}
	return *this;
}


/*---------------------------------------------------------------------+\

 * LoadItem -

\+---------------------------------------------------------------------*/
bool	CVariantData::LoadItem
		(
		ConstCVariantDataRef ,//r,
		const index_t //n
		)
{
	bool	bResult = true;

	PrepareLoad( T_ARRAY );

	return bResult;
}



/*---------------------------------------------------------------------+\

 * PrepareLoad -

\+---------------------------------------------------------------------*/
void	CVariantData::PrepareLoad
		(
		CVariantData::V_TYPE t
		)
{
	if ( T_STRING == m_eType )
	{
		if ( T_STRING != t )
		{
			delete m_pString;
			m_pString = 0;
		}
	}
	else if ( T_ARRAY == m_eType )
	{
		if ( T_ARRAY != t )
		{
			delete m_pArray;
			m_pArray = 0;
		}
	}
	else
	{
		m_nData = 0;
	}
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

NAMESPACE_COMMON_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

