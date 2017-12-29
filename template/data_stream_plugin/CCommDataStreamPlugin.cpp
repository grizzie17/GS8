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

	dd-mmm-9999			F.Lastname			(Reviewed by: xxxx)
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
		: VPluginWithAggregateList()
{
	// ToDo: Add initialization of added class data
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
		: VPluginWithAggregateList(pOwner)
{
	// ToDo: Add initialization of added class data
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
		: VPluginWithAggregateList(sName, pOwner)
{
	// ToDo: Add initialization of added class data
}


/**--------------------------------------------------------------------+\

 * <summary>~DerivedClass - destructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::~DerivedClass( void )
{
	// ToDo: Add code to close open connections and destroy class data.
	//
}

/**--------------------------------------------------------------------+\

 * <summary>~Initialize - Init function for DerivedClass</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::Initialize
			(
			void
			)
{
	NResult rtnResult = NR_S_SUCCESS;

	// ToDo: Add initialization code here. Do everything needed to prepare
	//       to connect to the device, without actually connecting. NOTE:
	//       the Load() function is executed before Initialize() so that XML
	//       parameters have been read and should be available.
	//
	//       Do not attempt to connect to the device here!!!
	//

	return( rtnResult );
}



/**--------------------------------------------------------------------+\

 * <summary>~Connect - Connect to streaming device</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::Connect
			(
			void
			)
{
	NResult rtnResult = NR_E_CONNECT_FAIL;

	// ToDo: Add code to connect to the device here. Connect() is called
	//       in the context of RxThread() and may have an infinite wait.
	//

	return rtnResult;
}


/**--------------------------------------------------------------------+\

 * <summary>Read - Read up to maxBytes of data into the buffer pointed
                   to by pBuf</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::Read(void *pBuf, int maxBytes )
{
	NResult nBytesRead = NR_E_RX_FAIL;

	// ToDo: Add code here to read a maximum of maxBytes from the device
	//
	// NOTE: use LogPrint() to log errors. For example:
	//
	//	LogPrint("DerivedClass.Read - read error %d\n",
	//	         errorValue);

	return nBytesRead;
}


/**--------------------------------------------------------------------+\

 * <summary>Write - Transfer/write nBytes of data from pBuf via the
                    data stream connection</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

NResult	DerivedClass::Write
			(
			void *pBuf,
			int nBytes
			)
{
	NResult nBytesWritten = NR_E_TX_FAIL;

	// ToDo: Add code here to write nBytes to the device.
	//
	// NOTE: use LogPrint() to log errors. For example:
	//
	//	LogPrint("DerivedClass.Write - write error %d\n",
	//	         errorValue);

	return nBytesWritten;
}


/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - COM overload for interface query</summary>

 * <remarks/>

 * (author)P.Hogan  --  dd-mmm-9999

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

	if ( rIID == IXID_IDataStream )
	{
		p = INTERFACE_THIS( IDataStreamPtr );
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

	// ToDo: Add code here to read device parameters from XML. For example:

	// m_DevNodeName = pConfig->GetParameterAsString("Port");
	// m_baudRate = pConfig->GetParameterAsUnsigned("Baud", 9600);
	// m_dataBits = pConfig->GetParameterAsUnsigned("Data Bits", 8);
	// m_stopBits = pConfig->GetParameterAsUnsigned("Stop Bits", 1);
	// m_parity = pConfig->GetParameterAsString("Parity", "None");
	// m_flowControl = pConfig->GetParameterAsString("Flow Control", "None");

#ifdef DerivedClass_DBG_PRINT
	// ToDo: Add debug print code here. For example:
	//
	// char dbgPrintString[128];
	// m_DevNodeName.CopyTo(dbgPrintString, sizeof(dbgPrintString));
	// DbgPrint("DerivedClass::Load : Port      = '%s'\n", dbgPrintString);
	// m_parity.CopyTo(dbgPrintString, sizeof(dbgPrintString));
	// DbgPrint("DerivedClass::Load : Parity    = '%s'\n", dbgPrintString);
	// m_flowControl.CopyTo(dbgPrintString, sizeof(dbgPrintString));
	// DbgPrint("DerivedClass::Load : Flow Cntl = '%s'\n", dbgPrintString);
	// DbgPrint("DerivedClass::Load : Baud      = %lu\n", m_baudRate);
	// DbgPrint("DerivedClass::Load : Data Bits = %lu\n", m_dataBits);
	// DbgPrint("DerivedClass::Load : Stop Bits = %lu\n", m_stopBits);
#endif // ifdef DerivedClass_DBG_PRINT

    return bResult;
}


NAMESPACE_COMMUNICATION_END



