/*---------------------------------------------------------------------+\
|
|	CDictPageConfigWrapper.h  --  Contained Data is CConfiguration
|
|	Purpose:
		Wrapper the Configuration file parameters

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
#ifndef _H_CDictPageConfigWrapper
#define _H_CDictPageConfigWrapper
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
#include "CConfiguration.h"



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
class CDictPageConfigWrapperEnumerator;	// forward declaration

typedef class CDictPageConfigWrapper*			CDictPageConfigWrapperPtr;
typedef class CDictPageConfigWrapper&			CDictPageConfigWrapperRef;
typedef const class CDictPageConfigWrapper&	ConstCDictPageConfigWrapperRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageConfigWrapper : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
			CDictPageConfigWrapper();
	virtual	~CDictPageConfigWrapper();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	AddEntry( const char* sName, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	AddEntry( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );

	virtual bool	SetConfiguration( Yogi::Common::CConfigurationPtr pConfig );

protected:
//	protected types  ----------------------------------------------------

	friend class CDictPageConfigWrapperEnumerator;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::CConfigurationPtr	m_pConfig;

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
	virtual bool	PutData( unsigned long nSel, const Yogi::Common::CVariantData* pData );

	virtual bool	UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	UpdateEntry( unsigned long nSel, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

	virtual VDictionaryEnumerator*
					GetEnumerator( void );

};


/*---------------------------------------------------------------------+\
|	class CDictPageConfigWrapperEnumerator
\+---------------------------------------------------------------------*/
class CDictPageConfigWrapperEnumerator : public VDictionaryEnumerator
{
public:
			CDictPageConfigWrapperEnumerator( CDictPageConfigWrapper* p );
	virtual	~CDictPageConfigWrapperEnumerator( void );

public:

	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual const Yogi::Common::CVariantData*	Current( void );
	virtual long			ID( void );
	virtual Yogi::Core::CCharString		Key( void );
	virtual Yogi::Common::CVariantData	Value( void );
	virtual	char			Page( void );

protected:

	CDictPageConfigWrapper*
					m_pPage;
	Yogi::Common::CConfiguration::Enumerator
					m_eList;
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



#endif /* _H_CDictPageConfigWrapper */
