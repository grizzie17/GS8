/*---------------------------------------------------------------------+\
|
|	CKeyEventMap.h  --  brief description of what CKeyEventMap.h is for
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
	26-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CKeyEventMap
#define _H_CKeyEventMap
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VDictionary.h"
#include "CDictionarySelector.h"
#include "TArray.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CKeyEventMap*			CKeyEventMapPtr;
typedef class CKeyEventMap&			CKeyEventMapRef;
typedef const class CKeyEventMap&	ConstCKeyEventMapRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CKeyEventMap
{
//	class lifecycle  ----------------------------------------------------
public:
					CKeyEventMap();
	virtual			~CKeyEventMap();

public:
//	public types  -------------------------------------------------------

	typedef struct KEYEVENT
	{
		unsigned char		key;
		unsigned char		modifiers;
		CDictionarySelector	selector;

		KEYEVENT() : selector() {};
		~KEYEVENT() {};
	} KEYEVENT;

	typedef Yogi::Core::TArray<KEYEVENT>	KeyEventArray;

//	public functions  ---------------------------------------------------

	bool		OnKeyDown( VDictionaryPtr pDict, int nKeyCode, int mModifiers );
	bool		OnKeyRepeat( VDictionaryPtr pDict, int nKeyCode, int nModifiers );
	bool		OnKeyUp( VDictionaryPtr pDict, int nKeyCode, int nModifiers );

	void		AddKeyDown( int nKeyCode, int mModifiers, const char* sEvent );
	void		AddKeyRepeat( int nKeyCode, int mModifiers, const char* sEvent );
	void		AddKeyUp( int nKeyCode, int mModifiers, const char* sEvent );

	KeyEventArray*	DownArray();
	KeyEventArray*	RepeatArray();
	KeyEventArray*	UpArray();

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool		OnKey( KeyEventArray* pArray, VDictionaryPtr pDict, int nKeyCode, int mModifiers );

//	protected data  -----------------------------------------------------

	KeyEventArray	m_aDown;
	KeyEventArray	m_aRepeat;
	KeyEventArray	m_aUp;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};

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

}}



#endif /* _H_CKeyEventMap */
