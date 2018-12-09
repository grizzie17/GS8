/*---------------------------------------------------------------------+\
|
|	CKeyEventMap.cpp  --  brief description of what CKeyEventMap.cpp is for
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
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	26-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CKeyEventMap.h"
#include "CVariantData.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

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

 * CKeyEventMap - constructor

\+---------------------------------------------------------------------*/
CKeyEventMap::CKeyEventMap
		(
		void
		)
		:
		m_aDown(),
		m_aRepeat(),
		m_aUp()
{
}

/*---------------------------------------------------------------------+\

 * ~CKeyEventMap - destructor

\+---------------------------------------------------------------------*/
CKeyEventMap::~CKeyEventMap
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CKeyEventMap::OnKeyDown
		(
		VDictionaryPtr pDict,
		int	nKeyCode,
		int	mModifiers
		)
{
	return OnKey( &m_aDown, pDict, nKeyCode, mModifiers );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CKeyEventMap::OnKeyRepeat
		(
		VDictionaryPtr pDict,
		int nKeyCode,
		int mModifiers
		)
{
	return OnKey( &m_aRepeat, pDict, nKeyCode, mModifiers );
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CKeyEventMap::OnKeyUp
		(
		VDictionaryPtr pDict,
		int nKeyCode,
		int mModifiers
		)
{
	return OnKey( &m_aUp, pDict, nKeyCode, mModifiers );
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CKeyEventMap::AddKeyDown
		(
		int			nKeyCode,
		int			mModifiers,
		const char*	sEvent
		)
{
	KEYEVENT	e;
	e.key = static_cast<unsigned char>(nKeyCode);
	e.modifiers = static_cast<unsigned char>(mModifiers);
	e.selector.SetName( sEvent );

	m_aDown.AppendData( &e );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CKeyEventMap::AddKeyRepeat
		(
		int			nKeyCode,
		int			mModifiers,
		const char*	sEvent
		)
{
	KEYEVENT	e;
	e.key = static_cast<unsigned char>(nKeyCode);
	e.modifiers = static_cast<unsigned char>(mModifiers);
	e.selector.SetName( sEvent );

	m_aRepeat.AppendData( &e );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CKeyEventMap::AddKeyUp
		(
		int			nKeyCode,
		int			mModifiers,
		const char*	sEvent
		)
{
	KEYEVENT	e;
	e.key = static_cast<unsigned char>(nKeyCode);
	e.modifiers = static_cast<unsigned char>(mModifiers);
	e.selector.SetName( sEvent );

	m_aUp.AppendData( &e );
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CKeyEventMap::KeyEventArray*
		CKeyEventMap::DownArray
		(
		void
		)
{
	return &m_aDown;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CKeyEventMap::KeyEventArray*
		CKeyEventMap::RepeatArray
		(
		void
		)
{
	return &m_aRepeat;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CKeyEventMap::KeyEventArray*
		CKeyEventMap::UpArray
		(
		void
		)
{
	return &m_aUp;
}




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * OnKey -

\+---------------------------------------------------------------------*/
bool	CKeyEventMap::OnKey
		(
		CKeyEventMap::KeyEventArray *pArray,
		VDictionaryPtr pDict,
		int nKeyCode,
		int mModifiers
		)
{
	bool		bResult = false;
	KEYEVENT*	p = pArray->PointArray();
	if ( p )
	{
		KEYEVENT*	pEnd = p + pArray->Length();

		while ( p < pEnd )
		{
			if ( nKeyCode == p->key )
			{
				if ( p->modifiers == (mModifiers & p->modifiers) )
				{
					VDictionary::Selector tEvent;
					tEvent = p->selector.GetSelector( pDict );
					if ( tEvent )
					{
						CVariantData	c;
						c = GFLOAT_1;
						pDict->PutData( tEvent, &c );
						bResult = true;
					}
				}
			}
			++p;
		}
	}
	return bResult;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
