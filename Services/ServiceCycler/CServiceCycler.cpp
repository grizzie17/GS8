/*---------------------------------------------------------------------+\
|
|	CServiceCycler.cpp  --  brief description of what CServiceCycler.cpp is for
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
#include <limits.h>

#include "CServiceCycler.h"

#include "VPluginFactory.h"
#include "CFactoryPlugin.h"
#include "UPlatformTime.h"

#include "TComPointer.h"


namespace Yogi { namespace Gadget {
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

PLUGIN_CREATE_FACTORY( CServiceCycler );



/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CServiceCycler - constructor

\+---------------------------------------------------------------------*/
CServiceCycler::CServiceCycler
		(
		void
		)
		: inherited(),
		m_pApplication( 0 ),
		m_aNPage(),
		m_oMutex(),
		m_nFrequency( 200 ),
		m_sRepeaterList(),
		m_hThread( 0 ),
		m_bInitDone( false )
{
}

CServiceCycler::CServiceCycler
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_pApplication( 0 ),
		m_aNPage(),
		m_oMutex(),
		m_nFrequency( 200 ),
		m_sRepeaterList(),
		m_hThread( 0 ),
		m_bInitDone( false )
{
}

CServiceCycler::CServiceCycler
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_pApplication( 0 ),
		m_aNPage(),
		m_oMutex(),
		m_nFrequency( 200 ),
		m_sRepeaterList(),
		m_hThread( 0 ),
		m_bInitDone( false )
{
}

/*---------------------------------------------------------------------+\

 * CServiceCycler - destructor

\+---------------------------------------------------------------------*/
CServiceCycler::~CServiceCycler
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
|	 IApplicationUser
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
bool	CServiceCycler::SetApplication
		(
		CApplicationGaugePtr	p
		)
{
	bool	bResult = true;

	CMutexLocker	locker( &m_oMutex );
	m_pApplication = p;


	return bResult;
}










/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/







/*---------------------------------------------------------------------+\

 * RunGlue - Function to call "Run" from within spawned thread

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceCycler::RunGlue
		(
		void*	pVoid
		)
{
	CServiceCyclerPtr	pThis = (CServiceCyclerPtr)pVoid;

	return pThis->Run();
}


/*---------------------------------------------------------------------+\

 * Run -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceCycler::Run
		(
		void
		)
{

	LOCAL_PRINT( "CServiceCycler::Run - start\n" );


	//m_nSequence	= 1;
	while ( m_bRunning )
	{
		long	m = milliseconds();

		CycleRepeaters();

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

	return (UThreadRtn) 0;
}


bool	CServiceCycler::CycleRepeaters
		(
		void
		)
{
	NPage*	p = m_aNPage.PointArray();
	if ( p )
	{
		NPage*	pEnd = p + m_aNPage.Length();

		while ( p < pEnd )
		{
			p->pIRepeater->Cycle();
			++p;
		}
	}

	return true;
}


bool	CServiceCycler::LoadRepeaters
		(
		void
		)
{
	bool	bResult = false;

	CMutexLocker	lock( &m_oMutex );

	do_sequence
	{
		TIP(IPluginLibrary)	pLibrary = m_pApplication->FindCOMObject( "PluginLibrary" );
		if ( ! pLibrary )
			break;
		pLibrary->Release();	// release from FindCOMObject; TIP holds addref'd pointer

		pLibrary->SetBaseFolder( GetApplicationFolder() );

		CFactoryPlugin	plug;
		plug.SetRelativePath( "plugins/repeaters" );
		TPointer<ISupportsArray>	aSup = plug.Make( m_sRepeaterList.Pointer(), pLibrary );
		if ( ! aSup )
			break;

		ISupportsPtr*	h = aSup->PointArray();
		if ( ! h )
			break;

		ISupportsPtr*	hEnd = h + aSup->Length();

		while ( h < hEnd )
		{
			IServicePtr	pISvc = QI_( *h, IService );
			if ( pISvc )
			{
				CCharString	sID = pISvc->GetID();

				IRepeaterPtr	pIRepeater = QI_( pISvc, IRepeater );
				if ( pIRepeater )
				{
					NPage	page;

					page.sID = sID;
					page.pIRepeater = pIRepeater;
					pIRepeater->AddRef();

					if ( pIRepeater->Initialize( m_pApplication, 0 ) )
					{
						m_aNPage.AppendData( &page );
					}
					pIRepeater->Release();
				}
				pISvc->Release();
			}
			(*h)->Release();
			++h;
		}


		bResult = true;
	}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CServiceCycler::CalculateMilliTime
		(
		void
		)
{
	time_t	n;
	m_nMilli = milliseconds();
	m_nTime = ::time( &n );
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
void*	CServiceCycler::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IApplicationUser )
			pI = INTERFACE_THIS( IApplicationUserPtr );
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
bool	CServiceCycler::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		GFLOAT	f = pConfig->GetParameterAsFloatUnits( "Frequency", "seconds", 0.2f );

		m_nFrequency = long(f * 1000.0f);

		m_sRepeaterList = pConfig->GetParameterAsString( "Repeater List", "default" );

		bResult = true;
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
NResult	CServiceCycler::Start
		(
		void
		)
{
	NResult	nr = NR_E_NOTHREAD;

	LOCAL_PRINT( "CServiceCycler::Start - Begin\n" );

	do_sequence
	{
		if ( ! LoadRepeaters() )
			break;

		m_hThread = ThreadCreate( (UThreadFunction)RunGlue, this, "SvcCycler" );
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

		m_bRunning = false;

	}
	LOCAL_PRINT( "CServiceCycler::Start - End\n" );

	return nr;
}


/*---------------------------------------------------------------------+\

 * Stop -

\+---------------------------------------------------------------------*/
NResult	CServiceCycler::Stop
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





}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
