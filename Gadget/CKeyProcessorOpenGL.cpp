/*---------------------------------------------------------------------+\
|
|	CKeyProcessorOpenGL.cpp  --  brief description of what CKeyProcessorOpenGL.cpp is for
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
	09-Dec-2009			C. Cason		(Reviewed by: R.Hosea)
		Initial Revision - baselined from CKeyProcessorVDDS.h
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UMachine.h"
#include "UPlatformString.h"

#if defined( GL_OPENGL )

#include "CKeyProcessorOpenGL.h"
#include "CKeyNames.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CKeyProcessorOpenGL - constructor

\+---------------------------------------------------------------------*/
CKeyProcessorOpenGL::CKeyProcessorOpenGL
		(
		void
		)
		: m_pApplication( 0 )
{
	unsigned char*	p = m_aKeys;
	unsigned char*	pEnd = p + sizeof(m_aKeys);
	while ( p < pEnd )
	{
		*p = 0;
		++p;
	}

	CKeyNames	keys;

	char	sName[40];
	int		i;

	m_aKeys[VK_BACK] = keys.GetKey( "BACK" );
	m_aKeys[VK_TAB] = keys.GetKey( "TAB" );
	m_aKeys[VK_ESCAPE] = keys.GetKey( "ESCAPE" );
	m_aKeys[VK_RETURN] = keys.GetKey( "RETURN" );
	m_aKeys[VK_SPACE] = keys.GetKey( "SPACE" );

	for ( i = '0'; i <= '9'; ++i )
	{
		sName[0] = i;
		sName[1] = 0;
		m_aKeys[i] = keys.GetKey( sName );
	}
	for ( i = 'A'; i <= 'Z'; ++i )
	{
		sName[0] = i;
		sName[1] = 0;
		m_aKeys[i] = keys.GetKey( sName );
	}

	m_aKeys[VK_OEM_COMMA] = keys.GetKey( "COMMA" );
	m_aKeys[VK_OEM_PERIOD] = keys.GetKey( "PERIOD" );

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
}


/*---------------------------------------------------------------------+\

 * ~CKeyProcessorOpenGL - destructor

\+---------------------------------------------------------------------*/
CKeyProcessorOpenGL::~CKeyProcessorOpenGL
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * OnKeyDown -

\+---------------------------------------------------------------------*/
void	CKeyProcessorOpenGL::OnKeyDown
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	int	nKeyCode = nChar;	// TODO:
	int	mModifiers = nFlags;
	if ( nChar < sizeof( m_aKeys ) )
	{
		//nKeyCode = m_aKeys[nChar];
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
	else
	{
		m_pApplication->OnKeyDown( nKeyCode, mModifiers );
	}
}


/*---------------------------------------------------------------------+\

 * OnKeyUp -

\+---------------------------------------------------------------------*/
void	CKeyProcessorOpenGL::OnKeyUp
		(
		UINT nChar,
		UINT,
		UINT nFlags
		)
{
	int	nKeyCode = nChar;	// TODO:
	int	mModifiers = nFlags;
	if ( nChar < sizeof( m_aKeys ) )
	{
		//nKeyCode = m_aKeys[nChar];
		if ( 0 != nKeyCode )
		{
			m_pApplication->OnKeyUp( nKeyCode, mModifiers );
		}
	}
	else
	{
		m_pApplication->OnKeyUp( nKeyCode, mModifiers );
	}
}


/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
void	CKeyProcessorOpenGL::SetApplication
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


#else

long	dummyCKeyProcessorOpenGL;	// dummy symbol to suppress 'no public symbols' message


#endif	//	OS_MSWIN


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
