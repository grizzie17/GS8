/*---------------------------------------------------------------------+\
|
|	VElement.cpp  --  brief description of what VElement.cpp is for
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
		Also add a new function to deal with the context
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	15-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "VElement.h"
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

 * VElement - constructor

\+---------------------------------------------------------------------*/
VElement::VElement
		(
		void
		)
		: VOwnership()
{
}

/*---------------------------------------------------------------------+\

 * VElement - copy constructor

\+---------------------------------------------------------------------*/
VElement::VElement
		(
		ConstVElementRef	r
		)
		: VOwnership( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~VElement - destructor

\+---------------------------------------------------------------------*/
VElement::~VElement
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
VElementRef
		VElement::operator=
		(
		ConstVElementRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
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

 * Calculate -

\+---------------------------------------------------------------------*/
int		VElement::Calculate
		(
		VDictionaryPtr
		)
{
	// subclasses need to override this function
	return VRDR_CALCULATE_NONE;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	VElement::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr
		)
{
	// Elements should not add themselves to the queue.
	// Those classes that have transformation properties should override this function.
	return true;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	VElement::Render
		(
		VDictionaryPtr,
		VDrawPtr
		)
{
	// subclass need to override this function
	return false;
}

/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	VElement::GetSize
		(
		VDictionaryPtr,
		long &,
		long &
		)
{
	// subclasses need to override this function
	return false;
}

/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	VElement::IsDisplayed
		(
		VDictionaryPtr
		)
{
	// subclasses need to override this function
	return true;
}


void	VElement::IncludeContext
		(
		int mask
		)
{
	VOwnership::IncludeContext( mask );
	if ( m_pParent )
		m_pParent->IncludeContext( mask );
}





NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

