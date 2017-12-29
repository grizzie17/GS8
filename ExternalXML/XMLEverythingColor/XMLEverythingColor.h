/*---------------------------------------------------------------------+\
|
|	XMLEverythingColor.h  --  Header for XMLEverythingColor Plugin
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
typedef class XMLEverythingColor*		XMLEverythingGaugePtr;
typedef class XMLEverythingColor&		XMLEverythingGaugeRef;
typedef const class XMLEverythingColor&	ConstXMLEverythingGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class XMLEverythingColor : public VPluginExternalXML
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(XMLEverythingColor);

public:
//	supported interfaces  -----------------------------------------------


public:
//	public types  -------------------------------------------------------


	typedef enum SORTFIELD
	{
		SORT_HUE = 0,
		SORT_SATURATION,
		SORT_VALUE,
		SORT_LIGHT
	} SORTFIELD;


	typedef struct ColorEntry
	{
		ColorName		data;
		HSLColorByte	hsl;

		bool		operator < ( const ColorEntry& b );
		ColorEntry&	operator = ( const ColorEntry& r );
	} ColorEntry;


//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	void			WriteLine( const char* s );
	void			WriteString( const char* s );


	void			BufferAppend( const char* s );
	void			BufferEOS( void );
	void			BufferLine( const char* s );
	void			BufferString( const char* s );

	void	WriteColorEntry
			(
			ColorEntry*	pe,
			long		nCol,
			long		nRow
			);
	void			WriteKeyMap( void );

	void			WriteHeader( void );
	void			WriteActive( void );
	void			WriteFooter( void );


//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;




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
			ConstCCharDescriptorRef	rArg
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

NAMESPACE_GADGET_END



#endif /* _H_XMLEverythingGauge */

