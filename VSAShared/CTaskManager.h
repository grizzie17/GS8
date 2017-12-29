/*---------------------------------------------------------------------+\
|
|	CTaskManager.h  --  Example command processor class
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
	12-Jul-2010			J.Griswold		(Reviewed by: P.Hogan)
		Add optional InitialState pointer for the RegisterCommand func.
	16-May-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CTaskManager
#define _H_CTaskManager
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VObject.h"

#include "ITask.h"
#include "CPluginLibrary.h"

#include "NamespaceCommon.h"
#include "NamespaceGadget.h"
//USING_NAMESPACE_COMMON
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
typedef class CTaskManager*			CTaskManagerPtr;
typedef class CTaskManager&			CTaskManagerRef;
typedef const class CTaskManager&	ConstCTaskManagerRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CTaskManager : public VObject
{
//	class lifecycle  ----------------------------------------------------
public:
					CTaskManager();
	virtual			~CTaskManager();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	bool		LoadTasks( char* sName );
	bool		SetLibrary( ISupportsPtr pI );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray<ITaskPtr>		m_aList;
	IPluginLibraryPtr		m_pLibrary;


private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================


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


//template<>
//inline
//unsigned long
//		THashValueFromKey<VDictionary::Selector>
//		(
//		const VDictionary::Selector&	key
//		)
//{
//	long	nHash = key & 0x00FFFFFF;
//	return nHash;
//}
//





#endif /* _H_CTaskManager */

