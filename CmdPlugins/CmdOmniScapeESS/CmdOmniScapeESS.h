/*---------------------------------------------------------------------+\
|
|	CmdOmniScapeESS.h  --  Header for CmdOmniScapeESS Plugin
|
|	Purpose:

		Test whether OmniScape is active or not

|	File Custodian:		J.Griswold
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
#ifndef _H_CmdOmniScapeESS
#define _H_CmdOmniScapeESS
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"
#include "CConsole.h"
#include "CSerial.h"
#include "IEssStatus.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMutex.h"

#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CmdOmniScapeESS*		CmdOmniScapeESSPtr;
typedef class CmdOmniScapeESS&		CmdOmniScapeESSRef;
typedef const class CmdOmniScapeESS&	ConstCmdOmniScapeESSRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdOmniScapeESS : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdOmniScapeESS);

public:
//	supported interfaces  -----------------------------------------------


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------


	typedef	struct XData
	{
		CConsolePtr	pConsole;
		CCharString	sPortName;
		bool		bOpen;

		XData()
			: pConsole( 0 ),
			sPortName(),
			bOpen( false )
		{
		}
		~XData()
		{
			if ( pConsole )
			{
				delete pConsole;
				pConsole = 0;
			}
		}
	} XData;

//	protected functions  ------------------------------------------------

	// registered commands
	bool		essStart( ConstCVariantDataRef r );
	bool		essReset( ConstCVariantDataRef r );
	bool		essCalculate( ConstCVariantDataRef r );
	bool		essVirgin( ConstCVariantDataRef r );

	bool		SaveData( void );
	bool		LoadData( void );


	bool		StartThreads( void );
	bool		StopThreads( void );

	void		UpdateDictionary( void );

	CCharString	BuildPath( void );


	void		SetVariable( int n );

//	protected data  -----------------------------------------------------

	CMutex					m_oMutex;
	VDictionaryPtr			m_pDictionary;

	VDictionary::Selector	m_nCmdStart;
	VDictionary::Selector	m_nCmdReset;
	VDictionary::Selector	m_nCmdCalculate;
	VDictionary::Selector	m_nCmdVirgin;


	CCharString				m_sFilePath;
	CCharString				m_sFilename;


	CSerialPortSettings		m_oPortSettings;
	CCharString				m_sServerIP;

	bool					m_bStaticDisplay;
	bool					m_bDirty;
	bool					m_bRunning;
	size_t					m_nPortCount;
	XData*					m_aPorts;




private:
//	private functions  --------------------------------------------------

	typedef	VPluginCommand	inherited;

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

public:
	//	ICommandPlugin
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VCommandSetupPtr		pCommandSetup
			);

	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector	selCommand,
			ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
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



#endif /* _H_CmdOmniScapeESS */

