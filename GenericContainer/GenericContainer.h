/*---------------------------------------------------------------------+\
|
|	GenericContainer.h  --  Header for GenericContainer Plugin - used to add constants to the dictionary.
|
|	Purpose:
|
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
	29-Jul-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_GenericContainer
#define _H_GenericContainer
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregateList.h"

#include "IAttribute.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
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
typedef class GenericContainer*			GenericContainerPtr;
typedef class GenericContainer&			GenericContainerRef;
typedef const class GenericContainer&	ConstGenericContainerRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class GenericContainer : public VPluginWithAggregateList,
						implements_ IAttribute
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(GenericContainer);

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IAttribute
	virtual
	CVariantDataPtr
			GetAttribute
			(
			const char*		sName	// IN:	description of arg2
			);

	virtual
	CVariantDataPtr
			GetAttribute
			(
			ConstCCharDescriptorRef	rName	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	THashTable<CCharString, CVariantData>			m_aAttributes;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

	//	VSupports
protected:
	virtual
	void*	FindInternalInterface
			(						// RTN:	pointer to discovered i/f
			ConstIXIDRef	rIID	// IN:	id of requested interface
			);

	//	IPluginLoadConfiguration
public:
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);

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



#endif /* _H_GenericContainer */

