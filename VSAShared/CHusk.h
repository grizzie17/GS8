/*---------------------------------------------------------------------+\
|
|	CHusk.h  --  container for manager objects
|
|	Purpose:

		A CHusk provides access to a set of manager objects and services.
		It also routes events and holds the current desk manager.
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
	01-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CHusk
#define _H_CHusk
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregateList.h"
#include "IHusk.h"
#include "IMouseTransform.h"
#include "IServiceManager.h"
#include "CFactoryConfiguration.h"
#include "THash.h"
#include "VObject.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class CHusk : public VPluginWithAggregateList,
					implements_ IHusk
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CHusk );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IHusk
	virtual
	Yogi::Core::NResult	AddService
			(
			Yogi::Common::ISupportsPtr	Ip,
			const char*		sName
			);

	virtual
	Yogi::Core::NResult	AddStorage
			(
			Yogi::Common::ISupportsPtr	pI,
			const char*		sName
			);


	virtual
	Yogi::Core::NResult	AddWidget
			(
			Yogi::Common::ISupportsPtr	pI,
			const char*		sName
			);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	bool	SpecifyConfiguration
			(
			const char*	sPath
			);

	virtual
	bool	Start
			(
			void
			);

	virtual
	bool	Stop
			(
			void
			);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	bool	m_bRunning;

	VConfigurationPtr	m_pConfiguration;

	//CLoaderPtr		m_pLoader;
	//CEventsPtr		m_pEvents;
	//CGesturesPtr		m_pGuestures;

	IServiceManagerPtr	m_pServiceManager;
	//CAppletManagerPtr	m_pApplets;
	//CDeskManagerPtr	m_pDesks;
	//CWidgetManagerPtr	m_pWidgets;

	//CLayoutServicePtr	m_pLayout;
	//CNotificationServicePtr	m_pNotification;

	Yogi::Common::THashTable<Yogi::Core::CCharString, ISupportsPtr>	m_tCOMObjects;
	Yogi::Common::THashTable<Yogi::Core::CCharString, VObjectPtr>		m_tObjects;




private:
//	private types -------------------------------------------------------

	typedef VPluginWithAggregateList	inherited;

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
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/
}}

#endif /* _H_CHusk */
