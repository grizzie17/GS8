/*---------------------------------------------------------------------+\
|
|	CFactoryDictActive.cpp  --  Make a dictionary page object from XML
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
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
	17-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Make the color values for Red, Green, Yellow a bit more
		distinctive.
	26-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that the correct units-of-measure have been
		assigned whenever possible.
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Lock the "Base-Data" (B) page when load is complete
	20-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add loading range information into ActiveDatum so we
		can check valid ranges in UpdateData method
	16-Oct-2009			J.Griswold		(Reveiwed by: M.Rose)
		Fix the handling of an ENUM Range tag to properly deal
		with the HiLo range.
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Allow the range related entries to be of the correct
		type (Integer/Float).  This allows for a better
		optimization when we are actually testing the values.
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Provide some alternate names for the types
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for VersionInfo tag - ignore it.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
		Also add support for Date/Time type
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add handling of ranges that contain multiple colors of the
		same name -- for instance a "Red" at the low numeric value
		and a "Red" at the top of the numeric range.
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	15-Sep-2009			M.Rose			(Reviewed by: J.Griswold)
		Manipulate code to satisfy linux gcc 4.2.1 compiler
	07-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <float.h>

#include "CFactoryDictActive.h"

#include "UPlatform.h"
#include "UPlatformString.h"
#include "CCharString.h"
#include "CUnitsOfMeasure.h"
#include "CColor.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CFactoryDictActive - constructor

\+---------------------------------------------------------------------*/
CFactoryDictActive::CFactoryDictActive
		(
		void
		)
		: VFactoryLite(),
		m_pActive( 0 ),
		m_pBase( 0 ),
		m_pNotify( 0 ),
		m_aRanges(),
		m_aEnumList()
{
	m_tDegreesUnits.SetUsingString( "degree" );
	m_tColorUnits.SetUsingString( "color" );
	m_tNumberUnits.SetUsingString( "number" );
	m_tStringUnits.SetUsingString( "string" );
}


/*---------------------------------------------------------------------+\

 * ~CFactoryDictActive - destructor

\+---------------------------------------------------------------------*/
CFactoryDictActive::~CFactoryDictActive
		(
		void
		)
{
	// make sure that you call GetPageActive and GetPageBase
	//	to clear the pointers to the corresponding objects
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Make -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::Make
		(
		const char*	sName
		)
{
	bool	bResult = false;

	if ( OpenFile( sName ) )
	{
		CCharDescriptor	tName;
		XMLIterator		it( this );

		while ( it.NextChild() )
		{
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				tName = it.NodeName();
				if ( tName == "Settings" )
				{
					bResult = Settings( &it );
				}
				break;
            default:
                break;
			}
		}
		if ( 0 < ErrorLineNumber() )
		{
			if ( m_pActive )
			{
				delete m_pActive;
				m_pActive = 0;
			}
			if ( m_pBase )
			{
				delete m_pBase;
				m_pBase = 0;
			}
			if ( m_pNotify )
			{
				delete m_pNotify;
				m_pNotify = 0;
			}
		}
		else
		{
			if ( m_pBase )
			{
				m_pBase->LockData( true );
			}
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetPageActive -

\+---------------------------------------------------------------------*/
CDictPageActivePtr
		CFactoryDictActive::GetPageActive
		(
		void
		)
{
	CDictPageActivePtr	p = m_pActive;
	m_pActive = 0;		// clear this because it is a TPointer
	return p;
}

/*---------------------------------------------------------------------+\

 * GetPageBase -

\+---------------------------------------------------------------------*/
CDictPageVariantReadPtr
		CFactoryDictActive::GetPageBase
		(
		void
		)
{
	CDictPageVariantReadPtr	p = m_pBase;
	m_pBase = 0;		// clear this because it is a TPointer
	return p;
}


/*---------------------------------------------------------------------+\

 * GetPageNotify -

\+---------------------------------------------------------------------*/
CDictPageAlertsPtr
		CFactoryDictActive::GetPageNotify
		(
		void
		)
{
	CDictPageAlertsPtr	p = m_pNotify;
	m_pNotify = 0;		// clear this because it is a TPointer
	return p;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * RangeItem::operator &lt; -

\+--------------------------------------------------------------------**/
bool	CFactoryDictActive::RangeItem::operator <
		(
		const RangeItem& rRight
		)
{
	if ( fLow < rRight.fHigh )
		return true;
	else
		return false;
}




/*---------------------------------------------------------------------+\

 * Settings -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::Settings
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	m_pActive = new CDictPageActive;
	m_pBase = new CDictPageVariantRead;
	m_pNotify = new CDictPageAlerts;
	if ( m_pActive  &&  m_pBase  &&  m_pNotify )
	{
		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Alerts" )
					bResult = Alerts( &it );
				else if ( tName == "Parameters" )
					bResult = Parameters( &it );
				else if ( tName == "Glossary" )
					EatNode();
				else if ( tName == "VersionInfo" )
					EatNode();
				else
					it.Error( "Unrecognized tag within Settings" );
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "VersionInfo" )
					EatNode();
				else
					it.Error( "Unrecognized tag within Settings" );
				break;
            default:
                break;
			}
		}
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Alerts -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::Alerts
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT:
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "Alert" )
				bResult = Alert( &it );
			else
				it.Error( "Unrecognized tag in Alerts element" );
			break;
		default:
			break;
		}
	}

	if ( bResult )
	{
		CVariantData	v;
		v = false;
		m_pNotify->AddEntry( "Alerts Active", v );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Alert -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryDictActive::Alert
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	tName = pIt->AttributeValue( "ID" );
	if ( 0 < tName.Length() )
	{
		char			sTemp[128];
		CVariantData	v;
		v = false;

		bResult = m_pNotify->AddEntry( tName, v );

		tValue = pIt->AttributeValue( "Label" );
		if ( 0 < tValue.Length() )
		{
			tName.CopyTo( sTemp, sizeof(sTemp) );
			strcat_s( sTemp, sizeof(sTemp), ".Label" );
			v = tValue;
			v.SetUnits( m_tStringUnits );
			m_pBase->AddEntry( sTemp, v );
		}

		long	nValue;
		nValue = pIt->AttributeValueAsInt( "Level" );
		if ( 0 < nValue )
		{
			tName.CopyTo( sTemp, sizeof(sTemp) );
			strcat_s( sTemp, sizeof(sTemp), ".Level" );
			v = nValue;
			v.SetUnits( m_tNumberUnits );
			m_pBase->AddEntry( sTemp, v );
		}

		tValue = pIt->AttributeValue( "Color" );
		if ( 0 < tValue.Length() )
		{
			CColor	c;
			tValue.ConvertLowercase();
			if ( tValue == "green" )
				 c.SetRGB( 0, 255, 0 );
			else if ( tValue == "red" )
				c.SetRGB( 255, 0, 0 );
			else if ( tValue == "yellow" )
				c.SetRGB( 0x00FF, 0x00CC, 0 );
			else
				c = CColor::ColorFromName( tValue );
			if ( ! c.IsNonColor() )
			{
				tName.CopyTo( sTemp, sizeof(sTemp) );
				strcat_s( sTemp, sizeof(sTemp), ".Color" );
				v = c;
				v.SetUnits( m_tColorUnits );
				m_pBase->AddEntry( sTemp, v );
			}
		}

		if ( ! pIt->NodeEmpty() )
		{
			GFLOAT		fFreq = -1.0;
			GFLOAT		fDur = -1.0;
			CCharDescriptor	tNode;

			XMLIterator	it(pIt);

			while ( it.NextChild() )
			{
				tNode = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT_BEGIN:
					EatNode();
					break;
				case XMLLite::NODE_ELEMENT:
					if ( tNode == "AlertSim" )
						bResult = AlertSim( &fFreq, &fDur, &it );
					else
						EatNode();
					break;
				default:
					break;
				}
			}

			if ( GFLOAT_0 < fFreq )
			{
				if ( tName.CopyTo( sTemp, sizeof(sTemp) ) )
				{
					::strcat_s( sTemp, sizeof(sTemp), ".Duration" );
					v = fDur;
					m_pBase->AddEntry( sTemp, v );
				}
				if ( tName.CopyTo( sTemp, sizeof(sTemp) ) )
				{
					::strcat_s( sTemp, sizeof(sTemp), ".Frequency" );
					v = fFreq;
					m_pBase->AddEntry( sTemp, v );
				}
			}

		}

	}

	return bResult;
}

//END_OVERRUN_WARNING




/*---------------------------------------------------------------------+\

 * ParamSim -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::AlertSim
		(
		GFLOAT*	pfFreq,
		GFLOAT*	pfDur,
		XMLIteratorPtr pIt
		)
{
	bool			bResult = true;

	*pfFreq = pIt->AttributeValueAsFloat( "Frequency" );
	*pfDur = pIt->AttributeValueAsFloat( "Duration" );

	return bResult;
}




/*---------------------------------------------------------------------+\

 * Parameters -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::Parameters
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
		case XMLLite::NODE_ELEMENT:
			tName = it.NodeName();
			if ( tName == "Param" )
			{
				bResult = Param( &it );
			}
			else
			{
				it.Error( "Unrecognized node in Parameters" );
			}
			break;
        default:
			break;
		}
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Param -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryDictActive::Param
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tName;
	CCharDescriptor	tValue;
	XMLIterator		it( pIt );
	CVariantData	v;

	//char		sID[80] = { 0 };
	//char		sLabel[80] = { 0 };
	char		sLabelKey[100] = { 0 };
	char		sAlias[100] = { 0 };
	int			nUnits = 0;
	CVariantData::V_TYPE	eType = CVariantData::T_UNDEFINED;
	VDictPageActiveDatumPtr	pDatum = 0;
	CDictPageActiveDatumEnum*	pEnumDatum = 0;

	m_aRanges.Truncate();
	m_fLow = FLT_MAX;
	m_fHigh = FLT_MIN;
	m_aEnumList.Truncate();

	CCharDescriptor	tID;
	CCharDescriptor	tAlias;
	CCharDescriptor	tLabel;
	CCharDescriptor tDefault;
	CCharDescriptor tReset;
	CCharDescriptor	tUnavailable;

	tID = pIt->AttributeValue( "ID" );
	if ( 0 < tID.Length() )
	{
		tDefault = pIt->AttributeValue( "Default" );
		tReset = pIt->AttributeValue( "Reset" );
		tUnavailable = pIt->AttributeValue( "Unavailable" );
		tAlias = pIt->AttributeValue( "Alias" );
		if ( 0 < tAlias.Length() )
		{
			tAlias.CopyTo( sAlias, sizeof(sAlias) );
		}

		tValue = pIt->AttributeValue( "Units" );
		if ( 0 < tValue.Length() )
		{
			tValue.ConvertLowercase();
			CUnitsOfMeasure	units;
			units.SetUsingString( tValue );
			nUnits = units.GetUnits();
		}

		tValue = pIt->AttributeValue( "Type" );
		if ( 0 < tValue.Length() )
		{
			tValue.ConvertUppercase();
			if ( tValue == "BOOLEAN"
					||	tValue == "BOOL" )
			{
				eType = CVariantData::T_BOOL;
				pDatum = new CDictPageActiveDatumBool;
			}
			else if ( tValue == "INTEGER"
					||	tValue == "INT" )
			{
				eType = CVariantData::T_INTEGER;
				pDatum = new CDictPageActiveDatumInteger;
			}
			else if ( tValue == "FLOAT" )
			{
				eType = CVariantData::T_FLOAT;
				pDatum = new CDictPageActiveDatumFloat;
			}
			else if ( tValue == "TEXT"
					||	tValue == "STRING" )
			{
				eType = CVariantData::T_STRING;
				pDatum = new CDictPageActiveDatumString;
			}
			else if ( tValue == "DATETIME"
					||	tValue == "TIME"
					||	tValue == "DATE" )
			{
				eType = CVariantData::T_DATETIME;
				pDatum = new CDictPageActiveDatumDate;
			}
			else if ( tValue == "ENUM" )
			{
				eType = CVariantData::T_INTEGER;
				pEnumDatum = new CDictPageActiveDatumEnum;
				pDatum = pEnumDatum;
			}
			else
			{
				bResult = false;
			}
		}

		if ( pDatum )
		{
			if ( 0 < tDefault.Length() )
			{
				CVariantData	v2 = tDefault;
				pDatum->UpdateData( m_pActive, v2 );
			}
			if ( 0 < tReset.Length() )
				pDatum->SetReset( tReset );

			if ( 0 < tUnavailable.Length() )
				pDatum->SetUnavailable( tUnavailable );

			pDatum->SetUnits( nUnits );
			m_pActive->AddDatumEntry( tID, pDatum );
		}

		if ( 0 < tAlias.Length() )
			m_pActive->AddAlias( tID, tAlias );



		tLabel = pIt->AttributeValue( "Label" );
		if ( 0 < tLabel.Length() )
		{
			if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
			{
				::strcat_s( sLabelKey, sizeof(sLabelKey), ".Label" );
				v = tLabel;
				v.SetUnits( m_tStringUnits );
				m_pBase->AddEntry( sLabelKey, v );
			}
		}

		bResult = true;
	}
	else
	{
		bResult = false;
	}

	GFLOAT		fFreq = -1.0;
	int			nWave = -1;

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "Range" )
				bResult = Range( tID, eType, nUnits, &it );
			else if ( tName == "Data" )
				EatNode();
			else
				it.Error( "Unrecognized tag within Param" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Range" )
				bResult = Range( tID, eType, nUnits, &it );
			else if ( tName == "ParamSim" )
				bResult = ParamSim( &nWave, &fFreq, &it );
			else
				it.Error( "Unrecognized tag within Param" );
			break;
        default:
			break;
		}
	}


	if ( bResult )
	{
		if ( -1 < nWave )
		{
			if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
			{
				::strcat_s( sLabelKey, sizeof(sLabelKey), ".Wave" );
				v = (long)nWave;
				m_pBase->AddEntry( sLabelKey, v );
			}
			if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
			{
				::strcat_s( sLabelKey, sizeof(sLabelKey), ".Frequency" );
				v = fFreq;
				m_pBase->AddEntry( sLabelKey, v );
			}
		}

		if ( m_fLow < m_fHigh )
		{

			if ( CVariantData::T_INTEGER == eType )
			{
				if ( ! pEnumDatum )
				{
					CDictPageActiveDatumInteger* pDatumInt
							= static_cast<CDictPageActiveDatumInteger*>(pDatum);
					pDatumInt->SetRange( static_cast<long>(m_fLow), static_cast<long>(m_fHigh) );
					if ( m_tDegreesUnits.GetUnits() == nUnits )
					{
						long	n = static_cast<long>(m_fHigh - m_fLow);
						if ( n == 360 )
							pDatumInt->SetCheckType( 2 );	// circular
					}
				}
			}
			else if ( CVariantData::T_FLOAT == eType )
			{
				CDictPageActiveDatumFloat* pDatumFlt
						= static_cast<CDictPageActiveDatumFloat*>(pDatum);
				pDatumFlt->SetRange( m_fLow, m_fHigh );
				if ( m_tDegreesUnits.GetUnits() == nUnits )
				{
					GFLOAT	f = m_fHigh - m_fLow;
					if ( ::fabsf(f - GFLOAT_360) < GFLOAT_EPSILON )
						pDatumFlt->SetCheckType( 2 );	// circular
				}
			}


			if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
			{
				::strcat_s( sLabelKey, sizeof(sLabelKey), ".High" );
				if ( CVariantData::T_INTEGER == eType )
					v = static_cast<long>(m_fHigh);
				else
					v = m_fHigh;
				v.SetUnits( nUnits );
				m_pBase->AddEntry( sLabelKey, v );
			}

			if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
			{
				::strcat_s( sLabelKey, sizeof(sLabelKey), ".Low" );
				if ( CVariantData::T_INTEGER == eType )
					v = static_cast<long>(m_fLow);
				else
					v = m_fLow;
				v.SetUnits( nUnits );
				m_pBase->AddEntry( sLabelKey, v );
			}

			if ( pEnumDatum )
			{
				if ( 0 < m_aEnumList.Length() )
				{
					CCharStringPtr	p = m_aEnumList.PointArray();
					CCharStringPtr	pEnd = p + m_aEnumList.Length();
					while ( p < pEnd )
					{
						pEnumDatum->AddItem( p->Pointer() );
						++p;
					}
				}
			}
			else
			{
				if ( 0 < m_aRanges.Length() )
				{
					m_aRanges.Sort();

					RangeMultiColor();

					RangeItem*	p = m_aRanges.PointArray();
					RangeItem*	pEnd = p + m_aRanges.Length();
					while ( p < pEnd )
					{
						if ( p->fHigh < p->fLow )
							p->fLow = p->fHigh;
						if ( p->fLow < m_fLow )
							p->fLow = m_fLow;
						if ( m_fHigh < p->fHigh )
							p->fHigh = m_fHigh;
						if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
						{
							::strcat_s( sLabelKey, sizeof(sLabelKey), "." );
							::strcat_s( sLabelKey, sizeof(sLabelKey), p->sID );
							if ( 0 < p->nCount )
							{
								char	sCount[20];
								sprintf_s( sCount, sizeof(sCount), "%d", p->nCount );
								::strcat_s( sLabelKey, sizeof(sLabelKey), sCount );
							}
							::strcat_s( sLabelKey, sizeof(sLabelKey), ".Low" );
							if ( CVariantData::T_INTEGER == eType )
								v = static_cast<long>(p->fLow);
							else
								v = p->fLow;
							v.SetUnits( nUnits );
							m_pBase->AddEntry( sLabelKey, v );
						}
						if ( tID.CopyTo( sLabelKey, sizeof(sLabelKey) ) )
						{
							::strcat_s( sLabelKey, sizeof(sLabelKey), "." );
							::strcat_s( sLabelKey, sizeof(sLabelKey), p->sID );
							if ( 0 < p->nCount )
							{
								char	sCount[20];
								sprintf_s( sCount, sizeof(sCount), "%d", p->nCount );
								::strcat_s( sLabelKey, sizeof(sLabelKey), sCount );
							}
							::strcat_s( sLabelKey, sizeof(sLabelKey), ".High" );
							if ( CVariantData::T_INTEGER == eType )
								v = static_cast<long>(p->fHigh);
							else
								v = p->fHigh;
							v.SetUnits( nUnits );
							m_pBase->AddEntry( sLabelKey, v );
						}
						++p;
					}
				}
			}

		}
	}

	return bResult;
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * RangeMultiColor -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::RangeMultiColor
		(
		void
		)
{
	bool	bResult = true;

	RangeItem*	pStart = m_aRanges.PointArray();
	RangeItem*	pEnd = pStart + m_aRanges.Length();
	RangeItem*	p = pStart;

	int		nCount = 0;

	while ( pStart < pEnd )
	{
		nCount = 1;
		p = pStart + 1;
		while ( p < pEnd )
		{
			if ( 0 == p->nCount )
			{
				if ( 0 == ::strcmp( pStart->sID, p->sID ) )
				{
					if ( 0 == pStart->nCount )
						pStart->nCount = 1;
					++nCount;
					p->nCount = nCount;
				}
			}
			++p;
		}
		++pStart;
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Range -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryDictActive::Range
		(
		CCharDescriptorRef,
		CVariantData::V_TYPE,
		int,
		XMLIteratorPtr			pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	if ( XMLLite::NODE_ELEMENT == pIt->NodeType() )
	{
		long	nAttrCount = pIt->AttributeCount();
		if ( 0 < nAttrCount )
		{
			bResult = true;
			RangeItem	rItem = {0};
			tValue = pIt->AttributeValue( "ID" );
			if ( tValue == "HiLo" )
			{
				m_fHigh = pIt->AttributeValueAsFloat( "Hi" );
				m_fLow = pIt->AttributeValueAsFloat( "Low" );
			}
			else
			{
				if ( tValue.CopyTo( rItem.sID, sizeof(rItem.sID) ) )
				{
					rItem.fHigh = pIt->AttributeValueAsFloat( "Hi" );
					rItem.fLow = pIt->AttributeValueAsFloat( "Low" );
					rItem.nCount = 0;
					m_aRanges.AppendData( &rItem );
				}
			}

		}
	}
	else	// NODE_ELEMENT_BEGIN
	{
		m_fHigh = pIt->AttributeValueAsFloat( "Hi" );
		m_fLow = pIt->AttributeValueAsFloat( "Low" );
		CCharDescriptor	tName;
		XMLIterator		it( pIt );
		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Enum" )
					bResult = Enum( &it );
				else
					it.Error( "Unrecognized tag in Range Element" );
				break;
			case XMLLite::NODE_ELEMENT_BEGIN:
				it.Error( "Malformed Range Element" );
				break;
            default:
				break;
			}
		}
	}


	return bResult;
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * ParamSim -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::ParamSim
		(
		int*	pnWave,
		GFLOAT*	pfFreq,
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( "Wave" );
	if ( 0 < tValue.Length() )
	{
		bResult = true;
		if ( tValue == "sawtooth" )
			*pnWave = 0;
		else if ( tValue == "sawtooth-inverted" )
			*pnWave = 1;
		else if ( tValue == "sine" )
			*pnWave = 2;
		else if ( tValue == "square" )
			*pnWave = 3;
		else if ( tValue == "triangle" )
			*pnWave = 4;
		else
			bResult = false;
	}

	*pfFreq = pIt->AttributeValueAsFloat( "Frequency" );

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Enum -

\+---------------------------------------------------------------------*/
bool	CFactoryDictActive::Enum
		(
		XMLIteratorPtr	pIt
		)
{
	bool			bResult = false;
	CCharDescriptor	tValue;

	tValue = pIt->AttributeValue( "Value" );
	if ( 0 < tValue.Length() )
	{
		CCharString	sEmpty;
		long n = pIt->AttributeValueAsInt( "ID" );
		while ( long(m_aEnumList.Length()) < n )
			m_aEnumList.AppendData( &sEmpty );
		CCharString sValue( tValue );
		m_aEnumList.AppendData( &sValue );
		bResult = true;
	}


	return bResult;
}










/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
