/*---------------------------------------------------------------------+\
|
|	CConfiguration.cpp  --  brief description of what CConfiguration.cpp is for
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
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	27-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include "stdafx.h"
#include "CConfiguration.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
namespace Yogi { namespace Common {

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

 * CConfiguration - constructor

\+---------------------------------------------------------------------*/
CConfiguration::CConfiguration
		(
		void
		)
		: m_aContent()
{
}


/*---------------------------------------------------------------------+\

 * ~CConfiguration - destructor

\+---------------------------------------------------------------------*/
CConfiguration::~CConfiguration
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * AddEntry -

\+---------------------------------------------------------------------*/
bool	CConfiguration::AddEntry
		(
		const char*				sName,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;
	CCharString	tName( sName );

	bResult = m_aContent.Add( tName, rData );

	return bResult;
}



/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CConfiguration::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	CCharString	tKey( rKey );
	CCharString	tAlias( rAlias );
	return m_aContent.AddAlias( tKey, tAlias );
}





/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CConfiguration::PutData
		(
		index_t				nSel,
		const CVariantData*	pData
		)
{
	bool	bResult = false;
	CVariantDataPtr	p = m_aContent.ItemAtIndex( nSel );
	if ( p )
	{
		if ( *p != *pData )
		{
			*p = *pData;
			bResult = true;
		}
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * ResolveVariable -

\+---------------------------------------------------------------------*/
Yogi::Core::CCharString
		CConfiguration::ResolveVariable
		(
		ConstCCharDescriptorRef r
		)
{
	CCharString	s = r;

	return GetEntryAsString( s.Pointer() );
}


/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
long	CConfiguration::LocateEntry
		(
		ConstCCharStringRef	rName
		) const
{
	return long(m_aContent.IndexOf( rName ));
}




/*---------------------------------------------------------------------+\

 * GetEntry -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CConfiguration::GetEntry
		(
		const char*	sKey
		) const
{
	CCharString	tName( sKey );
	return GetEntry( tName );
}


/*---------------------------------------------------------------------+\

 * GetEntry -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CConfiguration::GetEntry
		(
		ConstCCharStringRef	sKey
		) const
{
	return m_aContent.Find( sKey );
}


/*---------------------------------------------------------------------+\

 * GetEntry -

\+---------------------------------------------------------------------*/
ConstCVariantDataPtr
		CConfiguration::GetData
		(
		index_t	nSel
		) const
{
	return m_aContent.ItemAtIndex( nSel );
}



/*---------------------------------------------------------------------+\

 * GetParameterAsInteger -

\+---------------------------------------------------------------------*/
long	CConfiguration::GetEntryAsInteger
		(
		const char*	sKey,
		long		nDefault	//=0
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		long	n = pv->GetValueInteger();
		return n;
	}
	else
	{
		return nDefault;
	}
}

/*---------------------------------------------------------------------+\

 * GetParameterAsUnsigned -

\+---------------------------------------------------------------------*/
unsigned long
		CConfiguration::GetEntryAsUnsigned
		(
		const char*		sKey,
		unsigned long	nDefault	//=0
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		unsigned long	n = static_cast<unsigned long>(pv->GetValueInteger());
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
GFLOAT
		CConfiguration::GetEntryAsFloat
		(
		const char*	sKey,
		GFLOAT		fDefault	//=0
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		GFLOAT	f = pv->GetValueFloat();
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
DECL_API(GFLOAT)
		CConfiguration::GetEntryAsFloatUnits
		(
		const char*	sKey,
		const char*	sUnitName,
		GFLOAT		fDefault	//=0
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		if ( 0 < pv->GetUnits()
				&&	sUnitName )
		{
			CUnitsOfMeasure	u;
			u.SetUsingString( sUnitName );
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
DECL_API(Yogi::Core::CCharString)
		CConfiguration::GetEntryAsString
		(
		const char*	sKey,
		const char*	sDefault	//=0
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		CCharString	s = pv->GetValueString();
		return s;
	}
	else
	{
		CCharString	s( sDefault );
		return s;
	}
}


/*---------------------------------------------------------------------+\

 * GetEntryAsEnum -

\+---------------------------------------------------------------------*/
DECL_API(long)
		CConfiguration::GetEntryAsEnum
		(
		const char*			sKey,
		const VConfiguration::EnumDatumPtr	pEnumList,
		const long			nEnumCount,
		const long			nDefault,	//= 0
		const long			nError		//= 0
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		if ( CVariantData::T_STRING == pv->GetType() )
		{
			if ( pEnumList )
			{
				EnumDatumPtr	pDatum = pEnumList;
				EnumDatumPtr	pDatumEnd = pEnumList + nEnumCount;
				Yogi::Core::CCharString		s = pv->GetValueString();
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

 * GetEntryAsBool -

\+---------------------------------------------------------------------*/
DECL_API(bool)
		CConfiguration::GetEntryAsBool
		(
		const char*		sKey,
		const bool		bDefault	//= false
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		return pv->GetValueBool();
	}
	else
	{
		return bDefault;
	}
}


/*---------------------------------------------------------------------+\

 * GetEntryAsColor -

\+---------------------------------------------------------------------*/
DECL_API(Yogi::Core::CColor)
		CConfiguration::GetEntryAsColor
		(
		const char*					sKey,
		const Yogi::Core::CColor	cDefault	//= CColor(0,0,0)
		) const
{
	CVariantDataPtr	pv;
	pv = GetEntry( sKey );
	if ( pv )
	{
		return pv->GetValueColor();
	}
	else
	{
		return cDefault;
	}
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
DECL_API(CConfiguration::Enumerator)
		CConfiguration::GetEnumerator
		(
		void
		)
{
	return m_aContent.GetEnumerator();
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
