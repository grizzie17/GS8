/*---------------------------------------------------------------------+\
|
|	IXID.h  --  brief description of what IID.h is for
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
	20-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IXID
#define _H_IXID
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <cstddef>
#include <string.h>
//#include "CCharDescriptor.h"

#include "UDeclCommon.h"

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

typedef class IXID*			IXIDPtr;
typedef class IXID&			IXIDRef;
typedef const class IXID&	ConstIXIDRef;


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/
template< size_t N >
constexpr size_t conststrlen( char const (&)[N] )
{
	return N-1;
}





// This code is released under the terms of the "CC0" license.  Full terms and conditions
// can be found at: http://creativecommons.org/publicdomain/zero/1.0/

//#include <iostream>

// NOTE: hashing algorithm used is FNV-1a

// FNV-1a constants
static constexpr unsigned long long basis = 14695981039346656037ULL;
static constexpr unsigned long long prime = 1099511628211ULL;

// compile-time hash helper function
constexpr unsigned long long hash_one(char c, const char* remain, unsigned long long value)
{
	return c == 0 ? value : hash_one(remain[0], remain + 1, (value ^ c) * prime);
}

// compile-time hash
constexpr unsigned long long hash_const(const char* str)
{
	return hash_one(str[0], str + 1, basis);
}

// run-time hash
//unsigned long long hash_run(const char* str)
//{
//	unsigned long long hsh = basis;
//	while (*str != 0) {
//		hsh ^= str[0];
//		hsh *= prime;
//		++str;
//	}
//	return hsh;
//}

// ensure that the constexpr value is really compile-time constant
template <unsigned long long NUM>
struct test_const
{
	static const unsigned long long value = NUM;
};

// test
//int main()
//{
//	constexpr unsigned long long value = test_const<hash("hello, world!")>::value;
//	unsigned long long value_rt = hash_rt("hello, world!");
//
//	std::cout << "hash =    " << value << std::endl;
//	std::cout << "hash_rt = " << value_rt << std::endl;
//
//	return value == value_rt ? 0 : 127;
//}


//#define IXID(s) IXXID<s>




class DECL_CLASS IXID
{
//	class lifecycle  ----------------------------------------------------
public:
	IXID( const char* constString ) : m_iid(constString), m_iidHash(hash_const(constString)) {};
	IXID( const IXID& rIID ) : m_iid( rIID.m_iid ), m_iidHash( rIID.m_iidHash ) {};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	//IXIDRef	operator=( ConstIXIDRef r );		// assignment

	bool	operator==( ConstIXIDRef r ) const;
	bool	operator==( const char* s ) const;

	bool	Equals( ConstIXIDRef r ) const;
	bool	Equals( const char* s ) const;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	const char*	m_iid; // = constString;
	const unsigned long long m_iidHash; // = hash_const( constString );

private:
	ConstIXIDRef	operator=(ConstIXIDRef ) { return *this; };
};








#if 0

class IXID
{
//	class lifecycle  ----------------------------------------------------
public:
					IXID( const char* sIID );
					IXID( ConstIXIDRef r );	// copy constructor
	virtual			~IXID();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	IXIDRef	operator=( ConstIXIDRef r );		// assignment

	bool	operator==( ConstIXIDRef r ) const;
	bool	operator==( const char* s ) const;

	bool	Equals( ConstIXIDRef r ) const;
	bool	Equals( const char* s ) const;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	const CCharDescriptor	m_iid;
	unsigned long	m_iidHash;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};

#endif // 0

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


//inline
//IXIDRef	IXID::operator =
//		(
//		ConstIXIDRef	r
//		)
//{
//	m_iid = r.m_iid;
//	m_iidHash = r.m_iidHash;
//	return *this;
//}

inline
bool	IXID::operator ==
		(
		ConstIXIDRef	r
		) const
{
	return Equals( r );
}

inline
bool	IXID::operator ==
		(
		const char*	s
		) const
{
	return Equals( s );
}



inline
bool	IXID::Equals
		(
		ConstIXIDRef r
		) const
{
	if ( m_iidHash != r.m_iidHash )
		return false;
	else
		return 0 == ::strcmp(m_iid, r.m_iid);
}



inline
bool	IXID::Equals
		(
		const char*	s
		) const
{
	return 0 == ::strcmp( m_iid, s );
}


#if 0
template< unsigned int _Position_ >
inline void HashPosition( const char* string, unsigned int& hash )
{
	HashPosition< _Position_ - 1 >( string, hash );
	hash = string[_Position_] + (hash << 6) + (hash << 16) - hash;
}


// This specialisation is for terminating the recursion at the first character in the string
template<>
inline void HashPosition<0>( const char* string, unsigned int& hash )
{
	hash = string[0] + (hash << 6) + (hash << 16) - hash;
}

template< unsigned int _Size_ >
inline unsigned int consthash( const char& string, unsigned int hash = 0 )
{
	HashPosition< _Size_ - 2 >( string, hash );
	return hash;
}

// compile time strlen
constexpr size_t slen(const char* str) {
	return *str ? 1 + slen(str + 1) : 0;
}

template < unsigned int _Position_ >
inline void constlen(const char* string, size_t& nLen)
{
	//constlen< _Position_ + 1>(string, nLen);
	nLen = string[_Position_] ? 1 + constlen< _Position_+1>(string, nLen) : 0;
}

//template <>
//inline void constlen(const char* string, size_t& nLen)
//{
//	nLen = 0;
//}

template<unsigned int _Size_>
inline unsigned int conststrlen(const char* string, size_t nLen = 0)
{
	constlen< 0 >(string, nLen);
	return nLen;
}

//template<unsigned int _Size_>
//inline unsigned int constslen(const char* string)
//{
//	return *string ? 1 + constslen(string + 1) : 0;
//}

#endif // 0



#if 0

inline
IXID::IXID
		(
		ConstIXIDRef	r
		)
		:
		m_iid( r.m_iid ),
		m_iidHash( r.m_iidHash )
{
}

inline
IXID::IXID
		(
		const char*	sIID
		)
		:
		m_iid( sIID ),
		m_iidHash( consthash<slen(m_iid.Pointer())>( m_iid.Pointer() ) )
{
}

inline
IXID::~IXID
		(
		void
		)
{
}


inline
IXIDRef	IXID::operator =
		(
		ConstIXIDRef	r
		)
{
	m_iid = r.m_iid;
	m_iidHash = r.m_iidHash;
	return *this;
}

inline
bool	IXID::operator ==
		(
		ConstIXIDRef	r
		) const
{
	return Equals( r );
}

inline
bool	IXID::operator ==
		(
		const char*	s
		) const
{
	return Equals( s );
}



inline
bool	IXID::Equals
		(
		ConstIXIDRef r
		) const
{
	if ( m_iidHash != r.m_iidHash )
		return false;
	else
		return m_iid == r.m_iid;
}



inline
bool	IXID::Equals
		(
		const char*	s
		) const
{
	return m_iid == s;
}


#endif // 0





}}



#endif /* _H_IXID */
