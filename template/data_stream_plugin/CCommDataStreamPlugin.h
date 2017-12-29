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

	dd-mmm-9999			F.Lastname			(Reviewed by: xxxx)
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

#include "NamespaceCommunication.h"
#include "VPluginWithAggregateList.h"
#include "IDataStream.h"
#include "UNResult.h"

// ToDo: Add additional include files here
//

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMUNICATION_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ DerivedClass*			DerivedClassPtr;
typedef interface_ DerivedClass&			DerivedClassRef;
typedef const interface_ DerivedClass&	ConstDerivedClassRef;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/


class DerivedClass : public VPluginWithAggregateList,
							 implements_ IDataStream
{

	COM_LIFECYCLE( DerivedClass );

public:

	DECLARE_ISUPPORTS;

	//
	//	Initialize
	//
	//	Perform any initialization to prepare to connect to the data
	//  message stream.
	//
	virtual
	NResult	Initialize
			(
			void
			);

	//
	//	Connect
	//
	//	Connect to the external data bus.
	//
	virtual
	NResult	Connect
			(
			void
			);

	//
	//	Read
	//
	//	Read up to maxBytes of data into the buffer pointed to by pBuf.
	//
	virtual
	NResult	Read
			(
			void *pBuf,
			int maxBytes
			);

	//
	//	Write
	//
	//	Transfer/write nBytes of data from pBuf via the data stream connection.
	//
	virtual
	NResult	Write
			(
			void *pBuf,
			int nBytes
			);


	//
	//	Load
	//
	//	Load stream parameters from XML - e.g. baud rate, IP addresses...
	//
	virtual
	bool 	Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		);

protected:

	virtual void*	FindInternalInterface( ConstIXIDRef	rIID );

private:

	// ToDo: Add class data here
	//
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


NAMESPACE_COMMUNICATION_END


#endif /* _H_filename */

