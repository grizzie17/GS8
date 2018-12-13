/*---------------------------------------------------------------------+\
|
|	CKeyNames.cpp  --  brief description of what CKeyNames.cpp is for
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
	13-May-2010			J.Griswold		(Reviewed by: xxxx)
		Adjust to use the new UKEY_* defines for the key codes
	27-Oct-2009			M.Rose			(Reviewed by: R.Hosea)
		Fix g++ compile error, remove :: operator from sprintf_s
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for finding keys using character descriptors
	02-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <ctype.h>
#include <stdio.h>

#include "CKeyNames.h"
#include "UKeys.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
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

 * CKeyNames - constructor

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
CKeyNames::CKeyNames
		(
		void
		)
		: m_tNameMap()
{
	int		i;
	char	sName[40];

	m_tNameMap.Add(CCharString("BACK"), UKEY_BACK);
	m_tNameMap.Add(CCharString("TAB"), UKEY_TAB);
	m_tNameMap.Add(CCharString("CLEAR"), UKEY_CLEAR);
	m_tNameMap.Add(CCharString("RETURN"), UKEY_RETURN);
	m_tNameMap.Add(CCharString("ENTER"), UKEY_RETURN);
	m_tNameMap.Add(CCharString("ESCAPE"), UKEY_ESCAPE);
	m_tNameMap.Add(CCharString("SPACE"), UKEY_SPACE);

	// UKEY_0 .. UKEY_9
	for ( i = '0'; i <= '9'; ++i )
	{
		sName[0] = (char)i;
		sName[1] = 0;
		m_tNameMap.Add(CCharString(sName), (unsigned int)i);
	}

	//	UKEY_A .. UKEY_Z
	for (i = 'A'; i <= 'Z'; ++i)
	{
		sName[0] = (char)i;
		sName[1] = 0;
		m_tNameMap.Add( CCharString( sName ), (unsigned int)i );
	}

	m_tNameMap.Add( CCharString( "COMMA" ), UKEY_COMMA );
	m_tNameMap.Add( CCharString( "PERIOD" ), UKEY_PERIOD );
	m_tNameMap.Add( CCharString( "SLASH" ), UKEY_SLASH );
	m_tNameMap.Add( CCharString( "BACKSLASH" ), UKEY_BACKSLASH );
	m_tNameMap.Add( CCharString( "MINUS" ), UKEY_MINUS );
	m_tNameMap.Add( CCharString( "EQUAL" ), UKEY_EQUAL );
	m_tNameMap.Add( CCharString( "PLUS" ), UKEY_PLUS );
	m_tNameMap.Add( CCharString( "BRACKETOPEN" ), UKEY_BRACKETOPEN );
	m_tNameMap.Add( CCharString( "BRACKETCLOSE" ), UKEY_BRACKETCLOSE );
	m_tNameMap.Add( CCharString( "SEMICOLON" ), UKEY_SEMICOLON );
	m_tNameMap.Add( CCharString( "APOS" ), UKEY_APOS );
	m_tNameMap.Add( CCharString( "TILDE" ), UKEY_TILDE );


	// function keys
	//	UKEY_F1 .. UKEY_F26
	for ( i = 1; i <= 26; ++i )
	{
		::snprintf( sName, sizeof(sName), "F%d", i );
		m_tNameMap.Add( CCharString( sName ), UKEY_F1 + (unsigned int)(i - 1) );
	}

	// numeric keypad
	//	UKEY_NUMPAD0 .. UKEY_NUMPAD9
	for ( i = 0; i < 10; ++i )
	{
		::snprintf( sName, sizeof(sName), "NUMPAD%d", i );
		m_tNameMap.Add( sName, UKEY_NUMPAD0 + (unsigned int)i );
	}

	// numeric keypad
	m_tNameMap.Add( CCharString( "DIVIDE" ), UKEY_DIVIDE );
	m_tNameMap.Add( CCharString( "MULTIPLY" ), UKEY_MULTIPLY );
	m_tNameMap.Add( CCharString( "SUBTRACT" ), UKEY_SUBTRACT );
	m_tNameMap.Add( CCharString( "ADD" ), UKEY_ADD );
	m_tNameMap.Add( CCharString( "DECIMAL" ), UKEY_DECIMAL );
	m_tNameMap.Add( CCharString( "NUMPADENTER" ), UKEY_NUMPADENTER );

	m_tNameMap.Add( CCharString( "INSERT" ), UKEY_INSERT );
	m_tNameMap.Add( CCharString( "DELETE" ), UKEY_DELETE );
	m_tNameMap.Add( CCharString( "HOME" ), UKEY_HOME );
	m_tNameMap.Add( CCharString( "END" ), UKEY_END );
	m_tNameMap.Add( CCharString( "PRIOR" ), UKEY_PRIOR );
	m_tNameMap.Add( CCharString( "PAGEUP" ), UKEY_PRIOR );
	m_tNameMap.Add( CCharString( "NEXT" ), UKEY_NEXT );
	m_tNameMap.Add( CCharString( "PAGEDOWN" ), UKEY_NEXT );

	m_tNameMap.Add( CCharString( "PRINT" ), UKEY_PRINT );

	m_tNameMap.Add( CCharString( "LEFT" ), UKEY_LEFT );
	m_tNameMap.Add( CCharString( "RIGHT" ), UKEY_RIGHT );
	m_tNameMap.Add( CCharString( "UP" ), UKEY_UP );
	m_tNameMap.Add( CCharString( "DOWN" ), UKEY_DOWN );

	m_tNameMap.Add( CCharString( "BRIGHTUP" ), UKEY_BRIGHTUP );
	m_tNameMap.Add( CCharString( "BRIGHTDOWN" ), UKEY_BRIGHTDOWN );


	// bezel buttons
	//	UKEY_BEZEL1 .. UKEY_BEZEL32
	for ( i = 1; i <= 32; ++i )
	{
		snprintf( sName, sizeof(sName), "BEZEL%d", i );
		m_tNameMap.Add( CCharString( sName ), UKEY_BEZEL1 + (unsigned int)(i - 1) );
	}




}
//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * ~CKeyNames - destructor

\+---------------------------------------------------------------------*/
CKeyNames::~CKeyNames
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * GetKey -

\+---------------------------------------------------------------------*/
unsigned char
		CKeyNames::GetKey
		(
		const char*	sName
		)
{
	size_t	n = ::strlen( sName );
	CCharDescriptor	tName( sName, n );
	return GetKey( tName );
}

/*---------------------------------------------------------------------+\

 * GetKey -

\+---------------------------------------------------------------------*/
unsigned char
		CKeyNames::GetKey
		(
		ConstCCharDescriptorRef	rName
		)
{
	unsigned int	i = 0;
	const unsigned int*	p;
	CCharString		tName;

	tName = rName;
	tName.ConvertUppercase();

	p = m_tNameMap.Find( tName );
	if ( p )
		i = *p;
	return (unsigned char)( i & 0x00FFu );
}


/*---------------------------------------------------------------------+\

 * GetName -

\+---------------------------------------------------------------------*/
CCharString
		CKeyNames::GetName
		(
		unsigned int n
		)
{
	THashTableEnumerator< CCharString, unsigned int >
				tEnum = m_tNameMap.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		unsigned int	nValue = tEnum.Value();
		if ( nValue == n )
			return tEnum.Key();
	}

	CCharString	s;
	s.Format( "#%d", n );

	return s;
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


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
