/*---------------------------------------------------------------------+\
|
|	CDictPageAlerts.h  --  Dictionary page handling Alerts
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
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for reseting all of the entries to a default value
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageAlerts
#define _H_CDictPageAlerts
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
#include "CDictionarySelector.h"
#include "CDictPageEvents.h"

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
class CDictPageAlertsEnumerator;	// forward declaration

typedef class CDictPageAlerts*			CDictPageAlertsPtr;
typedef class CDictPageAlerts&			CDictPageAlertsRef;
typedef const class CDictPageAlerts&	ConstCDictPageAlertsRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageAlerts : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageAlerts();
	virtual			~CDictPageAlerts();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	Update( const char* sName, const char* sData );
	virtual bool	Update( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rData );
	virtual bool	Update( unsigned long nSel, Yogi::Core::ConstCCharDescriptorRef rData );

	void			ResetAllEntries( void );

protected:
//	protected types  ----------------------------------------------------

	friend class CDictPageAlertsEnumerator;

	typedef struct AlertInfo
	{
		CDictionarySelector			sel;
		Yogi::Common::CVariantData	v;

		AlertInfo( void ) : sel(), v() {}
		AlertInfo( long n ) : sel(), v( n ) {}
	} AlertInfo;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::TDictionaryIndexed< Yogi::Core::CCharString, AlertInfo>	m_aContent;
	CDictPageEventsPtr		m_pEventsPage;

	CDictionarySelector		m_tAlertSelector;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	// returns negative for error
	virtual long	LocateEntry( Yogi::Core::ConstCCharStringRef rName );

	virtual Yogi::Common::CVariantDataPtr
					GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, Yogi::Common::CVariantDataPtr pData );

	virtual bool	AddEntry( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	//virtual bool	AddEntry( const char* sName, const char* sData );
	virtual bool	AddEntry( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rData );

	virtual bool	UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	UpdateEntry( unsigned long nSel, Yogi::Common::ConstCVariantDataRef rData );

	virtual bool	AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

	virtual VDictionaryEnumerator*
					GetEnumerator( void );

};



/*---------------------------------------------------------------------+\
|	class CDictPageAlertsEnumerator
\+---------------------------------------------------------------------*/
class CDictPageAlertsEnumerator : public VDictionaryEnumerator
{
public:
			CDictPageAlertsEnumerator( CDictPageAlerts* p );
	virtual	~CDictPageAlertsEnumerator( void );

public:

	virtual bool						MoveNext( void );
	virtual void						Reset( void );
	virtual const Yogi::Common::CVariantData*	Current( void );
	virtual long						ID( void );
	virtual Yogi::Core::CCharString		Key( void );
	virtual Yogi::Common::CVariantData	Value( void );
	virtual	char						Page( void );

protected:

	CDictPageAlerts*
					m_pPage;
	Yogi::Common::TDictionaryIndexedEnumerator<Yogi::Core::CCharString, CDictPageAlerts::AlertInfo>
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



#endif /* _H_CDictPageAlerts */
