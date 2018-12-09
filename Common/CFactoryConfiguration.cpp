/*---------------------------------------------------------------------+\
|
|	CFactoryConfiguration.cpp  --  Make CConfiguration object from XML
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
	13-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Optimized the datatype handling in the Item tag
		sensitive file systems (Unix/Linux)
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Support "COLOR" as a "Type"
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		React to new base configuration class
	11-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add aliases for some types:
		BOOL for BOOLEAN, INT for INTEGER, DATE for DATETIME
	04-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Make sure comments are allowed
	02-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix a bug in getting the Units from an Item.
	29-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Support including another configuration file into the
		contents of the current configuration file
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Cleaned out older irrXML code
	02-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to use the new XMLLite classes
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include "stdafx.h"
#include <float.h>

#include "CFactoryConfiguration.h"

#include "UPlatform.h"
#include "CCharString.h"
#include "CUnitsOfMeasure.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * CFactoryConfiguration - constructor

\+---------------------------------------------------------------------*/
CFactoryConfiguration::CFactoryConfiguration
		(
		void
		)
		: VFactoryLite(),
		m_pConfig( 0 )
{
	m_pVariable = (VVariablePtr)this;
}


/*---------------------------------------------------------------------+\

 * ~CFactoryConfiguration - destructor

\+---------------------------------------------------------------------*/
CFactoryConfiguration::~CFactoryConfiguration
		(
		void
		)
{
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Make -

\+---------------------------------------------------------------------*/
VConfigurationPtr
		CFactoryConfiguration::Make
		(
		const char*			sName,
		VConfigurationPtr	pConfig
		)
{
	VConfigurationPtr	pNode = 0;

	m_pConfig = pConfig;

	if ( OpenFile( sName ) )
	{
		Yogi::Core::CCharDescriptor	tName;
		XMLIterator	it( this );

		while ( it.NextChild() )
		{
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				tName = it.NodeName();
				if ( tName == "Configuration" )
				{
					pNode = Configuration( pConfig );
				}
				break;
            default:
                break;
			}
		}
	}

	return pNode;
}




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/





/*---------------------------------------------------------------------+\

 * Configuration -

\+---------------------------------------------------------------------*/
VConfigurationPtr
		CFactoryConfiguration::Configuration
		(
		VConfigurationPtr	pConfig
		)
{
	VConfigurationPtr	pNode = 0;

	if ( pConfig )
		pNode = pConfig;
	else
		pNode = new CConfiguration;
	m_pConfig = pNode;
	if ( pNode )
	{

		XMLIterator	it( this );
		Yogi::Core::CCharDescriptor	tName;
		Yogi::Core::CCharDescriptor	tValue;
		//bool			bResult = false;

		while ( it.NextChild() )
		{
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				tName = it.NodeName();
				if ( tName == "Item" )
				{
					//bResult =
					Item( pNode, &it );
				}
				else if ( tName == "Include" )
				{
					//bResult =
					IncludeFile( pNode, &it );
				}
				break;
			case XMLLite::NODE_COMMENT:
				//bResult = true;
				break;
			default:
				//bResult = false;
				break;
			}
			//if ( ! bResult )
			//	break;
		}
	}


	return pNode;
}





/*---------------------------------------------------------------------+\

 * Item -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryConfiguration::Item
		(
		VConfigurationPtr	pConfig,
		XMLIteratorPtr		pit
		)
{
	bool	bResult = false;

	Yogi::Core::CCharDescriptor	tValue;
	Yogi::Core::CCharDescriptor	tName;


	char		sID[80] = { 0 };
	char		sData[128] = { 0 };
	int			nUnits = 0;
	CVariantData::V_TYPE	eType = CVariantData::T_UNDEFINED;
	CVariantData	v;

	bResult = true;


	tName = pit->AttributeValue( "ID" );
	if ( 0 < tName.Length() )
	{
		tName.CopyTo( sID, sizeof(sID) );

		tValue = pit->AttributeValue( "Units" );
		if ( 0 < tValue.Length() )
		{
			char	sUnits[40];
			tValue.CopyTo( sUnits, sizeof(sUnits) );
			tValue = Yogi::Core::CCharDescriptor( sUnits, tValue.Length() );
			tValue.ConvertLowercase();

			CUnitsOfMeasure	units;
			if ( ! units.SetUsingAbbrev( sUnits ) )
			{
				if ( ! units.SetUsingName( sUnits ) )
					units.SetUsingPluralName( sUnits );
			}
			nUnits = units.GetUnits();
		}


		tValue = pit->AttributeValue( "Type" );
		if ( 0 < tValue.Length() )
		{
			if ( tValue == "BOOLEAN"  ||  tValue == "BOOL" )
			{
				eType = CVariantData::T_BOOL;
			}
			else if ( tValue == "INTEGER"  ||  tValue == "INT" )
			{
				eType = CVariantData::T_INTEGER;
			}
			else if ( tValue == "FLOAT" )
			{
				eType = CVariantData::T_FLOAT;
			}
			else if ( tValue == "TEXT"
				||	tValue == "STRING"
				||	tValue == "ENUM" )
			{
				eType = CVariantData::T_STRING;
			}
			else if ( tValue == "DATETIME"  ||  tValue == "DATE" )
			{
				eType = CVariantData::T_DATETIME;
			}
			else if ( tValue == "COLOR" )
			{
				eType = CVariantData::T_COLOR;
			}
			else
			{
				bResult = false;
			}
		}
		else
		{
			bResult = false;
		}



	}
	else
	{
		bResult = false;
	}
	if ( bResult )
	{
		tValue = pit->NodeValue();
		v.SetUnits( nUnits );

		switch ( eType )
		{
		case CVariantData::T_BOOL:
			{
				tValue.CopyTo( sData, sizeof(sData) );
				bool	b = false;
				char	c = static_cast<char>(::tolower( *sData ));
				if ( ::strchr( "yt1", c ) )
					b = true;
				v = b;
			}
			break;
		case CVariantData::T_COLOR:
			{
				long			nValue;
				size_t			n;
				nValue = tValue.ParseInt( &n );
				if ( 0 < n )
				{
					Yogi::Core::CColor	c;
					c.SetColorLong( nValue );
					v = c;
					bResult = true;
				}
				else
				{
					Yogi::Core::CColor	c = Yogi::Core::CColor::ColorFromName( tValue );
					if ( ! c.IsNonColor() )
					{
						v = c;
					}
					else
					{
						pit->Error( "Unrecognized color name" );
						bResult = false;
					}
				}
			}
			break;
		case CVariantData::T_DATETIME:
			{
				Yogi::Core::CDateTime	d;
				if ( d.Parse( tValue ) )
				{
					v = d;
				}
				else
				{
					pit->Error( "Unrecognized date/time" );
					bResult = false;
				}
			}
			break;
		case CVariantData::T_FLOAT:
			{
				size_t	n;
				GFLOAT	f = tValue.ParseFloat( &n );
				if ( tValue.Length() == n )
				{
					v = f;
				}
				else
				{
					v = 0.0f;
					pit->Error( "Unrecognized character in float" );
					bResult = false;
				}
			}
			break;
		case CVariantData::T_INTEGER:
			{
				size_t	n;
				long	nData = tValue.ParseInt( &n );
				if ( tValue.Length() == n )
				{
					v = nData;
				}
				else
				{
					v = 0L;
					pit->Error( "Unrecognized character in integer" );
					bResult = false;
				}
			}
			break;
		case CVariantData::T_STRING:
			{
				v = tValue;
			}
			break;
		default:
			break;
		}

		pConfig->AddEntry( sID, v );
	}



	return bResult;
}

//END_OVERRUN_WARNING






/*---------------------------------------------------------------------+\

 * IncludeFile -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryConfiguration::IncludeFile
		(
		VConfigurationPtr	pConfig,
		XMLIteratorPtr		pIt
		)
{
	bool				bResult = false;
	VConfigurationPtr	pNode = 0;

	if ( 0 < pIt->AttributeCount() )
	{
		Yogi::Core::CCharDescriptor	tValue;

		tValue = pIt->AttributeValue( "File" );
		if ( 0 < tValue.Length() )
		{
			Yogi::Core::CCharString	sFile = tValue;

			CFactoryConfiguration	factory;
			Yogi::Core::CCharString	sRelPath = this->GetRelativePath();
			factory.SetRelativePath( sRelPath.Pointer() );
			factory.SetVariableIF( m_pVariable );
			factory.SetExternalXMLIF( this->m_pIExternalXML );
			pNode = factory.Make( sFile.Pointer(), pConfig );
		}
	}

	if ( ! pNode )
	{
		pIt->Error( "Problem with Include Tag" );
	}
	else
	{
		bResult = true;
	}

	return bResult;
}

//END_OVERRUN_WARNING











/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * ResolveVariable -

\+---------------------------------------------------------------------*/
Yogi::Core::CCharString
		CFactoryConfiguration::ResolveVariable
		(
		Yogi::Core::ConstCCharDescriptorRef r
		)
{
	Yogi::Core::CCharString	sResult;

	if ( m_pConfig )
	{
		Yogi::Core::CCharString	s = r;
		sResult = m_pConfig->GetEntryAsString( s.Pointer() );
	}
	return sResult;
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

