/*---------------------------------------------------------------------+\
|
|	CDictPageSystem.h  --  brief description of what CDictPageSystem.h is for
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
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageSystem
#define _H_CDictPageSystem
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionaryPage.h"

#include "TDictionaryIndexed.h"
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
class CDictPageSystemEnumerator;	// forward reference

typedef class CDictPageSystem*			CDictPageSystemPtr;
typedef class CDictPageSystem&			CDictPageSystemRef;
typedef const class CDictPageSystem&	ConstCDictPageSystemRef;


typedef class VDictPageHandler*			VDictPageHandlerPtr;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VDictPageHandler
{
public:
				VDictPageHandler() : m_tData() {}
	virtual		~VDictPageHandler(){};

public:
	virtual bool			BeginCalculate( CDictPageSystemPtr pPage ) = 0;
	virtual bool			EndCalculate( CDictPageSystemPtr pPage ) = 0;
	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage ) = 0;
	virtual bool			PutData( CDictPageSystemPtr pPage, CVariantDataPtr pData ) = 0;

protected:
	CVariantData		m_tData;

};




class CDictPageSystem : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageSystem();
	virtual			~CDictPageSystem();

	friend class VDictPageHandler;

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	bool	AddEntryPageHandler( const char* sName, VDictPageHandlerPtr pHandler );

protected:
//	protected types  ----------------------------------------------------

	friend class CDictPageSystemEnumerator;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< CCharString, VDictPageHandlerPtr>	m_aContent;



private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual void	BeginCalculate( void );
	virtual void	EndCalculate( void );
	virtual long	LocateEntry( ConstCCharStringRef rName );
	virtual CVariantDataPtr
					GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, CVariantDataPtr pData );
	virtual bool	UpdateByName( CCharDescriptorRef rKey, CVariantDataRef rData );
	virtual bool	AddAlias( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rAlias );

	virtual VDictionaryEnumerator*
					GetEnumerator( void );

};



/*---------------------------------------------------------------------+\
|	class CDictPageSystemEnumerator
\+---------------------------------------------------------------------*/
class CDictPageSystemEnumerator : public VDictionaryEnumerator
{
public:
			CDictPageSystemEnumerator( CDictPageSystem* p );
	virtual	~CDictPageSystemEnumerator( void );

public:

	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual CVariantData*	Current( void );
	virtual long			ID( void );
	virtual CCharString		Key( void );
	virtual CVariantData	Value( void );
	virtual	char			Page( void );

protected:

	CDictPageSystem*
					m_pPage;
	TDictionaryIndexedEnumerator<CCharString, VDictPageHandlerPtr>
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



#endif /* _H_CDictPageSystem */
