/*==================================================================*//**
*
*	@file	CFactoryConfiguration.h
*	@brief	Make a configuration object
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		React to new base configuration class
	29-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Support including another configuration file into the
		contents of the current configuration file
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	04-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Cleaned out older irrXML code
	02-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to use the new XMLLite classes
	18-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryConfiguration
#define _H_CFactoryConfiguration
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryLite.h"

#include "CConfiguration.h"
#include "CVariables.h"
#include "TPointer.h"
#include "TArray.h"

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

typedef class CFactoryConfiguration*		CFactoryConfigurationPtr;
typedef class CFactoryConfiguration&		CFactoryConfigurationRef;
typedef const class CFactoryConfiguration&	ConstCFactoryConfigurationRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryConfiguration : public VFactoryLite,
							public virtual VVariable
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryConfiguration();
	virtual			~CFactoryConfiguration();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual VConfigurationPtr	Make
								(
								const char*			sName,
								VConfigurationPtr	pConfig = 0
								);



protected:
//	protected types  ----------------------------------------------------


//	protected functions  ------------------------------------------------

	VConfigurationPtr	Configuration( VConfigurationPtr pConfig );
	bool				Item
						(
						VConfigurationPtr	pConfig,
						XMLIteratorPtr		pIt
						);

	bool				IncludeFile
						(
						VConfigurationPtr	pConfig,
						XMLIteratorPtr		pIt
						);



//	protected data  -----------------------------------------------------

	VConfigurationPtr	m_pConfig;



private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
public:

	virtual
	Yogi::Core::CCharString
			ResolveVariable
			(
			Yogi::Core::ConstCCharDescriptorRef	r
			) const;


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


#endif /* _H_CFactoryConfiguration */
