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

class CFactoryDictActive : public VFactoryLite
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

	bool			Settings( XMLIteratorPtr pIt );

	bool			Alerts( XMLIteratorPtr pIt );
	bool			Alert( XMLIteratorPtr pIt );
	bool			AlertSim
					(
					GFLOAT*					pfFreq,
					GFLOAT*					pfDur,
					XMLIteratorPtr			pIt
					);


	bool			Parameters( XMLIteratorPtr pIt );
	bool			Param( XMLIteratorPtr pIt );
	bool			RangeMultiColor( void );
	bool			Range
					(
					CCharDescriptorRef		rID,
					CVariantData::V_TYPE	eType,
					int						nUnits,
					XMLIteratorPtr			pIt
					);
	bool			ParamSim
					(
					int*					pnWave,
					GFLOAT*					pfFreq,
					XMLIteratorPtr			pIt
					);

	bool			Enum( XMLIteratorPtr pIt );







//	protected data  -----------------------------------------------------

	TPointer<CDictPageActive>	m_pActive;
	TPointer<CDictPageVariantRead>	m_pBase;
	TPointer<CDictPageAlerts>	m_pNotify;
	TArray<RangeItem>			m_aRanges;
	TArray<CCharString>			m_aEnumList;
	GFLOAT						m_fLow;
	GFLOAT						m_fHigh;
	CUnitsOfMeasure				m_tDegreesUnits;
	CUnitsOfMeasure				m_tColorUnits;
	CUnitsOfMeasure				m_tNumberUnits;
	CUnitsOfMeasure				m_tStringUnits;


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
