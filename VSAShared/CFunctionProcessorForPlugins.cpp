/*---------------------------------------------------------------------+\
|
|	CFunctionProcessorForPlugins.cpp  --  brief description of what CFunctionProcessor.cpp is for
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
	12-Jul-2010			J.Griswold		(Reviewed by: P.Hogan)
		Add optional InitialState pointer for the RegisterCommand func.
    02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Fix possible crash in InitializeFunctions and
		assure all needed parameters are present in RegisterCommand
	16-May-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CFunctionProcessorForPlugins.h"

#include "LogFile.h"
#include "CFactoryPlugin.h"


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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CFunctionProcessorForPlugins - constructor

\+---------------------------------------------------------------------*/
CFunctionProcessorForPlugins::CFunctionProcessorForPlugins
		(
		void
		)
		: CFunctionProcessor(),
		m_tCommands(),
		m_pLibrary( 0 ),
		m_pDictionary( 0 ),
		m_pDictCommands( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CFunctionProcessorForPlugins - destructor

\+---------------------------------------------------------------------*/
CFunctionProcessorForPlugins::~CFunctionProcessorForPlugins
		(
		void
		)
{
	THashTableEnumerator< VDictionary::Selector, ICommandPluginPtr>
			enumCmd = m_tCommands.GetEnumerator();

	while ( enumCmd.MoveNext() )
	{
		ICommandPluginPtr*	h = enumCmd.Current();
		if ( h )
			(*h)->Release();
	}

	if ( m_pLibrary )
		m_pLibrary->Release();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
void	CFunctionProcessorForPlugins::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	CFunctionProcessor::SetApplication( p );

	m_pLibrary = (IPluginLibraryPtr)p->QueryCOMObject( IXID_IPluginLibrary );

	m_pDictionary = p->Dictionary();
}



/*---------------------------------------------------------------------+\

 * InitializeFunctions -

\+---------------------------------------------------------------------*/
void	CFunctionProcessorForPlugins::InitializeFunctions
		(
		void
		)
{
	CFunctionProcessor::InitializeFunctions();


	m_pDictCommands = m_pApplication->DictPageFunctions();
	if ( m_pDictCommands )
	{
		CVariantDataPtr	pv;
		Yogi::Core::CCharString		sXML;

		pv = m_pApplication->Configuration()->GetEntry( "Active Functions" );
		if ( pv )
			sXML = pv->GetValueYogi::Core::CCharString();
		else
			sXML = "default";

		ISupportsArray*	aSup;
		Yogi::Core::CCharString		sPath = "plugins/functions";

		sPath += sXML;


		m_pLibrary->SetBaseFolder( GetApplicationFolder() );

		CFactoryPlugin	plug;
		plug.SetRelativePath( "plugins/functions" );
		aSup = plug.Make( sXML.Pointer(), m_pLibrary );

		if ( aSup )
		{
			ISupportsPtr*	h = aSup->PointArray();
			if ( h )
			{
				ISupportsPtr*	hEnd = h + aSup->Length();
				while ( h < hEnd )
				{
					m_pCommandPlugin = QI_( *h, ICommandPlugin );
					if ( m_pCommandPlugin )
					{
						m_pCommandPlugin->Initialize( m_pApplication, (VCommandSetupPtr)this );
						m_pCommandPlugin->Release();
						m_pCommandPlugin = 0;
					}
					(*h)->Release();
					++h;
				}
			}

			delete aSup;
		}

	}
}



/*---------------------------------------------------------------------+\

 * AddCommandPlugin - Function used by external "managers" to
                               add plugin commands associated with devices
							   the "manager" controls

\+---------------------------------------------------------------------*/
void	CFunctionProcessorForPlugins::AddCommandPlugin
		(
		ISupportsPtr pSupports
		)
{
	if (pSupports)
	{
		m_pCommandPlugin = QI_( pSupports, ICommandPlugin );
		if ( m_pCommandPlugin )
		{
			m_pCommandPlugin->Initialize( m_pApplication, (VCommandSetupPtr)this );
			m_pCommandPlugin->Release();
			m_pCommandPlugin = 0;
		}
	}
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

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CFunctionProcessorForPlugins::ProcessRequest
		(
		VDictionary::Selector	sel,
		ConstCVariantDataRef	vDataRef
		)
{
	bool	bResult = CFunctionProcessor::ProcessRequest( sel, vDataRef );
	if ( ! bResult )
	{
		ICommandPluginPtr*	h = m_tCommands.Find( sel );
		if ( h )
		{
			bResult = (*h)->ProcessRequest( sel, vDataRef );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * RegisterCommand -

\+---------------------------------------------------------------------*/
VDictionary::Selector
		CFunctionProcessorForPlugins::RegisterCommand
		(
		const char*		sCommandName,
		CVariantDataPtr	pInitialState //= 0
		)
{
	Yogi::Core::CCharDescriptor	sName( sCommandName );
	return RegisterCommand( sName, pInitialState );
}


/*---------------------------------------------------------------------+\

 * RegisterCommand -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

VDictionary::Selector
		CFunctionProcessorForPlugins::RegisterCommand
		(
		ConstYogi::Core::CCharDescriptorRef	rCommandName,
		CVariantDataPtr			pInitialState //= 0
		)
{
	VDictionary::Selector	sel = 0;

	if ( m_pCommandPlugin  &&  0 < rCommandName.Length() )
	{
		CVariantData	v;
		char			sTemp[256];

		::strcpy_s( sTemp, sizeof(sTemp), "F:" );
		rCommandName.ConcatenateTo( sTemp, sizeof(sTemp) );

		sel = m_pDictionary->LocateEntry( sTemp );
		if ( ! sel )
		{
			if ( pInitialState )
				v = *pInitialState;

			m_pDictCommands->AddEntry( rCommandName.Pointer(), v );


			sel = m_pDictionary->LocateEntry( sTemp );
			if ( sel )
			{
				m_tCommands.Add( sel, m_pCommandPlugin );
				m_pCommandPlugin->AddRef();
			}
		}
	}

	return sel;
}

//END_OVERRUN_WARNING


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
