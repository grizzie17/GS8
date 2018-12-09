/*---------------------------------------------------------------------+\
|
|	CPluginConfiguration.cpp  --  brief description of what CPluginConfiguration.cpp is for
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
	14-Jul-2010			S.Snider		(Reviewed by: P.Hogan)
		Fixed "CompareIgnoreCase" return value being checked
	13-Jul-2010			J.Griswold		(Reviewed by: S.Snider) [1]
		Allow for prunning of the hierarchy
	05-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Fixed a problem where deleting the string returned from the
		GetParameterAsString would corrupt the heap.  This was caused
		by two different heaps one for the DLL and the other for the App.
	09-May-2010			J.Griswold		(Reviewed by: P.Hogan) [1]
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CPluginConfiguration.h"

#include "LogFile.h"
#include "UPlatform.h"
namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

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

 * CPluginConfiguration - constructor

\+---------------------------------------------------------------------*/
CPluginConfiguration::CPluginConfiguration
		(
		void
		)
		: m_sClass()
		, m_sGroup()
		, m_sID()
		, m_sTemp()
		, m_aAttributes()
		, m_aParameters()
		, m_aFolders()
		, m_nFolderCount( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~CPluginConfiguration - destructor

\+---------------------------------------------------------------------*/
CPluginConfiguration::~CPluginConfiguration
		(
		void
		)
{
	const VPluginConfigurationPtr*	h;
	FolderEnum			tEnum = m_aFolders.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		h = tEnum.Current();
		if ( h )
		{
			delete (*h);
		}
	}

}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SelectSingleNode -

\+---------------------------------------------------------------------*/
VPluginConfiguration*
		CPluginConfiguration::SelectSingleNode
		(
		const char*	sQuery
		)
{
	const VPluginConfigurationPtr*	h;
	FolderEnum			tEnum = m_aFolders.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		h = tEnum.Current();
		if ( h )
		{
			Yogi::Core::CCharString	s = (*h)->GetClass();
			if ( s == sQuery )
			{
				return *h;
			}
			else
			{
				VPluginConfiguration*	p = (*h)->SelectSingleNode( sQuery );
				if ( p )
					return p;
			}
		}
	}
	return 0;
}

/*---------------------------------------------------------------------+\

 * SetClass -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::SetClass
		(
		Yogi::Core::ConstCCharDescriptorRef	r
		)
{
	m_sClass = r;
}

/*---------------------------------------------------------------------+\

 * GetClass -

\+---------------------------------------------------------------------*/
Yogi::Core::ConstCCharStringRef
		CPluginConfiguration::GetClass
		(
		void
		) const
{
	return m_sClass;
}


/*---------------------------------------------------------------------+\

 * SetGroup -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::SetGroup
		(
		Yogi::Core::ConstCCharDescriptorRef r
		)
{
	m_sGroup = r;
}

/*---------------------------------------------------------------------+\

 * GetGroup -

\+---------------------------------------------------------------------*/
Yogi::Core::ConstCCharStringRef
		CPluginConfiguration::GetGroup
		(
		void
		) const
{
	return m_sGroup;
}


/*---------------------------------------------------------------------+\

 * SetID -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::SetID
		(
		Yogi::Core::ConstCCharDescriptorRef r
		)
{
	m_sID = r;
}

/*---------------------------------------------------------------------+\

 * GetID -

\+---------------------------------------------------------------------*/
Yogi::Core::ConstCCharStringRef
		CPluginConfiguration::GetID
		(
		void
		) const
{
	return m_sID;
}



/*---------------------------------------------------------------------+\

 * AddParameter -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::AddParameter
		(
		Yogi::Core::ConstCCharDescriptorRef	rName,
		ConstCVariantDataRef				rData
		)
{
	if ( 0 < rName.Length() )
	    m_aParameters.Add( rName, rData );
}


/*---------------------------------------------------------------------+\

 * AddAttribute -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::AddAttribute
		(
		Yogi::Core::ConstCCharDescriptorRef	rName,
		Yogi::Core::ConstCCharDescriptorRef	rData
		)
{
	if ( 0 < rName.Length() )
	{
		Yogi::Core::CCharString	sName = rName;
		Yogi::Core::CCharString	sData = rData;

		m_aAttributes.Add( sName, sData );
	}
}


/*---------------------------------------------------------------------+\

 * AddFolder -

\+---------------------------------------------------------------------*/
bool	CPluginConfiguration::AddFolder
		(
		Yogi::Core::ConstCCharDescriptorRef rName,
		CPluginConfigurationPtr pFolder
		)
{
	bool	bResult = false;

	if ( pFolder )
	{
		++m_nFolderCount;
		if ( 0 < rName.Length() )
		{
	        bResult = m_aFolders.Add( rName, pFolder );
		}
		else
		{
			Yogi::Core::CCharString	sName;
			sName.Format( "@IDX@%ld", m_nFolderCount );
			bResult = m_aFolders.Add( sName, pFolder );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * PruneFolder -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::PruneFolder
		(
		CPluginConfigurationPtr pConfig
		)
{
	const VPluginConfigurationPtr*	h;
	FolderEnum			tEnum = m_aFolders.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		h = tEnum.Current();
		if ( h )
		{
			if ( (*h) == pConfig )
			{
				Yogi::Core::CCharString	sKey = tEnum.Key();
				m_aFolders.Remove( sKey );
			}
		}
	}
}

/*---------------------------------------------------------------------+\

 * GetParamEnum -

\+---------------------------------------------------------------------*/
CPluginConfiguration::ParamEnum
		CPluginConfiguration::GetParamEnum
		(
		void
		) const
{
	return m_aParameters.GetEnumerator();
}

/*---------------------------------------------------------------------+\

 * GetFolderEnum -

\+---------------------------------------------------------------------*/
CPluginConfiguration::FolderEnum
		CPluginConfiguration::GetFolderEnum
		(
		void
		) const
{
	return m_aFolders.GetEnumerator();
}


/*---------------------------------------------------------------------+\

 * GetAttribute -

\+---------------------------------------------------------------------*/
Yogi::Core::ConstCCharStringRef
		CPluginConfiguration::GetAttribute
		(
		const char*	sKey
		)
{
	Yogi::Core::CCharString			tName( sKey );
	const Yogi::Core::CCharString*	p = m_aAttributes.Find( tName );
	if ( p )
		m_sTemp = *p;
	else
		m_sTemp.ClearString();
	return m_sTemp;
}


/*---------------------------------------------------------------------+\

 * GetParameter -

\+---------------------------------------------------------------------*/
const CVariantData*
		CPluginConfiguration::GetParameter
		(
		const char*	sKey
		) const
{
	Yogi::Core::CCharString	tName( sKey );
	return GetParameter( tName );
}


/*---------------------------------------------------------------------+\

 * GetParameter -

\+---------------------------------------------------------------------*/
const CVariantData*
		CPluginConfiguration::GetParameter
		(
		Yogi::Core::ConstCCharStringRef	sKey
		) const
{
	return m_aParameters.Find( sKey );
}


/*---------------------------------------------------------------------+\

 * GetParameterAsInteger -

\+---------------------------------------------------------------------*/
long	CPluginConfiguration::GetParameterAsInteger
		(
		const char*	sKey,
		long		nDefault	//=0
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		long	n = pv->GetValueInteger();
		if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as integer\n" );
		}
		return n;
	}
	else
	{
		return nDefault;
	}
}

long	CPluginConfiguration::GetParameterAsIntegerArray
		(
		long*		pArray,
		long		nAlloc,
		const char*	sKey
		) const
{
	long			nResult = 0;
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		long*	pStart = pArray;
		long*	pEnd = pStart + nAlloc;
		Yogi::Core::CCharString	tValue = pv->GetValueCCharString();
		const char*	s = tValue.Pointer();
		const char*	sEnd = s + tValue.Length();
		long	nValue;
		size_t	n;

		while ( s < sEnd )
		{
			//s += this->SpanBlanks( s, sEnd );

			nValue = Yogi::Core::ParseIntT( s, (size_t)(sEnd - s), &n );
			if ( 0 < n )
			{
				if ( pArray < pEnd )
				{
					*pArray = nValue;
					++pArray;
				}
				++nResult;
			}
			s += n;

			//s += this->SpanBlanks( s, sEnd );

			if ( ',' == *s  ||  ';' == *s )
				++s;
			else
				break;
		}

		if ( s < sEnd )
			nResult = 0;

	}
	return nResult;
}

/*---------------------------------------------------------------------+\

 * GetParameterAsUnsigned -

\+---------------------------------------------------------------------*/
unsigned long
		CPluginConfiguration::GetParameterAsUnsigned
		(
		const char*		sKey,
		unsigned long	nDefault	//=0
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		unsigned long	n = pv->GetValueUnsignedInteger();
		if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as unsigned\n" );
		}
		return n;
	}
	else
	{
		return nDefault;
	}
}

/*---------------------------------------------------------------------+\

 * GetParameterAsFloat -

\+---------------------------------------------------------------------*/
GFLOAT	CPluginConfiguration::GetParameterAsFloat
		(
		const char*	sKey,
		GFLOAT		fDefault	//=0
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		GFLOAT	f = pv->GetValueFloat();
		if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as float\n" );
		}
		return f;
	}
	else
	{
		return fDefault;
	}
}


/*---------------------------------------------------------------------+\

 * GetParameterAsFloatUnits -

\+---------------------------------------------------------------------*/
GFLOAT	CPluginConfiguration::GetParameterAsFloatUnits
		(
		const char*	sKey,
		const char*	sUnitName,
		GFLOAT		fDefault	//=0
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( 0 < pv->GetUnits()
			&&	sUnitName )
		{
			CUnitsOfMeasure	u;
			u.SetUsingString( sUnitName );
			if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
			{
				Yogi::Core::LogPrint( "Problem with Parameter type as float\n" );
			}
			return pv->GetValueFloatAsUnits( u );
		}
		else
		{
			return pv->GetValueFloat();
		}
	}
	else
	{
		return fDefault;
	}
}


/*---------------------------------------------------------------------+\

 * GetParameterAsString -

\+---------------------------------------------------------------------*/
Yogi::Core::ConstCCharStringRef
		CPluginConfiguration::GetParameterAsString
		(
		const char*	sKey,
		const char*	sDefault	//=0
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	Yogi::Core::CCharString* ps = new Yogi::Core::CCharString;
	if ( pv )
	{
		if ( CVariantData::MT_CHARACTER != pv->GetMetaType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as string\n" );
		}
		ps->LoadCCharString( pv->GetValueCCharString() );
	}
	else if ( sDefault )
	{
		ps->LoadStringData( sDefault );
	}
	return *ps;
}


/*---------------------------------------------------------------------+\

 * GetParameterAsEnum -

\+---------------------------------------------------------------------*/
long	CPluginConfiguration::GetParameterAsEnum
		(
		const char*			sKey,
		const VPluginConfiguration::EnumDatumPtr	pEnumList,
		const long			nEnumCount,
		const long			nDefault,	//= 0
		const long			nError		//= 0
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::T_STRING == pv->GetType() )
		{
			if ( pEnumList )
			{
				EnumDatumPtr	pDatum = pEnumList;
				EnumDatumPtr	pDatumEnd = pEnumList + nEnumCount;
				Yogi::Core::CCharString		s = pv->GetValueCCharString();
				while ( pDatum < pDatumEnd )
				{
					if ( 0 == s.CompareIgnoreCase( pDatum->sKey ) )
					{
						return pDatum->nValue;
					}
					++pDatum;
				}
				return nError;	// not found
			}
			else
			{
				return nError;
			}
		}
		else
		{
			return pv->GetValueInteger();
		}
	}
	else
	{
		return nDefault;
	}
}

/*---------------------------------------------------------------------+\

 * GetParameterAsBool -

\+---------------------------------------------------------------------*/
bool	CPluginConfiguration::GetParameterAsBool
		(
		const char*		sKey,
		const bool		bDefault	//= false
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::T_BOOL != pv->GetType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as boolean\n" );
		}
		return pv->GetValueBool();
	}
	else
	{
		return bDefault;
	}
}

/*---------------------------------------------------------------------+\

 * GetParameterAsColor -

\+---------------------------------------------------------------------*/
Yogi::Core::CColor
		CPluginConfiguration::GetParameterAsColor
		(
		const char*		sKey,
		Yogi::Core::ConstCColorRef	cDefault	//= CColor(0,0,0)
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::MT_COLOR != pv->GetMetaType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as color\n" );
		}
		return pv->GetValueColor();
	}
	else
	{
		return cDefault;
	}
}

/*---------------------------------------------------------------------+\

 * GetParameterAsDateTime -

\+---------------------------------------------------------------------*/
Yogi::Core::CDateTime
		CPluginConfiguration::GetParameterAsDateTime
		(
		const char*		sKey,
		Yogi::Core::ConstCDateTimeRef	cDefault	//= CDateTime()
		) const
{
	const CVariantData*	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::MT_DATETIME != pv->GetMetaType() )
		{
			Yogi::Core::LogPrint( "Problem with Parameter type as date-time\n" );
		}
		return pv->GetValueDateTime();
	}
	else
	{
		return cDefault;
	}
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

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

