/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CmdM1200.h  --  brief description of what CmdM1200.h is for
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
	17-May-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdM1200
#define _H_CmdM1200
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "IVideoFeedCntl.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CApplicationGaugeVDDS.h"

#include "NamespaceVideoSource.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
USING_NAMESPACE_VIDEOSOURCE

NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CmdM1200*		CmdM1200Ptr;
typedef class CmdM1200&		CmdM1200Ref;
typedef const class CmdM1200&	ConstCmdM1200Ref;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdM1200 : public VPluginCommand,
				public virtual IVideoFeedCntl
{
//	class lifecycle  ----------------------------------------------------
public:
					CmdM1200();
					CmdM1200( ISupportsPtr pOwner );
					CmdM1200( const char* sName, ISupportsPtr pOwner );
protected:
	virtual			~CmdM1200();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	DECLARE_ISUPPORTS;

	//	IVideoFeedCntl
    virtual NResult ConnectVideoFeed( int videoFeedID, int videoSourceID, tVideoDisplayWindow& videoFeedDisplay );
    virtual NResult DisconnectVideoFeed( int videoFeedID );

    virtual void ProcessVideoFeedCntlEvent( tVideoEvent* pEvent );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	IVideoFeedCntlPtr		m_pVideoFeedCntl;	// pointer to real guy
	VDictionaryPtr			m_pDictionary;
	int						m_nVideoFeedID;
	int						m_nVideoSourceID;
	CCharString				m_sVideoSourceName;
	tVideoDisplayWindow		m_tVideoDisplay;
	VDictionary::Selector	m_selMouseX;
	VDictionary::Selector	m_selMouseY;
	VDictionary::Selector	m_selMouseEvent;

	THashTable<CCharString, CVariantData>	m_aList;
	THashTable<VDictionary::Selector, long>	m_aCommands;


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


public:
	//	ICommandPlugin
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VCommandSetupPtr		pCommandSetup
			);

	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector	selCommand,
			ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
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
NAMESPACE_GADGET_END






#endif /* _H_CmdM1200 */

