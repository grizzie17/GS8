/*---------------------------------------------------------------------+\
|
|	VFactoryLite.h  --  Root class for all XML based factories
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the psuedo-interface VVariable
	09-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change hierarchy
	02-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision - copy of previous VFactory
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFactoryLite
#define _H_VFactoryLite
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactory.h"

#include "CCharString.h"
#include "CVariables.h"
#include "IExternalXML.h"


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {

#define XML_LITE		1
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VFactoryLite*			VFactoryLitePtr;
typedef class VFactoryLite&			VFactoryLiteRef;
typedef const class VFactoryLite&	ConstVFactoryLiteRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VFactoryLite : public VFactory
{
//	class lifecycle  ----------------------------------------------------
public:
				VFactoryLite();
	virtual		~VFactoryLite();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


	void		SetRelativePath( const char* s );
	Yogi::Core::CCharStringRef
				GetRelativePath( void );

	void		SetVariableIF( VVariablePtr p );
	void		SetExternalXMLIF( ISupportsPtr p );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	//	This function assumes that the input file-path is
	//	relative to the GaugesXML folder.
	bool		OpenFile( const char*	sName );


	Yogi::Core::CCharString	BuildFilePath( const char* sName );


//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString	m_sRelativePath;
	VVariablePtr			m_pVariable;
	IExternalXMLPtr			m_pIExternalXML;

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



#endif /* _H_VFactoryLite */
