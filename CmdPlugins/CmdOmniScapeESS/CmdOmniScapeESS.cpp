/*---------------------------------------------------------------------+\
|
|	CmdOmniScapeESS.cpp  --  Plugin to process touch screen points
|
|	Purpose:
|
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
	08-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Major cleanup to protect from generating bogus matrix
	04-Aug-2010			J.Griswold		(Reviewed by: xxxx)
        Fixed overflow problem when calculating touch matrix
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CmdOmniScapeESS.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "CApplicationGauge.h"
#include "CScreen.h"
#include "CGauge.h"
#include "CFactoryPanel.h"
#include "CFactoryGauge.h"
#include "CSerial.h"

#include "VPluginFactory.h"
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
PLUGIN_CREATE_FACTORY( CmdOmniScapeESS );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdOmniScapeESS - constructor

\+---------------------------------------------------------------------*/
CmdOmniScapeESS::CmdOmniScapeESS
		(
		void
		)
		: inherited(),
		m_oMutex(),
		m_pDictionary( 0 ),
		m_nCmdStart( 0 ),
		m_sFilePath(),
		m_sFilename(),
		m_sServerIP(),
		m_aPorts( 0 )
{
}

CmdOmniScapeESS::CmdOmniScapeESS
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_oMutex(),
		m_pDictionary( 0 ),
		m_nCmdStart( 0 ),
		m_sFilePath(),
		m_sFilename(),
		m_sServerIP(),
		m_aPorts( 0 )
{
}

CmdOmniScapeESS::CmdOmniScapeESS
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_oMutex(),
		m_pDictionary( 0 ),
		m_nCmdStart( 0 ),
		m_sFilePath(),
		m_sFilename(),
		m_sServerIP(),
		m_aPorts( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~CmdOmniScapeESS - destructor

\+---------------------------------------------------------------------*/
CmdOmniScapeESS::~CmdOmniScapeESS
		(
		void
		)
{
	StopThreads();
	if ( m_aPorts )
		delete [] m_aPorts;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::essStart
		(
		ConstCVariantDataRef	//r
		)
{
	if ( ! m_bRunning )
	{
		StartThreads();
	}

	return true;
}


/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::essReset
		(
		ConstCVariantDataRef	//r
		)
{

	StopThreads();
	UpdateDictionary();

	StartThreads();


	return true;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::essCalculate
		(
		ConstCVariantDataRef	//r
		)
{
	UpdateDictionary();

	return true;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::essVirgin
		(
		ConstCVariantDataRef	//r
		)
{
	for ( uindex_t i = 0; i < m_nPortCount; ++i )
	{
		if ( m_aPorts[i].pConsole  &&  m_aPorts[i].bOpen )
		{
			m_aPorts[i].pConsole->Virginize();
		}
	}

	return true;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::StartThreads
		(
		void
		)
{
	if ( m_bStaticDisplay )
		return false;


	CMutexLocker	lock( &m_oMutex );
	//CVariantData	v;

	for ( uindex_t i = 0; i < m_nPortCount; ++i )
	{
		m_aPorts[i].bOpen = false;
		if ( 0 < m_aPorts[i].sPortName.Length() )
		{
			if ( m_aPorts[i].pConsole )
			{
				if ( m_aPorts[i].pConsole->Start( m_pDictionary ) )
				{
					m_aPorts[i].bOpen = true;
					m_aPorts[i].pConsole->Calculate( m_pDictionary );
				}
				else
				{
					delete m_aPorts[i].pConsole;
					m_aPorts[i].pConsole = 0;
				}
			}
			else
			{
				CConsolePtr	pCons = new CConsole;
				if ( pCons )
				{
					pCons->LoadSettings( &m_oPortSettings );
					pCons->SetPortName( m_aPorts[i].sPortName.Pointer() );
					pCons->SetServerIP( m_sServerIP.Pointer() );
					pCons->SetCallback( long(i), m_pApplication );
					if ( pCons->Start( m_pDictionary ) )
					{
						m_aPorts[i].bOpen = true;
						m_aPorts[i].pConsole = pCons;
						pCons->Calculate( m_pDictionary );
					}
					else
					{
						m_aPorts[i].pConsole = 0;
						//pCons->Calculate( m_pDictionary );
						delete pCons;
					}
				}
			}
		}

	}
	m_bDirty = true;
	m_bRunning = true;
	return true;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::StopThreads
		(
		void
		)
{
	CMutexLocker	lock( &m_oMutex );

	for ( uindex_t i = 0; i < m_nPortCount; ++i )
	{
		if ( m_aPorts[i].pConsole  &&  m_aPorts[i].bOpen )
		{
			m_aPorts[i].pConsole->Stop( m_pDictionary );
			delete m_aPorts[i].pConsole;
			m_aPorts[i].pConsole = 0;
		}
		m_aPorts[i].bOpen = false;
	}
	m_bDirty = true;
	m_bRunning = false;

	return true;
}





/*---------------------------------------------------------------------+\

 * SaveData -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::SaveData
		(
		void
		)
{
	bool	bResult = false;

	if ( 0 < m_sFilePath.Length() )
	{
		FILE*	pf;

		if ( 0 == fopen_s( &pf, m_sFilePath.Pointer(), "w+" ) )
		{
			//GFLOAT	a[9];

			//m_tMatrix.Get( &a[0], &a[1], &a[2],
			//				&a[3], &a[4], &a[5],
			//				&a[6], &a[7], &a[8] );

			//fprintf( pf, "%0.10f %0.10f %0.10f\n", double(a[0]), double(a[1]), double(a[2]) );
			//fprintf( pf, "%0.10f %0.10f %0.10f\n", double(a[3]), double(a[4]), double(a[5]) );
			//fprintf( pf, "%0.10f %0.10f %0.10f\n", double(a[6]), double(a[7]), double(a[8]) );
			//fclose( pf );
			bResult = true;
		}
	}
	return bResult;

}


/*---------------------------------------------------------------------+\

 * BuildPath -

\+---------------------------------------------------------------------*/
CCharString
		CmdOmniScapeESS::BuildPath
		(
		void
		)
{
	char		sPath[1024];
	CCharString	sUserID;
	CCharString	sName;

	const char*	s = GetUserConfigFolder();

	sUserID = m_pApplication->GetUserID();

	sName.Format( "%s%s.calibrate",
				m_sFilename.Pointer(),
				(0 < sUserID.Length() ? sUserID.Pointer() : "") );

	PathBuild( sPath, sizeof(sPath), s, sName.Pointer() );

	return CCharString( sPath );
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CmdOmniScapeESS::UpdateDictionary
		(
		void
		)
{
	if ( m_bStaticDisplay )
		return;

	CMutexLocker	lock( &m_oMutex );

	for ( uindex_t i = 0; i < m_nPortCount; ++i )
	{
		if ( m_aPorts[i].pConsole  &&  m_aPorts[i].bOpen )
			m_aPorts[i].pConsole->Calculate( m_pDictionary );
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




/*---------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	m_sFilePath = BuildPath();

	m_nCmdStart = pCommandSetup->RegisterCommand( "ESS START" );
	m_nCmdReset = pCommandSetup->RegisterCommand( "ESS RESET" );
	m_nCmdCalculate = pCommandSetup->RegisterCommand( "ESS CALCULATE" );
	m_nCmdVirgin = pCommandSetup->RegisterCommand( "ESS VIRGIN" );



	m_bDirty = true;
	m_bRunning = false;

	m_pDictionary = m_pApplication->Dictionary();
	if ( m_pDictionary )
	{

		//long	nUESSCount;
		CVariantData	v = (long)m_nPortCount;
		m_pConstantsPage->AddEntry( "ESS COUNT", v );
		//nUESSCount = m_pDictionary->LocateEntry( "U:ESS COUNT" );
		//if ( nUESSCount )
		//{
		//	CVariantData	v = (long)m_nPortCount;
		//	m_pDictionary->PutData( nUESSCount, &v );
		//}
	}

	for ( uindex_t i = 0; i < m_nPortCount; ++i )
	{
		m_aPorts[i].bOpen = false;
		if ( 0 < m_aPorts[i].sPortName.Length() )
		{
			if ( m_bStaticDisplay )
			{
				m_aPorts[i].pConsole = 0;
			}
			else
			{
				CConsolePtr	pCons = new CConsole;
				if ( pCons )
				{
					pCons->LoadSettings( &m_oPortSettings );
					pCons->SetPortName( m_aPorts[i].sPortName.Pointer() );
					pCons->SetServerIP( m_sServerIP.Pointer() );
					pCons->SetCallback( long(i), m_pApplication );
					m_aPorts[i].pConsole = pCons;
				}
			}
		}

	}

	//UpdateDictionary();

	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::ProcessRequest
		(
		VDictionary::Selector	selCommand,
		ConstCVariantDataRef	vData
		)
{
	bool	bResult = true;
	if ( selCommand == m_nCmdCalculate )
		bResult = essCalculate( vData );
	else if ( selCommand == m_nCmdStart )
		bResult = essStart( vData );
	else if ( selCommand == m_nCmdReset )
		bResult = essReset( vData );
	else if ( selCommand == m_nCmdVirgin )
		bResult = essVirgin( vData );
	else
		bResult = false;
	return bResult;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdOmniScapeESS::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );

	if ( bResult )
	{
		CCharString	sField;
		CCharString	sValue;

		m_bStaticDisplay = pConfig->GetParameterAsBool( "Static Display", false );

		m_sServerIP = pConfig->GetParameterAsString( "Server IP", "192.168.0.141" );


		CSerial::StringArray	aPortList;

		CSerial::EnumeratePorts( &aPortList );

#if 1
#if defined( _DEBUG )
		long	n = long(aPortList.Length());
		DbgPrint( "%s\n", __PRETTY_FUNCTION__ );
		DbgPrint( "Enum Port Count = %d\n", n );
		for ( int i = 0; i < n; ++i )
		{
			DbgPrint( "  %s\n", aPortList[i].Pointer() );
		}
#endif
#endif

		if ( ! m_bStaticDisplay  &&   0 < aPortList.Length() )
		{
			m_nPortCount = aPortList.Length();

			m_aPorts = new XData[m_nPortCount];

			for ( uindex_t i = 0; i < m_nPortCount; ++i )
			{
				m_aPorts[i].bOpen = false;
				m_aPorts[i].pConsole = 0;
				CCharStringPtr	p = aPortList.PointArray( (index_t)i );
				if ( p )
					m_aPorts[i].sPortName = *p;
			}
		}
		else
		{

			m_nPortCount = pConfig->GetParameterAsUnsigned( "Port Count", 4 );

			m_aPorts = new XData[m_nPortCount];

			for ( uindex_t i = 0; i < m_nPortCount; ++i )
			{
				sField.Format( "Port %d", i + 1 );
				sValue.Format( "COM%d", i + 10 );
				m_aPorts[i].bOpen = false;
				m_aPorts[i].pConsole = 0;
				m_aPorts[i].sPortName = pConfig->GetParameterAsString( sField.Pointer(), sValue.Pointer() );
				//m_aPorts[i].ndsOpen = 0;
				//m_aPorts[i].ndsState = 0;
				//m_aPorts[i].ndsMessage = 0;
				//m_aPorts[i].nCount = 0;
			}
		}

		unsigned long		nBaud;
		unsigned int		nDataBits;
		GFLOAT				fStopBits;
		CSerial::EStopBits	eStopBits;
		CSerial::EParitys	eParity;
		CSerial::EFlow		eFlow;

		VPluginConfiguration::EnumDatum PLGParity[]
		= {
			{ CSerial::PAR_NONE, "NONE" },
			{ CSerial::PAR_ODD, "ODD" },
			{ CSerial::PAR_EVEN, "EVEN" },
			{ CSerial::PAR_MARK, "MARK" },
			{ CSerial::PAR_SPACE, "SPACE" }
		};

		VPluginConfiguration::EnumDatum	PLGFlow[]
		= {
			{ CSerial::FLOW_OFF, "OFF" },
			{ CSerial::FLOW_HARDWARE, "HARDWARE" },
			{ CSerial::FLOW_XONXOFF, "XONXOFF" }
		};


		nBaud = pConfig->GetParameterAsUnsigned( "Baud", 115200 );
		nDataBits = pConfig->GetParameterAsUnsigned( "Data Bits", 8 );
		fStopBits = pConfig->GetParameterAsFloat( "Stop Bits", 1 );
		if ( fStopBits == GFLOAT_1 )
			eStopBits = CSerial::STOP_1;
		else if ( fStopBits == GFLOAT(1.5) )
			eStopBits = CSerial::STOP_1_5;
		else if ( fStopBits == GFLOAT_2 )
			eStopBits = CSerial::STOP_2;
		else
			eStopBits = CSerial::STOP_1;
		eParity = (CSerial::EParitys)pConfig->GetParameterAsEnum( "Parity", PLGParity,
											sizeof(PLGParity)/sizeof(VPluginConfiguration::EnumDatum),
											0
											);
		eFlow = (CSerial::EFlow)pConfig->GetParameterAsEnum( "Handshaking", PLGFlow,
											sizeof(PLGFlow)/sizeof(VPluginConfiguration::EnumDatum),
											0
											);

		m_oPortSettings.SetBaud( nBaud );
		m_oPortSettings.SetDataBits( nDataBits );
		m_oPortSettings.SetParity( eParity );
		m_oPortSettings.SetStopBits( eStopBits );
		m_oPortSettings.SetHandshaking( eFlow );

	}

	m_bRunning = false;

	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
