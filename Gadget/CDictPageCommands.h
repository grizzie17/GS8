/*---------------------------------------------------------------------+\
|
|	CDictPageCommands.h  --  Process command requests
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
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageCommands
#define _H_CDictPageCommands
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CDictPageVariant.h"
#include "VFunctionProcessor.h"
#include "CQueue.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CDictPageCommands*			CDictPageCommandsPtr;
typedef class CDictPageCommands&			CDictPageCommandsRef;
typedef const class CDictPageCommands&	ConstCDictPageCommandsRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageCommands : public CDictPageVariant
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageCommands();
	virtual			~CDictPageCommands();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void		SetCommandQueue( CQueuePtr p );
	CQueuePtr	CommandQueue( void );

	void		SetFunctionProcessor( VFunctionProcessorPtr p );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CQueuePtr				m_pCommandQueue;	// memory managed elswhere
	VFunctionProcessorPtr	m_pFunctions;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual bool	PutData( unsigned long nSel, Yogi::Common::CVariantDataPtr pData );
	virtual bool	UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

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



#endif /* _H_CDictPageCommands */
