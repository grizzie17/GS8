/*---------------------------------------------------------------------+\
|
|	VFactory.h  --  base class for XML based factories
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	15-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add new function 'ApplicationFolder' to help identify
		the default location for the GaugeXML folder.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	09-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Rework hierarchy
	21-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFactory
#define _H_VFactory
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "XMLLiteImpl.h"
#include "XMLLiteExtImpl.h"

#include "TPointer.h"
#include "UFloat.h"

#include "UDeclCommon.h"

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
typedef class VFactory*			VFactoryPtr;
typedef class VFactory&			VFactoryRef;
typedef const class VFactory&	ConstVFactoryRef;


typedef	Yogi::XMLLite::TTokenizerExt<char>	XMLParser;
typedef XMLParser*							XMLParserPtr;
typedef	Yogi::XMLLite::TTokenizerExt<char>	XMLTokenizer;
typedef	XMLTokenizer*						XMLTokenizerPtr;

typedef Yogi::XMLLite::TIteratorExt<char,XMLTokenizer>	XMLIterator;
typedef	XMLIterator*						XMLIteratorPtr;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS VFactory : public XMLParser
{
//	class lifecycle  ----------------------------------------------------
public:
					VFactory();
	virtual			~VFactory();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	//example derived function
	/*
	CGaugePtr	Make( char* sName );
	*/


protected:
//	protected types  ----------------------------------------------------

	typedef Yogi::XMLLite::VTokenizer<char>	XTokenizer;

//	protected functions  ------------------------------------------------


	// special function to eat nodes that we are not processing
	bool		EatNode( void );

	// make the xml parser/tokenizer
	bool		MakeXML( void );

	const char*	ApplicationFolder( void );

//	protected data  -----------------------------------------------------

	//XMLTokenizerPtr	m_pXML;

	static char	g_sApplicationFolder[];

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

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



#endif /* _H_VFactory */
