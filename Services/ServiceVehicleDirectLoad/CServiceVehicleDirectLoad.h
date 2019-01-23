/*---------------------------------------------------------------------+\
|
|	CServiceVehicleDirectLoad.h  --  brief description of what CServiceVehicleDirectLoad.h is for
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceVehicleDirectLoad
#define _H_CServiceVehicleDirectLoad
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
#include "IActiveXML.h"

#include "CMutex.h"
#include "TArray.h"
#include "UPlatformThreads.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


const int NUM_DISPLAYS = 4;

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CServiceVehicleDirectLoad*		CServiceVehicleDirectLoadPtr;
typedef class CServiceVehicleDirectLoad&		CServiceVehicleDirectLoadRef;
typedef const class CServiceVehicleDirectLoad&	ConstCServiceVehicleDirectLoadRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceVehicleDirectLoad : public VPluginService,
							implements_ IDictionaryUser,
							implements_ IVehicleDataSample,
							implements_ IActiveXML
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CServiceVehicleDirectLoad );

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


	//	IVehicleDataSample

	virtual
	Yogi::Core::NResult
			StartDataFlow
			(
			void
			);

	virtual
	Yogi::Core::NResult
			StopDataFlow
			(
			void
			);

	virtual
	Yogi::Core::NResult
			ToggleDataFlow
			(
			void
			);


	//	IActiveXML
	virtual
	Yogi::Core::NResult
			RegisterXMLClient
			(
			IActiveXMLClientPtr	p
			);


	virtual
	int		FetchXMLData
			(
			char**	hBuffer,	// OUT:	address of buffer
			size_t*	pnSize,		// OUT:	number of bytes in buffer
			size_t*	pnSequence	// OUT: sequence identifier
			);


	virtual
	void	ReleaseXMLData
			(
			int		nID			// IN:	id of buffer to release
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct	DBuf
	{
		long	nUsers;
		size_t	nSequence;
		size_t	nAlloc;
		size_t	nSize;
		char*	pBuffer;

		DBuf()
			: nUsers(0)
			, nSequence(0)
			, nAlloc(0)
			, nSize(0)
			, pBuffer(0)
		{};

		DBuf( const DBuf& r )
			: nUsers(r.nUsers)
			, nSequence(r.nSequence)
			, nAlloc(r.nAlloc)
			, nSize(r.nSize)
			, pBuffer(r.pBuffer)
		{
		};

		~DBuf()
		{
			if ( pBuffer )
				delete [] pBuffer;
		};
	} DBuf;


	typedef struct NPage
	{
		Yogi::Core::CCharString	sID;
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
		Yogi::Common::CVariantData::V_TYPE	eType;
		Yogi::Core::CCharString				sKey;
		long		nWave;
		GFLOAT		fFreq;
		GFLOAT		fHigh;
		GFLOAT		fLow;

		APage()
			: eType( Yogi::Common::CVariantData::T_INTEGER )
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
	Yogi::Core::NResult
			LocalStart
			(
			void
			);

	virtual
	Yogi::Core::NResult
			LocalStop
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

	bool	OpenMulticastDirectLoad
			(
			void
			);


	DBuf*	GetBufferForRead
			(
			void
			);


	DBuf*	FindIdleBuffer
			(
			void
			);

	void	GrowBuffer
			(
			DBuf*	p
			);


	void	NotifyClients
			(
			void
			);




	void	SetMCMaxMsgSize
			(
			int m
			);


	bool	MsgIsOk( char* buf, unsigned int len );


	size_t	BuildVehicleXML();
	void	CalculateMilliTime();




//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;

	Yogi::Core::TArray<APage>	m_aAPage;
	Yogi::Core::TArray<NPage>	m_aNPage;

	Yogi::Core::CMutex			m_oMutex;
	long					m_nFrequency;	// milliseconds

	UThreadHdl				m_hThread;

	Yogi::Core::TArray<IActiveXMLClientPtr>	m_aClients;
	Yogi::Core::TArray<DBuf>			m_aBuffers;


	char					m_sData[1024*4];





	size_t					m_nSequence;

	bool					m_bInitDone;

	int						m_nMCTimeOut;
	size_t 					m_nMCMaxMsgSize;


	long					m_nMilliStart;
	long					m_nMilli;
	time_t					m_nTime;
	//timeb					m_tTimeb;
	//struct tm				m_tTm;


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
			Yogi::Common::ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
			);

	//	IService
public:
	virtual
	Yogi::Core::NResult
			Start
			(
			void
			);

	virtual
	Yogi::Core::NResult
			Stop
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


}}


#endif /* _H_CServiceVehicleDirectLoad */
