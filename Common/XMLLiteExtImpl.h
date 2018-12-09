/*---------------------------------------------------------------------+\
|
|	XMLLiteExtImpl.h  --  brief description of what XMLLiteExtImpl.h is for
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
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to using UFloat.h to identify if we are building
		with fixed-point or not
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	10-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		call the time parse routine to handle date processing
		instead of doing the code directly.
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix problem in the NodeValueAsXxxxArray functions.  Basically,
		it would always fail because the condition for the list
		separator would always fail.
		Address a GCC++ limitation that requires the use of the "this"
		pointer to access the base class of a template class.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add NodeValueAsFloatArray and IntegerArray functions
	21-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_XMLLiteExtImpl
#define _H_XMLLiteExtImpl
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "XMLLiteImpl.h"

#include "CDateTime.h"


namespace Yogi { namespace XMLLite {

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
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

template < class T >
class TTokenizerExt : public TTokenizer<T>
{
//	class lifecycle  ----------------------------------------------------
public:
					TTokenizerExt();
	virtual			~TTokenizerExt();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual Yogi::Core::CDateTime	NodeValueAsDate( void );

	virtual long		NodeValueAsIntegerArray( long* pArray, long nSize );
	virtual long		NodeValueAsFloatArray( GFLOAT* pArray, long nSize );

	virtual Yogi::Core::CDateTime	AttributeValueAsDate( const char* sName );
	virtual Yogi::Core::CDateTime	AttributeValueAsDate( int idx );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	Yogi::Core::CDateTime	DateFromDescriptor( Yogi::Core::TCharDescriptor<T>& r );

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};



/*---------------------------------------------------------------------+\
|	template TIteratorExt												|
\+---------------------------------------------------------------------*/

template < class T, class TTok >
class TIteratorExt : public TIterator<T, TTok>
{
//	class lifecycle  ----------------------------------------------------
public:
				TIteratorExt( TTok* pTokenizer );
				TIteratorExt( VIterator<T, TTok>* p );
				TIteratorExt( VIterator<T, TTok>& r );
	virtual		~TIteratorExt();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual Yogi::Core::CDateTime	NodeValueAsDate( void );

	virtual long		NodeValueAsIntegerArray( long* pArray, long nSize );
	virtual long		NodeValueAsFloatArray( GFLOAT* pArray, long nSize );

	virtual Yogi::Core::CDateTime	AttributeValueAsDate( const char* sName );
	virtual Yogi::Core::CDateTime	AttributeValueAsDate( int idx );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

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


/*=====================================================================+\
||	TIteratorExt Functions												|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * TIteratorExt - constructor

\+---------------------------------------------------------------------*/
template < class T, class TTok >
TIteratorExt<T,TTok>::TIteratorExt
		(
		TTok*	pTokenizer
		)
		: TIterator<T,TTok>( pTokenizer )
{
}


/*---------------------------------------------------------------------+\

 * TIteratorExt - copy constructor

\+---------------------------------------------------------------------*/
template < class T, class TTok >
TIteratorExt<T,TTok>::TIteratorExt
		(
		VIterator<T,TTok>&	r
		)
		: TIterator<T,TTok>( r )
{
}


/*---------------------------------------------------------------------+\

 * TIteratorExt - constructor

\+---------------------------------------------------------------------*/
template < class T, class TTok >
TIteratorExt<T,TTok>::TIteratorExt
		(
		VIterator<T,TTok>*	p
		)
		: TIterator<T,TTok>( p )
{
}


/*---------------------------------------------------------------------+\

 * ~TIteratorExt - destructor

\+---------------------------------------------------------------------*/
template < class T, class TTok >
TIteratorExt<T,TTok>::~TIteratorExt
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * NodeValueAsDate -

\+---------------------------------------------------------------------*/
template < class T, class TTok >
Yogi::Core::CDateTime
		TIteratorExt<T,TTok>::NodeValueAsDate
		(
		void
		)
{
	return this->m_pTokenizer->NodeValueAsDate();
}


/*---------------------------------------------------------------------+\

 * NodeValueAsIntegerArray -

\+---------------------------------------------------------------------*/
template < class T, class TTok >
long	TIteratorExt<T,TTok>::NodeValueAsIntegerArray
		(
		long*	pArray,
		long	nSize
		)
{
	return this->m_pTokenizer->NodeValueAsIntegerArray( pArray, nSize );
}


/*---------------------------------------------------------------------+\

 * NodeValueAsFloatArray -

\+---------------------------------------------------------------------*/
template < class T, class TTok >
long	TIteratorExt<T,TTok>::NodeValueAsFloatArray
		(
		GFLOAT*	pArray,
		long	nSize
		)
{
	return this->m_pTokenizer->NodeValueAsFloatArray( pArray, nSize );
}


/*---------------------------------------------------------------------+\

 * AttributeValueAsDate -

\+---------------------------------------------------------------------*/
template < class T, class TTok >
Yogi::Core::CDateTime
		TIteratorExt<T,TTok>::AttributeValueAsDate
		(
		int	idx
		)
{
	return this->m_pTokenizer->AttributeValueAsDate( idx );
}


/*---------------------------------------------------------------------+\

 * AttributeValueAsDate -

\+---------------------------------------------------------------------*/
template < class T, class TTok >
Yogi::Core::CDateTime
		TIteratorExt<T,TTok>::AttributeValueAsDate
		(
		const char*	sName
		)
{
	return this->m_pTokenizer->AttributeValueAsDate( sName );
}


/*=====================================================================+\
||	TTokenizerExt Functions												|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * TTokenizerExt - constructor

\+---------------------------------------------------------------------*/
template < class T >
TTokenizerExt<T>::TTokenizerExt
		(
		void
		)
		: TTokenizer<T>()
{
}

/*---------------------------------------------------------------------+\

 * ~TTokenizerExt - destructor

\+---------------------------------------------------------------------*/
template < class T >
TTokenizerExt<T>::~TTokenizerExt
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * NodeValueAsDate -

\+---------------------------------------------------------------------*/
template < class T >
Yogi::Core::CDateTime
		TTokenizerExt<T>::NodeValueAsDate
		(
		void
		)
{
	Yogi::Core::CDateTime			tResult;
	Yogi::Core::TCharDescriptor<T>	tValue;
	tValue = this->NodeValue();
	if ( 0 < tValue.Length() )
		return DateFromDescriptor( tValue );
	else
		return tResult;
}


/*---------------------------------------------------------------------+\

 * NodeValueAsIntegerArray -

\+---------------------------------------------------------------------*/
template < class T >
long	TTokenizerExt<T>::NodeValueAsIntegerArray
		(
		long*	pArray,
		long	nSize
		)
{
	long	nResult = 0;
	long*	pStart = pArray;
	long*	pEnd = pStart + nSize;
	Yogi::Core::TCharDescriptor<T>	tValue;
	tValue = this->NodeValue();
	const T*	s = tValue.Pointer();
	const T*	sEnd = s + tValue.Length();
	long	nValue;
	long	n;

	while ( s < sEnd )
	{
		s += this->SpanBlanks( s, sEnd );

		n = this->SpanNumber( s, sEnd, &nValue );
		if ( 0 < n )
		{
			if ( pArray < pEnd )
			{
				*pArray = nValue;
				++pArray;
			}
			++nResult;
		}
		s += n;

		s += this->SpanBlanks( s, sEnd );

		if ( ',' == *s  ||  ';' == *s )
			++s;
		else
			break;
	}

	if ( s < sEnd )
		nResult = 0;

	return nResult;
}



/*---------------------------------------------------------------------+\

 * NodeValueAsFloatArray -

\+---------------------------------------------------------------------*/
template < class T >
long	TTokenizerExt<T>::NodeValueAsFloatArray
		(
		GFLOAT*	pArray,
		long	nSize
		)
{
	long		nResult = 0;
	GFLOAT*		pStart = pArray;
	GFLOAT*		pEnd = pStart + nSize;
	Yogi::Core::TCharDescriptor<T>	tValue;
	tValue = this->NodeValue();
	const T*	s = tValue.Pointer();
	const T*	sEnd = s + tValue.Length();
	GFLOAT		fValue;
	long		n;

	while ( s < sEnd )
	{
		s += this->SpanBlanks( s, sEnd );

		n = this->SpanFloat( s, sEnd, &fValue );
		if ( 0 < n )
		{
			if ( pArray < pEnd )
			{
				*pArray = fValue;
				++pArray;
			}
			++nResult;
		}
		s += n;

		s += this->SpanBlanks( s, sEnd );

		if ( ',' == *s  ||  ';' == *s )
			++s;
		else
			break;
	}

	if ( s < sEnd )
		nResult = 0;

	return nResult;
}



/*---------------------------------------------------------------------+\

 * AttributeValueAsDate -

\+---------------------------------------------------------------------*/
template < class T >
Yogi::Core::CDateTime
		TTokenizerExt<T>::AttributeValueAsDate
		(
		const char*	sName
		)
{
	Yogi::Core::TCharDescriptor<T>	tValue;

	tValue = this->AttributeValue( sName );
	if ( 0 < tValue.Length() )
		return DateFromDescriptor( tValue );
	else
		return Yogi::Core::CDateTime();
}



/*---------------------------------------------------------------------+\

 * AttributeValueAsDate -

\+---------------------------------------------------------------------*/
template < class T >
Yogi::Core::CDateTime
		TTokenizerExt<T>::AttributeValueAsDate
		(
		int idx
		)
{
	Yogi::Core::TCharDescriptor<T>	tValue;

	tValue = this->AttributeValue( idx );
	if ( 0 < tValue.Length() )
		return DateFromDescriptor( tValue );
	else
		return Yogi::Core::CDateTime();
}



/*---------------------------------------------------------------------+\

 * DateFromDescriptor -

\+---------------------------------------------------------------------*/
template < class T >
Yogi::Core::CDateTime
		TTokenizerExt<T>::DateFromDescriptor
		(
		Yogi::Core::TCharDescriptor<T>&	r
		)
{
	Yogi::Core::CDateTime	tTime;

	tTime.Parse( r.Pointer() );

	return tTime;
}



}}



#endif /* _H_XMLLiteExtImpl */

