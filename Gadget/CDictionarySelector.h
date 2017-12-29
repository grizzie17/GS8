/*---------------------------------------------------------------------+\
|
|	CDictionarySelector.h  --  brief description of what CDictionarySelector.h is for
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
#ifndef _H_CDictionarySelector
#define _H_CDictionarySelector
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionary.h"
#include "CCharString.h"
#include "CCharDescriptor.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CDictionarySelector*			CDictionarySelectorPtr;
typedef class CDictionarySelector&			CDictionarySelectorRef;
typedef const class CDictionarySelector&	ConstCDictionarySelectorRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictionarySelector
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictionarySelector();
					CDictionarySelector( ConstCDictionarySelectorRef r );	// copy constructor
	virtual			~CDictionarySelector();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CDictionarySelectorRef	operator=( ConstCDictionarySelectorRef r );		// assignment

	void					SetName( const char* sName );
	void					SetName( ConstCCharDescriptorRef rName);
	CCharStringPtr			Name(void);

	VDictionary::Selector	GetSelector( VDictionaryPtr pDict );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VDictionary::Selector	m_nSelector;
	CCharString				m_tName;

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

NAMESPACE_GADGET_END



#endif /* _H_CDictionarySelector */

