/*---------------------------------------------------------------------+\
|
|	CFactoryVehicleData.h  --  Load the VehicleData from XML
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
	10-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add a special "N:Alerts Active" variable that indicates
		that at least one "Alert" is active.
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Alerts
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryVehicleData
#define _H_CFactoryVehicleData
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactory.h"


#include "CDictPageActive.h"
#include "CDictPageVariant.h"
#include "CDictPageAlerts.h"


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

typedef class CFactoryVehicleData*			CFactoryVehicleDataPtr;
typedef class CFactoryVehicleData&			CFactoryVehicleDataRef;
typedef const class CFactoryVehicleData&	ConstCFactoryVehicleDataRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryVehicleData : public VFactory
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryVehicleData();
	virtual			~CFactoryVehicleData();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	LoadData( XMLLite::VReadCallBack* pCallBack );


	bool			SpecifyActivePage( VDictionaryPagePtr p );
	bool			SpecifyNotifyPage( VDictionaryPagePtr p );



protected:
//	protected types  ----------------------------------------------------


//	protected functions  ------------------------------------------------

	bool			VehicleData( XMLIteratorPtr pIt );
	bool			Alerts( XMLIteratorPtr pIt );
	bool			Alert( XMLIteratorPtr pIt );
	bool			Parameters( XMLIteratorPtr pIt );
	bool			Param( XMLIteratorPtr pIt );




//	protected data  -----------------------------------------------------

	CDictPageActivePtr	m_pActive;
	CDictPageAlertsPtr	m_pNotify;

	bool				m_bNotifyActive;
	CCharString			m_sAAName;
	char				m_sTrue[2];
	char				m_sFalse[2];

private:
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
}}


#endif /* _H_CFactoryVehicleData */
