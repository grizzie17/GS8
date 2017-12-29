/*---------------------------------------------------------------------+\
|
|	VControlEventMap.cpp  --  brief description of what VControlEventMap.cpp is for
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
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VControlEventMap.h"
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

 * VControlEventMap - constructor

\+---------------------------------------------------------------------*/
VControlEventMap::VControlEventMap
		(
		void
		)
		: VControl(),
		m_pKeyEventMap( 0 )
{
}

/*---------------------------------------------------------------------+\

 * VControlEventMap - copy constructor

\+---------------------------------------------------------------------*/
VControlEventMap::VControlEventMap
		(
		VControlEventMapRef	r
		)
		: VControl( r ),
		m_pKeyEventMap( 0 )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~VControlEventMap - destructor

\+---------------------------------------------------------------------*/
VControlEventMap::~VControlEventMap
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
VControlEventMapRef
		VControlEventMap::operator=
		(
		VControlEventMapRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}




/*---------------------------------------------------------------------+\

 * SetKeyEventMap -

\+---------------------------------------------------------------------*/
void	VControlEventMap::SetKeyEventMap
		(
		CKeyEventMapPtr p
		)
{
	m_pKeyEventMap = p;
}

/*---------------------------------------------------------------------+\

 * KeyEventMap -

\+---------------------------------------------------------------------*/
CKeyEventMapPtr
		VControlEventMap::KeyEventMap
		(
		void
		)
{
	return m_pKeyEventMap;
}


/*---------------------------------------------------------------------+\

 * CalculateDirtyRectangle -

\+---------------------------------------------------------------------*/
int		VControlEventMap::CalculateDirtyRectangle
		(
		VDictionaryPtr	,//pDict,
		long*	pLeft,
		long*	pTop,
		long*	pRight,
		long*	pBottom
		)
{
	*pLeft = 0;
	*pTop = 0;
	*pRight = 0;
	*pBottom = 0;
	return 0;
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









NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

