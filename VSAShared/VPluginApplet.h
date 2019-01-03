/*---------------------------------------------------------------------+\
|
|	VPluginApplet.h  --  Base class for plugin applets
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
	21-Dec-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginApplet
#define _H_VPluginApplet
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregateList.h"

#include "IApplet.h"
#include "VPluginLibrary.h"
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
typedef class VPluginApplet*		VPluginAppletPtr;
typedef class VPluginApplet&		VPluginAppletRef;
typedef const class VPluginApplet&	ConstVPluginAppletRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPluginApplet : public Yogi::Common::VPluginWithAggregateList,
						implements_ IApplet
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VPluginApplet );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IApplet
	virtual
	Yogi::Core::NResult	
			OnLoad
			(
			IHuskPtr	pHusk
			);

	virtual
	Yogi::Core::NResult	
			OnUnload
			(
			);


	virtual
	Yogi::Core::NResult	
			OnStart
			(
			);

	virtual
	Yogi::Core::NResult	
			OnExit
			(
			);

	virtual
	Yogi::Core::NResult	
			OnPause
			(
			);

	virtual
	Yogi::Core::NResult	
			OnResume
			(
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

	IHuskPtr					m_pHusk;


private:
//	private types  ------------------------------------------------------

	typedef	Yogi::Common::VPluginWithAggregateList	inherited;

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
			Yogi::Common::VPluginLibraryPtr		pLib
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



#endif /* _H_VPluginApplet */
