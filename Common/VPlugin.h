/*---------------------------------------------------------------------+\
|
|	VPlugin.h  --  brief description of what VPlugin.h is for
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
	29-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add new "ID" function.
	10-Apr-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPlugin
#define _H_VPlugin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VSupports.h"
#include "IPlugin.h"
#include "IPluginLoadConfiguration.h"

#include "ISupportsLocal.h"

#include "UDeclCommon.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VPlugin*			VPluginPtr;
typedef class VPlugin&			VPluginRef;
typedef const class VPlugin&	ConstVPluginRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPlugin 
				: public VSupports
				, implements_ IPlugin
				, implements_ IPluginLoadConfiguration
				, implements_ ISupportsLocal
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VPlugin );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IPlugin
	virtual
	const char*
			ClassName
			(
			void
			) const throw();

	virtual
	const char*
			ID
			(
			void
			) const throw();


	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);

	//	ISupportsLocal
	virtual
	void*	QueryInterfaceLocal
			(
			ConstIXIDRef			rIID,
			Yogi::Core::NResultPtr	pResult = 0
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString		m_sID;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);


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



#endif /* _H_VPlugin */
