/*---------------------------------------------------------------------+\
|
|	CKeyNames.h  --  Map Key "Names" into key identifiers (unsigned char)
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
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for finding keys using character descriptors
	02-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CKeyNames
#define _H_CKeyNames
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CKeyNames*		CKeyNamesPtr;
typedef class CKeyNames&		CKeyNamesRef;
typedef const class CKeyNames&	ConstCKeyNamesRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CKeyNames
{
//	class lifecycle  ----------------------------------------------------
public:
					CKeyNames();
	virtual			~CKeyNames();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	unsigned char	GetKey( const char* sName );
	unsigned char	GetKey( Yogi::Core::ConstCCharDescriptorRef rName);

	Yogi::Core::CCharString		GetName(unsigned int n);


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


	Yogi::Common::THashTable< Yogi::Core::CCharString, unsigned int >	m_tNameMap;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


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



#endif /* _H_CKeyNames */
