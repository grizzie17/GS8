/*---------------------------------------------------------------------+\
|
|	CDictPageCommands.cpp  --  Process command requests
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
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDictPageCommands.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
//USING_NAMESPACE_COMMON

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

 * CDictPageCommands - constructor

\+---------------------------------------------------------------------*/
CDictPageCommands::CDictPageCommands
		(
		void
		)
		: CDictPageVariant(),
		m_pCommandQueue( 0 ),
		m_pFunctions( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageCommands - destructor

\+---------------------------------------------------------------------*/
CDictPageCommands::~CDictPageCommands
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * SetEventQueue - set event queue pointer

\+---------------------------------------------------------------------*/
void	CDictPageCommands::SetCommandQueue
		(
		CQueuePtr	p
		)
{
	m_pCommandQueue = p;
}



/*---------------------------------------------------------------------+\

 * EventQueue - get pointer to event queue

\+---------------------------------------------------------------------*/
CQueuePtr
		CDictPageCommands::CommandQueue
		(
		void
		)
{
	return m_pCommandQueue;
}


/*---------------------------------------------------------------------+\

 * SetEventQueue - set event queue pointer

\+---------------------------------------------------------------------*/
void	CDictPageCommands::SetFunctionProcessor
		(
		VFunctionProcessorPtr	p
		)
{
	m_pFunctions = p;
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

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictPageCommands::PutData
		(
		unsigned long nSel,
		CVariantDataPtr pData
		)
{
	bool	bResult = false;

	CVariantDataPtr	p = m_aContent.ItemAtIndex( nSel );
	if ( p )
	{
		if ( m_pCommandQueue )
		{
			VDictionary::Selector	vSel = m_pDictionary->MakeSelector( m_cPageID, (long)nSel );
			if ( m_pCommandQueue->Push( vSel ) )
				bResult = true;
		}
		if ( *p != *pData )
		{
			*p = *pData;
		}

	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageCommands::UpdateByName
		(
		CCharDescriptorRef	rKey,
		CVariantDataRef		rData
		)
{
	bool	bResult = false;
	long	n = long(m_aContent.IndexOf( CCharString( rKey ) ));
	if ( -1 < n )
	{
		bResult = UpdateEntry( (unsigned long)n, rData );
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageCommands::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	CCharString	tKey( rKey );
	CCharString	tAlias( rAlias );
	return m_aContent.AddAlias( tKey, tAlias );
}





NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

