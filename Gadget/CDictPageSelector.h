/*---------------------------------------------------------------------+\
|
|	CDictPageSelector.h  --  brief description of what CDictPageSelector.h is for
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
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add Name accessor function
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for character descriptors
	02-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageSelector
#define _H_CDictPageSelector
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionaryPage.h"
#include "CCharString.h"
#include "CCharDescriptor.h"

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
typedef class CDictPageSelector*		CDictPageSelectorPtr;
typedef class CDictPageSelector&		CDictPageSelectorRef;
typedef const class CDictPageSelector&	ConstCDictPageSelectorRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageSelector
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageSelector();
					CDictPageSelector( ConstCDictPageSelectorRef r );	// copy constructor
	virtual			~CDictPageSelector();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CDictPageSelectorRef	operator=( ConstCDictPageSelectorRef r );		// assignment

	void			SetName( const char* sName );
	void			SetName( Yogi::Core::ConstCCharDescriptorRef rName );
	Yogi::Core::CCharStringPtr 	Name( void );

	unsigned long	GetSelector( VDictionaryPagePtr pDict );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	unsigned long	m_nSelector;
	Yogi::Core::CCharString		m_tName;

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



#endif /* _H_CDictPageSelector */
