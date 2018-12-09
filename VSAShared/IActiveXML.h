/*---------------------------------------------------------------------+\
|
|	IActiveXML.h  --  brief description of what IActiveXML.h is for
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IActiveXML
#define _H_IActiveXML
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"


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

typedef interface_ IActiveXML*			IActiveXMLPtr;

extern const IXID	IXID_IActiveXML;


typedef interface_ IActiveXMLClient*	IActiveXMLClientPtr;

extern const IXID	IXID_IActiveXMLClient;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IActiveXML : public ISupports
{
	//
	//	RegisterXMLClient
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	NResult	RegisterXMLClient
			(
			IActiveXMLClientPtr	p
			) PURE;


	//	FetchXMLData
	//
	//	Gets the next available buffer from the service
	//
	//	returns an ID that is used to release the buffer
	//
	virtual
	int		FetchXMLData
			(
			char**	hBuffer,	// OUT:	address of buffer
			size_t*	pnSize,		// OUT:	number of bytes in buffer
			size_t*	pnSequence	// OUT: sequence identifier
			) PURE;


	virtual
	void	ReleaseXMLData
			(
			int		nID			// IN:	id of buffer to release
			) PURE;
};


interface_ IActiveXMLClient : public ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	NResult	NotifyXMLAvailable
			(
			void
			) PURE;
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


#endif /* _H_IActiveXML */
