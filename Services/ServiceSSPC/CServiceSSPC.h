/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CServiceSSPC.h  --  brief description of what CServiceSSPC.h is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceSSPC
#define _H_CServiceSSPC
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <pthread.h>
#include <unistd.h>

#include "VPluginService.h"
#include "UNResult.h"


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

namespace Yogi { namespace Gadget {


#define	SSPC_MAX_CHANNELS	16
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CServiceSSPC*			CServiceSSPCPtr;
typedef class CServiceSSPC&			CServiceSSPCRef;
typedef const class CServiceSSPC&	ConstCServiceSSPCRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceSSPC : public VPluginService
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CServiceSSPC );

public:
//	supported interfaces  -----------------------------------------------

	//	Inherited from VPluginService

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	static
	unsigned int	RunGlueRx
					(
					void*	pVoid
					);

	void			RunRx( void );

	static
	unsigned int	RunGlueTx
					(
					void*	pVoid
					);

	void			RunTx( void );

	long			vddsOpenCanPort(char *port_to_open, unsigned int *port_name);
	int				set_bitrate( int can_fd, int baud);
	void			Power_On_Cameras( void );


//	protected data  -----------------------------------------------------

	CCharString		m_sPort;
	int				m_nBaud;
	long			m_nChannelCount;
	long			m_aChannels[SSPC_MAX_CHANNELS];
	long			m_nDelay;
	long			m_nRetry;

	int				m_nCanHandle;
	unsigned short	m_nChannelState;

	pthread_t		m_pRxThread;
	pthread_t		m_pTxThread;


private:
//	private types  ------------------------------------------------------

	typedef VPluginService	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr pLib
			);

public:
	//	IService
	virtual
	NResult	Start
			(
			void
			);

	virtual
	NResult	Stop
			(
			void
			);


};

}}

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


#endif /* _H_CServiceSSPC */
