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
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageSystemPtr pPage ) = 0;
	virtual bool			PutData( CDictPageSystemPtr pPage, Yogi::Common::ConstCVariantDataPtr pData ) = 0;

protected:
	Yogi::Common::CVariantData	m_tData;

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

	Yogi::Common::TDictionaryIndexed< Yogi::Core::CCharString, VDictPageHandlerPtr>	m_aContent;



private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual void	BeginCalculate( void );
	virtual void	EndCalculate( void );
	virtual long	LocateEntry( Yogi::Core::ConstCCharStringRef rName ) const;
	virtual Yogi::Common::CVariantDataPtr
					GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, Yogi::Common::ConstCVariantDataPtr pData );
	virtual bool	UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

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
	virtual const Yogi::Common::CVariantData*	Current( void );
	virtual long			ID( void );
	virtual Yogi::Core::CCharString		Key( void );
	virtual Yogi::Common::CVariantData	Value( void );
	virtual	char			Page( void );

protected:

	CDictPageSystem*
					m_pPage;
	Yogi::Common::TDictionaryIndexedEnumerator<Yogi::Core::CCharString, VDictPageHandlerPtr>
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
