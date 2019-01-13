/*---------------------------------------------------------------------+\
|
|	VPluginExternalXML.h  --  Base class for plugin commands
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
	28-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginExternalXML
#define _H_VPluginExternalXML
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregateList.h"

#include "IExternalXML.h"
#include "IApplicationUser.h"
#include "XMLLite.h"
#include "TArray.h"


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
typedef class VPluginExternalXML*		VPluginExternalXMLPtr;
typedef class VPluginExternalXML&		VPluginExternalXMLRef;
typedef const class VPluginExternalXML&	ConstVPluginExternalXMLRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPluginExternalXML : public Yogi::Common::VPluginWithAggregateList,
						implements_ IApplicationUser,
						implements_ IExternalXML,
						public virtual XMLLite::VReadCallBack
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VPluginExternalXML );

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

	//	VReadCallBack
	virtual
	size_t	Read					// RTN:	returns number of bytes actually read
			(
			void*			pBuffer,		// OUT: buffer to receive data
			size_t			nBytesToRead,	// IN:	number of bytes to read
			XMLLite::ETEXT_FORMAT	eFmt			// IN:	target format
			);

	/*
		Gets the size of the file (stream)
	*/
	virtual
	size_t	GetSize		// RTN:	return file (stream) size in bytes
			(
			void
			);

	/*
		Get a name associated with the call-back stream.
		For files this should be name of the file or
		at least a partial path with name.
	*/
	virtual
	size_t	GetName					// RTN:	string length of name
			(
			char*			sTarget,	// OUT:	buffer to receive name
			size_t			nSizeTarget	// IN:	size of target
			);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	void	AppendData
			(
			const char*	s
			);

	void	AppendData
			(
			const char*	s,
			size_t		n
			);


	bool	SaveData
			(
			const char*	sFilePath
			);


	Yogi::Core::CCharString
			BuildPath
			(
			const char*	sFilename
			);


//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString		m_sID;
	CApplicationGaugePtr		m_pApplication;
	Yogi::Core::TArray<char>	m_sData;
	index_t						m_nDataIndex;

private:
//	private functions  --------------------------------------------------

	typedef	VPluginWithAggregateList	inherited;

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
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



#endif /* _H_VPluginExternalXML */
