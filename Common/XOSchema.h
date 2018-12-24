/*---------------------------------------------------------------------+\
|
|	XOSchema.h  --  Make a XOParse object based on schema file
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
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_XOSchema
#define _H_XOSchema
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryLite.h"

#include "XOParse.h"


#include "VPluginLibrary.h"
#include "VPluginFilter.h"
#include "TPointer.h"
#include "TArray.h"
#include "ISupports.h"

#include "UDeclSpec.h"


namespace Yogi { namespace Common {

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/


typedef	TArray<ISupportsPtr>	ISupportsArray;


typedef class XOSchema*			XOSchemaPtr;
typedef class XOSchema&			XOSchemaRef;
typedef const class XOSchema&	ConstXOSchemaRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS XOSchema : public VFactoryLite
{
//	class lifecycle  ----------------------------------------------------
public:
					XOSchema();
	virtual			~XOSchema();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	XOParsePtr
			Make
			(
			const char*			sNameXML,
			VPluginLibraryPtr	pLib,
			VPluginFilterPtr	pFilter = 0
			);


protected:
//	protected types  ----------------------------------------------------


//	protected functions  ------------------------------------------------


	XOParsePtr
			Root
			(
			XMLIteratorPtr		pIt
			);


	bool	XmlObjects
			(
			XMLIteratorPtr		pIt
			);

	bool	RootDef
			(
			XMLIteratorPtr		pIt
			);




	bool	TypeDefs
			(
			XMLIteratorPtr		pIt
			);

	bool	TypeDef
			(
			XMLIteratorPtr		pIt
			);




	bool	AttributeDefs
			(
			XMLIteratorPtr		pIt
			);

	bool	AttributeDef
			(
			XMLIteratorPtr		pIt
			);

	bool	Attribute
			(
			XMLIteratorPtr		pIt
			);





	bool	PropertyDefs
			(
			XMLIteratorPtr		pIt
			);

	bool	PropertyDef
			(
			XMLIteratorPtr		pIt
			);

	bool	Property
			(
			XMLIteratorPtr		pIt
			);





	bool	NPropertyDefs
			(
			XMLIteratorPtr		pIt
			);

	bool	NPropertyDef
			(
			XMLIteratorPtr		pIt
			);

	bool	NProperty
			(
			XMLIteratorPtr		pIt
			);





	bool	SetDefs
			(
			XMLIteratorPtr		pIt
			);

	bool	SetDef
			(
			XMLIteratorPtr		pIt
			);

	bool	Set
			(
			XMLIteratorPtr		pIt
			);






	bool	Include
			(
			XMLIteratorPtr		pIt
			);



//	protected data  -----------------------------------------------------

	//TDictionaryIndexed< IXID, CXOTypes



private:
//	private types  ------------------------------------------------------

	typedef VFactoryLite	inherited;

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


#endif /* _H_XOSchema */
