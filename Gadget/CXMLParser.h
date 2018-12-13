/*---------------------------------------------------------------------+\
|
|	CXMLParser.h  --  FILE RETIRED
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
	15-Sep-2009			J.Griswold		(Reviewed by: xxxx)
		THIS FILE IS RETIRED
	21-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CXMLParser
#define _H_CXMLParser
#pragma once


#if 0	// FILE RETIRED



/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "TPointer.h"
#include "irrXML.h"
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

using namespace irr;
using namespace io;

typedef class CXMLParser*		CXMLParserPtr;
typedef class CXMLParser&		CXMLParserRef;
typedef const class CXMLParser&	ConstCXMLParserRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CXMLParser
{
//	class lifecycle  ----------------------------------------------------
public:
					CXMLParser();
	virtual			~CXMLParser();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


	bool		OpenFile( char* sFile );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TPointer<IrrXMLReader>		m_pXML;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

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



#endif	// FILE RETIRED

#endif /* _H_CXMLParser */
