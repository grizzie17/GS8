/*---------------------------------------------------------------------+\
|
|	IExternalXML.h  --  
|
|	Purpose:

		Supports the external 'run-time' generation of xml for the
		gadget system.

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
	21-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IExternalXML
#define _H_IExternalXML
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "XMLLite.h"
#include "CCharDescriptor.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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

typedef interface_ IExternalXML*			IExternalXMLPtr;
typedef interface_ IExternalXMLServer*		IExternalXMLServerPtr;

extern const IXID	IXID_IExternalXML;
extern const IXID	IXID_IExternalXMLServer;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IExternalXML : public ISupports
{
	virtual
	bool	Initialize
			(
			IExternalXMLServerPtr p 
			) PURE;


	virtual
	XMLLite::VReadCallBack*
			GetCallBack
			(
			const char*	sArg
			) PURE;

	virtual
	XMLLite::VReadCallBack*
			GetCallBack
			(
			ConstCCharDescriptorRef	rArg
			) PURE;

	virtual
	void	ReleaseCallBack
			(
			XMLLite::VReadCallBack*	p
			) PURE;
};




interface_ IExternalXMLServer : ISupports
{
	virtual
	bool	Register
			(
			const char*		sName,
			ISupportsPtr	pIF
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


NAMESPACE_COMMON_END


#endif /* _H_IExternalXML */

