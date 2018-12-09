/*---------------------------------------------------------------------+\
|
|	UKeys.h  --  brief description of what UKeys.h is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	24-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Reorganize the codes to make things a bit cleaner
		Add support for BRIGHTUP/DOWN
	13-May-2010			J.Griswold		(Reviewed by: xxxx)
		Add UKEY_* definitions for all of our internal key values
	26-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UKeys
#define _H_UKeys
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

NAMESPACE_ROOT_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

//
// keycode modifiers
//
#define	MODKEY_M_SHIFT		(0x0001)
#define MODKEY_M_CONTROL	(0x0002)
#define MODKEY_M_ALT		(0x0004)

//
//	keycodes
//
//	Letters are the ASCII uppercase form (look at the SHIFT modifier)
//	Numbers are the ASCII codes
//	F1-F26 start with (0x80 | 'A')
//	BEZEL1-BEZEL32 start with 0x81
//
#define	UKEY_BACK			0x08u
#define	UKEY_TAB			0x09u
#define	UKEY_CLEAR			0x0Cu
#define	UKEY_RETURN			0x0Du
#define	UKEY_ESCAPE			0x1Bu
#define	UKEY_SPACE			0x20u

#define UKEY_EXCLAIM		'!'
#define UKEY_DQUOTE			'"'
#define UKEY_POUND			'#'
#define UKEY_DOLLAR			'$'
#define UKEY_PERCENT		'%'
#define UKEY_AMPERSAND		'&'
#define	UKEY_APOS			'\''
#define UKEY_PARENOPEN		'('
#define UKEY_PARENCLOSE		')'
#define	UKEY_ASTERISK		'*'
#define	UKEY_PLUS			'+'
#define	UKEY_COMMA			','
#define	UKEY_MINUS			'-'
#define	UKEY_PERIOD			'.'
#define	UKEY_SLASH			'/'

//	numeric keys are simply ascii codes
#define	UKEY_0				'0'
#define	UKEY_9				'9'

#define	UKEY_SEMICOLON		';'
#define	UKEY_EQUAL			'='

// look at MODKEY_M_SHIFT to determine if upper- or lower-case
#define	UKEY_A				'A'
#define	UKEY_Z				'Z'

#define	UKEY_BACKSLASH		'\\'
#define	UKEY_BRACKETOPEN	'['
#define	UKEY_BRACKETCLOSE	']'
#define	UKEY_TILDE			'~'



#define	UKEY_BEZEL1			UKEY_HDEF(1)
#define UKEY_BEZEL10		UKEY_HDEF(10)
#define	UKEY_BEZEL32		UKEY_HDEF(32)


// numeric keypad

#define UKEY_NUMPAD0		UKEY_HDEF('0')	// same as '0' with sign bit
#define UKEY_NUMPAD9		UKEY_HDEF('9')

#define UKEY_DIVIDE			UKEY_HDEF('/')
#define UKEY_MULTIPLY		UKEY_HDEF('*')
#define UKEY_SUBTRACT		UKEY_HDEF('-')
#define UKEY_ADD			UKEY_HDEF('+')
#define UKEY_DECIMAL		UKEY_HDEF('.')
#define UKEY_NUMPADENTER	UKEY_HDEF(')')




#define	UKEY_F1				UKEY_HDEF('A')
#define	UKEY_F26			UKEY_HDEF('Z')

// edit keypad

#define	UKEY_INSERT			UKEY_HDEF('a')
#define	UKEY_DELETE			UKEY_HDEF('b')
#define	UKEY_HOME			UKEY_HDEF('c')
#define	UKEY_END			UKEY_HDEF('d')
#define	UKEY_PRIOR			UKEY_HDEF('e')	// page-up
#define	UKEY_NEXT			UKEY_HDEF('f')	// page-down

#define	UKEY_PRINT			UKEY_HDEF('g')


#define	UKEY_LEFT			UKEY_HDEF('h')
#define	UKEY_RIGHT			UKEY_HDEF('i')
#define	UKEY_UP				UKEY_HDEF('j')
#define	UKEY_DOWN			UKEY_HDEF('k')

#define UKEY_BRIGHTUP		UKEY_HDEF('l')
#define UKEY_BRIGHTDOWN		UKEY_HDEF('m')



#define	UKEY_HDEF( ltr )	(unsigned int)((0x0080u | (unsigned int)(ltr)) & 0x00FFu)





/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

NAMESPACE_ROOT_END



#endif /* _H_UKeys */
