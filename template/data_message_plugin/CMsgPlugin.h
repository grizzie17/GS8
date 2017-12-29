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
#include "IDataMessage.h"
#include "UNResult.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMUNICATION_BEGIN

// ToDo: Add any additional constants/#defines needed to construct device
//       messages here
//

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class DerivedClass*         DerivedClassPtr;
typedef class DerivedClass&         DerivedClassRef;
typedef const class DerivedClass&   ConstDerivedClassRef;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DerivedClass : public VPluginWithAggregateList,
                           implements_ IDataMessage
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( DerivedClass );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	DECLARE_ISUPPORTS;

	//   IDataMessage implementation
	//
	NResult	Initialize(void);
	NResult	Connect(void);
	NResult ReadMessage( void *pMsg, int maxMsgSize );
	NResult WriteMessage( void *pMsg, int msgSize );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	virtual void*	FindInternalInterface( ConstIXIDRef	rIID );

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

	IDataStream* 	m_pDataStream;

	// ToDo: Add any additional class variables here. Be sure to initialize
	//       them in the constructor.
	//


//============================== Overrides ==============================

public:
	//	IPluginLoadConfiguration override
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);


private:

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

