/*---------------------------------------------------------------------+\
|
|	CServiceClogTest.cpp  --  brief description of what CServiceClogTest.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	11-Jun-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <limits.h>

#include "UOSIncludes.h"

#include "CServiceClogTest.h"

#include "VPluginFactory.h"
#include "UPlatformTime.h"
#include "UPlatformString.h"


NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define	RECORD_XML


// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( CServiceClogTest );



/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CServiceClogTest - constructor

\+---------------------------------------------------------------------*/
CServiceClogTest::CServiceClogTest
		(
		void
		)
		: inherited(),
		m_pDictionary( 0 ),
		m_oMutex(),
		m_nFrequency( 200 ),
		m_hThread( 0 ),
		m_nSequence( 0 ),
		m_bInitDone( false )
{
}

CServiceClogTest::CServiceClogTest
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_pDictionary( 0 ),
		m_oMutex(),
		m_nFrequency( 200 ),
		m_hThread( 0 ),
		m_nSequence( 0 ),
		m_bInitDone( false )
{
}

CServiceClogTest::CServiceClogTest
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_pDictionary( 0 ),
		m_oMutex(),
		m_nFrequency( 200 ),
		m_hThread( 0 ),
		m_nSequence( 0 ),
		m_bInitDone( false )
{
//	memset(&gVDMsgs,0,sizeof(gVDMsgs));
}

/*---------------------------------------------------------------------+\

 * CServiceClogTest - destructor

\+---------------------------------------------------------------------*/
CServiceClogTest::~CServiceClogTest
		(
		void
		)
{
	if ( m_hThread )
		ThreadClose( m_hThread );



}

/*=====================================================================+\
||	 interface implementation functions									|
\+=====================================================================*/



/*---------------------------------------------------------------------+\
|	 IDictionaryUser
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CServiceClogTest::SetDictionary
		(
		VDictionaryPtr	p
		)
{
	bool	bResult = true;

	CMutexLocker	locker( &m_oMutex );

	if ( ! m_pDictionary )
	{
		//VDictionary::Selector	sel;
		//CVariantDataPtr			pv;

		m_pDictionary = p;

		BuildPageLists();


		//sel = m_pDictionary->LocateEntry( "P:Simulate Data Frequency" );
		//if ( sel )
		//{
		//	pv = m_pDictionary->GetData( sel );
		//	if ( pv )
		//	{
		//		long	nFrequency = *pv;
		//		if ( 0 < nFrequency )
		//			m_nFrequency = 1000 / nFrequency;
		//	}
		//}

		LocalStart();
	}
	else
	{
		bResult = false;
	}

	return bResult;
}






/*---------------------------------------------------------------------+\
|	 IRepeater
\+---------------------------------------------------------------------*/

//virtual
bool	CServiceClogTest::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VRepeaterSetup*			pRepeaterSetup
		)
{
	bool	bResult = true;

	if ( pRepeaterSetup )
		bResult = pRepeaterSetup->RegisterRepeater( m_sID, m_nFrequency );
	m_pDictionary = pApplication->Dictionary();
	BuildPageLists();

	return bResult;
}

//virtual
bool	CServiceClogTest::Cycle
		(
		void
		)
{
	// call function to build buffer
	if ( m_pDictionary )
	{
		long	nDataLen = BuildVehicleXML();

		(void)nDataLen;	// stop compiler from complaining about unused variable
	}

	return true;
}


//virtual
bool	CServiceClogTest::Idle
		(
		void
		)
{
	return true;
}



/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/





/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CServiceClogTest::LocalStart
		(
		void
		)
{
	NResult	nr = NR_S_SUCCESS;

	CCharString		sESS;
	CCharString		sEmpty;
	CVariantData	v;

	//CMutexLocker	lock( &m_oMutex );

	LOCAL_PRINT( "CServiceClogTest::Start - Begin\n" );

	do_sequence
	{
		m_bRunning = true;
		m_hThread = ThreadCreate( (UThreadFunction)RunGlue, this, m_sID.Pointer() );
		if ( ! m_hThread )
			break;

		nr = NR_S_SUCCESS;
	}

	if ( NR_FAILED(nr) )
	{
		if ( m_hThread )
			ThreadClose( m_hThread );
		m_hThread = 0;

		m_bRunning = false;

	}
	LOCAL_PRINT( "CServiceClogTest::Start - End\n" );

	return nr;

}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CServiceClogTest::LocalStop
		(
		void
		)
{
	m_bRunning = false;
	if ( m_hThread )
		ThreadClose( m_hThread );
	m_hThread = 0;




	return NR_S_SUCCESS;
}

/*---------------------------------------------------------------------+\

 * RunGlue - Function to call "Run" from within spawned thread

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceClogTest::RunGlue
		(
		void*	pVoid
		)
{
	CServiceClogTestPtr	pThis = (CServiceClogTestPtr)pVoid;

	return pThis->Run();
}

/*---------------------------------------------------------------------+\

 * Run -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceClogTest::Run
		(
		void
		)
{

	while ( m_bRunning )
	{
		if ( m_pDictionary )
		{
			long	m = milliseconds();

			Cycle();

			long	n = milliseconds() - m;

			if ( m_nFrequency < n  )
				DbgPrint( "%s - overtime\n", m_sID.Pointer() );

			long	j = m_nFrequency - (m % m_nFrequency) - n;
			if ( j < 10 )
			{
				j = m_nFrequency;
				DbgPrint( "%s - %d\n", m_sID.Pointer(), j );
			}
			millisleep( j );
		}
		else
		{
			millisleep( 1000 );
		}
	}

	return (UThreadRtn) 0;
}


/*---------------------------------------------------------------------+\

 * BuildPageLists -

\+---------------------------------------------------------------------*/
void	CServiceClogTest::BuildPageLists
		(
		)
{
	VDictionaryPtr		pDict = m_pDictionary;
	//CDictPageActivePtr	pAct = m_pApplication->DictPageActive();

	CVariantDataPtr	pv;
	VDictionary::Selector	nSel;

	m_aAPage.SetBlockSize( 8 );
	m_aNPage.SetBlockSize( 8 );



	VDictionaryEnumerator*	pDictEnum;
	pDictEnum = pDict->GetPageEnumerator( 'N' );
	if ( pDictEnum )
	{
		while( pDictEnum->MoveNext() )
		{
			CCharString	sKey = pDictEnum->Key();

			if ( sKey == "VEHICLE SHUTDOWN"
				||	sKey == "Alerts Active" )
				continue;

			CCharString	sLabel;
			GFLOAT		fDur = 20.0f;
			GFLOAT		fFreq = 200.0f;


			pv = pDictEnum->Current();
			if ( pv )
			{
				CVariantData	v = *pv;

				sLabel.Format( "B:%s.Duration", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pv = pDict->GetData( nSel );
					fDur = *pv;
				}

				sLabel.Format( "B:%s.Frequency", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pv = pDict->GetData( nSel );
					fFreq = *pv;
				}

				NPage	page;

				page.sID = sKey;
				page.fFrequency = fFreq;
				page.fDuration = fDur;

				m_aNPage.AppendData( &page );
			}
		}
		delete pDictEnum;
	}

	pDictEnum = pDict->GetPageEnumerator( 'A' );
	if ( pDictEnum )
	{
		while( pDictEnum->MoveNext() )
		{
			CCharString	sKey = pDictEnum->Key();
			CCharString	sLabel;
			long		nWave = 2;
			GFLOAT		fFreq = 10.0f;
			GFLOAT		fHigh = 0.0f;
			GFLOAT		fLow = 0.0f;
			CVariantDataPtr	pvHigh = 0;
			CVariantDataPtr	pvLow = 0;

			pv = pDictEnum->Current();
			if ( pv )
			{
				CVariantData			v;
				CVariantData::V_TYPE	eType = pv->GetType();

				v = *pv;

				sLabel.Format( "B:%s.Wave", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pv = pDict->GetData( nSel );
					nWave = *pv;
				}

				sLabel.Format( "B:%s.Frequency", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pv = pDict->GetData( nSel );
					fFreq = *pv;
				}

				sLabel.Format( "B:%s.High", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pvHigh = pDict->GetData( nSel );
					if ( pvHigh )
						fHigh = *pvHigh;
				}

				sLabel.Format( "B:%s.Low", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pvLow = pDict->GetData( nSel );
					if ( pvLow )
						fLow = *pvLow;
				}

				APage	page;

				page.sKey = sKey;
				page.eType = eType;
				page.fFreq = fFreq;
				page.fHigh = fHigh;
				page.fLow = fLow;
				page.nWave = nWave;

				m_aAPage.AppendData( &page );
			}
		}
		delete pDictEnum;
	}
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
long	CServiceClogTest::BuildVehicleXML
		(
		void
		)
{

	CalculateMilliTime();


	char			sData[80];


	//strcpy_s( m_sData, sizeof(m_sData), "<?xml version='1.0'?>" );
	strcpy_s( m_sData, sizeof(m_sData), "<VehicleData>" );
	strcat_s( m_sData, sizeof(m_sData), "<Alerts>" );

	if ( 0 < m_aNPage.Length() )
	{
		NPage*	p = m_aNPage.PointArray();
		NPage*	pEnd = p + m_aNPage.Length();

		while( p < pEnd )
		{

			long	iFreq = long(p->fFrequency * 1000.0f);
			long	iDur = long(p->fDuration * 1000.0f);
			long	i = m_nMilli % iFreq;

			char	c = i < iDur ? 'Y' : 'N';
			sprintf_s( sData, sizeof(sData),
				"<Alert ID='%s' Value='%c'/>", p->sID.Pointer(), c );
			strcat_s( m_sData, sizeof(m_sData), sData );

			++p;
		}
	}



	strcat_s( m_sData, sizeof(m_sData), "</Alerts>" );
	strcat_s( m_sData, sizeof(m_sData), "<Parameters>" );


	if ( 0 < m_aAPage.Length() )
	{
		APage*	p = m_aAPage.PointArray();
		APage*	pEnd = p + m_aAPage.Length();

		while( p < pEnd )
		{
			CCharString	sKey = p->sKey;
			CCharString	sLabel;
			long		nWave = p->nWave;
			GFLOAT		fFreq = p->fFreq;
			GFLOAT		fHigh = p->fHigh;
			GFLOAT		fLow = p->fLow;
			CVariantData::V_TYPE	eType = p->eType;


			GFLOAT	fAmplitude;

			// this produces a normalized (0..1) value
			long	iFreq = long(fFreq * 1000.0f);
			long	i = m_nMilli % iFreq;
			GFLOAT	f = GFLOAT(i) / GFLOAT(iFreq);


			switch ( nWave )
			{
			case 0:		// sawtooth
				fAmplitude = f;
				break;
			case 1:		// sawtooth-inverted
				fAmplitude = GFLOAT_1 - f;
				break;
			case 2:		// sine
				{
					GFLOAT	t = sinf(GFLOAT_2PI * f );
					fAmplitude = t / GFLOAT_2 + GFLOAT_1_2;
				}
				break;
			case 3:		// square
				fAmplitude = GFLOAT_0 < sinf(GFLOAT_2PI * f) ? GFLOAT_1 : GFLOAT_0;
				break;
			case 4:		// triangle
				fAmplitude = f * GFLOAT_2;
				if ( GFLOAT_1 < fAmplitude )
					fAmplitude = GFLOAT_2 - fAmplitude;
				break;
			default:
				fAmplitude = GFLOAT_0;
				break;
			}

			switch ( eType )
			{
			case CVariantData::T_BOOL:
				{
					char	c = GFLOAT_1_2 < fAmplitude ? 'Y' : 'N';
					sprintf_s( sData, sizeof(sData),
						"<Param ID='%s' Value='%c'/>", sKey.Pointer(), c );
					strcat_s( m_sData, sizeof(m_sData), sData );
				}
				break;
			case CVariantData::T_COLOR:
				break;
			case CVariantData::T_DATETIME:
				{
					char	sTime[80];
					CDateTime	t;
					//long	nOffset = t.TimeAdjustOffset();
					//t = m_tTimeb.time;// + nOffset;
					t = m_nTime;
					t.FormatGMT( sTime, sizeof(sTime), "%Y-%m-%d %H:%M:%S Z" );
					sprintf_s( sData, sizeof(sData),
						"<Param ID='%s' Value='%s'/>", sKey.Pointer(), sTime );
					strcat_s( m_sData, sizeof(m_sData), sData );
				}
				break;
			case CVariantData::T_FLOAT:
				{
					GFLOAT	fMagnitude;
					if ( fLow < fHigh )
					{
						fMagnitude = fHigh - fLow;
					}
					else
					{
						fMagnitude = GFLOAT_1;
						fHigh = GFLOAT_1;
						fLow = GFLOAT_0;
					}
					GFLOAT	fValue = fMagnitude * fAmplitude + fLow;
					sprintf_s( sData, sizeof(sData),
						"<Param ID='%s' Value='%f'/>", sKey.Pointer(), (float)fValue );
					strcat_s( m_sData, sizeof(m_sData), sData );
				}
				break;
			case CVariantData::T_INTEGER:
				{
					long	nLow = 0;
					long	fMagnitude;
					if ( fLow < fHigh )
					{
						fMagnitude = long(fHigh - fLow);
					}
					else
					{
						fMagnitude = 1;
					}
					long	fValue = long(fMagnitude * fAmplitude) + nLow;
					sprintf_s( sData, sizeof(sData),
						"<Param ID='%s' Value='%ld'/>", sKey.Pointer(), fValue );
					strcat_s( m_sData, sizeof(m_sData), sData );
				}
				break;
			case CVariantData::T_STRING:
				{
					if ( fLow < fHigh )
					{
						long	nHigh = long(fHigh);
						long	nLow = long(fLow);
						long	fMagnitude = nHigh - nLow;
						long	fValue = long(fMagnitude * fAmplitude) + nLow;
						sprintf_s( sData, sizeof(sData),
							"<Param ID='%s' Value='%ld'/>", sKey.Pointer(), fValue );
						strcat_s( m_sData, sizeof(m_sData), sData );
					}
				}
				break;
			case CVariantData::T_UNDEFINED:
			default:
				break;
			}

			++p;

		}
	}


	strcat_s( m_sData, sizeof(m_sData), "</Parameters>" );
	strcat_s( m_sData, sizeof(m_sData), "</VehicleData>" );



	return long(strlen( m_sData ));
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CServiceClogTest::CalculateMilliTime
		(
		void
		)
{
	time_t	n;
	m_nMilli = milliseconds();
	m_nTime = ::time( &n );
	//DbgPrint( "CalculateMilliTime = %ld\n", (long)m_nTime );
	//::ftime( &m_tTimeb );
}





/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	VSupports
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CServiceClogTest::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDictionaryUser )
			pI = INTERFACE_THIS( IDictionaryUserPtr );
		else if ( rIID == IXID_IRepeater )
			pI = INTERFACE_THIS( IRepeaterPtr );
		else
			pI = 0;
	}

	return pI;
}




/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * Load - Load parameters from XML

\+---------------------------------------------------------------------*/
bool	CServiceClogTest::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{



		GFLOAT	f = pConfig->GetParameterAsFloatUnits( "Message Frequency", "seconds", 0.2f );

		m_nFrequency = long(f * 1000.0f);


		LOCAL_PRINT( "CServiceClogTest::Load - complete\n" );
		bResult = true;
		m_nSequence	= 1;

	}

	m_bRunning = false;

	return bResult;
}




/*---------------------------------------------------------------------+\
|	 IService
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
NResult	CServiceClogTest::Start
		(
		void
		)
{
	NResult	nr = NR_S_SUCCESS;


	return nr;

}


/*---------------------------------------------------------------------+\

 * Stop -

\+---------------------------------------------------------------------*/
NResult	CServiceClogTest::Stop
		(
		void
		)
{
	m_bRunning = false;
	if ( m_hThread )
	{
		ThreadClose( m_hThread );
		m_hThread = 0;
	}

	return NR_S_SUCCESS;
}





NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
