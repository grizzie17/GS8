//=====================================================================//
//!
//!	@file	CCharString.h
//!	@brief	Class encapsulating a character string
//!
//!	@note	unlike the 'descriptor' classes this class does manage
//! 		the memory
//! 
//!	@see	CCharDescriptor.h
//!
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	01-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add AppendFormat function which operates like the Format function
		except that it appends the current contents.
	28-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Change hierarchy to separate descriptor (non-memory control)
		into a different class.
	27-Aug-2009			J.Griswold
		Add support for new Format method that operates as a printf
		type functionality for loading the string.
	15-Aug-2009			J.Griswold
		Add "Append" function and "+=" operator
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCharString_Root
#define _H_CCharString_Root
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <c++/string>
#include "CCharDescriptor.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CCharString*			CCharStringPtr;
typedef class CCharString&			CCharStringRef;
typedef const class CCharString&	ConstCCharStringRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCharString : public std::string
{
//	class lifecycle  ----------------------------------------------------
public:
					CCharString();
					CCharString( ConstCCharStringRef r );	// copy constructor
					CCharString( ConstCCharDescriptorRef r );
					CCharString( const char* s );
					CCharString( const char* s, size_t n );
					CCharString( const std::string& r );
	virtual			~CCharString();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CCharStringRef	operator=( ConstCCharStringRef r );		// assignment
	CCharStringRef	operator=( ConstCCharDescriptorRef r );
	CCharStringRef	operator=( const char* s );
	CCharStringRef	operator=( const std::string& r );
	CCharStringRef	operator+=( ConstCCharDescriptorRef r );
	CCharStringRef	operator+=( const char* s );

	//operator char* ( void ) const;
	//operator const char* ( void );
	//operator CCharString ( void );
	operator const CCharDescriptor ( void ) const;
	//operator ConstCCharDescriptorRef ( void ) const;
	//operator const CCharDescriptorPtr ( void ) const;
	//operator CCharDescriptorPtr ( void ) const;

	//bool	operator==( const char* s );
	//bool	operator==( ConstCCharStringRef r );


	size_t		Length( void ) const;
	const char*	Pointer( index_t n = 0 ) const;
	char		AtIndex( index_t n ) const;

	bool	Append( const char* s );
	bool	Append( ConstCCharStringRef r );
	bool	Append( ConstCCharDescriptorRef r );
	bool	Append(	float	f);
	bool	AppendFormat( const char* sFormat, ... );

	bool	CopyTo( char* s, size_t n ) const;
	bool	ConcatenateTo( char* s, size_t n ) const;

	int		Compare( ConstCCharStringRef r ) const;
	int		Compare( ConstCCharDescriptorRef r ) const;
	int		Compare( const char* s, size_t n ) const;
	int		Compare( const char* s ) const;
	int		Compare( const std::string& r ) const;

	int		CompareIgnoreCase( ConstCCharStringRef r ) const;
	int		CompareIgnoreCase( ConstCCharDescriptorRef r ) const;
	int		CompareIgnoreCase( const char* s, size_t n ) const;
	int		CompareIgnoreCase( const char* s ) const;
	//int		CompareIgnoreCase( const std::string& r ) const;

	void	ConvertUppercase( void );
	void	ConvertLowercase( void );



	CCharStringRef	Format( const char* sFormat, ... );




	void	ClearString( void );
	bool	LoadCCharString( ConstCCharStringRef r );
	bool	LoadCCharDescriptor( ConstCCharDescriptorRef r );
	bool	LoadStringData( const char* s, index_t n = -1 );
	bool	AppendStringData( const char* s, index_t n );

	//!	parse the descriptor
	long		ParseInt( size_t* pParseCount ) const;
	GFLOAT		ParseFloat( size_t* pParseCount ) const;

	uintmax_t	Hash( void ) const;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


	bool	ValidAddr( const char*	s );

//	protected data  -----------------------------------------------------

private:
	typedef	std::string	inherited;

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

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline
CCharStringRef
		CCharString::operator=
		(
		ConstCCharStringRef	r
		)
{
	LoadCCharString( r );
	return *this;
}


inline
CCharStringRef
		CCharString::operator=
		(
		ConstCCharDescriptorRef	r
		)
{
	LoadCCharDescriptor( r );
	return *this;
}


inline
CCharStringRef
		CCharString::operator=
		(
		const char* s
		)
{
	LoadStringData( s );
	return *this;
}


inline
CCharStringRef
		CCharString::operator=
		(
		const std::string&	r
		)
{
	this->assign( r );
	return *this;
}





/*---------------------------------------------------------------------+\

 * operator+= - append operator

\+---------------------------------------------------------------------*/
inline
CCharStringRef
		CCharString::operator +=
		(
		ConstCCharDescriptorRef r
		)
{
	Append( r );
	return *this;
}

inline
CCharStringRef
		CCharString::operator +=
		(
		const char* s
		)
{
	Append( s );
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator CCharDescriptorRef - cast operator

\+---------------------------------------------------------------------*/
// inline
// CCharString::operator ConstCCharDescriptorRef
// 		(
// 		void
// 		) const
// {
// 	return (ConstCCharDescriptorRef)*this;
// }

// inline
// CCharString::operator const CCharDescriptorPtr
// 		(
// 		void
// 		) const
// {
// 	return (const CCharDescriptorPtr) this;
// }

//inline
//CCharString::operator CCharDescriptorPtr
//		(
//		void
//		) const
//{
//	return (CCharDescriptorPtr) this;
//}

inline
CCharString::operator const CCharDescriptor
		(
		void
		) const
{
	return CCharDescriptor( c_str(), length() );
}


inline
const char* CCharString::Pointer( index_t n ) const
{
	if ( 0 <= n  &&  n < index_t(length()) )
		return c_str() + n;
	else
		return NULL;
}

inline
size_t CCharString::Length( void ) const
{
	return length();
}


}}



#endif /* _H_CCharString */

