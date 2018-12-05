/*---------------------------------------------------------------------+\
|
|	CUnitsOfMeasure.h  --  brief description of what CUnitsOfMeasure.h is for
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
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
	21-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Added some new unit types. Added new function to
		get unit name from unit Id.
	07-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for char-descriptors for locating entries
	08-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CUnitsOfMeasure
#define _H_CUnitsOfMeasure
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharDescriptor.h"
#include "UFloat.h"

#include "NamespaceCommon.h"
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
typedef class CUnitsOfMeasure*			CUnitsOfMeasurePtr;
typedef class CUnitsOfMeasure&			CUnitsOfMeasureRef;
typedef const class CUnitsOfMeasure&	ConstCUnitsOfMeasureRef;

typedef enum UNITFAMILY
{
	UF_UNDEFINED = 0,
	UF_DISTANCE,
	UF_AREA,
	UF_VOLUME,
	UF_VOLUMERATE,
	UF_FUELCONSUMPTION,
	UF_TEMPERATURE,
	UF_ANGLE,
	UF_GLOBALPOSITION,
	UF_ANGULARVELOCITY,
	UF_SPEED,
	UF_ACCELERATION,
	UF_TIME,
	UF_FREQUENCY,
	UF_POWER,
	UF_DATE,
	UF_WEIGHT,
	UF_WEIGHTRATE,
	UF_ELECTRICAL_CURRENT,
	UF_ELECTRICAL_POTENTIAL,
	UF_DENSITY,
	UF_PRESSURE,
	UF_TORQUE,
	UF_SOUND,
	UF_LIGHT,
	UF_PERCENT,
	UF_SPECIAL
} UNITFAMILY;


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CUnitsOfMeasure
{
//	class lifecycle  ----------------------------------------------------
public:
				CUnitsOfMeasure();
				CUnitsOfMeasure( ConstCUnitsOfMeasureRef r );	// copy constructor
				CUnitsOfMeasure( int n );
				CUnitsOfMeasure( const char* sString );
				CUnitsOfMeasure( Yogi::Core::ConstCCharDescriptorRef r );
	virtual		~CUnitsOfMeasure();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CUnitsOfMeasureRef	operator=( ConstCUnitsOfMeasureRef r );		// assignment

	bool		operator == ( ConstCUnitsOfMeasureRef r ) const;
	bool		operator == ( int n ) const;
	bool		operator != ( ConstCUnitsOfMeasureRef r ) const;
	bool		operator != ( int n ) const;
				operator int ( void ) const;

	int			SetUsingString( const char* s );
	int			SetUsingString( Yogi::Core::ConstCCharDescriptorRef r );

	int			SetUsingName( const char* s );
	int			SetUsingName( Yogi::Core::ConstCCharDescriptorRef r );
	int			SetUsingPluralName( const char* s );
	int			SetUsingPluralName( Yogi::Core::ConstCCharDescriptorRef r );
	int			SetUsingAbbrev( const char* s );
	int			SetUsingAbbrev( Yogi::Core::ConstCCharDescriptorRef r );

	const char*	ToName( void );
	const char*	ToPluralName( void );
	const char*	ToAbbrevName( void );

	int			GetUnits( void ) const;

	static GFLOAT	Convert( int nOutUnits, int nInUnits, GFLOAT fInValue );
	static const char*	NameFromUnits( int nUnits );
	static const char*	PluralNameFromUnits( int nUnits );
	static const char*	AbbrevFromUnits( int nUnits );


protected:
//	protected types  ----------------------------------------------------


//	protected functions  ------------------------------------------------

	static void	InitUnitTable( void );

//	protected data  -----------------------------------------------------

	short		m_nUnits;		// actually index into UNITDATA array

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
/*---------------------------------------------------------------------+\

 * CUnitsOfMeasure - constructor

\+---------------------------------------------------------------------*/
inline
CUnitsOfMeasure::CUnitsOfMeasure
		(
		void
		)
		: m_nUnits( 0 )
{
}


/*---------------------------------------------------------------------+\

 * CUnitsOfMeasure - constructor

\+---------------------------------------------------------------------*/
inline
CUnitsOfMeasure::CUnitsOfMeasure
		(
		int		n
		)
		: m_nUnits( static_cast<short>(n) )
{
}

inline
CUnitsOfMeasure::CUnitsOfMeasure
		(
		const char* s
		)
		: m_nUnits( 0 )
{
	SetUsingString( s );
}

inline
CUnitsOfMeasure::CUnitsOfMeasure
		(
		Yogi::Core::ConstCCharDescriptorRef	r
		)
		: m_nUnits( 0 )
{
	SetUsingString( r );
}

/*---------------------------------------------------------------------+\

 * CUnitsOfMeasure - copy constructor

\+---------------------------------------------------------------------*/
inline
CUnitsOfMeasure::CUnitsOfMeasure
		(
		ConstCUnitsOfMeasureRef	r
		)
		: m_nUnits( r.m_nUnits )
{
}

/*---------------------------------------------------------------------+\

 * ~CUnitsOfMeasure - destructor

\+---------------------------------------------------------------------*/
inline
CUnitsOfMeasure::~CUnitsOfMeasure
		(
		void
		)
{
}


/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline
CUnitsOfMeasureRef
		CUnitsOfMeasure::operator=
		(
		ConstCUnitsOfMeasureRef	r
		)
{
	m_nUnits = r.m_nUnits;
	return *this;
}




/*---------------------------------------------------------------------+\

 * ToAaaaa -

\+---------------------------------------------------------------------*/
inline
const char*
		CUnitsOfMeasure::ToName
		(
		void
		)
{
	return NameFromUnits( m_nUnits );
}


inline
const char*
		CUnitsOfMeasure::ToPluralName
		(
		void
		)
{
	return PluralNameFromUnits( m_nUnits );
}


inline
const char*
		CUnitsOfMeasure::ToAbbrevName
		(
		void
		)
{
	return AbbrevFromUnits( m_nUnits );
}



/*---------------------------------------------------------------------+\

 * GetUnits -

\+---------------------------------------------------------------------*/
inline
int		CUnitsOfMeasure::GetUnits
		(
		void
		) const
{
	return m_nUnits;
}


/*---------------------------------------------------------------------+\

 * operator == -

\+---------------------------------------------------------------------*/
inline
bool	CUnitsOfMeasure::operator ==
		(
		ConstCUnitsOfMeasureRef r
		) const
{
	return m_nUnits == r.m_nUnits;
}


inline
bool	CUnitsOfMeasure::operator ==
		(
		int	n
		) const
{
	return m_nUnits == n;
}


/*---------------------------------------------------------------------+\

 * operator != -

\+---------------------------------------------------------------------*/
inline
bool	CUnitsOfMeasure::operator !=
		(
		ConstCUnitsOfMeasureRef r
		) const
{
	return m_nUnits != r.m_nUnits;
}


inline
bool	CUnitsOfMeasure::operator !=
		(
		int	n
		) const
{
	return m_nUnits != n;
}


/*---------------------------------------------------------------------+\

 * operator int -

\+---------------------------------------------------------------------*/
inline
CUnitsOfMeasure::operator int
		(
		void
		) const
{
	return m_nUnits;
}



}}



#endif /* _H_CUnitsOfMeasure */

