/*---------------------------------------------------------------------+\
|
|	CFactoryPlugin.cpp  --  Make plugin object from XML
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
\\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	27-Jul-2010			S.Snider		(Reviewed by: J.Griswold)
		Fix to MakeConfiguration() for "parameter include" support
	22-Jul-2010			S.Snider		(Reviewed by: J.Griswold)
		Removed copying string data for debug prints
	13-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Optimize the Param parsing for datatype
	03-Jul-2010			J.Griswold		(Reviewed by: PJH) [1]
		use new TIP (template interface pointer)
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <float.h>

#include "CFactoryPlugin.h"
#include "IPluginLoadConfiguration.h"

#include "CPluginConfiguration.h"

#include "TComPointer.h"
#include "LogFile.h"
#include "UPlatform.h"
#include "CCharString.h"
#include "CCharDescriptor.h"
#include "CUnitsOfMeasure.h"
#include "CColor.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\\+---------------------------------------------------------------------*/

// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CFactoryPlugin - constructor

\\+---------------------------------------------------------------------*/
CFactoryPlugin::CFactoryPlugin
		(
		void
		)
		: VFactoryLite()
{
}


/*---------------------------------------------------------------------+\

 * ~CFactoryPlugin - destructor

\\+---------------------------------------------------------------------*/
CFactoryPlugin::~CFactoryPlugin
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

\\+---------------------------------------------------------------------*/
ISupportsArray*
		CFactoryPlugin::Make
		(
		const char*			sNameXML,
		VPluginLibraryPtr	pLib,
		VPluginFilterPtr	pFilter	// = 0
		)
{
	ISupportsArray*			pList = 0;
	CPluginConfiguration*	pConfig = 0;

	pConfig = MakeConfiguration( sNameXML, 0 );
	if ( pConfig )
	{
		if ( pFilter )
		{
			CPluginConfiguration*	pTConfig;
			pTConfig = pFilter->Filter( pConfig );
			// Note: pConfig should be cleaned up by filter
			pConfig = pTConfig;
		}
		pList = new ISupportsArray;
		VPluginConfiguration::FolderEnum tFolder = pConfig->GetFolderEnum();
		while ( tFolder.MoveNext() )
		{
			VPluginConfigurationPtr	pSubConfig;

			pSubConfig = tFolder.Value();
			if ( pSubConfig )
			{
				CCharString	sClass = pSubConfig->GetClass();
				CCharString	sGroup = pSubConfig->GetGroup();
				CCharString	sID = pSubConfig->GetID();

				pLib->SetRelativeFolder( sGroup.Pointer() );

				LOCAL_PRINT("CFactoryPlugin.Make: Creating class '%s', ID '%s'\n",
				         sClass.Pointer(), sID.Pointer());

				ISupportsPtr pSup = pLib->Create( sClass, 0 );
				if ( pSup )
				{
					TIP(IPluginLoadConfiguration)	pLoad( pSup );

					if ( pLoad )
					{
						if ( pLoad->Load( pSubConfig, pLib ) )
						{
							pList->AppendData( &pSup );
						}
					}
				}
			}
		}
		delete pConfig;
	}

	return pList;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * Make -

\+---------------------------------------------------------------------*/
CPluginConfigurationPtr
		CFactoryPlugin::MakeConfiguration
		(
		const char*				sName,
		CPluginConfigurationPtr	pConfig
		)
{
	CPluginConfigurationPtr	pNode = 0;

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
				if ( tName == "Plugins" )
				{
					pNode = Plugins( pConfig, &it );
				}
				else
				{
					if ( pConfig )
					{
						if ( PluginInclude( pConfig, &it ) )
						{
							pNode = pConfig;
						}
						else
						{
							it.Error( "PluginInclude must be nested within a Plugins XML" );
						}
					}
				}
				break;
            default:
                break;
			}
		}
	}

	return pNode;
}



/*---------------------------------------------------------------------+\

 * Configuration -

\+---------------------------------------------------------------------*/
CPluginConfigurationPtr
		CFactoryPlugin::Plugins
		(
		CPluginConfigurationPtr	pConfig,
		XMLIteratorPtr			pIt
		)
{
	CPluginConfigurationPtr	pNode = 0;

	if ( pConfig )
		pNode = pConfig;
	else
		pNode = new CPluginConfiguration;
	if ( pNode )
	{

		XMLIterator		it( pIt );
		CCharDescriptor	tName;
		CCharDescriptor	tValue;
		bool			bResult = false;

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Plugin" )
				{
					bResult = Plugin( pNode, &it );
				}
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Include" )
				{
					bResult = IncludeFile( pNode, &it );
				}
				break;
			case XMLLite::NODE_COMMENT:
				bResult = true;
				break;
			default:
				bResult = false;
				break;
			}
			if ( ! bResult )	// this was commented out
				break;
		}
	}


	return pNode;
}


/*---------------------------------------------------------------------+\

 * PluginInclude -

\+---------------------------------------------------------------------*/
bool	CFactoryPlugin::PluginInclude
		(
		CPluginConfigurationPtr	pConfig,
		XMLIteratorPtr			pIt
		)
{
	bool			bResult = false;

	CPluginConfigurationPtr	pNode = 0;

	pNode = pConfig;
	if ( pNode )
	{

		XMLIterator		it( pIt );
		CCharDescriptor	tName;
		CCharDescriptor	tValue;

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Parameters" )
				{
					bResult = Parameters( pNode, &it );
				}
				else if ( tName == "Plugin" )
				{
					bResult = Plugin( pNode, &it );
				}
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Include" )
				{
					bResult = IncludeFile( pNode, &it );
				}
				break;
			case XMLLite::NODE_COMMENT:
				bResult = true;
				break;
			default:
				break;
			}
			//if ( ! bResult )
			//	break;
		}
	}


	return bResult;
}


/*---------------------------------------------------------------------+\

 * Plugin -

\+---------------------------------------------------------------------*/
bool	CFactoryPlugin::Plugin
		(
		CPluginConfigurationPtr	pParent,
		XMLIteratorPtr			pIt
		)
{
	bool	bResult = false;
	if ( pParent )
	{

		XMLIterator		it( pIt );
		CCharDescriptor	tName;
		CCharDescriptor	tValue;
		CCharString		sID;
		CCharString		sClass;
		CCharString		sGroup;

		CPluginConfigurationPtr	pNode;

		tValue = it.AttributeValue( "ID" );
		sID = tValue;
		tValue = it.AttributeValue( "Class" );
		sClass = tValue;
		tValue = it.AttributeValue( "Group" );
		sGroup = tValue;

		if ( sGroup.Length() < 1 )
			sGroup = pParent->GetGroup();

		pNode = new CPluginConfiguration;
		if ( pNode )
		{
			pNode->SetClass( sClass );
			pNode->SetGroup( sGroup );
			pNode->SetID( sID );

			long	nAttributes = it.AttributeCount();
			if ( 0 < nAttributes )
			{
				for ( int n = 0; n < nAttributes; ++n )
				{
					tName = it.AttributeName( n );
					tValue = it.AttributeValue( n );
					pNode->AddAttribute( tName, tValue );
				}
			}


			while ( it.NextChild() )
			{
				tName = it.NodeName();
				switch ( it.NodeType() )
				{
				case XMLLite::NODE_ELEMENT_BEGIN:
					if ( tName == "Plugin" )
					{
						bResult = Plugin( pNode, &it );
					}
					else
					{
						it.Error( "Unrecognized token in Plugins" );
					}
					break;
				case XMLLite::NODE_ELEMENT:
					if ( tName == "Param" )
					{
						bResult = Param( pNode, &it );
					}
					else if ( tName == "Plugin" )
					{
						bResult = Plugin( pNode, &it );
					}
					else if ( tName == "Include" )
					{
						bResult = IncludeFile( pNode, &it );
					}
					break;
				case XMLLite::NODE_COMMENT:
					bResult = true;
					break;
				default:
					break;
				}
				//if ( ! bResult )
				//	break;
			}

			if ( bResult )
			{
				bResult = pParent->AddFolder( sID, pNode );
				if ( ! bResult )
					delete pNode;
			}
			else
			{
				delete pNode;
			}
		}
	}


	return bResult;
}



/*---------------------------------------------------------------------+\

 * Parameters -

\+---------------------------------------------------------------------*/
bool	CFactoryPlugin::Parameters
		(
		CPluginConfigurationPtr	pNode,
		XMLIteratorPtr			pIt
		)
{
	bool	bResult = false;
	if ( pNode )
	{

		XMLIterator		it( pIt );
		CCharDescriptor	tName;
		CCharDescriptor	tValue;

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT_BEGIN:
				if ( tName == "Plugin" )
				{
					bResult = Plugin( pNode, &it );
				}
				else
				{
					it.Error( "Unrecognized token in Plugins" );
				}
				break;
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Param" )
				{
					bResult = Param( pNode, &it );
				}
				else if ( tName == "Plugin" )
				{
					bResult = Plugin( pNode, &it );
				}
				else if ( tName == "Include" )
				{
					bResult = IncludeFile( pNode, &it );
				}
				break;
			case XMLLite::NODE_COMMENT:
				bResult = true;
				break;
			default:
				break;
			}
			//if ( ! bResult )
			//	break;

		}
	}


	return bResult;
}





/*---------------------------------------------------------------------+\

 * Param -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryPlugin::Param
		(
		CPluginConfigurationPtr	pConfig,
		XMLIteratorPtr		pit
		)
{
	bool	bResult = false;

	CCharDescriptor	tValue;
	CCharDescriptor	tName;

	CCharDescriptor	tID;


	char	sData[128] = { 0 };
	int		nUnits = 0;
	CVariantData::V_TYPE	eType = CVariantData::T_UNDEFINED;
	CVariantData	v;

	bResult = true;


	tID = pit->AttributeValue( "Name" );
	if ( 0 < tID.Length() )
	{

		tValue = pit->AttributeValue( "Units" );
		if ( 0 < tValue.Length() )
		{
			char	sUnits[40];
			tValue.CopyTo( sUnits, sizeof(sUnits) );
			tValue = CCharDescriptor( sUnits, tValue.Length() );
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
				||	tValue == "ENUM"
				||	tValue == "ENUMERATION" )
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
					CColor	c;
					c.SetColorLong( nValue );
					v = c;
					bResult = true;
				}
				else
				{
					CColor	c = CColor::ColorFromName( tValue );
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
				CDateTime	d;
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

		pConfig->AddParameter( tID, v );
	}



	return bResult;
}

//END_OVERRUN_WARNING






/*---------------------------------------------------------------------+\

 * IncludeFile -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CFactoryPlugin::IncludeFile
		(
		CPluginConfigurationPtr	pConfig,
		XMLIteratorPtr		pIt
		)
{
	bool				bResult = false;
	CPluginConfigurationPtr	pNode = 0;

	if ( 0 < pIt->AttributeCount() )
	{
		CCharDescriptor	tValue;

		tValue = pIt->AttributeValue( "File" );
		if ( 0 < tValue.Length() )
		{
			CCharString	sPath;
			char		sXML[128];

			tValue.CopyTo( sXML, sizeof(sXML) );


			sPath = GetRelativePath();

			CFactoryPlugin	factory;
			factory.SetRelativePath( sPath.Pointer() );
			factory.SetVariableIF(m_pVariable);

			pNode = factory.MakeConfiguration( sXML, pConfig );
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

}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
