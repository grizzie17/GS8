/*---------------------------------------------------------------------+\
|
|	VDictionaryPageServer.h  --  Page Server Functions
|
|	Purpose:

		Identify functions that are available from the Dictionary for
		use from the Dictionary Pages.

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
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ClearMilliseconds function
	28-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VDictionaryPageServer
#define _H_VDictionaryPageServer
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VDictionary.h"
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
typedef class VDictionaryPageServer*		VDictionaryPageServerPtr;
typedef class VDictionaryPageServer&		VDictionaryPageServerRef;
typedef const class VDictionaryPageServer&	ConstVDictionaryPageServerRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VDictionaryPageServer : public VDictionary
{
//	class lifecycle  ----------------------------------------------------
public:
					VDictionaryPageServer();
	virtual			~VDictionaryPageServer();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual void	ClearMilliseconds( void ) = 0;
	virtual void	SetDirty( bool bDirty = true ) = 0;	// called from pages
	virtual VDictionary::Selector
					MakeSelector( char cPageID, long id ) = 0;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VDictionary-1
	//	VDictionary

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



#endif /* _H_VDictionaryPageServer */
