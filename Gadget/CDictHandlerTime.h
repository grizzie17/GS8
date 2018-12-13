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
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageSystemPtr pPage );
	virtual bool			PutData( CDictPageSystemPtr pPage, Yogi::Common::ConstCVariantDataPtr pData );

};


class CDictTime_Milli : public CDictTimeBase
{
public:
	CDictTime_Milli() : CDictTimeBase() {}
	virtual	~CDictTime_Milli(){}

public:
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageSystemPtr pPage );
};



class CDictTime_Absolute_Time : public CDictTimeBase
{
public:
	CDictTime_Absolute_Time() : CDictTimeBase() {}
	virtual	~CDictTime_Absolute_Time(){}

public:
	virtual Yogi::Common::ConstCVariantDataPtr	GetData( CDictPageSystemPtr pPage );
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



#endif /* _H_CDictHandlerTime */
