/*---------------------------------------------------------------------+\
|
|	CFactoryExternalXML.cpp  --  brief description of what CFactoryExternalXML.cpp is for
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
	21-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <string.h>
#include "CFactoryExternalXML.h"

#include "CFactoryPlugin.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
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

 * CFactoryExternalXML - constructor

\+---------------------------------------------------------------------*/
CFactoryExternalXML::CFactoryExternalXML
		(
		void
		)
		: inherited(),
		m_aList(),
		m_pApplication( 0 ),
		m_pLibrary( 0 ),
		m_pActive( 0 )
{
}

CFactoryExternalXML::CFactoryExternalXML
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_aList(),
		m_pApplication( 0 ),
		m_pLibrary( 0 ),
		m_pActive( 0 )
{
}

CFactoryExternalXML::CFactoryExternalXML
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_aList(),
		m_pApplication( 0 ),
		m_pLibrary( 0 ),
		m_pActive( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CFactoryExternalXML - copy constructor

\+---------------------------------------------------------------------*/
CFactoryExternalXML::~CFactoryExternalXML
		(
		void
		)
{
	THashTableEnumerator< CCharString, IExternalXMLPtr >
			enumCmd = m_aList.GetEnumerator();

	while ( enumCmd.MoveNext() )
	{
		IExternalXMLPtr*	h = enumCmd.Current();
		if ( h )
			(*h)->Release();
	}

	if ( m_pLibrary )
		m_pLibrary->Release();
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
bool	CFactoryExternalXML::SetApplication
		(
		CApplicationGaugePtr	p	// IN:	application pointer
		)
{
	bool	bResult = true;
	m_pApplication = p;

 	m_pLibrary = (IPluginLibraryPtr)p->QueryCOMObject( IXID_IPluginLibrary );

	// TODO: add other initialization code here

	CVariantDataPtr	pv;
	CCharString		sXML;

	pv = m_pApplication->Configuration()->GetEntry( "External XML" );
	if ( pv )
		sXML = pv->GetValueCCharString();
	else
		sXML = "default";


	ISupportsArray*	aSup;


	m_pLibrary->SetBaseFolder( GetApplicationFolder() );

	CFactoryPlugin	plug;
	plug.SetRelativePath( "plugins/externalxml" );
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
				IExternalXMLPtr		pExt = QI_( *h, IExternalXML );
				IApplicationUserPtr	pUser = QI_( *h, IApplicationUser );
				if ( pUser  &&  pExt )
				{
					pUser->SetApplication( m_pApplication );
					pUser->Release();
					pUser = 0;
					pExt->Initialize( this );
					pExt->Release();
				}
				(*h)->Release();
				++h;
			}
		}

		delete aSup;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\
|	 IExternalXML
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CFactoryExternalXML::Initialize
		(
		IExternalXMLServerPtr //p
		)
{
	return false;	// this is a dummy function
}


/*---------------------------------------------------------------------+\

 * GetCallBack -

\+---------------------------------------------------------------------*/


XMLLite::VReadCallBack*
		CFactoryExternalXML::GetCallBack
		(
		const char*	sArg
		)
{
	CCharDescriptor	tArg( sArg );

	return GetCallBack( tArg );
}

XMLLite::VReadCallBack*
		CFactoryExternalXML::GetCallBack
		(
		ConstCCharDescriptorRef	rArg
		)
{
	XMLLite::VReadCallBack*	pResult = 0;
	const char*	s = rArg.Pointer();

	// make sure that we don't have an active external processing
	if ( ! m_pActive )
	{

		if ( '@' == *s )
		{
			++s;
			size_t	n;

			char*	sSpace = ::strchr( (char*)s, ' ' );
			if ( sSpace )
			{
				n = static_cast<size_t>(sSpace - s);
			}
			else
			{
				n = rArg.Length() - 1;	// subtract for '@'
			}
			if ( 0 < n )
			{
				CCharString	sName( s, n );

				IExternalXMLPtr*	pIx = m_aList.Find( sName );
				if ( pIx )
				{
					m_pActive = *pIx;
					pResult = m_pActive->GetCallBack( rArg );
				}
			}
		}
	}
	return pResult;
}

/*---------------------------------------------------------------------+\

 * ReleaseCallBack -

\+---------------------------------------------------------------------*/
void	CFactoryExternalXML::ReleaseCallBack
		(
		XMLLite::VReadCallBack*	p
		)
{
	if ( m_pActive )
		m_pActive->ReleaseCallBack( p );
	m_pActive = 0;
}


/*---------------------------------------------------------------------+\
|	 IExternalXML
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Register -

\+---------------------------------------------------------------------*/
bool	CFactoryExternalXML::Register
		(
		const char*		sName,
		ISupportsPtr	pIF
		)
{
	bool			bResult = false;
	CCharString		tName( sName );
	IExternalXMLPtr*	hIx = m_aList.Find( tName );

	if ( ! hIx )
	{
		IExternalXMLPtr	pIx = QI_( pIF, IExternalXML );
		if ( pIx )
		{
			bResult = m_aList.Add( tName, pIx );
		}
	}

	return bResult;
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

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

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CFactoryExternalXML::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = VSupports::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IApplicationUser )
			pI = INTERFACE_THIS( IApplicationUserPtr );
		else if ( rIID == IXID_IExternalXML )
			pI = INTERFACE_THIS( IExternalXMLPtr );
		else
			pI = 0;
	}

	return pI;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/


NAMESPACE_GADGET_END

