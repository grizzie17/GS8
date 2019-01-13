/*---------------------------------------------------------------------+\
|
|	XMLEverythingGauge.h  --  Header for XMLEverythingGauge Plugin
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
#ifndef _H_XMLEverythingGauge
#define _H_XMLEverythingGauge
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
typedef class XMLEverythingGauge*		XMLEverythingGaugePtr;
typedef class XMLEverythingGauge&		XMLEverythingGaugeRef;
typedef const class XMLEverythingGauge&	ConstXMLEverythingGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class XMLEverythingGauge : public VPluginExternalXML
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(XMLEverythingGauge);

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
	void			WriteString( Yogi::Core::ConstCCharStringRef r );


	void			BufferAppend( const char* s );
	void			BufferEOS( void );
	void			BufferLine( const char* s );
	void			BufferString( const char* s );
	void			BufferString( Yogi::Core::ConstCCharStringRef r );


	void			WriteHeader( void );
	void			WriteAlerts( void );
	void			WriteActive( void );
	void			WriteFooter( void );


//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;
	long					m_nAlertCount;
	long					m_nPosition;

	Yogi::Core::TArray<char>			m_sBuffer;




private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

public:

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
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



#endif /* _H_XMLEverythingGauge */
