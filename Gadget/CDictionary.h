/*---------------------------------------------------------------------+\
|
|	CDictionary.h  --  brief description of what CDictionary.h is for
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the psuedo-interface VVariable
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add functionality deal with an immediate millisecond calculation
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add GetMilliseconds
	28-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictionary
#define _H_CDictionary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include <time.h>
//#include <sys/types.h>

#include "VDictionaryPageServer.h"
#include "CVariables.h"

#include "VDictionaryPage.h"
#include "TArray.h"

namespace Yogi { namespace Gadget {
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

class CDictionaryEnumerator;	// forward declaration

typedef class CDictionary*		CDictionaryPtr;
typedef class CDictionary&		CDictionaryRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictionary : public VDictionaryPageServer,
					public virtual Yogi::Common::VVariable
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictionary();
	virtual			~CDictionary();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void				SetPushPage( char c );
	void				SetDictionaryPage( char c, VDictionaryPagePtr pPage );

protected:
//	protected types  ----------------------------------------------------

	friend class CDictionaryEnumerator;

	static const long	kPageCount = ('Z' - 'A' + 1);

//	protected functions  ------------------------------------------------

	void				LazyMilliseconds( void );

//	protected data  -----------------------------------------------------

	bool				m_bDirty;				// data in dictionary pages has changed
	VDictionaryPagePtr	m_aPages[kPageCount];	// to handle the pages (A-Z)
	char				m_cPushPage;
	long				m_nPushCount;

	long				m_nMilli;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionary
public:
	virtual void			BeginCalculate( void );
	virtual void			EndCalculate( void );

	virtual Selector		LocateEntry( Yogi::Core::ConstCCharStringRef rName );
	virtual Selector		LocateEntry( const char* sName );
	virtual Yogi::Common::ConstCVariantDataPtr
							GetData( Selector nSel );
	virtual bool			PutData( Selector nSel, Yogi::Common::ConstCVariantDataPtr pData );
	virtual bool			IsDataLocked( Selector nSel );

	virtual	bool			PushDictionaryPage( VDictionaryPage* pDict );
	virtual bool			PopDictionaryPage( void );


	virtual bool			IsDirty( void );
	virtual long			GetMilliseconds( void );

	// application dictionary is type = 'A'
	virtual int				GetType( void );	// return type of dictionary
	virtual VDictionaryEnumerator*
							GetEnumerator( void );
	virtual VDictionaryEnumerator*
							GetPageEnumerator( char cPageID );

	virtual Yogi::Common::VVariablePtr
							GetVariableIF( void );

	//	VDictionaryPageServer
	virtual void			ClearMilliseconds( void );
	virtual void			SetDirty( bool bDirty = true );
	virtual VDictionary::Selector
							MakeSelector( char cPageID, long id );


	//	VVariables
public:
	virtual
	Yogi::Core::CCharString
			ResolveVariable
			(
			Yogi::Core::ConstCCharDescriptorRef	r
			) const;

};





class CDictionaryEnumerator : public VDictionaryEnumerator
{
public:
			CDictionaryEnumerator( CDictionary* p );
	virtual ~CDictionaryEnumerator( void );

public:

	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual	const Yogi::Common::CVariantData*
							Current( void );

	virtual long			ID( void );
	virtual Yogi::Core::CCharString
							Key( void );
	virtual Yogi::Common::CVariantData
							Value( void );
	virtual char			Page( void );

protected:

	CDictionary*	m_pDictionary;
	VDictionaryEnumerator*
					m_pEnumPage;
	long			m_nIndex;
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

#endif /* _H_CDictionary */
