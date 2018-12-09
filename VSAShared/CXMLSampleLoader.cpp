/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2009 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CXMLSampleLoader.cpp  --  brief description of what CXMLSampleLoader.cpp is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	06-Jul-2010			P.Hogan			(Reviewed by: J.Griswold)
		Changed case of Stdafx.h include file for compatibility with
		case sensitive file systems.
	14-Dec-2009			R.Hosea			(Reviewed by: J.Griswold)
		Fixed gcc compile problem for omniscape
	09-Dec-2009			C.Cason			(Reviewed by: R.Hosea)
		Changed GFLOAT casts to double casts for Linux compilation
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	04-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add an alert for FWD BLGE PUMP
	27-Oct-2009			M.Rose			(Reviewed by: R.Hosea)
		Fix g++ compile error, remove :: operator from sprintf_s
	22-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove previous gear-position stuff and add Latitude
	19-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fake out the simulator stuff for gear-position
	18-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Adjust some values: Time between gear shifts & how
		steering angle affected heading.
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add test cases for Battery Voltage.
		Also add range failure case to check Maximum/Minimum shift
	07-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Change Transmission Selector to Current Gear
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Adjust for optional <?xml?> header test code
	05-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add generation of Trans Oil Temp and Pressure data
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Transmission Selector
		Fix Steering name to reflect actual data from Noregon
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add test generation of Alert data
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		transition to gmtime_s to resolve MSVC
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Integrate CFactoryVehicleData
	23-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include <math.h>
#include "CXMLSampleLoader.h"

#include "UPlatform.h"
#include "CDateTime.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

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
//static char	g_sGears[] = "PRND";
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


class SampleReadCallBack : public XMLLite::VReadCallBack
{
public:
	SampleReadCallBack
		(
		char* s
		)
		: m_sData( s ),
		m_nLength( ::strlen( s ) )
	{}

	virtual
	long	Read					// RTN:	returns number of bytes actually read
			(
			void*			pBuffer,		// OUT: buffer to receive data
			long			nBytesToRead,	// IN:	number of bytes to read
			XMLLite::ETEXT_FORMAT			// IN:	target format
			)
	{
		long	n = nBytesToRead < m_nLength ? nBytesToRead : m_nLength;
		if ( 0 == memcpy_s( pBuffer, nBytesToRead, m_sData, n ) )
			return n;
		else
			return 0;
	}

	/*
		Gets the size of the file (stream)
	*/
	virtual
	size_t	GetSize		// RTN:	return file (stream) size in bytes
			(
			void
			)
	{
		return m_nLength;
	}

	/*
		Get a name associated with the call-back stream.
		For files this should be name of the file or
		at least a partial path with name.
	*/
	//BEGIN_OVERRUN_WARNING
	virtual
	size_t	GetName					// RTN:	string length of name
			(
			char*			sTarget,	// OUT:	buffer to receive name
			size_t			nSizeTarget	// IN:	size of target
			)
	{
		char	sName[] = "VehicleData";
		if ( 0 < nSizeTarget )
			strcpy_s( sTarget, (size_t)nSizeTarget, sName );
		return strlen( sName );
	}
	//END_OVERRUN_WARNING

protected:
	char*	m_sData;
	size_t	m_nLength;
};


/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CXMLSampleLoader - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
CXMLSampleLoader::CXMLSampleLoader
		(
		void
		)
		: m_pApplication( 0 ),
		m_pVehicleData( 0 ),
		m_nMilliStart( 0 ),
		m_nMilli( 0 ),
		m_fHeading( GFLOAT_0 )
{
}


/**--------------------------------------------------------------------+\

 * <summary>~CXMLSampleLoader - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
CXMLSampleLoader::~CXMLSampleLoader
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

void	CXMLSampleLoader::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;

	if ( ! m_pVehicleData )
		m_pVehicleData = new CFactoryVehicleData;

	m_pVehicleData->SpecifyActivePage( p->DictPageActive() );
	m_pVehicleData->SpecifyNotifyPage( p->DictPageNotify() );
}


//BEGIN_OVERRUN_WARNING
void	CXMLSampleLoader::UpdateActivePage
		(
		void
		)
{
	CalculateMilliTime();

	//long	n = m_nMilli;

	VDictionaryPtr		pDict = m_pApplication->Dictionary();
	//CDictPageActivePtr	pAct = m_pApplication->DictPageActive();

	char			sData[80];
	CVariantDataPtr	pv;
	VDictionary::Selector	nSel;

	//float	fValueHi;
	//float	fValueLo;
	//float	fValue;
	//float	fValueRange;
	//long	nValueHi;
	//long	nValueLo;
	//long	nValue;
	//long	nValueRange;
	//float	fSteering;
	//char	cGear;


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


#if 0

	nSel = pDict->LocateEntry( "B:Engine Oil Pressure.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 500.0f;
	fValue = float(n % (long(fValueHi) * 2 * 200 )) / 200.0f;
	//fValue = ::fmodf(float(n) / 200.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	nSel = pDict->LocateEntry( "B:Engine Oil Pressure.Green.Low" );
	pv = pDict->GetData( nSel );
	fValueLo = pv->GetValueFloat();
	strcat_s( m_sData, sizeof(m_sData), "<Alert ID='Engine Oil Level Low' Value='" );
	if ( fValue < fValueLo )
		strcat_s( m_sData, sizeof(m_sData), "Y" );
	else
		strcat_s( m_sData, sizeof(m_sData), "N" );

	strcat_s( m_sData, sizeof(m_sData), "'/>" );



	nValue = n % (1000*60);
	strcat_s( m_sData, sizeof(m_sData), "<Alert ID='Forward Bilge Pump' Value='" );
	if ( nValue < (1000*20) )
		strcat_s( m_sData, sizeof(m_sData), "Y" );
	else
		strcat_s( m_sData, sizeof(m_sData), "N" );
	strcat_s( m_sData, sizeof(m_sData), "'/>" );

#endif

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
						CDateTime	t;
						//long	nOffset = t.TimeAdjustOffset();
						t = m_tTimeb.time;// + nOffset;
						t.FormatGMT( sTime, sizeof(sTime), "%Y-%m-%d %H:%M:%S Z" );
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

#if 0
	//nValue = (n / 15000 ) % strlen(g_sGears);
	//cGear = g_sGears[nValue];
	//sprintf_s( sData, sizeof(sData), "<Param ID='Current Gear' Value='%c'/>", cGear );
	//strcat_s( m_sData, sizeof(m_sData), sData );

	nSel = pDict->LocateEntry( "B:Current Gear.High" );
	pv = pDict->GetData( nSel );
	nValueHi = pv ? pv->GetValueInteger() : 10;
	nSel = pDict->LocateEntry( "B:Current Gear.Low" );
	pv = pDict->GetData( nSel );
	nValueLo = pv ? pv->GetValueInteger() : -1;
	nValueRange = nValueHi - nValueLo;
	nValue = (n / 2500) % nValueRange;
	nValue += nValueLo;
	sprintf_s( sData, sizeof(sData), "<Param ID='Current Gear' Value='%ld'/>", nValue );
	strcat_s( m_sData, sizeof(m_sData), sData );


	nSel = pDict->LocateEntry( "B:Steering Wheel Angle.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 45.0f;
	nSel = pDict->LocateEntry( "B:Steering Wheel Angle.Low" );
	pv = pDict->GetData( nSel );
	fValueLo = pv ? float(pv->GetValueFloat()) : -45.0f;
	fValueRange = fValueHi - fValueLo;
	fValue = float(n % (long(fValueRange) * 2 * 175)) / 175.0f;
	//fValue = ::fmodf((float(n) / 175.0f), fValueRange * 2);
	if ( fValueRange < fValue )
		fValue = fValueRange * 2.0f - fValue;
	fValue += fValueLo;
	sprintf_s( sData, sizeof(sData), "<Param ID='Steering Wheel Angle' Value='%f'/>", (float)fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "Steering Angle", sData );
	fSteering = fValue;


	// calculate compass heading
		nSel = pDict->LocateEntry( "B:Compass.High" );
		pv = pDict->GetData( nSel );
		fValueHi = pv ? float(pv->GetValueFloat()) : 360.0f;
		fValue = m_fHeading + fSteering / 15.0f;
		//  (S:MILLI) 50 / 1800 % 5 /
		fValue = ::fmodf(fValue, fValueHi);
		sprintf_s( sData, sizeof(sData), "<Param ID='Compass' Value='%0.5f'/>", (float)fValue );
		strcat_s( m_sData, sizeof(m_sData), sData );
		//pAct->UpdateEntry( "Compass", sData );
		m_fHeading = fValue;


		nSel = pDict->LocateEntry( "B:Latitude.High" );
		pv = pDict->GetData( nSel );
		fValueHi = pv ? float(pv->GetValueFloat()) : 180.0f;
		nSel = pDict->LocateEntry( "B:Latitude.Low" );
		pv = pDict->GetData( nSel );
		fValueLo = pv ? float(pv->GetValueFloat()) : -180.0f;
		fValueRange = fValueHi - fValueLo;
		fValue = fValueHi - (float(n % (long(fValueRange) * 800)) / 800.0f);
		//fValue = fValueHi - ::fmodf((float(n) / 800.0f), fValueRange);
		sprintf_s( sData, sizeof(sData), "<Param ID='Latitude' Value='%f'/>", (float)fValue );
		strcat_s( m_sData, sizeof(m_sData), sData );


	nSel = pDict->LocateEntry( "B:Fuel Level.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 100.0f;
	fValue = fValueHi - (float(n % long(fValueHi * 300.0f)) / 300.0f);
	//fValue = fValueHi - ::fmodf((float(n) / 300.0f), fValueHi);
	sprintf_s( sData, sizeof(sData), "<Param ID='Fuel Level' Value='%f'/>", (float)fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );


		nSel = pDict->LocateEntry( "B:Vehicle Speed.High" );
		pv = pDict->GetData( nSel );
		fValueHi = pv ? float(pv->GetValueFloat()) : 200.0f;
		fValue = float(n % (long(fValueHi) * 2 * 150)) / 150.0f;
		//fValue = ::fmodf(float(n) / 150.0f, fValueHi * 2.0f);
		if ( fValueHi < fValue )
			fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Vehicle Speed' Value='%0.5f'/>", (float)fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );


	nSel = pDict->LocateEntry( "B:RPM.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 10000.0f;
	fValue = float(n % (long(fValueHi) * 2 * 2)) / 2.0f;
		//fValue = ::fmodf(float(n) * 2.0f, fValueHi * 2.0f);
		if ( fValueHi < fValue )
			fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='RPM' Value='%f'/>", (float)fValue );
	//sprintf_s( sData, sizeof(sData), "%f", fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "RPM", sData );


	nSel = pDict->LocateEntry( "B:Engine Coolant Temp.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 500.0f;
	fValue = float(n % (long(fValueHi) * 2 * 60)) / 60.0f;
	//fValue = ::fmodf(float(n) / 60.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Engine Coolant Temp' Value='%f'/>", (float)fValue );
	//sprintf_s( sData, sizeof(sData), "%f", fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "Engine Coolant Temp", sData );


	nSel = pDict->LocateEntry( "B:Engine Oil Temp.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 500.0f;
	fValue = float(n % (long(fValueHi) * 2 * 50)) / 50.0f;
	//fValue = ::fmodf(float(n) / 50.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Engine Oil Temp' Value='%f'/>", (float)fValue );
	//sprintf_s( sData, sizeof(sData), "%f", fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "Engine Oil Temp", sData );


	nSel = pDict->LocateEntry( "B:Engine Oil Pressure.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 500.0f;
	fValue = float(n % (long(fValueHi) * 2 * 200)) / 200.0f;
	//fValue = ::fmodf(float(n) / 200.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Engine Oil Pressure' Value='%f'/>", (float)fValue );
	//sprintf_s( sData, sizeof(sData), "%f", fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "Engine Oil Pressure", sData );


	nSel = pDict->LocateEntry( "B:Trans Oil Temp.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 500.0f;
	fValue = float(n % (long(fValueHi) * 2 * 80)) / 80.0f;
	//fValue = ::fmodf(float(n) / 80.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Trans Oil Temp' Value='%f'/>", (float)fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );


	nSel = pDict->LocateEntry( "B:Trans Oil Pressure.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 500.0f;
	fValue = ::fmodf(float(n) / 70.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Trans Oil Pressure' Value='%f'/>", (float)fValue );
	//sprintf_s( sData, sizeof(sData), "%f", fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "Engine Oil Pressure", sData );




	nSel = pDict->LocateEntry( "B:Battery Voltage.High" );
	pv = pDict->GetData( nSel );
	fValueHi = pv ? float(pv->GetValueFloat()) : 40.0f;
	fValue = ::fmodf(float(n) / 800.0f, fValueHi * 2.0f);
	if ( fValueHi < fValue )
		fValue = fValueHi * 2.0f - fValue;
	sprintf_s( sData, sizeof(sData), "<Param ID='Battery Voltage' Value='%f'/>", (float)fValue );
	//sprintf_s( sData, sizeof(sData), "%f", fValue );
	strcat_s( m_sData, sizeof(m_sData), sData );
	//pAct->UpdateEntry( "Engine Oil Pressure", sData );



	char	sTime[80];
	CDateTime	t;
	//long	nOffset = t.TimeAdjustOffset();
	t = m_tTimeb.time;// + nOffset;
	t.FormatGMT( sTime, sizeof(sTime), "%Y-%m-%d %H:%M:%S Z" );
	sprintf_s( sData, sizeof(sData), "<Param ID='Date/Time' Value='%s'/>", sTime );
	strcat_s( m_sData, sizeof(m_sData), sData );

#endif

	strcat_s( m_sData, sizeof(m_sData), "</Parameters>" );
	strcat_s( m_sData, sizeof(m_sData), "</VehicleData>" );


	SampleReadCallBack	callback( m_sData );
	m_pVehicleData->LoadData( &callback );




}
//END_OVERRUN_WARNING


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


void	CXMLSampleLoader::CalculateMilliTime
		(
		void
		)
{
	::ftime( &m_tTimeb );
	if ( 0 == gmtime_s( &m_tTm, &m_tTimeb.time ) )
	{
		//m_tTm = *::gmtime( &m_tTimeb.time );

		long	nCount = m_tTimeb.millitm + (m_tTimeb.time & 0xFFFFF) * 1000;
		if ( 0 == m_nMilliStart )
			m_nMilliStart = nCount;

		long	nSpan = nCount - m_nMilliStart;
		if ( nSpan < 0 )
			nSpan += 0x100000 * 1000;
		m_nMilli = nSpan;
	}
	else
	{
		m_nMilli = 0;
	}
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  23-Aug-2009

\+---------------------------------------------------------------------*/
