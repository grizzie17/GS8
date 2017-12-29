/*---------------------------------------------------------------------+\
|
|	VPolylist.cpp  --  brief description of what VPolylist.cpp is for
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
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VPolylist.h"
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

 * VPolylist - constructor

\+---------------------------------------------------------------------*/
VPolylist::VPolylist
		(
		void
		)
		: VGraphic(),
		m_nWidth( 1 ),
		m_tColor(),
		m_tPointList()
{
}

/*---------------------------------------------------------------------+\

 * VPolylist - copy constructor

\+---------------------------------------------------------------------*/
VPolylist::VPolylist
		(
		ConstVPolylistRef	r
		)
		: VGraphic( r ),
		m_nWidth( 1 ),
		m_tColor(),
		m_tPointList()
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~VPolylist - destructor

\+---------------------------------------------------------------------*/
VPolylist::~VPolylist
		(
		void
		)
{
	CPointValuePtr	*h = m_tPointList.PointArray();

	if ( h )
	{
		CPointValuePtr	*hEnd = h + m_tPointList.Length();

		while ( h < hEnd )
		{
			if ( *h )
				delete (*h);
			++h;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
VPolylistRef
		VPolylist::operator=
		(
		ConstVPolylistRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * SetLineWidth -

\+---------------------------------------------------------------------*/
void	VPolylist::SetLineWidth
		(
		short nWidth
		)
{
	m_nWidth = nWidth;
}


/*---------------------------------------------------------------------+\

 * SetLineColor -

\+---------------------------------------------------------------------*/
void	VPolylist::SetLineColor
		(
		ConstCColorRef	tColor
		)
{
	m_tColor = tColor;
}

/*----------------------------------------------------------------------+\

 * AddPoint - append a point

\+---------------------------------------------------------------------*/
bool	VPolylist::AddPoint
		(
		CPointValuePtr pPoint
		)
{
	CPointValuePtr*	h = m_tPointList.AppendArray();
	if ( h )
	{
		*h = pPoint;
		return true;
	}
	else
	{
		return false;
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

 * someFunction -

\+---------------------------------------------------------------------*/
int		VPolylist::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	CPointValuePtr*	h = m_tPointList.PointArray();
	if ( h )
	{
		CPointValuePtr*	hEnd = h + m_tPointList.Length();
		while ( h < hEnd )
		{
			if ( *h )
				nResult |= (*h)->Calculate( pDict );
			++h;
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	VPolylist::Render
		(
		VDictionaryPtr pDict,
		VDrawPtr pDraw
		)
{
	// this function must be overridden by the derived class and then this class should be called
	bool	bResult = VGraphic::Render( pDict, pDraw );
	CPointValuePtr*	h = m_tPointList.PointArray();
	if ( h )
	{

		CPointValuePtr*	hEnd = h + m_tPointList.Length();
		while ( h < hEnd )
		{
			if ( *h )
			{
				bResult = (*h)->Render( pDict, pDraw );
				if ( ! bResult )
					break;
			}
			++h;
		}
	}


	return bResult;
}


NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

