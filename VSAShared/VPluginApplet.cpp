/*---------------------------------------------------------------------+\
|
|	VPluginApplet.cpp  --  base class for applet plugins
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
	21-Dec-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "VPluginApplet.h"

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
/**--------------------------------------------------------------------+\

 * <summary>VPluginApplet - constructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
VPluginApplet::VPluginApplet
		(
		void
		)
		: inherited(),
		m_sID(),
		m_bRunning(false),
		m_oMutex(),
		m_pHusk( 0 )
{
}

VPluginApplet::VPluginApplet
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_sID(),
		m_bRunning(false),
		m_oMutex(),
		m_pHusk( 0 )
{
}

VPluginApplet::VPluginApplet
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_sID(),
		m_bRunning(false),
		m_oMutex(),
		m_pHusk( 0 )
{
}

/**--------------------------------------------------------------------+\

 * <summary>~VPluginApplet - destructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
VPluginApplet::~VPluginApplet
		(
		void
		)
{
	if ( IsRunning() )
		OnExit();

	if ( m_pHusk )
		m_pHusk->Release();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IApplet
\+---------------------------------------------------------------------*/

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult	VPluginApplet::OnLoad
		(
		IHuskPtr	pHusk
		)
{
	NResult	nr = NR_E_FAIL;

	m_pHusk = QI_( pHusk, IHusk );
	if ( m_pHusk )
		nr = NR_S_SUCCESS;

	return nr;
}

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult	VPluginApplet::OnUnload
		(
		void
		)
{
	if ( m_pHusk )
	{
		m_pHusk->Release();
		m_pHusk = 0;
	}

	return NR_S_SUCCESS;
}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult	VPluginApplet::OnStart
		(
		)
{
	NResult	nr = NR_S_SUCCESS;

	m_bRunning = true;

	return nr;
}

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult	VPluginApplet::OnExit
		(
		)
{
	NResult	nr = NR_S_SUCCESS;

	m_bRunning = false;

	return nr;
}

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult	VPluginApplet::OnPause
		(
		)
{
	NResult	nr = NR_S_SUCCESS;

	m_bRunning = false;

	return nr;
}

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult	VPluginApplet::OnResume
		(
		)
{
	NResult	nr = NR_S_SUCCESS;

	m_bRunning = true;

	return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>IsRunning - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	VPluginApplet::IsRunning
		(
		void
		)
{
	CMutexLocker	lock( &m_oMutex );

	return m_bRunning;
}


/**--------------------------------------------------------------------+\

 * <summary>GetID - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
ConstYogi::Core::CCharStringRef
		VPluginApplet::GetID
		(
		void
		)
{
	return m_sID;
}



/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/**--------------------------------------------------------------------+\

 * <summary>Load - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	VPluginApplet::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	m_sID = pConfig->GetID();
	return inherited::Load( pConfig, pLib );
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

/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
void*	VPluginApplet::FindInternalInterface
		(
		ConstIXIDRef rIID
		)
{
	void*	p = inherited::FindInternalInterface( rIID );
	if ( p )
		return p;

	if ( rIID == IXID_IApplet )
		return INTERFACE_THIS( IAppletPtr );
	else
		return 0;
}


}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
