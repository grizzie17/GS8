/*---------------------------------------------------------------------+\
|
|	CCommandProcessorForPlugins.cpp  --  brief description of what CCommandProcessor.cpp is for
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
#include "CCommandProcessorForPlugins.h"

#include "LogFile.h"
#include "CFactoryPlugin.h"
#include "IPluginLibrary.h"

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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CCommandProcessorForPlugins - constructor

\+---------------------------------------------------------------------*/
CCommandProcessorForPlugins::CCommandProcessorForPlugins
		(
		void
		)
		: inherited()
		, m_tCommands()
		, m_pLibrary( 0 )
		, m_pDictionary( 0 )
		, m_pDictCommands( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CCommandProcessorForPlugins - destructor

\+---------------------------------------------------------------------*/
CCommandProcessorForPlugins::~CCommandProcessorForPlugins
		(
		void
		)
{
	THashTableEnumerator< VDictionary::Selector, ICommandPluginPtr>
			enumCmd = m_tCommands.GetEnumerator();

	while ( enumCmd.MoveNext() )
	{
		const ICommandPluginPtr*	h = enumCmd.Current();
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
void	CCommandProcessorForPlugins::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	inherited::SetApplication( p );

	m_pDictionary = p->Dictionary();

	m_pLibrary = (IPluginLibraryPtr)p->QueryCOMObject( IXID_IPluginLibrary );
}



/*---------------------------------------------------------------------+\

 * InitializeFunctions -

\+---------------------------------------------------------------------*/
void	CCommandProcessorForPlugins::InitializeFunctions
		(
		void
		)
{
	inherited::InitializeFunctions();


	m_pDictCommands = m_pApplication->DictPageCommands();
	if ( m_pDictCommands )
	{
		CVariantDataPtr	pv;
		CCharString		sXML;

		pv = m_pApplication->Configuration()->GetEntry( "Active Commands" );
		if ( pv )
			sXML = pv->GetValueCCharString();
		else
			sXML = "default";

		ISupportsArray*	aSup;
		CCharString		sPath = "plugins/commands";

		sPath += sXML;


		m_pLibrary->SetBaseFolder( GetApplicationFolder() );

		CFactoryPlugin	plug;
		plug.SetRelativePath( "plugins/commands" );
		plug.SetVariableIF( m_pApplication->Configuration());
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
void	CCommandProcessorForPlugins::AddCommandPlugin
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
bool	CCommandProcessorForPlugins::ProcessRequest
		(
		VDictionary::Selector	sel,
		ConstCVariantDataRef	vDataRef
		)
{
	bool	bResult = inherited::ProcessRequest( sel, vDataRef );
	if ( ! bResult )
	{
		const ICommandPluginPtr*	h = m_tCommands.Find( sel );
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
		CCommandProcessorForPlugins::RegisterCommand
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
		CCommandProcessorForPlugins::RegisterCommand
		(
		ConstCCharDescriptorRef	rCommandName,
		CVariantDataPtr			pInitialState //= 0
		)
{
	VDictionary::Selector	sel = 0;

	if ( m_pCommandPlugin  &&  0 < rCommandName.Length() )
	{
		CVariantData	v;
		char			sTemp[256];

		strcpy_s( sTemp, sizeof(sTemp), "C:" );
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
