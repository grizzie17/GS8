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
|	DerivedClass.cpp  --  brief description of what DerivedClass.cpp is for
|
|	Purpose:
|	File Custodian:		F.Lastname
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
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
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "DerivedClass.h"

#include "UNResult.h"
#include "VPluginFactory.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

NAMESPACE_USER_INPUT_DEVICE_BEGIN

// Uncomment the following #define to enable debug printing statements
//
//#define DerivedClass_DBG_PRINT

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( DerivedClass );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - constructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		void
		)
		: VPluginWithAggregateList(),
		m_graphicsThreadID(-1),
		m_inputDeviceID(-1),
		m_pDevice(0),
		m_pGraphicsEvent(0),
		m_deviceName(),
		m_pRxThread(0)
{
}

DerivedClass::DerivedClass
		(
		ISupportsPtr	pOwner
		)
		: VPluginWithAggregateList( pOwner ),
		m_graphicsThreadID(-1),
		m_inputDeviceID(-1),
		m_pDevice(0),
		m_pGraphicsEvent(0),
		m_deviceName(),
		m_pRxThread(0)
{
}

DerivedClass::DerivedClass
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginWithAggregateList( sName, pOwner ),
		m_graphicsThreadID(-1),
		m_inputDeviceID(-1),
		m_pDevice(0),
		m_pGraphicsEvent(0),
		m_deviceName(),
		m_pRxThread(0)
{
}

/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - destructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::~DerivedClass
		(
		void
		)
{
	// ToDo: Add code to destroy any added class data here.

	if ( m_pRxThread )
	{
		void*	pVoid;
		pthread_join( m_pRxThread, &pVoid );
		m_pRxThread = 0;
	}
}

/*=====================================================================+\
||	 interface implementation functions									|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IUserInputDevice
\+---------------------------------------------------------------------*/


/**--------------------------------------------------------------------+\

 * <summary>Name - Return the device name read from XML</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
ConstCCharStringRef
		DerivedClass::Name
		(
		void
		)
{
	return m_deviceName;
}


/**--------------------------------------------------------------------+\

 * <summary>Initialize - Initialize the input device, including starting
                         necessary threads</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult	DerivedClass::Initialize
		(
		int graphicsThreadID,	// IN:	ID of associated graphics thread
		int userInputDeviceID	// IN:	ID to assign to this device
		)
{
	NResult rtnResult = NR_S_SUCCESS;

	m_graphicsThreadID = graphicsThreadID;
	m_inputDeviceID = userInputDeviceID;

	// Get the IDataMessage interface
	//
	m_pDevice = QI_(this, IDataMessage);

	if (m_pDevice)
	{
		m_pDevice->Initialize();

		// This is another interface to this aggregate list of COM objects, so release
		// it now.
		m_pDevice->Release();
	}
	else
	{
		LogPrint("DerivedClass.Initialize - Error, IDataMessage interface not found\n");
		rtnResult = NR_E_ERROR;
	}

	// Get the Graphics Event interface
	//
	m_pGraphicsEvent = QI_(this, IGraphicsEvent);
	if (m_pGraphicsEvent)
	{
		m_pGraphicsEvent->Initialize( m_graphicsThreadID );

		// This is another interface pointer to this aggregate list of COM objects,
		// so release it now.
		m_pGraphicsEvent->Release();
	}
	else
	{
		LogPrint("DerivedClass.Initialize - Error, IGraphicsEvent interface not found\n");
		rtnResult = NR_E_ERROR;
	}

	// ToDo: Add any additional initialization code here.
	//

	if ( rtnResult == 0 )
	{
		// Start RX thread
		//
        int status = pthread_create( &m_pRxThread, NULL, (void* (*)(void*))RxThreadGlue, (void*)this );
        if (status != 0)
        {
            LogPrint("DerivedClass (%d): Could not create RX thread for input device (%d)\n", m_graphicsThreadID, m_inputDeviceID);
        }

		// ToDo: Add code to start TX thread as necessary
		//
	}

	return rtnResult;
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>RxThreadGlue - User input device RX thread</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
//static
unsigned int
		DerivedClass::RxThreadGlue
		(
		void*	pVoid
		)
{
	if ( pVoid )
	{
		DerivedClass*	pThis = (DerivedClass*)pVoid;

		return pThis->RxThread();
	}
	else
	{
		return NR_E_NOTHREAD;
	}
}

/**--------------------------------------------------------------------+\

 * <summary>RxThread - User input device RX thread</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
unsigned int
		DerivedClass::RxThread
		(
		void
		)
{
	NResult					nr = NR_E_ERROR;
	tMessageStruct			msg;
	tUserInputDeviceStatus	deviceStatus = DEVICE_DISCONNECTED;
	IGraphicsEventPtr		pEvent = m_pGraphicsEvent;
	IDataMessagePtr			pDevice = m_pDevice;

	// ToDo: Add other variable needed to process input device messages

#ifdef DerivedClass_DBG_PRINT
	DbgPrint("RxThread: connecting to graphics engine\n");
#endif // ifdef DerivedClass_DBG_PRINT

	do
	{
		nr = pEvent->Connect();
		if ( nr < 0 )
		{
			sleep(1);
		}
	} while( nr < 0 );
	pEvent->SendUserInputDeviceStatusEvent( deviceStatus, m_inputDeviceID );

#ifdef DerivedClass_DBG_PRINT
	DbgPrint("RxThread: connecting to device\n");
#endif // ifdef DerivedClass_DBG_PRINT

	nr = NR_E_ERROR;
	do
	{
		nr = pDevice->Connect();
		if ( nr < 0 )
		{
			sleep( 1 );
		}
	} while( nr < 0 );

	deviceStatus = DEVICE_CONNECTED;
	pEvent->SendUserInputDeviceStatusEvent( deviceStatus, m_inputDeviceID );

#ifdef DerivedClass_DBG_PRINT
	DbgPrint("RxThread: connect complete\n");
#endif // ifdef DerivedClass_DBG_PRINT

	while ( 1 )
	{
		nr = pDevice->ReadMessage( &msg, sizeof(msg) );
		if ( nr > 0 )
		{
//#ifdef DerivedClass_DBG_PRINT
//			DbgPrint("RxThread: read %d\n", (int)nr);
//#endif // ifdef DerivedClass_DBG_PRINT

			// ToDo: Add code here to process the message (including filters,
			//       and coordinate conversions).
			//

			// ToDo: Add code here to generate graphics event(s) for the received
			//       device message
			//
			// Example:
			//   if (pEvent->SendMouseEvent(MOUSE_MOVE, (int)x, (int)y) < 0)
			//   {
			//	    LogPrint("Mouse Move: dropped (%d,%d)\n", xPos, yPos);
			//   }

			// ToDo: Update device status as necessary
			//
			// Example:
			//   if ( deviceStatus != DEVICE_CONNECTED )
			//   {
//#ifdef DerivedClass_DBG_PRINT
			//	    DbgPrint("RxThread: update device status (connected)\n")
//#endif // ifdef DerivedClass_DBG_PRINT
			//	    deviceStatus = DEVICE_CONNECTED;
			//	    pEvent->SendUserInputDeviceStatusEvent( deviceStatus, pUserInput->m_inputDeviceID );
			//   }
		}
		else
		{
			LogPrint("RxThread: read message error %d\n", (int)nr);
			deviceStatus = DEVICE_COMM_ERROR;
			pEvent->SendUserInputDeviceStatusEvent( deviceStatus, m_inputDeviceID );
		}
	}

	return NR_S_SUCCESS;
}


/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - COM overload for interface query</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
void*	DerivedClass::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	p = VPluginWithAggregateList::FindInternalInterface( rIID );
	if ( p )
	{
		return p;
	}

	if ( rIID == IXID_IUserInputDevice )
	{
		p = INTERFACE_THIS(IUserInputDevicePtr);
	}

	return p;
}


/**--------------------------------------------------------------------+\

 * <summary>Load - Load parameters from XML</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
bool	DerivedClass::Load
		(
		VPluginConfigurationPtr pConfig,
		VPluginLibraryPtr pLib
		)
{
	bool bSuccess = VPluginWithAggregateList::Load( pConfig, pLib );

	m_deviceName = pConfig->GetID();

	// ToDo: Add code to load any additional user input device parameters
	//       from XML here
	//

	return bSuccess;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/


NAMESPACE_USER_INPUT_DEVICE_END

