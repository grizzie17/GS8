/*---------------------------------------------------------------------+\
|
|	CmdTouchCalibrate.cpp  --  Plugin to process touch screen points
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
#include "CmdTouchCalibrate.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "CApplicationGauge.h"
#include "CScreen.h"
#include "CGauge.h"
#include "CFactoryPanel.h"
#include "CFactoryGauge.h"

#include "VPluginFactory.h"


using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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
PLUGIN_CREATE_FACTORY( CmdTouchCalibrate );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdTouchCalibrate - constructor

\+---------------------------------------------------------------------*/
CmdTouchCalibrate::CmdTouchCalibrate
		(
		void
		)
		: VPluginCommand()
		, m_pDictionary( 0 )
		, m_nCmdInstall( 0 )
		, m_nCmdCalibrate( 0 )
		, m_nCmdStart( 0 )
		, m_nCmdPoint( 0 )
		, m_nCmdTimeout( 0 )
		, m_nUPointX( 0 )
		, m_nUPointY( 0 )
		, m_nUScreenX( 0 )
		, m_nUScreenY( 0 )
		, m_nUPanel( 0 )
		, m_vUPanel()
		, m_nUPrompt( 0 )
		, m_tMatrix()
		, m_sFilePath()
		, m_sFilename()
		, m_fTolerance( 20.0f )
		, m_nCount( 0 )
{
}

CmdTouchCalibrate::CmdTouchCalibrate
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner )
		, m_pDictionary( 0 )
		, m_nCmdInstall( 0 )
		, m_nCmdCalibrate( 0 )
		, m_nCmdStart( 0 )
		, m_nCmdPoint( 0 )
		, m_nCmdTimeout( 0 )
		, m_nUPointX( 0 )
		, m_nUPointY( 0 )
		, m_nUScreenX( 0 )
		, m_nUScreenY( 0 )
		, m_nUPanel( 0 )
		, m_vUPanel()
		, m_nUPrompt( 0 )
		, m_tMatrix()
		, m_sFilePath()
		, m_sFilename()
		, m_fTolerance( 20.0f )
		, m_nCount( 0 )
{
}

CmdTouchCalibrate::CmdTouchCalibrate
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner )
		, m_pDictionary( 0 )
		, m_nCmdInstall( 0 )
		, m_nCmdCalibrate( 0 )
		, m_nCmdStart( 0 )
		, m_nCmdPoint( 0 )
		, m_nCmdTimeout( 0 )
		, m_nUPointX( 0 )
		, m_nUPointY( 0 )
		, m_nUScreenX( 0 )
		, m_nUScreenY( 0 )
		, m_nUPanel( 0 )
		, m_vUPanel()
		, m_nUPrompt( 0 )
		, m_tMatrix()
		, m_sFilePath()
		, m_sFilename()
		, m_fTolerance( 20.0f )
		, m_nCount( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~CmdTouchCalibrate - destructor

\+---------------------------------------------------------------------*/
CmdTouchCalibrate::~CmdTouchCalibrate
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetSize -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::SetSize
		(
		long	nWidth,
		long	nHeight
		)
{
	m_fScreenWidth = GFLOAT(nWidth);
	m_fScreenHeight = GFLOAT(nHeight);

	return true;
}


/*---------------------------------------------------------------------+\

 * Transform -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Transform
		(
		GFLOAT*	pOutX,
		GFLOAT*	pOutY,
		GFLOAT&	rInX,
		GFLOAT&	rInY
		)
{
	GFLOAT	dx;
	GFLOAT	dy;

	m_tMatrix.Transform( dx, dy, rInX, rInY );

	if ( dx < -m_fScreenWidth )
		dx = -m_fScreenWidth;
	else if ( m_fScreenWidth*GFLOAT_2 < dx )
		dx = m_fScreenWidth*GFLOAT_2;

	if ( dy < -m_fScreenHeight )
		dy = -m_fScreenHeight;
	else if ( m_fScreenHeight*GFLOAT_2 < dy )
		dy = m_fScreenHeight*GFLOAT_2;

	//DbgPrint( "Touch X=%f, Y=%f\n", dx, dy );

	*pOutX = dx;
	*pOutY = dy;

	return true;
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Install - load touch panel and gauges

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Install
		(
		ConstCVariantDataRef	//r
		)
{
	CScreenPtr	pScreen = m_pApplication->Screen();
	CPanelPtr	pP = 0;
	CGaugePtr	pG = 0;

	// gauges to all panels
	CFactoryGaugePtr	pGgeFactory = new CFactoryGauge;
	if ( pGgeFactory )
	{
		pGgeFactory->SetDictionary( m_pDictionary );

		CPanelEnumerator	tEnum = pScreen->GetEnumerator();
		while ( tEnum.MoveNext() )
		{
			pP = tEnum.Value();
			if ( pP )
			{
				pG = pGgeFactory->Make( "gauges/touch-recalibrate" );
				if ( pG )
				{
					pP->AddChild( pG );
					long n = pG->MouseAreas();
					if ( 0 < n )
						pP->IncrementMouseAreas( n );
				}
			}
		}
		delete pGgeFactory;
	}


	// add our panel
	CFactoryPanelPtr	pPnlFactory = new CFactoryPanel;
	if ( pPnlFactory )
	{
		pPnlFactory->SetDictionary( m_pDictionary );

		pP = pPnlFactory->Make( "panels/touch_calibrate" );
		if ( pP )
		{
			pScreen->AddPanel( pP, "touch_calibrate" );
		}
		delete pPnlFactory;
	}

	return true;
}

/*---------------------------------------------------------------------+\

 * Calibrate -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Calibrate
		(
		ConstCVariantDataRef	//r
		)
{
	//	save U:PANEL value
	m_nUPanel = m_pDictionary->LocateEntry( "U:PANEL" );

	CVariantDataPtr	pv;

	pv = m_pDictionary->GetData( m_nUPanel );
	if ( pv )
		m_vUPanel = *pv;
	else
		m_vUPanel = "err_uknown";

	//	set U:PANEL to touch_calibrate
	CVariantData	v( "touch_calibrate" );
	m_pDictionary->PutData( m_nUPanel, &v );

	//	clear any existing calibration data in the application
	m_pApplication->SetMouseTransform( 0 );


	return true;
}


/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Start
		(
		ConstCVariantDataRef	//r
		)
{
	VDictionary::Selector	nSel;

	nSel = m_pDictionary->LocateEntry( "S:SCREEN WIDTH" );
	if ( nSel )
	{
		GFLOAT	fWidth = 0;
		GFLOAT	fHeight = 0;
		CVariantDataPtr	pv;

		pv = m_pDictionary->GetData( nSel );
		if ( pv )
			fWidth = pv->GetValueFloat();

		nSel = m_pDictionary->LocateEntry( "S:SCREEN HEIGHT" );
		if ( nSel )
		{
			pv = m_pDictionary->GetData( nSel );
			if ( pv )
				fHeight = pv->GetValueFloat();

			// set four corners
			m_aPoints[0].x = 50.0f;
			m_aPoints[0].y = 50.0f;
			m_aPoints[1].x = fWidth - 50.0f;
			m_aPoints[1].y = fHeight / 3.0f;
			m_aPoints[2].x = fWidth / 2.0f;
			m_aPoints[2].y = fHeight - 50.0f;

			m_aPoints[3].x = 60.0f;
			m_aPoints[3].y = fHeight / 2.0f;
			m_aPoints[4].x = fWidth / 2.0f;
			m_aPoints[4].y = fHeight / 4.0f;
			//m_aPoints[5].x = fWidth - 40.0f;
			//m_aPoints[5].y = 40.0f;
			//m_aPoints[6].x = fWidth - 40.0f;
			//m_aPoints[6].y = fHeight - 40.0f;
			//m_aPoints[7].x = 40.0f;
			//m_aPoints[7].y = fHeight - 40.0f;


			m_nCount = 0;

			SetVariable( m_nCount );

			CVariantData	v = " ";
			m_pDictionary->PutData( m_nUPrompt, &v );
		}
	}

	return true;
}


/*---------------------------------------------------------------------+\

 * SetVariable - Set (U:Touch Point)

\+---------------------------------------------------------------------*/
void	CmdTouchCalibrate::SetVariable
		(
		int n
		)
{
	CVariantData	v;

	v = m_aPoints[n].x;
	m_pDictionary->PutData( m_nUPointX, &v );

	v = m_aPoints[n].y;
	m_pDictionary->PutData( m_nUPointY, &v );
}


/*---------------------------------------------------------------------+\

 * Point -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Point
		(
		ConstCVariantDataRef	//r
		)
{
	//	receive next points from U:Touch Point and U:Touch Screen
	//	When points equals three perform calibration calculation
	//		Save calibration data
	//		Activate calibration data in application
	//		Restore U:PANEL to saved value

	CCharString	s = " ";

	if ( m_nCount < TOUCH_K_POINTCOUNT )
	{
		CVariantDataPtr	pv;

		pv = m_pDictionary->GetData( m_nUScreenX );
		if ( pv )
			m_aScreen[m_nCount].x = pv->GetValueFloat();
		pv = m_pDictionary->GetData( m_nUScreenY );
		if ( pv )
			m_aScreen[m_nCount].y = pv->GetValueFloat();
		++m_nCount;

		if ( m_nCount < 3 )
		{
			SetVariable( m_nCount );
			s.Format( "Select Point #%d", m_nCount+1 );
		}
		else if ( 3 == m_nCount )
		{
			if ( ! GenerateMatrix() )
			{
				m_nCount = 0;
				s = "Please reselect points";
			}
			SetVariable( m_nCount );
		}
		else if ( m_nCount < TOUCH_K_POINTCOUNT )
		{
			GFLOAT	x;
			GFLOAT	y;
			GFLOAT	fTol = m_fTolerance;

			int		i = m_nCount - 1;

			m_tMatrix.Transform( x, y,
								m_aScreen[i].x, m_aScreen[i].y );

			if ( fTol < fabsf( x - m_aPoints[i].x )
				||	fTol < fabsf( y - m_aPoints[i].y ) )
			{
				m_nCount = 0;
				s = "Please reselect points";
				DbgPrint( "Point offsets x = %f, y = %f\n",
						x - m_aPoints[i].x,
						y - m_aPoints[i].y );
			}
			SetVariable( m_nCount );

		}
		else
		{
			if ( ValidateMatrix() )
			{
				if ( SaveData() )
				{
					m_pApplication->SetMouseTransform( INTERFACE_THIS( IMouseTransformPtr ) );

					m_pDictionary->PutData( m_nUPanel, &m_vUPanel );
				}
			}
			else
			{
				m_nCount = 0;
				SetVariable( m_nCount );
				s = "Please reselect points";
			}
		}
		CVariantData	v = s;
		m_pDictionary->PutData( m_nUPrompt, &v );
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * Timeout -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Timeout
		(
		ConstCVariantDataRef	//r
		)
{
	m_tMatrix = CMatrix3x3();	// set the matrix to identity
	if ( SaveData() )
	{
		m_pApplication->SetMouseTransform( INTERFACE_THIS( IMouseTransformPtr ) );

		m_pDictionary->PutData( m_nUPanel, &m_vUPanel );
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * LoadData -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::LoadData
		(
		void
		)
{
	bool	bResult = false;

	if ( 0 < m_sFilePath.Length() )
	{
		if ( FileExists( m_sFilePath.Pointer() ) )
		{
			FILE*	pf;

			if ( 0 == fopen_s( &pf, m_sFilePath.Pointer(), "r" ) )
			{
				char	sBuffer[256];

				::fseek( pf, 0, SEEK_END );
				size_t	nSize = (size_t)::ftell( pf );
				::fseek( pf, 0, SEEK_SET );

				if ( sizeof(sBuffer) < nSize )
					nSize = sizeof(sBuffer);

				::fread( sBuffer, 1, nSize, pf );

				::fclose( pf );

				GFLOAT	a[9];
				size_t	n, i, j;

				j = 0;
				for ( i = 0; i < 9; ++i )
				{
					a[i] = ParseFloat( sBuffer + j, nSize - j, &n );
					if ( 0 < n )
					{
						j += n;
						while ( sBuffer[j] && sBuffer[j] <= ' ' )
							++j;
					}
				}

				m_tMatrix.Set( a[0], a[1], a[2],
							a[3], a[4], a[5],
							a[6], a[7], a[8] );

				bResult = true;

			}
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * SaveData -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::SaveData
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
			GFLOAT	a[9];

			m_tMatrix.Get( &a[0], &a[1], &a[2],
							&a[3], &a[4], &a[5],
							&a[6], &a[7], &a[8] );

			fprintf( pf, "%0.10f %0.10f %0.10f\n", double(a[0]), double(a[1]), double(a[2]) );
			fprintf( pf, "%0.10f %0.10f %0.10f\n", double(a[3]), double(a[4]), double(a[5]) );
			fprintf( pf, "%0.10f %0.10f %0.10f\n", double(a[6]), double(a[7]), double(a[8]) );
			fclose( pf );
			bResult = true;
		}
	}
	return bResult;

}


/*---------------------------------------------------------------------+\

 * BuildPath -

\+---------------------------------------------------------------------*/
CCharString
		CmdTouchCalibrate::BuildPath
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

 * GenerateMatrix -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::GenerateMatrix
		(
		void
		)
{
	bool	bResult = true;

	double	nDivider = ((m_aScreen[0].x - m_aScreen[2].x) * (m_aScreen[1].y - m_aScreen[2].y))
					- ((m_aScreen[1].x - m_aScreen[2].x) * (m_aScreen[0].y - m_aScreen[2].y));

	if ( 0 == nDivider )
	{
		m_tMatrix = CMatrix3x3::_Identity();
		bResult = false;
	}
	else
	{
		double	a, b;
		double	c, d;
		double	e, f;

		double	fDivider = double(nDivider);

		a = double(((m_aPoints[0].x - m_aPoints[2].x) * (m_aScreen[1].y - m_aScreen[2].y))
			- ((m_aPoints[1].x - m_aPoints[2].x) * (m_aScreen[0].y - m_aScreen[2].y))) / fDivider ;

		b = double(((m_aScreen[0].x - m_aScreen[2].x) * (m_aPoints[1].x - m_aPoints[2].x))
			- ((m_aPoints[0].x - m_aPoints[2].x) * (m_aScreen[1].x - m_aScreen[2].x))) / fDivider ;

		c = double((m_aScreen[2].x * m_aPoints[1].x - m_aScreen[1].x * m_aPoints[2].x) * m_aScreen[0].y
			+ (m_aScreen[0].x * m_aPoints[2].x - m_aScreen[2].x * m_aPoints[0].x) * m_aScreen[1].y
			+ (m_aScreen[1].x * m_aPoints[0].x - m_aScreen[0].x * m_aPoints[1].x) * m_aScreen[2].y) / fDivider ;

		d = double(((m_aPoints[0].y - m_aPoints[2].y) * (m_aScreen[1].y - m_aScreen[2].y))
			- ((m_aPoints[1].y - m_aPoints[2].y) * (m_aScreen[0].y - m_aScreen[2].y))) / fDivider ;

		e = double(((m_aScreen[0].x - m_aScreen[2].x) * (m_aPoints[1].y - m_aPoints[2].y))
			- ((m_aPoints[0].y - m_aPoints[2].y) * (m_aScreen[1].x - m_aScreen[2].x))) / fDivider ;

		f = double((m_aScreen[2].x * m_aPoints[1].y - m_aScreen[1].x * m_aPoints[2].y) * m_aScreen[0].y
			+ (m_aScreen[0].x * m_aPoints[2].y - m_aScreen[2].x * m_aPoints[0].y) * m_aScreen[1].y
			+ (m_aScreen[1].x * m_aPoints[0].y - m_aScreen[0].x * m_aPoints[1].y) * m_aScreen[2].y) / fDivider ;

		m_tMatrix = CMatrix3x3( GFLOAT(a), GFLOAT(d),
								GFLOAT(b), GFLOAT(e),
								GFLOAT(c), GFLOAT(f) );

	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ValidateMatrix -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::ValidateMatrix
		(
		void
		)
{
	bool	bResult = true;
	GFLOAT	x;
	GFLOAT	y;
	GFLOAT	fTol = m_fTolerance;

	for ( int i = 0; i < TOUCH_K_POINTCOUNT; ++i )
	{

		m_tMatrix.Transform( x, y,
							m_aScreen[i].x, m_aScreen[i].y );

		if ( fTol < fabsf( x - m_aPoints[i].x )
			||	fTol < fabsf( y - m_aPoints[i].y ) )
		{
			bResult = false;
			break;
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * MidPoint -

\+---------------------------------------------------------------------*/
void	CmdTouchCalibrate::MidPoint
		(
		GFLOAT*	px,
		GFLOAT*	py,
		UPoint&	pt1,
		UPoint&	pt2
		)
{
	*px = (pt1.x + pt2.x) / GFLOAT_2;
	*py = (pt1.y + pt2.y) / GFLOAT_2;
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

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CmdTouchCalibrate::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = VPluginCommand::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IMouseTransform )
			pI = INTERFACE_THIS( IMouseTransformPtr );
		else
			pI = 0;
	}

	return pI;
}


void	CmdTouchCalibrate::FinalRelease
		(
		void
		)
{
	VPluginCommand::FinalRelease();
	m_tMatrix = CMatrix3x3();
}




/*---------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	m_sFilePath = BuildPath();


	//DbgPrint( "\n\nCmdTouchCalibrate::Initialize\n\n" );


	// some thoughts::::
	//	Test to see if TouchCalibration#.dat is present
	//	If it is then load the file and activate the data in the application
	//	If not get setup to perform calibration...
	//		Queue command for (C:Touch Calibrate)

	m_nCmdInstall = pCommandSetup->RegisterCommand( "Touch Install" );
	m_nCmdCalibrate = pCommandSetup->RegisterCommand( "Touch Calibrate" );
	m_nCmdStart = pCommandSetup->RegisterCommand( "Touch Start" );
	m_nCmdPoint = pCommandSetup->RegisterCommand( "Touch Point" );
	m_nCmdTimeout = pCommandSetup->RegisterCommand( "Touch Timeout" );

	m_pDictionary = m_pApplication->Dictionary();
	if ( m_pDictionary )
	{
		m_nUPointX = m_pDictionary->LocateEntry( "U:Touch Point X" );
		m_nUPointY = m_pDictionary->LocateEntry( "U:Touch Point Y" );

		m_nUScreenX = m_pDictionary->LocateEntry( "U:Touch Screen X" );
		m_nUScreenY = m_pDictionary->LocateEntry( "U:Touch Screen Y" );

		m_nUPhase = m_pDictionary->LocateEntry( "U:Touch Phase" );
		m_nUPrompt = m_pDictionary->LocateEntry( "U:Touch Prompt" );

		CVariantData	v( 0L );
		m_pDictionary->PutData( m_nCmdInstall, &v );

		if ( LoadData() )
		{
			m_pApplication->SetMouseTransform( INTERFACE_THIS( IMouseTransformPtr ) );
		}
		else
		{
			m_pDictionary->PutData( m_nUPhase, &v );

			// add command to the queue
			m_pDictionary->PutData( m_nCmdCalibrate, &v );
		}
	}

	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdTouchCalibrate::ProcessRequest
		(
		VDictionary::Selector	selCommand,
		ConstCVariantDataRef	vData
		)
{
	bool	bResult = true;
	if ( selCommand == m_nCmdCalibrate )
		bResult = Calibrate( vData );
	else if ( selCommand == m_nCmdStart )
		bResult = Start( vData );
	else if ( selCommand == m_nCmdPoint )
		bResult = Point( vData );
	else if ( selCommand == m_nCmdInstall )
		bResult = Install( vData );
	else if ( selCommand == m_nCmdTimeout )
		bResult = Timeout( vData );
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
bool	CmdTouchCalibrate::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );

	if ( bResult )
	{
		m_sFilename = pConfig->GetParameterAsString( "Filename", "touch" );
		m_fTolerance = pConfig->GetParameterAsFloat( "Tolerance", 20.0f );
	}

	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
