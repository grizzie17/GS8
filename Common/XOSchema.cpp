/*---------------------------------------------------------------------+\
|
|	XOSchema.cpp  --  Make XOParse object from XML
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
	10-Oct-2010			J.Griswold		(Reviewed by: xxxx)
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

#include "XOSchema.h"
#include "IPluginLoadConfiguration.h"

#include "CPluginConfiguration.h"

#include "TComPointer.h"
#include "UPlatform.h"
#include "CCharString.h"
#include "CUnitsOfMeasure.h"

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

//#define FACTORY_PLUGIN_DBG_PRINT

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
/**--------------------------------------------------------------------+\

 * <summary>XOSchema - constructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
XOSchema::XOSchema
		(
		void
		)
		: inherited()
{
}


/**--------------------------------------------------------------------+\

 * <summary>~XOSchema - destructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
XOSchema::~XOSchema
		(
		void
		)
{
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/**--------------------------------------------------------------------+\

 * <summary>Make - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
XOParsePtr
		XOSchema::Make
		(
		const char*			sNameXML,
		VPluginLibraryPtr	pLib,
		VPluginFilterPtr	pFilter	// = 0
		)
{
	XOParsePtr				pParse = 0;
	ISupportsArray*			pList = 0;
	CPluginConfiguration*	pConfig = 0;

	//pConfig = MakeConfiguration( sNameXML, 0 );
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

#ifdef FACTORY_PLUGIN_DBG_PRINT
				DbgPrint("XOSchema.Make: Creating class '%s', ID '%s'\n",
				         sClass.Pointer(), sID.Pointer());
#endif
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

	return pParse;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/**--------------------------------------------------------------------+\

 * <summary>Make - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
#if 0
CPluginConfigurationPtr
		XOSchema::MakeXOParse
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
				if ( tName == "XmlObjects" )
				{
					pNode = XmlObjects( pConfig, &it );
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
#endif // 0


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
XOParsePtr
		XOSchema::Root
		(
		XMLIteratorPtr pIt
		)
{
	XOParsePtr	pNode = 0;

	CCharDescriptor	tName;
	XMLIterator		it( this );

	while ( it.NextChild() )
	{
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			tName = it.NodeName();
			if ( tName == "XmlObjects" )
			{
				XmlObjects( &it );
			}
			break;
        default:
            break;
		}
	}

	return pNode;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::XmlObjects
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
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "TypeDefs" )
				bResult = TypeDefs( &it );
			else if ( tName == "AttributeDefs" )
				bResult = AttributeDefs( &it );
			else if ( tName == "PropertyDefs" )
				bResult = PropertyDefs( &it );
			else if ( tName == "NPropertyDefs" )
				bResult = NPropertyDefs( &it );
			else if ( tName == "SetDefs" )
				bResult = SetDefs( &it );
			else
				it.Error( "Unrecognized element within XmlObjects" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Include" )
				bResult = Include( &it );
			else
				it.Error( "Unrecognized element within XmlObjects" );
			break;
		default:
			break;
		}
	}

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::TypeDefs
		(
		XMLIteratorPtr pIt
		)
{
	const char		kUnrecognizedElement[] = "Unrecognized element within TypeDefs";
	bool			bResult = false;
	CCharDescriptor	tName;
	XMLIterator		it( pIt );

	while ( it.NextChild() )
	{
		tName = it.NodeName();
		switch ( it.NodeType() )
		{
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "TypeDef" )
				bResult = TypeDef( &it );
			else
				it.Error( kUnrecognizedElement );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Include" )
				bResult = Include( &it );
			else
				it.Error( "Unrecognized element within TypeDefs" );
			break;
		default:
			break;
		}
	}

	return bResult;
}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::TypeDef
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sFactory;
	CCharString		sDescr;

	do	// sequence
	{
		tValue = it.AttributeValue( "Name" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Name attribute required for TypeDef" );
			break;
		}

		sName = tValue;

		tValue = it.AttributeValue( "Factory" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Factory attribute required for TypeDef" );
			break;
		}

		sFactory = tValue;

		tValue = it.AttributeValue( "Descr" );
		if ( 0 < tValue.Length() )
			sDescr = tValue;


		bResult = true;

		// XOParseTypeDef
		//	populate

	} sequence;

	return bResult;
}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::AttributeDefs
		(
		XMLIteratorPtr pIt
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
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "AttributeDef" )
				bResult = AttributeDef( &it );
			else
				it.Error( "Unrecognized element within AttributeDefs" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Include" )
				bResult = Include( &it );
			else
				it.Error( "Unrecognized element within AttributeDefs" );
			break;
		default:
			break;
		}
	}

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::AttributeDef
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sFactory;
	CCharString		sDefault;
	CCharString		sDescr;

	do	// sequence
	{
		tValue = it.AttributeValue( "Name" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Name attribute required for AttributeDef" );
			break;
		}

		sName = tValue;

		tValue = it.AttributeValue( "Type" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Type attribute required for AttributeDef" );
			break;
		}

		//tValue = it.AttributeValue( "Factory" );
		//if ( tValue.Length() < 1 )
		//{
		//	it.Error( "Factory attribute required for AttributeDef" );
		//	break;
		//}

		//sFactory = tValue;

		tValue = it.AttributeValue( "Default" );
		if ( 0 < tValue.Length() )
			sDefault = tValue;

		tValue = it.AttributeValue( "Descr" );
		if ( 0 < tValue.Length() )
			sDescr = tValue;


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::Attribute
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sRequired;

	do	// sequence
	{
		tValue = it.AttributeValue( "Ref" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Name attribute required for Attribute" );
			break;
		}

		sName = tValue;



		tValue = it.AttributeValue( "Required" );
		if ( 0 < tValue.Length() )
			sRequired = tValue;


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::PropertyDefs
		(
		XMLIteratorPtr pIt
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
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "PropertyDef" )
				bResult = PropertyDef( &it );
			else
				it.Error( "Unrecognized element within PropertyDefs" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Include" )
				bResult = Include( &it );
			else
				it.Error( "Unrecognized element within PropertyDefs" );
			break;
		default:
			break;
		}
	}

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::PropertyDef
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sType;
	CCharString		sFactory;
	CCharString		sDefault;
	CCharString		sDescr;

	do	// sequence
	{
		tValue = it.AttributeValue( "Name" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Name attribute required for PropertyDef" );
			break;
		}

		sName = tValue;

		tValue = it.AttributeValue( "Type" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Type attribute required for PropertyDef" );
			break;
		}

		sType = tValue;


		tValue = it.AttributeValue( "Factory" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Factory attribute required for PropertyDef" );
			break;
		}

		sFactory = tValue;

		tValue = it.AttributeValue( "Default" );
		if ( 0 < tValue.Length() )
			sDefault = tValue;

		tValue = it.AttributeValue( "Descr" );
		if ( 0 < tValue.Length() )
			sDescr = tValue;


		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Attribute" )
					bResult = Attribute( &it );
				else if ( tName == "Include" )
					bResult = Include( &it );
				else
					it.Error( "Unrecognized element within PropertyDef" );
				break;
			default:
				break;
			}
		}


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::Property
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sRequired;
	int				nMaxOccurs;
	int				nMinOccurs;

	do	// sequence
	{
		tValue = it.AttributeValue( "Ref" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Ref attribute required for Property" );
			break;
		}

		sName = tValue;



		tValue = it.AttributeValue( "Required" );
		if ( 0 < tValue.Length() )
			sRequired = tValue;

		nMaxOccurs = it.AttributeValueAsInt( "MaxOccurs" );

		nMinOccurs = it.AttributeValueAsInt( "MinOccurs" );


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::NPropertyDefs
		(
		XMLIteratorPtr pIt
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
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "NPropertyDef" )
				bResult = NPropertyDef( &it );
			else
				it.Error( "Unrecognized element within NPropertyDefs" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Include" )
				bResult = Include( &it );
			else
				it.Error( "Unrecognized element within NPropertyDefs" );
			break;
		default:
			break;
		}
	}

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::NPropertyDef
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sType;
	CCharString		sFactory;
	CCharString		sDefault;
	CCharString		sDescr;

	do	// sequence
	{
		tValue = it.AttributeValue( "Name" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Name attribute required for NPropertyDef" );
			break;
		}

		sName = tValue;


		tValue = it.AttributeValue( "Factory" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Factory attribute required for NPropertyDef" );
			break;
		}

		sFactory = tValue;

		tValue = it.AttributeValue( "Descr" );
		if ( 0 < tValue.Length() )
			sDescr = tValue;


		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Attribute" )
					bResult = Attribute( &it );
				else if ( tName == "Include" )
					bResult = Include( &it );
				else
					it.Error( "Unrecognized element within NPropertyDef" );
				break;
			default:
				break;
			}
		}


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::NProperty
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sRequired;
	int				nMaxOccurs;
	int				nMinOccurs;

	do	// sequence
	{
		tValue = it.AttributeValue( "Ref" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Ref attribute required for NProperty" );
			break;
		}

		sName = tValue;



		tValue = it.AttributeValue( "Required" );
		if ( 0 < tValue.Length() )
			sRequired = tValue;

		nMaxOccurs = it.AttributeValueAsInt( "MaxOccurs" );

		nMinOccurs = it.AttributeValueAsInt( "MinOccurs" );


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}




/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::SetDefs
		(
		XMLIteratorPtr pIt
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
		case XMLLite::NODE_ELEMENT_BEGIN:
			if ( tName == "SetDef" )
				bResult = SetDef( &it );
			else
				it.Error( "Unrecognized element within SetDefs" );
			break;
		case XMLLite::NODE_ELEMENT:
			if ( tName == "Include" )
				bResult = Include( &it );
			else
				it.Error( "Unrecognized element within SetDefs" );
			break;
		default:
			break;
		}
	}

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::SetDef
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sFactory;
	CCharString		sDescr;
	CCharString		sRoot;
	bool			bRoot = false;

	do	// sequence
	{

		tValue = it.AttributeValue( "Name" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Name attribute required for SetDef" );
			break;
		}
		sName = tValue;


		tValue = it.AttributeValue( "Factory" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Factory attribute required for SetDef" );
			break;
		}
		sFactory = tValue;


		tValue = it.AttributeValue( "Descr" );
		if ( 0 < tValue.Length() )
			sDescr = tValue;


		tValue = it.AttributeValue( "Root" );
		if ( 0 < tValue.Length() )
		{
			char	c = tolower(*tValue.Pointer());
			if ( ::strchr( "ty1", c ) )
				bRoot = true;
		}

		while ( it.NextChild() )
		{
			tName = it.NodeName();
			switch ( it.NodeType() )
			{
			case XMLLite::NODE_ELEMENT:
				if ( tName == "Attribute" )
					bResult = Attribute( &it );
				else if ( tName == "Property" )
					bResult = Property( &it );
				else if ( tName == "NProperty" )
					bResult = NProperty( &it );
				else if ( tName == "Set" )
					bResult = Set( &it );
				else if ( tName == "Include" )
					bResult = Include( &it );
				else
					it.Error( "Unrecognized element within SetDef" );
				break;
			default:
				break;
			}
		}


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
bool	XOSchema::Set
		(
		XMLIteratorPtr pIt
		)
{
	bool			bResult = false;
	XMLIterator		it( pIt );
	CCharDescriptor	tName;
	CCharDescriptor	tValue;

	CCharString		sName;
	CCharString		sRequired;
	int				nMaxOccurs;
	int				nMinOccurs;

	do	// sequence
	{
		tValue = it.AttributeValue( "Ref" );
		if ( tValue.Length() < 1 )
		{
			it.Error( "Ref attribute required for Set" );
			break;
		}

		sName = tValue;



		tValue = it.AttributeValue( "Required" );
		if ( 0 < tValue.Length() )
			sRequired = tValue;

		nMaxOccurs = it.AttributeValueAsInt( "MaxOccurs" );

		nMinOccurs = it.AttributeValueAsInt( "MinOccurs" );


		bResult = true;

		// XOParseAttributeDef
		//	populate

	} sequence;

	return bResult;
}







/**--------------------------------------------------------------------+\

 * <summary>IncludeFile - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	XOSchema::Include
		(
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

			//::strcpy_s( sPath, sizeof(sPath), "plugins/" );
			//tValue.ConcatenateTo( sPath, sizeof(sPath) );

			sPath = GetRelativePath();

			XOSchema	factory;
			//factory.SetRelativePath( sPath );

			//pNode = factory.MakeConfiguration( sXML, pConfig );
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

NAMESPACE_COMMON_END

/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/

