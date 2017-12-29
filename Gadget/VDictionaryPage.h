/*---------------------------------------------------------------------+\
|
|	VDictionaryPage.h  --  root class for all Dictionary Pages
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
	12-Nov-2015			J.Griswold		(Reviewed by: xxx)
		Change nSel to be unsigned long
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Change the arguments to AddAlias to be 'const'
	08-Jan-2009			J.Griswold		(Reviewed by: M.Rose)
		Support a new Template class of VDictionaryPage that will
		deal some more of the common functions.
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	21-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for new "standardized" update functionality
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for enumeration
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VDictionaryPage
#define _H_VDictionaryPage
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CVariantData.h"
#include "VDictionaryPageServer.h"
#include "TDictionaryIndexed.h"
#include "CMutex.h"
#include "NamespaceGadget.h"
#include "LogFile.h"
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
NAMESPACE_GADGET_BEGIN

class VDictionaryEnumerator;	// forward reference

typedef class VDictionaryPage*		VDictionaryPagePtr;
typedef class VDictionaryPage&		VDictionaryPageRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					VDictionaryPage();
	virtual			~VDictionaryPage();
	virtual long	AddRef();
	virtual long	Release();
	virtual long	RefCount();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


	virtual void	BeginCalculate( void ) {};
	virtual void	EndCalculate( void ) {};

	virtual bool	AddEntry( ConstCCharDescriptorRef rKey, ConstCVariantDataRef rData );
			bool	AddEntry( const char* sName, ConstCVariantDataRef rData );
			bool	AddEntry( const char* sName, const char* sData );
			bool	AddEntry( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rData );

	virtual long	LocateEntry( ConstCCharStringRef rName ) = 0;
			long	LocateEntry( const char* sName );
	virtual CVariantDataPtr
					GetData( unsigned long nSel ) = 0;
	virtual bool	PutData( unsigned long nSel, CVariantDataPtr pData ) = 0;


			bool	UpdateByName( const char* sName, CVariantDataRef rData );
	virtual bool	UpdateByName( CCharDescriptorRef rKey, CVariantDataRef rData ) = 0;
	virtual bool	UpdateEntry( unsigned long nSel, CVariantDataRef rData );

			bool	AddAlias( const char* sKey, const char* sAlias );
	virtual bool	AddAlias( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rAlias ) = 0;

	virtual bool	IsDataLocked( unsigned long nSel );

	virtual bool	SetPageID( char c );
	virtual bool	SetDictionary( VDictionaryPageServerPtr pDict );
	virtual VDictionaryPageServerPtr
					Dictionary( void );

	virtual VDictionaryEnumerator*
					GetEnumerator( void ) = 0;



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	char						m_cPageID;
	long						m_nRefCount;	// when count goes to zero (via Release) object is deleted.
	VDictionaryPageServerPtr	m_pDictionary;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};


template < class TDATUM >
class TDictionaryPage : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					TDictionaryPage();
	virtual			~TDictionaryPage();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< CCharString, TDATUM>	m_aContent;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

	//	VDictionaryPage
public:
	virtual long	LocateEntry( ConstCCharStringRef rName );
	virtual bool	AddAlias( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rAlias );

	virtual bool	UpdateByName( CCharDescriptorRef rKey, CVariantDataRef rData );

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


template < class TDATUM >
TDictionaryPage<TDATUM>::TDictionaryPage
		(
		void
		)
		:  VDictionaryPage(),
		m_aContent()
{
}


template < class TDATUM >
TDictionaryPage<TDATUM>::~TDictionaryPage
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
template < class TDATUM >
long	TDictionaryPage<TDATUM>::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	return m_aContent.IndexOf( rName );
}



/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
template < class TDATUM >
bool	TDictionaryPage<TDATUM>::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	CCharString	tKey( rKey );
	CCharString	tAlias( rAlias );
	return m_aContent.AddAlias( tKey, tAlias );
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
template < class TDATUM >
bool	TDictionaryPage<TDATUM>::UpdateByName
		(
		CCharDescriptorRef	rKey,
		CVariantDataRef		rData
		)
{
	bool	bResult = false;
	long	n = m_aContent.IndexOf( CCharString( rKey ) );
	if ( -1 < n )
	{
		bResult = UpdateEntry( n, rData );
	}
	return bResult;
}





NAMESPACE_GADGET_END


#endif /* _H_VDictionaryPage */

