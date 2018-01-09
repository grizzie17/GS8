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
//#include <string>
#include "CCharDescriptor.h"

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
typedef class CCharString*			CCharStringPtr;
typedef class CCharString&			CCharStringRef;
typedef const class CCharString&	ConstCCharStringRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCharString : public CCharDescriptor
{
//	class lifecycle  ----------------------------------------------------
public:
					CCharString();
					CCharString( ConstCCharStringRef r );	// copy constructor
					CCharString( ConstCCharDescriptorRef r );
					CCharString( const char* s );
					CCharString( const char* s, size_t n );
	virtual			~CCharString();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CCharStringRef	operator=( ConstCCharStringRef r );		// assignment
	CCharStringRef	operator=( ConstCCharDescriptorRef r );
	CCharStringRef	operator=( const char* s );
	CCharStringRef	operator+=( ConstCCharDescriptorRef r );
	CCharStringRef	operator+=( const char* s );

	//operator char* ( void ) const;
	//operator const char* ( void );
	//operator CCharString ( void );
	operator CCharDescriptor ( void ) const;
	operator ConstCCharDescriptorRef ( void ) const;
	operator const CCharDescriptorPtr ( void ) const;
	//operator CCharDescriptorPtr ( void ) const;

	//bool	operator==( const char* s );
	//bool	operator==( ConstCCharStringRef r );


	//size_t	Length( void );
	//int		Compare( const char* s );
	//int		Compare( ConstCCharStringRef r );

	bool			Append( const char* s );
	bool			Append( ConstCCharStringRef r );
	bool			Append( ConstCCharDescriptorRef r );
	bool			Append(	float	f);
	bool			AppendFormat( const char* sFormat, ... );

	CCharStringRef	Format( const char* sFormat, ... );

	//unsigned long	Hash( void ) const;


	void	ClearString( void );
	bool	LoadCCharString( ConstCCharStringRef r );
	bool	LoadCCharDescriptor( ConstCCharDescriptorRef r );
	bool	LoadStringData( const char* s, index_t n = -1 );
	bool	AppendStringData( const char* s, index_t n );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


	bool	ValidAddr( const char*	s );

//	protected data  -----------------------------------------------------

private:
	typedef	CCharDescriptor	inherited;

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
		CCharString::operator =
		(
		const char* s
		)
{
	LoadStringData( s );
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
inline
CCharString::operator ConstCCharDescriptorRef
		(
		void
		) const
{
	return (ConstCCharDescriptorRef)*this;
}

inline
CCharString::operator const CCharDescriptorPtr
		(
		void
		) const
{
	return (const CCharDescriptorPtr) this;
}

//inline
//CCharString::operator CCharDescriptorPtr
//		(
//		void
//		) const
//{
//	return (CCharDescriptorPtr) this;
//}

inline
CCharString::operator CCharDescriptor
		(
		void
		) const
{
	return CCharDescriptor( m_s, m_n );
}




NAMESPACE_COMMON_END



#endif /* _H_CCharString */

