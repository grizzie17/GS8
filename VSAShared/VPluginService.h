/*---------------------------------------------------------------------+\
|
|	VPluginService.h  --  Base class for plugin commands
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
	12-Jul-2010			S.Snider		(Reviewed by: R.Hosea)
		Added page constants member.
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Allow commands to participate in Aggregation
	16-May-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginService
#define _H_VPluginService
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregateList.h"

#include "IService.h"
#include "CMutex.h"


namespace Yogi { namespace Gadget {
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
typedef class VPluginService*		VPluginServicePtr;
typedef class VPluginService&		VPluginServiceRef;
typedef const class VPluginService&	ConstVPluginServiceRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPluginService : public Yogi::Common::VPluginWithAggregateList,
						implements_ IService
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VPluginService );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IService
	virtual
	Yogi::Core::NResult	Start
			(
			void
			);

	virtual
	Yogi::Core::NResult	Stop
			(
			void
			);

	virtual
	bool	IsRunning
			(
			void
			);

	virtual
	Yogi::Core::ConstCCharStringRef
			GetID
			(
			void
			);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString		m_sID;
	bool						m_bRunning;
	Yogi::Core::CMutex			m_oMutex;


private:
//	private types  ------------------------------------------------------

	typedef	VPluginWithAggregateList	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
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



#endif /* _H_VPluginService */
