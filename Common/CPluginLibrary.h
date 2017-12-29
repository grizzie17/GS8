/*---------------------------------------------------------------------+\
|
|	CPluginLibrary.h  --  brief description of what CPluginLibrary.h is for
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
	11-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPluginLibrary
#define _H_CPluginLibrary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VSupports.h"

#include "VPluginLibrary.h"

#include "VPluginFactory.h"
#include "CPluginLoader.h"
#include "ISupports.h"
#include "IPluginLibrary.h"

#include "TDictionaryIndexed.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "CMutex.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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
typedef class CPluginLibrary*		CPluginLibraryPtr;
typedef class CPluginLibrary&		CPluginLibraryRef;
typedef const class CPluginLibrary&	ConstCPluginLibraryRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPluginLibrary : public VSupports,
					implements_ IPluginLibrary
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CPluginLibrary );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IPluginLibrary
	virtual
	ISupportsPtr	Create
					(
					const char*		sLibraryname,
					ISupportsPtr	pOwner = 0
					);
	virtual
	ISupportsPtr	Create
					(
					ConstCCharDescriptorRef rLibraryname,
					ISupportsPtr	pOwner = 0
					);

	virtual
	void			SetBaseFolder
					(
					const char* sFolder
					);

	virtual
	void			SetRelativeFolder
					(
					const char*	sFolder
					);



public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

	typedef struct FactoryCampus
	{
		VPluginFactoryPtr	m_pFactory;
		ULibraryHdl			m_hLibrary;
	} FactoryCampus;

//	protected functions  ------------------------------------------------

	VPluginFactoryPtr	GetFactory( ConstCCharDescriptorRef rLibraryname );

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< CCharString, FactoryCampus>	m_aContent;
	CCharString		m_sBaseFolder;
	CPluginLoader	m_tLoader;
	CMutex			m_oMutex;

private:
//	private types  ------------------------------------------------------

	typedef	VSupports	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

#ifdef _DEBUG
	virtual
	void	FinalRelease
			(
			void
			);

	virtual
	NRefCount
			InternalAddRef
			(
			void
			);

	virtual
	NRefCount
			InternalRelease
			(
			void
			);
#endif
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

NAMESPACE_COMMON_END



#endif /* _H_CPluginLibrary */

