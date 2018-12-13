/*---------------------------------------------------------------------+\
|
|	CFactoryDictActive.h  --  Create the Active and Base dictionary pages
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
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
	26-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that the correct units-of-measure have been
		assigned whenever possible.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add handling of ranges that contain multiple colors of the
		same name -- for instance a "Red" at the low numeric value
		and a "Red" at the top of the numeric range.
	07-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryDictActive
#define _H_CFactoryDictActive
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VFactoryLite.h"

#include "CFactoryEquation.h"
#include "CFactoryGauge.h"

#include "CDictPageActive.h"
#include "CDictPageAlerts.h"
#include "CDictPageVariantRead.h"

#include "CUnitsOfMeasure.h"
#include "TPointer.h"
#include "TArray.h"



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

typedef class CFactoryDictActive*		CFactoryDictActivePtr;
typedef class CFactoryDictActive&		CFactoryDictActiveRef;
typedef const class CFactoryDictActive&	ConstCFactoryDictActiveRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryDictActive : public Yogi::Common::VFactoryLite
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryDictActive();
	virtual			~CFactoryDictActive();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	Make( const char* sName );

	virtual CDictPageActivePtr
					GetPageActive( void );
	virtual CDictPageVariantReadPtr
					GetPageBase( void );
	virtual CDictPageAlertsPtr
					GetPageNotify( void );



protected:
//	protected types  ----------------------------------------------------

	typedef struct RangeItem
	{
		GFLOAT	fLow;
		GFLOAT	fHigh;
		int		nCount;		// zero if only one
		char	sID[20];

		bool	operator < ( const RangeItem& tRight );
	} RangeItem;

//	protected functions  ------------------------------------------------

	bool	Settings( Yogi::Common::XMLIteratorPtr pIt );

	bool	Alerts( Yogi::Common::XMLIteratorPtr pIt );
	bool	Alert( Yogi::Common::XMLIteratorPtr pIt );
	bool	AlertSim
			(
			GFLOAT*							pfFreq,
			GFLOAT*							pfDur,
			Yogi::Common::XMLIteratorPtr	pIt
			);


	bool	Parameters( Yogi::Common::XMLIteratorPtr pIt );
	bool	Param( Yogi::Common::XMLIteratorPtr pIt );
	bool	RangeMultiColor( void );
	bool	Range
			(
			Yogi::Core::ConstCCharDescriptorRef	rID,
			Yogi::Common::CVariantData::V_TYPE	eType,
			int									nUnits,
			Yogi::Common::XMLIteratorPtr		pIt
			);
	bool	ParamSim
			(
			int*							pnWave,
			GFLOAT*							pfFreq,
			Yogi::Common::XMLIteratorPtr	pIt
			);

	bool	Enum( Yogi::Common::XMLIteratorPtr pIt );







//	protected data  -----------------------------------------------------

	Yogi::Core::TPointer<CDictPageActive>		m_pActive;
	Yogi::Core::TPointer<CDictPageVariantRead>	m_pBase;
	Yogi::Core::TPointer<CDictPageAlerts>		m_pNotify;
	Yogi::Core::TArray<RangeItem>				m_aRanges;
	Yogi::Core::TArray<Yogi::Core::CCharString>	m_aEnumList;
	GFLOAT										m_fLow;
	GFLOAT										m_fHigh;
	Yogi::Common::CUnitsOfMeasure				m_tDegreesUnits;
	Yogi::Common::CUnitsOfMeasure				m_tColorUnits;
	Yogi::Common::CUnitsOfMeasure				m_tNumberUnits;
	Yogi::Common::CUnitsOfMeasure				m_tStringUnits;


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


#endif /* _H_CFactoryDictActive */
