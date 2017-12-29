/*---------------------------------------------------------------------+\
|
|	CServiceClogTest.h  --  brief description of what CServiceClogTest.h is for
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
	11-Jun-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceClogTest
#define _H_CServiceClogTest
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <time.h>

#include "VPluginService.h"

#include "IDictionaryUser.h"
#include "IVehicleDataSample.h"
#include "IRepeater.h"

#include "CMutex.h"
#include "TArray.h"
#include "UPlatformThreads.h"

#include "NamespaceGadget.h"
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

typedef class CServiceClogTest*		CServiceClogTestPtr;
typedef class CServiceClogTest&		CServiceClogTestRef;
typedef const class CServiceClogTest&	ConstCServiceClogTestRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceClogTest : public VPluginService,
							implements_ IDictionaryUser,
							implements_ IRepeater
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CServiceClogTest );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IDictionaryUser
	virtual
	bool	SetDictionary
			(
			VDictionaryPtr	p	// IN:	dictionary pointer
			);



	//	IRepeater
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VRepeaterSetup*			pRepeaterSetup = 0
			);

	virtual
	bool	Cycle
			(
			void
			);
			

	virtual
	bool	Idle
			(
			void
			);





public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct NPage
	{
		CCharString	sID;
		GFLOAT		fFrequency;
		GFLOAT		fDuration;

		NPage()
			: sID()
			, fFrequency(200.0f)
			, fDuration(20.0f)
		{
		};

		NPage( const NPage& r )
			: sID( r.sID )
			, fFrequency( r.fFrequency )
			, fDuration( r.fDuration )
		{
		};

		~NPage()
		{
		};
	} NPage;

	typedef struct APage
	{
		CVariantData::V_TYPE	eType;
		CCharString	sKey;
		long		nWave;
		GFLOAT		fFreq;
		GFLOAT		fHigh;
		GFLOAT		fLow;

		APage()
			: eType( CVariantData::T_INTEGER )
			, sKey()
			, nWave(2)
			, fFreq(10.0f)
			, fHigh(0.0f)
			, fLow(0.0f)
		{};

		APage( const APage& r )
			: eType( r.eType )
			, sKey( r.sKey )
			, nWave( r.nWave )
			, fFreq( r.fFreq )
			, fHigh( r.fHigh )
			, fLow( r.fLow)
		{};

		~APage()
		{};

	} APage;

//	protected functions  ------------------------------------------------

	virtual
	NResult	LocalStart
			(
			void
			);

	virtual
	NResult	LocalStop
			(
			void
			);

	static
	UThreadRtn
			RunGlue
			(
			void*	pVoid
			);

	UThreadRtn
			Run( void );

	void	BuildPageLists( void );
	long	BuildVehicleXML();
	void	CalculateMilliTime();


//	protected data  -----------------------------------------------------

	VDictionaryPtr	m_pDictionary;

	TArray<APage>	m_aAPage;
	TArray<NPage>	m_aNPage;

	CMutex			m_oMutex;
	long			m_nFrequency;	// milliseconds

	UThreadHdl				m_hThread;

	char					m_sData[1024*4];

	unsigned int			m_nSequence;

	bool					m_bInitDone;
	long					m_nMilliStart;
	long					m_nMilli;
	time_t					m_nTime;

private:
//	private types  ------------------------------------------------------

	typedef	VPluginService	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr		pLib
			);

	//	IService
public:
	virtual
	NResult	Start
			(
			void
			);

	virtual
	NResult	Stop
			(
			void
			);
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


#endif /* _H_CServiceClogTest */

