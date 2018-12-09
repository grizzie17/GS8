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
	virtual bool	Update( CCharDescriptorRef rKey, CCharDescriptorRef rData );
	virtual bool	Update( unsigned long nSel, CCharDescriptorRef rData );

	void			ResetAllEntries( void );

protected:
//	protected types  ----------------------------------------------------

	friend class CDictPageAlertsEnumerator;

	typedef struct AlertInfo
	{
		CDictionarySelector	sel;
		CVariantData		v;

		AlertInfo( void ) : sel(), v() {}
		AlertInfo( long n ) : sel(), v( n ) {}
	} AlertInfo;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< CCharString, AlertInfo>	m_aContent;
	CDictPageEventsPtr		m_pEventsPage;

	CDictionarySelector		m_tAlertSelector;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	// returns negative for error
	virtual long	LocateEntry( ConstCCharStringRef rName );

	virtual CVariantDataPtr
					GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, CVariantDataPtr pData );

	virtual bool	AddEntry( ConstCCharDescriptorRef rKey, ConstCVariantDataRef rData );
	//virtual bool	AddEntry( const char* sName, const char* sData );
	virtual bool	AddEntry( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rData );

	virtual bool	UpdateByName( CCharDescriptorRef rKey, CVariantDataRef rData );
	virtual bool	UpdateEntry( unsigned long nSel, CVariantDataRef rData );

	virtual bool	AddAlias( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rAlias );

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

	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual CVariantData*	Current( void );
	virtual long			ID( void );
	virtual CCharString		Key( void );
	virtual CVariantData	Value( void );
	virtual	char			Page( void );

protected:

	CDictPageAlerts*
					m_pPage;
	TDictionaryIndexedEnumerator<CCharString, CDictPageAlerts::AlertInfo>
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
