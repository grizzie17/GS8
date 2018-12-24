/*==================================================================*//**
*
*	@file	CCharDescriptor.h
*	@brief	Implementation of TCharDescriptor as "char"
*
*	@see	TCharDescriptor.h
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	11-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add operators that deal with left hand operand char* strings
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add constructor that receives a TCharDescriptor<char>
	01-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ConvertLowercase and ConvertUppercase
	31-Aug-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add CompareIgnoreCase functions
		Fix casting of const char* to char*
	28-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCharDescriptor_Common
#define _H_CCharDescriptor_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <ctype.h>

#include "TCharDescriptor.h"
#include "UDeclSpec.h"

namespace Yogi { namespace Core {
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
class DECL_CLASS CCharString;	// forward reference

typedef class CCharDescriptor*			CCharDescriptorPtr;
typedef class CCharDescriptor&			CCharDescriptorRef;
typedef const class CCharDescriptor&	ConstCCharDescriptorRef;
typedef const class CCharDescriptor*	ConstCCharDescriptorPtr;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

/**
 *	@class CCharDescriptor
 *
 *	Specialization of TCharDescriptor
 */
class DECL_CLASS CCharDescriptor : public TCharDescriptor<char>
{
//	class lifecycle  ----------------------------------------------------
public:
			CCharDescriptor();
			CCharDescriptor( ConstCCharDescriptorRef r );	// copy constructor
			CCharDescriptor( const TCharDescriptor<char>& r );
			CCharDescriptor( const char* s );	// search for null and set Length
			CCharDescriptor( const char* s, size_t n );
	virtual	~CCharDescriptor();


	friend class CCharString;

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	int		CompareIgnoreCase( const TCharDescriptor<char>& r ) const;
	int		CompareIgnoreCase( const char* s, size_t n ) const;
	int		CompareIgnoreCase( const char* s ) const;

	void	ConvertUppercase( void );
	void	ConvertLowercase( void );

	CCharDescriptorRef
			operator = ( const TCharDescriptor<char>& r );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
	typedef	TCharDescriptor<char>	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};




template<>
inline
char	TCharDescriptorCompareFilter<char>
		(
		char	c
		)
{
	return static_cast<char>(::toupper( c ));
}




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

 * operator== - Equals

\+---------------------------------------------------------------------*/
#if 0
template<>
bool	operator==
		(
		const TCharDescriptor<char>&,
		const TCharDescriptor<char>&
		);

template<>
bool	operator==
		(
		const TCharDescriptor<char>&,
		const char*
		);

template<>
bool	operator==
		(
		const char*,
		const TCharDescriptor<char>&
		);
#endif
/*---------------------------------------------------------------------+\

 * operator!= - Not Equals

\+---------------------------------------------------------------------*/
#if 0
template<>
bool	operator!=
		(
		const TCharDescriptor<char>&,
		const TCharDescriptor<char>&
		);

template<>
bool	operator!=
		(
		const TCharDescriptor<char>&,
		const char*
		);

template<>
bool	operator!=
		(
		const char*,
		const TCharDescriptor<char>&
		);
#endif
/*---------------------------------------------------------------------+\

 * operator< - less than

\+---------------------------------------------------------------------*/
#if 0
template<>
bool	operator<
		(
		const TCharDescriptor<char>&,
		const TCharDescriptor<char>&
		);

template<>
bool	operator<
		(
		const TCharDescriptor<char>&,
		const char*
		);

template<>
bool	operator<
		(
		const char*,
		const TCharDescriptor<char>&
		);
#endif
/*---------------------------------------------------------------------+\

 * operator<= - Less than or equal

\+---------------------------------------------------------------------*/
#if 0
template<>
bool	operator<=
		(
		const TCharDescriptor<char>&,
		const TCharDescriptor<char>&
		);

template<>
bool	operator<=
		(
		const TCharDescriptor<char>&,
		const char*
		);

template<>
bool	operator<=
		(
		const char*,
		const TCharDescriptor<char>&
		);
#endif
/*---------------------------------------------------------------------+\

 * operator> - greater than

\+---------------------------------------------------------------------*/
#if 0
template<>
bool	operator>
		(
		const TCharDescriptor<char>&,
		const TCharDescriptor<char>&
		);

template<>
bool	operator>
		(
		const TCharDescriptor<char>&,
		const char*
		);

template<>
bool	operator>
		(
		const char*,
		const TCharDescriptor<char>&
		);
#endif
/*---------------------------------------------------------------------+\

 * operator>= - greater than or equal

\+---------------------------------------------------------------------*/
#if 0
template<>
bool	operator>=
		(
		const TCharDescriptor<char>&,
		const TCharDescriptor<char>&
		);

template<>
bool	operator>=
		(
		const TCharDescriptor<char>&,
		const char*
		);

template<>
bool	operator>=
		(
		const char*,
		const TCharDescriptor<char>&
		);
#endif


/*---------------------------------------------------------------------+\

 * CCharDescriptor - constructors

\+---------------------------------------------------------------------*/
inline
CCharDescriptor::CCharDescriptor
		(
		void
		)
		: TCharDescriptor<char>()
{
}


inline
CCharDescriptor::CCharDescriptor
		(
		ConstCCharDescriptorRef	r
		)
		: TCharDescriptor<char>( r )
{
}



inline
CCharDescriptor::CCharDescriptor
		(
		const TCharDescriptor<char>&	r
		)
		: TCharDescriptor<char>( r )
{
}



inline
CCharDescriptor::CCharDescriptor
		(
		const char*	s,
		size_t		n
		)
		: TCharDescriptor<char>( (char*)s, n )
{
}

inline
CCharDescriptor::CCharDescriptor
		(
		const char*	s
		)
		: TCharDescriptor<char>( (char*)s )
{
}


/*---------------------------------------------------------------------+\

 * ~CCharDescriptor - destructor

\+---------------------------------------------------------------------*/
inline
CCharDescriptor::~CCharDescriptor
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * CompareIgnoreCase - ignore case comparison

\+---------------------------------------------------------------------*/
inline
int		CCharDescriptor::CompareIgnoreCase
		(
		const TCharDescriptor<char>& r
		) const
{
	return CompareFiltered( r );
}


inline
int		CCharDescriptor::CompareIgnoreCase
		(
		const char*	s,
		size_t		n
		) const
{
	return CompareFiltered( s, n );
}

inline
int		CCharDescriptor::CompareIgnoreCase
		(
		const char*	s
		) const
{
	return CompareFiltered( s );
}

/*---------------------------------------------------------------------+\

 * operator = - assignment

\+---------------------------------------------------------------------*/
inline
CCharDescriptorRef
		CCharDescriptor::operator =
		(
		const TCharDescriptor<char>& r
		)
{
	TCharDescriptor<char>::operator =( r );
	return *this;
}



//inline
//bool	operator <
//		(
//		const char*				a,
//		const CCharDescriptor&	b
//		)
//{
//	CCharDescriptor	x( a );
//	return x < b;
//}


/*---------------------------------------------------------------------+\

 * strcmp - compatible with string library

\+---------------------------------------------------------------------*/
inline
int		strcmp
		(
		const CCharDescriptor&	a,
		const CCharDescriptor&	b
		)
{
	return a.Compare( b );
}

inline
int		strcmp
		(
		const CCharDescriptor&	a,
		const char*				b
		)
{
	return a.Compare( b );
}


inline
int		strcmp
		(
		const char*				a,
		const CCharDescriptor&	b
		)
{
	CCharDescriptor	x( a );
	return x.Compare( b );
}





}}



#endif /* _H_CCharDescriptor */
