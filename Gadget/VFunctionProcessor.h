/*---------------------------------------------------------------------+\
|
|	VFunctionProcessor.h  --  Interface for dealing with functions
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
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFunctionProcessor
#define _H_VFunctionProcessor
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VObject.h"
#include "VDictionary.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
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
typedef class VFunctionProcessor*		VFunctionProcessorPtr;
typedef class VFunctionProcessor&		VFunctionProcessorRef;
typedef const class VFunctionProcessor&	ConstVFunctionProcessorRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VFunctionProcessor : public VObject
{
//	class lifecycle  ----------------------------------------------------
public:

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual bool	ProcessRequest
					(
					VDictionary::Selector	sel,
					ConstCVariantDataRef	vData
					) = 0;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


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



#endif /* _H_VFunctionProcessor */

