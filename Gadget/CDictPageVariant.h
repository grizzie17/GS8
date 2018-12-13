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

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
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

	Yogi::Common::TDictionaryIndexed< Yogi::Core::CCharString, Yogi::Common::CVariantData>	m_aContent;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:

	virtual bool	AddEntry( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );

	// returns negative for error
	virtual long	LocateEntry( Yogi::Core::ConstCCharStringRef rName );

	virtual Yogi::Common::CVariantDataPtr
					GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, const Yogi::Common::CVariantData* pData );

	virtual bool	UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	UpdateEntry( unsigned long nSel, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

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

	virtual bool						MoveNext( void );
	virtual void						Reset( void );
	virtual const Yogi::Common::CVariantData*	Current( void );
	virtual long						ID( void );
	virtual Yogi::Core::CCharString		Key( void );
	virtual Yogi::Common::CVariantData	Value( void );
	virtual	char						Page( void );

protected:

	CDictPageVariant*
					m_pPage;
	Yogi::Common::TDictionaryIndexedEnumerator<Yogi::Core::CCharString, Yogi::Common::CVariantData>
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


}}



#endif /* _H_CDictPageVariant */
