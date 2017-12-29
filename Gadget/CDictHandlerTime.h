/*---------------------------------------------------------------------+\
|
|	CDictHandlerTime.h  --  brief description of what CDictHandlerTime.h is for
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
	10-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictHandlerTime
#define _H_CDictHandlerTime
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CDictPageSystem.h"
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
typedef class DerivedClass*			DerivedClassPtr;
typedef class DerivedClass&			DerivedClassRef;
typedef const class DerivedClass&	ConstDerivedClassRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictTimeBase : public VDictPageHandler
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictTimeBase();
	virtual			~CDictTimeBase();

//============================== Overrides ==============================
	//	VDictPageHandler
public:
	virtual bool			BeginCalculate( CDictPageSystemPtr pPage );
	virtual bool			EndCalculate( CDictPageSystemPtr pPage );
	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage );
	virtual bool			PutData( CDictPageSystemPtr pPage, CVariantDataPtr pData );

};


class CDictTime_Milli : public CDictTimeBase
{
public:
	CDictTime_Milli() : CDictTimeBase() {}
	virtual	~CDictTime_Milli(){}

public:
	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage );
};



class CDictTime_Absolute_Time : public CDictTimeBase
{
public:
	CDictTime_Absolute_Time() : CDictTimeBase() {}
	virtual	~CDictTime_Absolute_Time(){}

public:
	virtual CVariantDataPtr	GetData( CDictPageSystemPtr pPage );
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



#endif /* _H_CDictHandlerTime */

