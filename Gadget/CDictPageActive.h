/*---------------------------------------------------------------------+\
|
|	CDictPageActive.h  --  implementation of "Active" Engineering page
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
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	31-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for logging time of last update
		Add support for reseting values back to defaults.
	20-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for range checking in the UpdateData methods
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initialize the types for the datum classes to force the
		correct data type.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support the date/time type
	07-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for char-descriptors for add and update entry
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageActive
#define _H_CDictPageActive
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionaryPage.h"

#include "TDictionaryIndexed.h"
#include "CVariantData.h"
#include "CCharDescriptor.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "UFloat.h"

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
class CDictPageActiveEnumerator;	// forward declaration

typedef class CDictPageActive*			CDictPageActivePtr;
typedef class CDictPageActive&			CDictPageActiveRef;
typedef const class CDictPageActive&	ConstCDictPageActiveRef;


typedef class VDictPageActiveDatum*		VDictPageActiveDatumPtr;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/



/*---------------------------------------------------------------------+\
|	class VDictPageActiveDatum
\+---------------------------------------------------------------------*/

class VDictPageActiveDatum
{
public:
				VDictPageActiveDatum();
	virtual		~VDictPageActiveDatum();

public:
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageActivePtr pPage );
	virtual bool			UpdateData( CDictPageActivePtr pPage, const char* sXML ) = 0;
	virtual bool			UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
	virtual void			ResetData( CDictPageActivePtr pPage );
	virtual bool			SetUnits( int nUnits );
	virtual void			SetReferenced( void );
	virtual void			SetUnavailable( Yogi::Core::ConstCCharDescriptorRef r );
	virtual void			SetReset( Yogi::Core::ConstCCharDescriptorRef r );

protected:
	Yogi::Common::CVariantData	m_tData;
	VDictionary::Selector	m_nSelector;
	bool					m_bReferenced;
	Yogi::Core::CCharString	m_sReset;
	Yogi::Core::CCharString	m_sUnavailable;

};


/*---------------------------------------------------------------------+\
|	class CDictPageActive
\+---------------------------------------------------------------------*/

class CDictPageActive : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageActive();
	virtual			~CDictPageActive();

	friend class VDictPageHandler;

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	bool		AddDatumEntry( const char* sKey, VDictPageActiveDatumPtr pDatum );
	bool		AddDatumEntry( Yogi::Core::ConstCCharDescriptorRef rKey, VDictPageActiveDatumPtr pDatum );

	bool		BeginUpdate( void );
	bool		Update( const char* sKey, const char* sData );
	bool		Update( Yogi::Core::ConstCCharDescriptorRef rKey, const char* sData );
	bool		EndUpdate( void );

	void		SetDirty( void );

	void		ResetAllEntries( void );
	long		LastUpdate( void );

protected:
//	protected types  ----------------------------------------------------

	friend class CDictPageActiveEnumerator;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::TDictionaryIndexed< Yogi::Core::CCharString, VDictPageActiveDatumPtr>	m_aContent;
	long		m_nLastUpdate;



private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:

	virtual long			LocateEntry( Yogi::Core::ConstCCharStringRef rName );
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( unsigned long nSel );
	virtual bool			PutData( unsigned long nSel, Yogi::Common::ConstCVariantDataPtr pData );

	virtual bool			UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool			UpdateEntry( unsigned long nSel, Yogi::Common::ConstCVariantDataRef rData );

	virtual bool			AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

	virtual VDictionaryEnumerator*
							GetEnumerator( void );

};



/*---------------------------------------------------------------------+\
|	class CDictPageActiveEnumerator
\+---------------------------------------------------------------------*/
class CDictPageActiveEnumerator : public VDictionaryEnumerator
{
public:
			CDictPageActiveEnumerator( CDictPageActive* p );
	virtual	~CDictPageActiveEnumerator( void );

public:

	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual const Yogi::Common::CVariantData*	Current( void );
	virtual long			ID( void );
	virtual Yogi::Core::CCharString		Key( void );
	virtual Yogi::Common::CVariantData	Value( void );
	virtual	char			Page( void );

protected:

	CDictPageActive*
					m_pPage;
	Yogi::Common::TDictionaryIndexedEnumerator<Yogi::Core::CCharString, VDictPageActiveDatumPtr>
					m_eList;
	index_t			m_nIndex;

};






/*---------------------------------------------------------------------+\
|	class CDictPageActiveDatumBool
\+---------------------------------------------------------------------*/

class CDictPageActiveDatumBool : public VDictPageActiveDatum
{
public:
	CDictPageActiveDatumBool() : VDictPageActiveDatum()
	{
		m_tData = false;
		m_sReset = "F";
	};
	virtual	~CDictPageActiveDatumBool(){};

public:
	virtual bool	UpdateData( CDictPageActivePtr pPage, const char* sXML );
	virtual bool	UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
	virtual void	ResetData( CDictPageActivePtr pPage );
};

/*---------------------------------------------------------------------+\
|	class CDictPageActiveDatumInteger
\+---------------------------------------------------------------------*/

class CDictPageActiveDatumInteger : public VDictPageActiveDatum
{
public:
	CDictPageActiveDatumInteger()
		: VDictPageActiveDatum(),
		m_nLow( 0 ), m_nHigh( 0 ), m_nDelta( 0 ),
		m_nCheckType( 0 )
	{
		m_tData = 0L;
		m_sReset = "0";
	};
	virtual	~CDictPageActiveDatumInteger(){};

public:
	void	SetRange( long nLow, long nHigh );
	void	SetCheckType( int nType );

protected:
	long	AdjustInRange( long n );

	long	m_nLow;
	long	m_nHigh;
	long	m_nDelta;
	int		m_nCheckType;	// 0=none; 1=clip; 2=circular

public:
	virtual bool	UpdateData( CDictPageActivePtr pPage, const char* sXML );
	virtual bool	UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
	virtual void	ResetData( CDictPageActivePtr pPage );
};

/*---------------------------------------------------------------------+\
|	class CDictPageActiveDatumFloat
\+---------------------------------------------------------------------*/

class CDictPageActiveDatumFloat : public VDictPageActiveDatum
{
public:
	CDictPageActiveDatumFloat()
		: VDictPageActiveDatum(),
		m_fLow( 0.0f ), m_fHigh( 0.0f ), m_fDelta( 0.0f ),
		m_nCheckType( 0 )
	{
		m_tData = GFLOAT_0;
		m_sReset = "0.0";
	};
	virtual	~CDictPageActiveDatumFloat(){};

public:
	void	SetRange( GFLOAT fLow, GFLOAT fHigh );
	void	SetCheckType( int ntype );

protected:
	GFLOAT	adjustInRange( GFLOAT f );

	GFLOAT	m_fLow;
	GFLOAT	m_fHigh;
	GFLOAT	m_fDelta;
	int		m_nCheckType;	// 0=none; 1=clip; 2=circular

public:
	virtual bool	UpdateData( CDictPageActivePtr pPage, const char* sXML );
	virtual bool	UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
	virtual void	ResetData( CDictPageActivePtr pPage );
};

/*---------------------------------------------------------------------+\
|	class CDictPageActiveDatumString
\+---------------------------------------------------------------------*/

class CDictPageActiveDatumString : public VDictPageActiveDatum
{
public:
	CDictPageActiveDatumString() : VDictPageActiveDatum() { m_tData = "Uninitialized"; };
	virtual	~CDictPageActiveDatumString(){};

public:
	virtual bool	UpdateData( CDictPageActivePtr pPage, const char* sXML );
	virtual bool	UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
};

/*---------------------------------------------------------------------+\
|	class CDictPageActiveDatumEnum
\+---------------------------------------------------------------------*/

class CDictPageActiveDatumEnum : public VDictPageActiveDatum
{
public:
	CDictPageActiveDatumEnum();
	virtual	~CDictPageActiveDatumEnum(){};

public:
	bool	AddItem( const char* s );

protected:
	Yogi::Core::TArray<Yogi::Common::CVariantData>	m_aList;
	int						m_nEnumUnits;

public:
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageActivePtr pPage );
	virtual bool	UpdateData( CDictPageActivePtr pPage, const char* sXML );
	virtual bool	UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
	virtual void	ResetData( CDictPageActivePtr pPage );

};



/*---------------------------------------------------------------------+\
|	class CDictPageActiveDatumDate
\+---------------------------------------------------------------------*/

class CDictPageActiveDatumDate : public VDictPageActiveDatum
{
public:
	CDictPageActiveDatumDate() : VDictPageActiveDatum()
	{
		m_tData = Yogi::Core::CDateTime();
		m_nDelta = 0;
		m_bStale = false;
	};
	virtual	~CDictPageActiveDatumDate(){};

protected:
	time_t			m_nDelta;
	bool			m_bStale;

public:
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageActivePtr pPage );
	virtual bool	UpdateData( CDictPageActivePtr pPage, const char* sXML );
	virtual bool	UpdateData( CDictPageActivePtr pPage, Yogi::Common::ConstCVariantDataRef rData );
	virtual void	ResetData( CDictPageActivePtr pPage );
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

inline
void	CDictPageActive::SetDirty
		(
		void
		)
{
	if ( m_pDictionary )
		m_pDictionary->SetDirty( true );
}



}}



#endif /* _H_CDictPageActive */
