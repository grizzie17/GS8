/*---------------------------------------------------------------------+\
|
|	XMLEverythingAlert.h  --  Header for XMLEverythingAlert Plugin
|
|	Purpose:

		Provide support for touch screen calibration

|
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
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_XMLEverythingAlert
#define _H_XMLEverythingAlert
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginExternalXML.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"


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
typedef class XMLEverythingAlert*		XMLEverythingAlertPtr;
typedef class XMLEverythingAlert&		XMLEverythingAlertRef;
typedef const class XMLEverythingAlert&	ConstXMLEverythingAlertRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class XMLEverythingAlert : public VPluginExternalXML
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(XMLEverythingAlert);

public:
//	supported interfaces  -----------------------------------------------


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	void			WriteLine( const char* s );
	void			WriteString( const char* s );


	void			WriteHeader( void );
	void			WriteFooter( void );



//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;
	long					m_nAlertCount;
	long					m_nPosition;




private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

public:

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
			);


	//	IExternalXML
	virtual
	bool	Initialize
			(
			Yogi::Common::IExternalXMLServerPtr p
			);

	virtual
	XMLLite::VReadCallBack*
			GetCallBack
			(
			Yogi::Core::ConstCCharDescriptorRef	rArg
			);

	virtual
	void	ReleaseCallBack
			(
			XMLLite::VReadCallBack*	p
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



#endif /* _H_XMLEverythingAlert */
