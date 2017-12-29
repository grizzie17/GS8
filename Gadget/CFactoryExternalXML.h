/*---------------------------------------------------------------------+\
|
|	CFactoryExternalXML.h  --  brief description of what CFactoryExternalXML.h is for
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
	21-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryExternalXML
#define _H_CFactoryExternalXML
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VSupports.h"

#include "IExternalXML.h"
#include "IApplicationUser.h"

#include "CPluginLibrary.h"
#include "THash.h"

#include "NamespaceGadget.h"
//USING_NAMESPACE_COMMON
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
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryExternalXML : public VSupports,
							implements_ IApplicationUser,
							implements_ IExternalXML,
							implements_ IExternalXMLServer
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CFactoryExternalXML );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IApplicationUser
	virtual
	bool	SetApplication
			(
			CApplicationGaugePtr	p	// IN:	application pointer
			);


	//	IExternalXML
	virtual
	bool	Initialize
			(
			IExternalXMLServerPtr p
			);

	virtual
	XMLLite::VReadCallBack*
			GetCallBack
			(
			const char*	sArg
			);

	virtual
	XMLLite::VReadCallBack*
			GetCallBack
			(
			ConstCCharDescriptorRef	rArg
			);

	virtual
	void	ReleaseCallBack
			(
			XMLLite::VReadCallBack*	p
			);

	//	IExternalXMLServer
	virtual
	bool	Register
			(
			const char*		sName,
			ISupportsPtr	pIF
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	THashTable<CCharString, IExternalXMLPtr>
							m_aList;

	CApplicationGaugePtr	m_pApplication;
	IPluginLibraryPtr		m_pLibrary;


	IExternalXMLPtr			m_pActive;

private:
//	private types  ------------------------------------------------------

	typedef VSupports	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

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


#endif /* _H_CFactoryExternalXML */

