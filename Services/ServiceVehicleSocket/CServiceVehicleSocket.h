/*---------------------------------------------------------------------+\
|
|	CServiceVehicleSocket.h  --  brief description of what CServiceVehicleSocket.h is for
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceVehicleSocket
#define _H_CServiceVehicleSocket
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginService.h"

#include "IActiveXML.h"

#include "CSocket.h"
#include "CMutex.h"
#include "UPlatformThreads.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


const int NUM_DISPLAYS = 4;

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CServiceVehicleSocket*		CServiceVehicleSocketPtr;
typedef class CServiceVehicleSocket&		CServiceVehicleSocketRef;
typedef const class CServiceVehicleSocket&	ConstCServiceVehicleSocketRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CServiceVehicleSocket : public VPluginService,
							implements_ IActiveXML
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CServiceVehicleSocket );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IActiveXML
	virtual
	NResult	RegisterXMLClient
			(
			IActiveXMLClientPtr	p
			);


	virtual
	int		FetchXMLData
			(
			char**	hBuffer,	// OUT:	address of buffer
			size_t*	pnSize,		// OUT:	number of bytes in buffer
			size_t*	pnSequence	// OUT: sequence identifier
			);


	virtual
	void	ReleaseXMLData
			(
			int		nID			// IN:	id of buffer to release
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct	DBuf
	{
		long	nUsers;
		size_t	nSequence;
		size_t	nAlloc;
		size_t	nSize;
		char*	pBuffer;

		DBuf()
			: nUsers(0),
			nSequence(0),
			nAlloc(0),
			nSize(0),
			pBuffer(0)
		{};

		DBuf( const DBuf& r )
			: nUsers(r.nUsers),
			nSequence(r.nSequence),
			nAlloc(r.nAlloc),
			nSize(r.nSize),
			pBuffer(r.pBuffer)
		{
		};

		~DBuf()
		{
			if ( pBuffer )
				delete [] pBuffer;
		};
	} DBuf;

//	protected functions  ------------------------------------------------

	static
	UThreadRtn
			RunGlueRx
			(
			void*	pVoid
			);

	UThreadRtn
			RunRx( void );

	bool	OpenMulticastSocket
			(
			void
			);


	DBuf*	GetBufferForRead
			(
			void
			);


	DBuf*	FindIdleBuffer
			(
			void
			);

	void	GrowBuffer
			(
			DBuf*	p
			);


	void	NotifyClients
			(
			void
			);




	void	SetMCMaxMsgSize
			(
			int m
			);


	bool		MsgIsOk( char* buf, unsigned int len );






//	protected data  -----------------------------------------------------


	CMutex					m_oMutex;
	CSocketUDPPtr			m_pSocket;		// multicast socket
	CCharString				m_sMCAddress;
	unsigned short			m_nMCPort;

	UThreadHdl				m_pRxThread;

	TArray<IActiveXMLClientPtr>	m_aClients;
	TArray<DBuf>			m_aBuffers;







	size_t					m_nSequence;

	bool					m_bInitDone;

	int						m_nMCTimeOut;
	size_t 					m_nMCMaxMsgSize;




private:
//	private types  ------------------------------------------------------

	typedef	VPluginService	inherited;

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

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr		pLib
			);

	//	IService
public:
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


#endif /* _H_CServiceVehicleSocket */

