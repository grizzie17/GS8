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
|	Local defines / constants	
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
		: VSupports()
{
}

DerivedClass::DerivedClass
		(
		ISupportsPtr	pOwner
		)
		: VSupports( pOwner )
{
}

DerivedClass::DerivedClass
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VSupports( sName, pOwner )
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

 * <summary>FindInternalInterface - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
void*	DerivedClass::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = VSupports::FindInternalInterface( rIID );
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

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/


NAMESPACE_GADGET_END

