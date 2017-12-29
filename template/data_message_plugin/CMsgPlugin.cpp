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
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	filename.cpp  --  brief description of what filename.h is for
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

/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "filename.h"
#include "VPluginFactory.h"
#include <unistd.h>

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMUNICATION_BEGIN

// Uncomment the following #define to enable debug printing statements
//
//#define DerivedClass_DBG_PRINT

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
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
		  m_pDataStream(0)
{
}


/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - constructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		ISupportsPtr pOwner
		)
		: VPluginWithAggregateList(pOwner),
		  m_pDataStream(0)
{
}

/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - constructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		const char* sName,
		ISupportsPtr pOwner
		)
		: VPluginWithAggregateList(sName, pOwner),
		  m_pDataStream(0)
{
}


/**--------------------------------------------------------------------+\

 * <summary>~DerivedClass - destructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::~DerivedClass( void )
{
	// ToDo: Add code to destroy any added class data
	//
}

/**--------------------------------------------------------------------+\

 * <summary>~Initialize - Init function for DerivedClass</summary>

 * <remarks>Perform any initialization that needs to be done
				prior to prepare to connect to the data stream.
				This includes querying for the IDataStream interface
				to use for communicating with the user input device
				and initializing the data stream:</remarks>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::Initialize
			(
			void
			)
{


	NResult Result = NR_S_SUCCESS;

	m_pDataStream = QI_(this, IDataStream);
	if (m_pDataStream)
	{
		m_pDataStream->Initialize();
		m_pDataStream->Release();
	}
	else
	{
		LogPrint("DerivedClass.Initialize - Error, data stream interface not found\n");
	}

	// ToDo: Add additional initialization code here. Do not attempt
	//       to connect during initialization.
	//

	return( Result );
}



/**--------------------------------------------------------------------+\

 * <summary>~Connect - Connect to device (physical data stream)</summary>

 * <remarks>This function performs the initial connection to the
				communication bus.  This function will execute in the
				context of the RX thread and may contain a infinite wait
				to establish the physical connection to the communication
				bus. The IDataMessage::Connect() must execute the
				IDataStream::Connect() of the associated physical data
				stream communication bus.</remarks>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::Connect
			(
			void
			)
{
	NResult Result = NR_E_CONNECT_FAIL;

	// Connect to the device data stream.
	//
	do
	{
		if (m_pDataStream)
		{
			Result = m_pDataStream->Connect();
		}
		if (Result < 0)
		{
			sleep(1);
		}
	} while(Result < 0);

	return Result;
}


/**--------------------------------------------------------------------+\

 * <summary>Read - Reads data stream for input data to frame /summary>

 * <remarks>This function reads a message from the input device. The function uses the
			IDataStream interface to access the input device data stream.  This function
			is responsible for constructing a message and performing protocol validation
			– e.g. checksum validation.

			Returns:
			>0 : nBytes put in pMsg (size of message read)
			-1 : Failure
	</remarks>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/


NResult DerivedClass::ReadMessage( void *pMsg, int maxMsgSize )
{
	NResult msgSize = NR_E_RX_FAIL;
	// ToDo: Add local variables for reading, constucting, and validating
	//       the device message here.
	//

	if ((m_pDataStream) && (pMsg))
	{
		// ToDo: Add code here to read, construct and validate the device
		//       data messages. Use the IDataStream interface (m_pDataStream)
		//       to read data from the device.
		//
		// Example:
		//   msgSize = m_pDataStream->Read( pMsg, maxMsgSize );
		//   #ifdef DerivedClass_DBG_PRINT
		//      DbgPrint("DerivedClass.ReadMessage - RX %d bytes\n", msgSize);
		//   #endif // ifdef DerivedClass_DBG_PRINT
	}
	else
	{
		LogPrint("DerivedClass.ReadMessage - NULL interface (0x%p) or message pointer (0x%p)\n",
		         m_pDataStream, pMsg);
	}

	return msgSize;
}




/**--------------------------------------------------------------------+\

 * <summary>WriteMessage - Write message</summary>

 * <remarks>This function writes a message to the connected device.
				The function uses the IDataStream interface to access the
				input device data stream.</remarks>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::WriteMessage
			(
			void *pMsg,
			int nBytes
			)
{
	NResult nBytesWritten =  NR_E_TX_FAIL;

	if ((m_pDataStream) && (pMsg))
	{
		// ToDo: Add message protocol code here - e.g. checksum
		//

		nBytesWritten = m_pDataStream->Write( pMsg, nBytes );
#ifdef DerivedClass_DBG_PRINT
		DbgPrint("DerivedClass.WriteMessage - TX %d bytes\n", nBytesWritten);
#endif // ifdef DerivedClass_DBG_PRINT
	}
	else
	{
		LogPrint("DerivedClass.WriteMessage - NULL interface (0x%p) or message pointer (0x%p)\n",
		         m_pDataStream, pMsg);
	}

	return nBytesWritten;
}


/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - COM override for interface query</summary>

 * <remarks/>

 * (author)P.Hogan  --  28-Jun-2010

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

	if ( rIID == IXID_IDataMessage )
	{
		p = INTERFACE_THIS( IDataMessagePtr );
	}

	return p;
}

/*--------------------------------------------------------------------+\

 * <summary>Load - XML class data loader</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
bool	DerivedClass::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = true;

	// ToDo: Add code to load XML data for this plugin here
	//

    return bResult;
}


NAMESPACE_COMMUNICATION_END



