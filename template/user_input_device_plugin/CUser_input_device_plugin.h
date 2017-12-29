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
|	Delete this comment block
|
|	globally substitute "filename" to be the name of this file (no suffix).
|	globally substitute "dd-mmm-9999" to be today's date.
|	globally substitute "F.Lastname" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "DerivedClass" to be the name of this class.
|   globally substitute "MessageStruct" to be the name of the input device message structure
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	filename.h  --  brief description of what filename.h is for
|
|	Purpose:
|	File Custodian:		F.Lastname
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_filename
#define _H_filename
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <pthread.h>
#include <unistd.h>

#include "VPluginWithAggregateList.h"

#include "IUserInputDevice.h"
#include "IDataMessage.h"
#include "IGraphicsEvent.h"
#include "UNResult.h"

#include "NamespaceUserInputDevice.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
USING_NAMESPACE_COMMUNICATION
USING_NAMESPACE_GRAPHICS_EVENT

NAMESPACE_USER_INPUT_DEVICE_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef struct MessageStruct
{
	// ToDo: fill in message structure
} tMessageStruct;

// ToDo: Add special constants/#defines

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DerivedClass : public VPluginWithAggregateList,
						implements_ IUserInputDevice
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( DerivedClass );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IUserInputDevice
	virtual ConstCCharStringRef Name();

	virtual
	NResult	Initialize
			(
			int graphicsThreadID,	// IN:	ID of associated graphics thread
			int userInputDeviceID	// IN:	ID to assign to this device
			);



public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

	unsigned int		RxThread( void );

	static unsigned int	RxThreadGlue( void* pThis );

//	private data  -------------------------------------------------------

	int					m_graphicsThreadID;
	int					m_inputDeviceID;
	IDataMessagePtr		m_pDevice;
	IGraphicsEventPtr	m_pGraphicsEvent;
	CCharString			m_deviceName;
	pthread_t			m_pRxThread;

	// ToDo: Add additional private data for the user input device here
	//       Make sure new variables are initialized in the constructors
	//       and properly destroyed in the destructor.

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);


	//	IPluginLoadConfiguration
public:

	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);

};

NAMESPACE_USER_INPUT_DEVICE_END

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


#endif /* _H_filename */

