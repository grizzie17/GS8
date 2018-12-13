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


//USING_NAMESPACE_COMMON
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
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryExternalXML : public Yogi::Common::VSupports,
							implements_ IApplicationUser,
							implements_ Yogi::Common::IExternalXML,
							implements_ Yogi::Common::IExternalXMLServer
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
			Yogi::Common::IExternalXMLServerPtr p
			);

	virtual
	Yogi::XMLLite::VReadCallBack*
			GetCallBack
			(
			const char*	sArg
			);

	virtual
	Yogi::XMLLite::VReadCallBack*
			GetCallBack
			(
			Yogi::Core::ConstCCharDescriptorRef	rArg
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
			const char*					sName,
			Yogi::Common::ISupportsPtr	pIF
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::THashTable<Yogi::Core::CCharString, Yogi::Common::IExternalXMLPtr>
									m_aList;

	CApplicationGaugePtr			m_pApplication;
	Yogi::Common::IPluginLibraryPtr	m_pLibrary;

	Yogi::Common::IExternalXMLPtr	m_pActive;

private:
//	private types  ------------------------------------------------------

	typedef Yogi::Common::VSupports	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
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


}}


#endif /* _H_CFactoryExternalXML */
