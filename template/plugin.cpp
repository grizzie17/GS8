/*---------------------------------------------------------------------+\
|	Delete this comment block
|
|	globally substitute "filename" to be the name of this file (no suffix).
|	globally substitute "dd-mmm-9999" to be today's date.
|	globally substitute "F.Lastname" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "DerivedClass" to be the name of this class.
|	globally substitute "IInterface" to be your interface-name.
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	filename.cpp  --  brief description of what filename.cpp is for
|
|	Purpose:
|	File Custodian:		F.Lastname
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "filename.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|									
|	Local defines / constant
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Local Type Definitions	
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Private Global Variables
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Public Global Variables	
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|						
|	External Variables	
|						
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||			
||	 Code	
||			
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( DerivedClass );

/*=====================================================================+\
||	 class lifecycle functions	
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - constructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		void
		)
		: VPluginWithAggregateList()
{
}

DerivedClass::DerivedClass
		(
		ISupportsPtr	pOwner
		)
		: VPluginWithAggregateList( pOwner )
{
}

DerivedClass::DerivedClass
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginWithAggregateList( sName, pOwner )
{
}

/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - copy constructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
DerivedClass::~DerivedClass
		(
		void
		)
{
}

/*=====================================================================+\
||	 interface implementation functions
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IInterface
\+---------------------------------------------------------------------*/


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
NResult
		DerivedClass::SomeFunction
		(
		SomeType	arg1,	// OUT:	description of arg1
		AnotherType	arg2	// IN:	description of arg2
		)
{
	NResult	nr = NR_S_OK;

	return nr;
}


/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/*=====================================================================+\
||	 protected member functions
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions
\+=====================================================================*/

/*=====================================================================+\
||				
||	 Overrides	
||				
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - identify implemented interfaces</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
void*	DerivedClass::FindInternalInterface
		(
		ConstIXIDRef	rIID	//	IN:	requested interface iid
		)
{
	void*	pI = VPluginWithAggregateList::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IInterface )
			pI = INTERFACE_THIS( IInterfacePtr );
		else
			pI = 0;
	}

	return pI;
}


/**--------------------------------------------------------------------+\

 * <summary>Load - fetch configuration parameters</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	DerivedClass::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginWithAggregateList::Load( pConfig, pLib );
	if ( bResult )
	{
		// TODO: insert your code to get parameters from config

		//CCharString	sID = pConfig->GetID();
		//CCharString	sClass = pConfig->GetClass();

		//long			n = pConfig->GetParameterAsInteger("Param Name", 0 );

	}
	return bResult;
}




/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/


NAMESPACE_GADGET_END

