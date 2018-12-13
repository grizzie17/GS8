/*---------------------------------------------------------------------+\
|
|	CKeyProcessorWin.cpp  --  brief description of what CKeyProcessorWin.cpp is for
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
	24-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		fix a problem where we had hard-coded values instead
		of the UKEY_* defines.
	14-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Move bezel button functions to mfcview class
	22-Oct-2009			R.Hosea			(Reviewed by: M.Rose)
		Added bezel button fcns
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
#include "UPlatform.h"
#include "UPlatformString.h"

#if defined( OS_MSWIN )

#include <Winuser.h>
#include <stdio.h>

#include "CKeyProcessorWin.h"
#include "CKeyNames.h"



using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define MAX_LOADSTRING 100
//#define RX_HEAD_BYTE_0 0xAA
//#define RX_HEAD_BYTE_1 0x55
//#define MAX_NUM_DSPS 4
//#define KEY_STATE_MSG_SIZE 7
//#define TCPIP_HEADER_SIZE 48
//#define RS232_RX_SIZE 250


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

 * CKeyProcessorWin - constructor

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
CKeyProcessorWin::CKeyProcessorWin
		(
		void
		)
		: m_pApplication( 0 )
{
	unsigned char*	p = m_aKeys;
	unsigned char*	pEnd = p + sizeof(m_aKeys);

	while ( p < pEnd )
	{
		//if ( uc < 256 )
		//	*p = (unsigned char)uc;
		//else
			*p = 0;
		//++uc;
		++p;
	}

	CKeyNames	keys;

	char			sName[40];
	int				c;
	unsigned int	i;

	m_aKeys[VK_BACK] = keys.GetKey( "BACK" );
	m_aKeys[VK_TAB] = keys.GetKey( "TAB" );
	m_aKeys[VK_ESCAPE] = keys.GetKey( "ESCAPE" );
	m_aKeys[VK_RETURN] = keys.GetKey( "RETURN" );
	m_aKeys[VK_SPACE] = keys.GetKey( "SPACE" );

	for ( c = '0'; c <= '9'; ++c )
	{
		sName[0] = (char)c;
		sName[1] = 0;
		m_aKeys[c] = keys.GetKey( sName );
	}
	for ( c = 'A'; c <= 'Z'; ++c )
	{
		sName[0] = (char)c;
		sName[1] = 0;
		m_aKeys[c] = keys.GetKey( sName );
	}

#if defined(VK_SEMICOLON)
	m_aKeys[VK_SEMICOLON] = keys.GetKey( "SEMICOLON" );
#elif defined(VK_OEM_1)
	m_aKeys[VK_OEM_1] = keys.GetKey( "SEMICOLON" );
#endif
#if defined(VK_OEM_PLUS)
	m_aKeys[VK_OEM_PLUS] = keys.GetKey( "PLUS" );
#elif defined(VK_EQUAL)
	m_aKeys[VK_EQUAL] = keys.GetKey( "PLUS" );
#endif
#if defined(VK_EQUAL)
	m_aKeys[VK_EQUAL] = keys.GetKey( "EQUAL" );
#endif
#if defined(VK_COMMA)
	m_aKeys[VK_COMMA] = keys.GetKey( "COMMA" );
#elif defined(VK_OEM_COMMA)
	m_aKeys[VK_OEM_COMMA] = keys.GetKey( "COMMA" );
#endif
#if defined(VK_OEM_MINUS)
	m_aKeys[VK_OEM_MINUS] = keys.GetKey( "MINUS" );
#elif defined(VK_HYPHEN)
	m_aKeys[VK_HYPHEN] = keys.GetKey( "MINUS" );
#endif
#if defined(VK_HYPHEN)
	m_aKeys[VK_HYPHEN] = keys.GetKey( "HYPHEN" );
#endif
#if defined(VK_PERIOD)
	m_aKeys[VK_PERIOD] = keys.GetKey( "PERIOD" );
#elif defined(VK_OEM_PERIOD)
	m_aKeys[VK_OEM_PERIOD] = keys.GetKey( "PERIOD" );
#endif
#if defined(VK_SLASH)
	m_aKeys[VK_SLASH] = keys.GetKey( "SLASH" );
#elif defined(VK_OEM_2)
	m_aKeys[VK_OEM_2] = keys.GetKey( "SLASH" );
#endif
#if defined(VK_BACKQUOTE)
	m_aKeys[VK_BACKQUOTE] = keys.GetKey( "TILDE" );
#elif defined(VK_OEM_3)
	m_aKeys[VK_OEM_3] = keys.GetKey( "TILDE" );
#endif
#if defined(VK_BACKQUOTE)
	m_aKeys[VK_BACKQUOTE] = keys.GetKey( "BACKQUOTE" );
#endif
#if defined( VK_LBRACKET )
	m_aKeys[VK_LBRACKET] = keys.GetKey( "BRACKETOPEN" );
#elif defined( VK_OEM_4 )
	m_aKeys[VK_OEM_4] = keys.GetKey( "BRACKETOPEN" );
#endif
#if defined( VK_BACKSLASH )
	m_aKeys[VK_BACKSLASH] = keys.GetKey( "BACKSLASH" );
#elif defined( VK_OEM_5 )
	m_aKeys[VK_OEM_5] = keys.GetKey( "BACKSLASH" );
#endif
#if defined(VK_RBRACKET)
	m_aKeys[VK_RBRACKET] = keys.GetKey( "BRACKETCLOSE" );
#elif defined(VK_OEM_6)
	m_aKeys[VK_OEM_6] = keys.GetKey( "BRACKETCLOSE" );
#endif
#if defined(VK_APOSTROPHE)
	m_aKeys[VK_APOSTROPHE] = keys.GetKey( "APOS" );
#elif defined(VK_OEM_7)
	m_aKeys[VK_OEM_7] = keys.GetKey( "APOS" );
#endif

	for ( i = 1; i <= 24; ++i )
	{
		sprintf_s( sName, sizeof(sName), "F%d", i );
		m_aKeys[VK_F1 + i - 1] = keys.GetKey( sName );
	}
	for ( i = 0; i <= 9; ++i )
	{
		sprintf_s( sName, sizeof(sName), "NUMPAD%d", i );
		m_aKeys[VK_NUMPAD0 + i] = keys.GetKey( sName );
	}
	m_aKeys[VK_MULTIPLY] = keys.GetKey( "MULTIPLY" );
	m_aKeys[VK_ADD] = keys.GetKey( "ADD" );
	m_aKeys[VK_SUBTRACT] = keys.GetKey( "SUBTRACT" );
	m_aKeys[VK_DECIMAL] = keys.GetKey( "DECIMAL" );
	m_aKeys[VK_DIVIDE] = keys.GetKey( "DIVIDE" );
	m_aKeys[VK_INSERT] = keys.GetKey( "INSERT" );
	m_aKeys[VK_DELETE] = keys.GetKey( "DELETE" );

	m_aKeys[VK_PRIOR] = keys.GetKey( "PRIOR" );
	m_aKeys[VK_NEXT] = keys.GetKey( "NEXT" );
	m_aKeys[VK_END] = keys.GetKey( "END" );
	m_aKeys[VK_HOME] = keys.GetKey( "HOME" );

	m_aKeys[VK_LEFT] = keys.GetKey( "LEFT" );
	m_aKeys[VK_UP] = keys.GetKey( "UP" );
	m_aKeys[VK_RIGHT] = keys.GetKey( "RIGHT" );
	m_aKeys[VK_DOWN] = keys.GetKey( "DOWN" );

	// TODO: add support for the bezel buttons
	for ( i = 1; i <= 32; ++i )
	{
		sprintf_s( sName, sizeof(sName), "BEZEL%d", i );
		m_aKeys[255 + i] = keys.GetKey( sName );
	}

	//using function keys for supporting bezel buttons

}
//END_OVERRUN_WARNING

/*---------------------------------------------------------------------+\

 * ~CKeyProcessorWin - destructor

\+---------------------------------------------------------------------*/
CKeyProcessorWin::~CKeyProcessorWin
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * OnBezelDown -

\+---------------------------------------------------------------------*/
void	CKeyProcessorWin::OnBezelDown
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	int	nKeyCode = (int)nChar;	// TODO:
	int	mModifiers = (int)nFlags;
	if ( nChar < sizeof( m_aKeys ) )
	{
		nKeyCode = m_aKeys[nChar];
		if ( 0 != nKeyCode )
		{
			if ( nFlags & (0x1<<14) )
			{
				if ( nRepCnt < 2 )
					nRepCnt = 2;
			}
			if ( 1 < nRepCnt )
				m_pApplication->OnKeyRepeat( nKeyCode, mModifiers );
			else
				m_pApplication->OnKeyDown( nKeyCode, mModifiers );
		}
	}
}


/*---------------------------------------------------------------------+\

 * OnBezelUp -

\+---------------------------------------------------------------------*/
void	CKeyProcessorWin::OnBezelUp
		(
		UINT nChar,
		UINT,
		UINT nFlags
		)
{
	int	nKeyCode = (int)nChar;	// TODO:
	int	mModifiers = (int)nFlags;
	if ( nChar < sizeof( m_aKeys ) )
	{
		nKeyCode = m_aKeys[nChar];
		if ( 0 != nKeyCode )
		{
			m_pApplication->OnKeyUp( nKeyCode, mModifiers );
		}
	}
}



/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * OnKeyDown -

\+---------------------------------------------------------------------*/
void	CKeyProcessorWin::OnKeyDown
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	int	nKeyCode = (int)nChar;	// TODO:
	int	mModifiers = (int)nFlags;
	if ( nChar < sizeof( m_aKeys ) )
	{
		nKeyCode = m_aKeys[nChar];
		if ( 0 != nKeyCode )
		{
			if ( nFlags & (0x1<<14) )
			{
				if ( nRepCnt < 2 )
					nRepCnt = 2;
			}
			if ( 1 < nRepCnt )
				m_pApplication->OnKeyRepeat( nKeyCode, mModifiers );
			else
				m_pApplication->OnKeyDown( nKeyCode, mModifiers );
		}
	}
}


/*---------------------------------------------------------------------+\

 * OnKeyUp -

\+---------------------------------------------------------------------*/
void	CKeyProcessorWin::OnKeyUp
		(
		UINT nChar,
		UINT,
		UINT nFlags
		)
{
	int	nKeyCode = (int)nChar;	// TODO:
	int	mModifiers = (int)nFlags;
	if ( nChar < sizeof( m_aKeys ) )
	{
		nKeyCode = m_aKeys[nChar];
		if ( 0 != nKeyCode )
		{
			m_pApplication->OnKeyUp( nKeyCode, mModifiers );
		}
	}
}


/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
void	CKeyProcessorWin::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;
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


}}



#endif	//	OS_MSWIN


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
