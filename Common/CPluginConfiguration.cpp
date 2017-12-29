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
NAMESPACE_COMMON_BEGIN
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
		: m_sClass(),
		m_sGroup(),
		m_sID(),
		m_sTemp(),
		m_aAttributes(),
		m_aParameters(),
		m_aFolders(),
		m_nFolderCount( 0 )
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
	VPluginConfigurationPtr*	h;
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
	VPluginConfigurationPtr*	h;
	FolderEnum			tEnum = m_aFolders.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		h = tEnum.Current();
		if ( h )
		{
			CCharString	s = (*h)->GetClass();
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
		CCharDescriptorRef	r
		)
{
	m_sClass = r;
}

/*---------------------------------------------------------------------+\

 * GetClass -

\+---------------------------------------------------------------------*/
CCharStringRef
		CPluginConfiguration::GetClass
		(
		void
		)
{
	return m_sClass;
}


/*---------------------------------------------------------------------+\

 * SetGroup -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::SetGroup
		(
		CCharDescriptorRef r
		)
{
	m_sGroup = r;
}

/*---------------------------------------------------------------------+\

 * GetGroup -

\+---------------------------------------------------------------------*/
CCharStringRef
		CPluginConfiguration::GetGroup
		(
		void
		)
{
	return m_sGroup;
}


/*---------------------------------------------------------------------+\

 * SetID -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::SetID
		(
		CCharDescriptorRef r
		)
{
	m_sID = r;
}

/*---------------------------------------------------------------------+\

 * GetID -

\+---------------------------------------------------------------------*/
CCharStringRef
		CPluginConfiguration::GetID
		(
		void
		)
{
	return m_sID;
}



/*---------------------------------------------------------------------+\

 * AddParameter -

\+---------------------------------------------------------------------*/
void	CPluginConfiguration::AddParameter
		(
		CCharDescriptorRef rName,
		CVariantDataRef rData
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
		CCharDescriptorRef	rName,
		CCharDescriptorRef	rData
		)
{
	if ( 0 < rName.Length() )
	{
		CCharString	sName = rName;
		CCharString	sData = rData;

		m_aAttributes.Add( sName, sData );
	}
}


/*---------------------------------------------------------------------+\

 * AddFolder -

\+---------------------------------------------------------------------*/
bool	CPluginConfiguration::AddFolder
		(
		CCharDescriptorRef rName,
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
			CCharString	sName;
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
	VPluginConfigurationPtr*	h;
	FolderEnum			tEnum = m_aFolders.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		h = tEnum.Current();
		if ( h )
		{
			if ( (*h) == pConfig )
			{
				CCharString	sKey = tEnum.Key();
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
		)
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
		)
{
	return m_aFolders.GetEnumerator();
}


/*---------------------------------------------------------------------+\

 * GetAttribute -

\+---------------------------------------------------------------------*/
CCharStringRef
		CPluginConfiguration::GetAttribute
		(
		const char*	sKey
		)
{
	CCharString		tName( sKey );
	CCharStringPtr	p = m_aAttributes.Find( sKey );
	if ( p )
		m_sTemp = *p;
	else
		m_sTemp.ClearString();
	return m_sTemp;
}


/*---------------------------------------------------------------------+\

 * GetParameter -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CPluginConfiguration::GetParameter
		(
		const char*	sKey
		)
{
	CCharString	tName( sKey );
	return GetParameter( tName );
}


/*---------------------------------------------------------------------+\

 * GetParameter -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CPluginConfiguration::GetParameter
		(
		ConstCCharStringRef	sKey
		)
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
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		long	n = *pv;
		if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
		{
			LogPrint( "Problem with Parameter type as integer\n" );
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
		)
{
	long			nResult = 0;
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		long*	pStart = pArray;
		long*	pEnd = pStart + nAlloc;
		CCharString	tValue = pv->GetValueCCharString();
		const char*	s = tValue.Pointer();
		const char*	sEnd = s + tValue.Length();
		long	nValue;
		size_t	n;

		while ( s < sEnd )
		{
			//s += this->SpanBlanks( s, sEnd );

			nValue = ParseInt( s, (size_t)(sEnd - s), &n );
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
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		unsigned long	n = pv->GetValueUnsignedInteger();
		if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
		{
			LogPrint( "Problem with Parameter type as unsigned\n" );
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
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		GFLOAT	f = *pv;
		if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
		{
			LogPrint( "Problem with Parameter type as float\n" );
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
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( 0 < pv->GetUnits()
			&&	sUnitName )
		{
			CUnitsOfMeasure	u;
			u.SetUsingString( sUnitName );
			if ( CVariantData::MT_NUMERIC != pv->GetMetaType() )
			{
				LogPrint( "Problem with Parameter type as float\n" );
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
CCharStringRef
		CPluginConfiguration::GetParameterAsString
		(
		const char*	sKey,
		const char*	sDefault	//=0
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::MT_CHARACTER != pv->GetMetaType() )
		{
			LogPrint( "Problem with Parameter type as string\n" );
		}
		m_sTemp = pv->GetValueCCharString();
	}
	else if ( sDefault )
	{
		m_sTemp = sDefault;
	}
	else
	{
		m_sTemp = CCharString();
	}
	return m_sTemp;
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
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::T_STRING == pv->GetType() )
		{
			if ( pEnumList )
			{
				EnumDatumPtr	pDatum = pEnumList;
				EnumDatumPtr	pDatumEnd = pEnumList + nEnumCount;
				CCharString		s = *pv;
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
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::T_BOOL != pv->GetType() )
		{
			LogPrint( "Problem with Parameter type as boolean\n" );
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
CColor	CPluginConfiguration::GetParameterAsColor
		(
		const char*		sKey,
		const CColor	cDefault	//= CColor(0,0,0)
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::MT_COLOR != pv->GetMetaType() )
		{
			LogPrint( "Problem with Parameter type as color\n" );
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
CDateTime
		CPluginConfiguration::GetParameterAsDateTime
		(
		const char*		sKey,
		const CDateTime	cDefault	//= CDateTime()
		)
{
	CVariantDataPtr	pv;
	pv = GetParameter( sKey );
	if ( pv )
	{
		if ( CVariantData::MT_DATETIME != pv->GetMetaType() )
		{
			LogPrint( "Problem with Parameter type as date-time\n" );
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


NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

