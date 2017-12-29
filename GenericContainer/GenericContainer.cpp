/*---------------------------------------------------------------------+\
|
|	GenericContainer.cpp  --  Plugin used to add constants to the dictionary.
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
	12-Jul-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "GenericContainer.h"

#include "VPluginFactory.h"

NAMESPACE_GADGET_BEGIN

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
PLUGIN_CREATE_FACTORY( GenericContainer );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * GenericContainer - constructor

\+---------------------------------------------------------------------*/
GenericContainer::GenericContainer
		(
		void
		)
		: VPluginWithAggregateList(),
		m_aAttributes()
{
}

GenericContainer::GenericContainer
		(
		ISupportsPtr	pOwner
		)
		: VPluginWithAggregateList( pOwner ),
		m_aAttributes()
{
}

GenericContainer::GenericContainer
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginWithAggregateList( sName, pOwner ),
		m_aAttributes()
{
}



/*---------------------------------------------------------------------+\

 * ~GenericContainer - destructor

\+---------------------------------------------------------------------*/
GenericContainer::~GenericContainer
		(
		void
		)
{
}

/*=====================================================================+\
||	 interface implementation functions									|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IInterface
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		GenericContainer::GetAttribute
		(
		const char*		sName	// IN:	description of arg2
		)
{
	CCharString	tName( sName );
	return GetAttribute( tName );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		GenericContainer::GetAttribute
		(
		ConstCCharDescriptorRef	rName	// IN:	description of arg2
		)
{
	return m_aAttributes.Find( rName );
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
void*	GenericContainer::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = VPluginWithAggregateList::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IAttribute )
			pI = INTERFACE_THIS( IAttributePtr );
		else
			pI = 0;
	}

	return pI;
}


/*---------------------------------------------------------------------+\

 * Load - fetch configuration parameters

\+---------------------------------------------------------------------*/
bool	GenericContainer::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginWithAggregateList::Load( pConfig, pLib );
	if ( bResult )
	{
		CVariantData	v;
		CCharString		s;
		VPluginConfiguration::ParamEnum	eCfg = pConfig->GetParamEnum();

		while ( eCfg.MoveNext() )
		{
			v = eCfg.Value();
			s = eCfg.Key();

			m_aAttributes.Add( s, v );
		}
	}
	return bResult;
}




NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

