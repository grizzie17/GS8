/*---------------------------------------------------------------------+\
|
|	CDictPageVariant.h  --  Contained Data is CVariantData
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
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Change the arguments to AddAlias to be 'const'
	08-Jan-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for new template Dictionary Page.
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add CCharDescriptor variations of Add and Update entries
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageVariant
#define _H_CDictPageVariant
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionaryPage.h"

#include "TDictionaryIndexed.h"
#include "CVisible.h"
#include "CVariantData.h"
#include "CCharStringHash.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
class CDictPageVariantEnumerator;	// forward declaration

typedef class CDictPageVariant*			CDictPageVariantPtr;
typedef class CDictPageVariant&			CDictPageVariantRef;
typedef const class CDictPageVariant&	ConstCDictPageVariantRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageVariant : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageVariant();
	virtual			~CDictPageVariant();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

	friend class CDictPageVariantEnumerator;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< CCharString, CVariantData>	m_aContent;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:

	virtual bool	AddEntry( ConstCCharDescriptorRef rKey, ConstCVariantDataRef rData );

	// returns negative for error
	virtual long	LocateEntry( ConstCCharStringRef rName );

	virtual CVariantDataPtr
					GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, CVariantDataPtr pData );

	virtual bool	UpdateByName( CCharDescriptorRef rKey, CVariantDataRef rData );
	virtual bool	UpdateEntry( unsigned long nSel, CVariantDataRef rData );
	virtual bool	AddAlias( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rAlias );

	virtual VDictionaryEnumerator*
					GetEnumerator( void );

};


/*---------------------------------------------------------------------+\
|	class CDictPageVariantEnumerator
\+---------------------------------------------------------------------*/
class CDictPageVariantEnumerator : public VDictionaryEnumerator
{
public:
			CDictPageVariantEnumerator( CDictPageVariant* p );
	virtual	~CDictPageVariantEnumerator( void );

public:

	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual CVariantData*	Current( void );
	virtual long			ID( void );
	virtual CCharString		Key( void );
	virtual CVariantData	Value( void );
	virtual	char			Page( void );

protected:

	CDictPageVariant*
					m_pPage;
	TDictionaryIndexedEnumerator<CCharString, CVariantData>
					m_eList;
	index_t			m_nIndex;

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


NAMESPACE_GADGET_END



#endif /* _H_CDictPageVariant */

