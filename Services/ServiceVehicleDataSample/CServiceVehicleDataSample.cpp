/*---------------------------------------------------------------------+\
|
|	CServiceVehicleDataSample.cpp  --  brief description of what CServiceVehicleDataSample.cpp is for
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformTime.h"
#include "UPlatformThreads.h"
#include "UPlatformString.h"
#include "CServiceVehicleDataSample.h"
#include "VPluginFactory.h"
#include "UNResult.h"


/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/


// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
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

PLUGIN_CREATE_FACTORY( CServiceVehicleDataSample );






/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CServiceVehicleDataSample - constructor

\+---------------------------------------------------------------------*/
CServiceVehicleDataSample::CServiceVehicleDataSample
		(
		void
		)
		: inherited()
		, m_pDictionary( 0 )
		, m_pSocket( 0 )
		, m_sMCAddress()
		, m_nMCPort( 0 )
		, m_hThread( 0 )
		, m_nFrequency( 200 )
		, m_oTime()
{
}

CServiceVehicleDataSample::CServiceVehicleDataSample
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_pDictionary( 0 )
		, m_pSocket( 0 )
		, m_sMCAddress()
		, m_nMCPort( 0 )
		, m_hThread( 0 )
		, m_nFrequency( 200 )
		, m_oTime()
{
}

CServiceVehicleDataSample::CServiceVehicleDataSample
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_pDictionary( 0 )
		, m_pSocket( 0 )
		, m_sMCAddress()
		, m_nMCPort( 0 )
		, m_hThread( 0 )
		, m_nFrequency( 200 )
		, m_oTime()
{
}

/*---------------------------------------------------------------------+\

 * CServiceVehicleDataSample - destructor

\+---------------------------------------------------------------------*/
CServiceVehicleDataSample::~CServiceVehicleDataSample
		(
		void
		)
{
	if ( m_bRunning )
		Stop();
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
bool	CServiceVehicleDataSample::SetDictionary
		(
		VDictionaryPtr	p
		)
{
	bool	bResult = true;

	CMutexLocker	locker( &m_oMutex );

	if ( ! m_pDictionary )
	{
		VDictionary::Selector	sel;
		ConstCVariantDataPtr	pv;

		m_pDictionary = p;

		sel = m_pDictionary->LocateEntry( "P:Vehicle Data Multicast Address" );
		if ( sel )
		{
			pv = m_pDictionary->GetData( sel );
			if ( pv )
				m_sMCAddress = pv->GetValueCCharString();
		}

		sel = m_pDictionary->LocateEntry( "P:Vehicle Data Multicast Port" );
		if ( sel )
		{
			pv = m_pDictionary->GetData( sel );
			if ( pv )
				m_nMCPort = pv->GetValueInteger();
		}

		sel = m_pDictionary->LocateEntry( "P:Simulate Data Frequency" );
		if ( sel )
		{
			pv = m_pDictionary->GetData( sel );
			if ( pv )
			{
				long	nFrequency = *pv;
				if ( 0 < nFrequency )
					m_nFrequency = 1000 / nFrequency;
			}
		}
	}
	else
	{
		bResult = false;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\
|	 IVehicleDataSample
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
//virtual
NResult	CServiceVehicleDataSample::StartDataFlow
		(
		void
		)
{
	if ( ! m_bRunning )
		LocalStart();
	return NR_S_SUCCESS;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
//virtual
NResult	CServiceVehicleDataSample::StopDataFlow
		(
		void
		)
{
	if ( m_bRunning )
		LocalStop();
	return NR_S_SUCCESS;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
//virtual
NResult	CServiceVehicleDataSample::ToggleDataFlow
		(
		void
		)
{
	if ( m_bRunning )
		LocalStop();
	else
		LocalStart();
	return NR_S_SUCCESS;
}



/*---------------------------------------------------------------------+\
|	 IService
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleDataSample::Start
		(
		void
		)
{
	NResult	nr = inherited::Start();

	// this basically does nothing
	//	 we will do the real work in LocalStart which should
	//	usually be called from the XxxxDataFlow functions

	nr = NR_S_SUCCESS;


	return nr;

}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleDataSample::Stop
		(
		void
		)
{
	if ( m_bRunning )
		LocalStop();

	return inherited::Stop();
}




/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CServiceVehicleDataSample::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDictionaryUser )
			pI = INTERFACE_THIS( IDictionaryUserPtr );
		else if ( rIID == IXID_IVehicleDataSample )
			pI = INTERFACE_THIS( IVehicleDataSamplePtr );
		else
			pI = 0;
	}

	return pI;
}



/*---------------------------------------------------------------------+\

 * Load - Load parameters from XML

\+---------------------------------------------------------------------*/
bool	CServiceVehicleDataSample::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		CCharString	sField;
		CCharString	sValue;

		m_sMCAddress = pConfig->GetParameterAsString( "Multicast Address", "235.55.55.5" );
		m_nMCPort = pConfig->GetParameterAsInteger( "Multicast Port", 55555 );

		GFLOAT	f = pConfig->GetParameterAsFloatUnits( "Message Frequency", "seconds", 0.2f );

		m_nFrequency = long(f * 1000.0f);


	}

	m_bRunning = false;

	return bResult;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/




/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleDataSample::LocalStart
		(
		void
		)
{
	NResult	nr = NR_S_SUCCESS;

	CCharString		sESS;
	CCharString		sEmpty;
	CVariantData	v;

	//CMutexLocker	lock( &m_oMutex );

	LOCAL_PRINT( "CServiceVehicleDataSample::LocalStart - Begin\n" );

	do_sequence
	{
		m_pSocket = new CSocketUDP;
		if ( ! m_pSocket )
			break;

		m_pSocket->SetMulticastTTL( 1 );

		m_hThread = ThreadCreate( (UThreadFunction)RunGlue, this );
		if ( ! m_hThread )
			break;

		nr = NR_S_SUCCESS;
		m_bRunning = true;
	}

	if ( NR_FAILED(nr) )
	{
		if ( m_hThread )
			ThreadClose( m_hThread );
		m_hThread = 0;

		if ( m_pSocket )
			delete m_pSocket;
		m_pSocket = 0;

		m_bRunning = false;

	}
	LOCAL_PRINT( "CServiceVehicleDataSample::LocalStart - End\n" );

	return nr;

}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleDataSample::LocalStop
		(
		void
		)
{
	if ( m_hThread )
		ThreadClose( m_hThread );
	m_hThread = 0;

	if ( m_pSocket )
		delete m_pSocket;
	m_pSocket = 0;

	m_bRunning = false;

	return NR_S_SUCCESS;
}





/*---------------------------------------------------------------------+\

 * RunGlue - Function to call "Run" from within spawned thread

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceVehicleDataSample::RunGlue
		(
		void*	pVoid
		)
{
	CServiceVehicleDataSamplePtr	pThis
				= (CServiceVehicleDataSamplePtr)pVoid;

	pThis->Run();

	return 0;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceVehicleDataSample::Run
		(
		void
		)
{
	m_bRunning = true;


	forever_loop
	{
		// call function to build buffer
		if ( m_pDictionary )
		{
			long	nDataLen = BuildVehicleXML();

			m_pSocket->SendTo( m_sData, nDataLen, m_sMCAddress, (unsigned short)m_nMCPort );

			millisleep( m_nFrequency );
		}
		else
		{
			millisleep( 1000 );
		}
	}

	return (UThreadRtn) 0;

}





/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
long	CServiceVehicleDataSample::BuildVehicleXML
		(
		void
		)
{

	CalculateMilliTime();

	VDictionaryPtr		pDict = m_pDictionary;
	//CDictPageActivePtr	pAct = m_pApplication->DictPageActive();

	char					sData[80];
	ConstCVariantDataPtr	pv;
	VDictionary::Selector	nSel;



	//strcpy_s( m_sData, sizeof(m_sData), "<?xml version='1.0'?>" );
	strcpy_s( m_sData, sizeof(m_sData), "<VehicleData>" );
	strcat_s( m_sData, sizeof(m_sData), "<Alerts>" );

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
				CVariantData			v;

				v = *pv;

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

				long	iFreq = long(fFreq * 1000.0f);
				long	iDur = long(fDur * 1000.0f);
				long	i = m_nMilli % iFreq;

				//if ( i < iDur )
				//{
					char	c = i < iDur ? 'Y' : 'N';
					sprintf_s( sData, sizeof(sData),
						"<Alert ID='%s' Value='%c'/>", sKey.Pointer(), c );
					strcat_s( m_sData, sizeof(m_sData), sData );
				//}

			}

		}
		delete pDictEnum;
	}



	strcat_s( m_sData, sizeof(m_sData), "</Alerts>" );
	strcat_s( m_sData, sizeof(m_sData), "<Parameters>" );



	pDictEnum = pDict->GetPageEnumerator( 'A' );
	if ( pDictEnum )
	{
		while( pDictEnum->MoveNext() )
		{
			CCharString	sKey = pDictEnum->Key();
			CCharString	sLabel;
			long		nWave = 2;
			GFLOAT		fFreq = 10.0f;
			ConstCVariantDataPtr	pvHigh = 0;
			ConstCVariantDataPtr	pvLow = 0;

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
				}

				sLabel.Format( "B:%s.Low", sKey.Pointer() );
				nSel = pDict->LocateEntry( sLabel );
				if ( nSel )
				{
					pvLow = pDict->GetData( nSel );
				}

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
						//CDateTime	t;
						//long	nOffset = t.TimeAdjustOffset();
						//t = m_tTimeb.time;// + nOffset;
						//t = m_nTime;
						m_oTime.FormatGMT( sTime, sizeof(sTime), "%Y-%m-%d %H:%M:%S Z" );
						sprintf_s( sData, sizeof(sData),
							"<Param ID='%s' Value='%s'/>", sKey.Pointer(), sTime );
						strcat_s( m_sData, sizeof(m_sData), sData );
					}
					break;
				case CVariantData::T_FLOAT:
					{
						GFLOAT	fHigh = GFLOAT_1;
						GFLOAT	fLow = GFLOAT_0;
						if ( pvHigh )
							fHigh = pvHigh->GetValueFloat();
						if ( pvLow )
							fLow = pvLow->GetValueFloat();
						GFLOAT	fMagnitude = fHigh - fLow;
						GFLOAT	fValue = fMagnitude * fAmplitude + fLow;
						sprintf_s( sData, sizeof(sData),
							"<Param ID='%s' Value='%f'/>", sKey.Pointer(), (float)fValue );
						strcat_s( m_sData, sizeof(m_sData), sData );
					}
					break;
				case CVariantData::T_INTEGER:
					{
						long	fHigh = 1;
						long	fLow = 0;
						if ( pvHigh )
							fHigh = pvHigh->GetValueInteger();
						if ( pvLow )
							fLow = pvLow->GetValueInteger();
						long	fMagnitude = fHigh - fLow;
						long	fValue = long(fMagnitude * fAmplitude) + fLow;
						sprintf_s( sData, sizeof(sData),
							"<Param ID='%s' Value='%ld'/>", sKey.Pointer(), fValue );
						strcat_s( m_sData, sizeof(m_sData), sData );
					}
					break;
				case CVariantData::T_STRING:
					{
						if ( pvHigh  &&  pvLow )
						{
							long	fHigh = 1;
							long	fLow = 0;
							if ( pvHigh )
								fHigh = pvHigh->GetValueInteger();
							if ( pvLow )
								fLow = pvLow->GetValueInteger();
							long	fMagnitude = fHigh - fLow;
							long	fValue = long(fMagnitude * fAmplitude) + fLow;
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

			}

		}
		delete pDictEnum;
	}


	strcat_s( m_sData, sizeof(m_sData), "</Parameters>" );
	strcat_s( m_sData, sizeof(m_sData), "</VehicleData>" );



	return long(strlen( m_sData ));
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CServiceVehicleDataSample::CalculateMilliTime
		(
		void
		)
{
	//time_t	n;

	m_nMilli = milliseconds();
	m_oTime = CDateTime::CurrentTime();
	//m_nTime = ::time( &n );
	//::ftime( &m_tTimeb );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
