/*---------------------------------------------------------------------+\
|
|	CServiceManager.h  --  Example command processor class
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
#ifndef _H_CServiceManager
#define _H_CServiceManager
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VObject.h"
#include "IService.h"
#include "CPluginLibrary.h"
#include "THash.h"
#include "CMutex.h"

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
class CApplicationGauge;	// forward declaration

typedef class CServiceManager*			CServiceManagerPtr;
typedef class CServiceManager&			CServiceManagerRef;
typedef const class CServiceManager&	ConstCServiceManagerRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceManager : public VObject
{
//	class lifecycle  ----------------------------------------------------
public:
					CServiceManager();
	virtual			~CServiceManager();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	bool			SetApplication( CApplicationGauge* pApplication );

	bool			LoadServices( const char* sName );
	bool			StopServices( void );

	IServicePtr		FindServiceByName( const char* sName );
	ISupportsPtr	FindServiceByIF( ConstIXIDRef rIID );

	bool			SetLibrary( ISupportsPtr pI );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	THashTable<CCharString, IServicePtr>	m_aList;
	IPluginLibraryPtr						m_pLibrary;
	CApplicationGauge*						m_pApplication;
	CMutex									m_oMutex;


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







#endif /* _H_CServiceManager */

