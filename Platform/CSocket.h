/*==================================================================*//**
*
*	@file	CSocket.h
*	@brief	Wrapper for Posix/Windows Sockets
*
*	@note
		Inspired by Practical Sockets
		http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/practical/
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CSocket
#define _H_CSocket
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"
#if defined( OS_MSWIN )
#	include <winsock2.h>
#endif

#include "CCharString.h"
#include "UDeclSpec.h"

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#if defined( OS_MSWIN )
#	define IS_SOCKETHDL( h )	(h)
#	define NOT_SOCKETHDL( h )	(! (h))
#else
#	define IS_SOCKETHDL( h )	(0 <= (h))
#	define NOT_SOCKETHDL( h )	((h) < 0)
#endif

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/


typedef class CSocketTCP*		CSocketTCPPtr;
typedef class CSocketTCP&		CSocketTCPRef;
typedef const class CSocketTCP&	ConstCSocketTCPRef;


typedef class CSocketTCPServer*			CSocketTCPServerPtr;
typedef class CSocketTCPServer&			CSocketTCPServerRef;
typedef const class CSocketTCPServer&	ConstCSocketTCPServerRef;


typedef class CSocketUDP*		CSocketUDPPtr;
typedef class CSocketUDP&		CSocketUDPRef;
typedef const class CSocketUDP&	ConstCSocketUDPRef;


typedef class CSocketICMP*			CSocketICMPPtr;
typedef class CSocketICMP&			CSocketICMPRef;
typedef const class CSocketICMP&	ConstCSocketICMPRef;




#if defined( OS_MSWIN )
	typedef	SOCKET	SOCKETHDL;
#else
	typedef	int		SOCKETHDL;
#endif


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/



/*---------------------------------------------------------------------+\
|	CSocket
\+---------------------------------------------------------------------*/

class DECL_CLASS CSocket // BaseClass
{
//	class lifecycle  ----------------------------------------------------
public:

	///	Close and deallocate this socket
	virtual	~CSocket();

protected:

			CSocket( int type, int protocol );
			CSocket( SOCKETHDL nSockDesc );

private:
	// prevent copy semantics
			CSocket( const CSocket& r );
	void	operator=( const CSocket& r );

public:
//	public types  -------------------------------------------------------


//	public functions  ---------------------------------------------------


	///	GetLocalAddress
	///
	///	Get the local address of the socket
	///
	CCharString
			GetLocalAddress		///@return the local address of the socket
			(
			void
			);


	unsigned short
			GetLocalPort
			(
			void
			);

	void	SetLocalPort
			(
			unsigned short	n
			);

	void	SetLocalAddressAndPort
			(
			ConstCCharStringRef	rAddress,
			unsigned short		nPort = 0
			);

	int		LastError
			(
			void
			);

	static
	void	CleanUp
			(
			void
			);

	static
	unsigned short
			ResolveService
			(
			ConstCCharStringRef	rService,
			ConstCCharStringRef	rProtocol = "tcp"
			);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	int		InternalError
			(
			void
			);

//	protected data  -----------------------------------------------------

	SOCKETHDL	m_nSockDesc;
	int			m_nError;

private:
//	private types  ------------------------------------------------------

	//typedef BaseClass	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

	static bool	g_bInitialized;


};



/*---------------------------------------------------------------------+\
|	CSocketCommunicate
\+---------------------------------------------------------------------*/


class DECL_CLASS CSocketCommunicate : public CSocket
{
//	class lifecycle  ----------------------------------------------------
public:

	virtual	~CSocketCommunicate();

protected:
			CSocketCommunicate( int type, int protocol );
			CSocketCommunicate( SOCKETHDL nNewConnSD );

private:
	// prevent copy semantics
	CSocketCommunicate( const CSocketCommunicate& r );
	void	operator=(const CSocketCommunicate& r);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	Connect
			(
			ConstCCharStringRef	sForeignAddress,
			unsigned short		nForeignPort
			);

	void	Send
			(
			const void*	pBuffer,
			size_t		nBufferLength
			);

	int		Recv
			(
			void*	pBuffer,
			size_t	nBufferLength
			);

	CCharStringRef
			GetForeignAddress
			(
			void
			);

	unsigned short
			GetForeignPort
			(
			void
			);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CCharString		m_sForeignAddress;
	unsigned short	m_nForeignPort;

private:
//	private types  ------------------------------------------------------

	typedef CSocket	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};




/*---------------------------------------------------------------------+\
|	CSocketTCP
\+---------------------------------------------------------------------*/


class DECL_CLASS CSocketTCP : public CSocketCommunicate
{
//	class lifecycle  ----------------------------------------------------
public:
			CSocketTCP();

			CSocketTCP
				(
				ConstCCharStringRef	rForeignAddress,
				unsigned short		nForeignPort
				);

	virtual	~CSocketTCP();

private:
	
	CSocketTCP( SOCKETHDL nNewConnSD );

	friend class CSocketTCPServer;

	// prevent copy semantics
	CSocketTCP( const CSocketTCP& r );
	void	operator=(const CSocketTCP& r);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef CSocketCommunicate	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};




/*---------------------------------------------------------------------+\
|	CSocketTCPServer
\+---------------------------------------------------------------------*/


class DECL_CLASS CSocketTCPServer : public CSocket
{
//	class lifecycle  ----------------------------------------------------
public:
			CSocketTCPServer
			(
			unsigned short	nLocalPort,
			int				nQueueLen = 5
			);

			CSocketTCPServer
			(
			ConstCCharStringRef	rLocalAddress,
			unsigned short		nLocalPort,
			int					nQueueLen = 5
			);

	virtual	~CSocketTCPServer();

private:
	// prevent copy semantics
	CSocketTCPServer( const CSocketTCPServer& r );
	void	operator=(const CSocketTCPServer& r);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CSocketTCP*
			Accept
			(
			void
			);


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef CSocket	inherited;

//	private functions  --------------------------------------------------

	void	SetListen
			(
			int	nQueueLen
			);

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};




/*---------------------------------------------------------------------+\
|	CSocketUDP
\+---------------------------------------------------------------------*/


class DECL_CLASS CSocketUDP : public CSocketCommunicate
{
//	class lifecycle  ----------------------------------------------------
public:
			CSocketUDP();

			CSocketUDP
			(
			unsigned short	nLocalPort,
			bool			bSharePort = false
			);

			CSocketUDP
			(
			ConstCCharStringRef	rLocalAddress,
			unsigned short		nLocalPort,
			bool				bSharedPort = false
			);

	virtual	~CSocketUDP();

private:
	// prevent copy semantics
	CSocketUDP( const CSocketUDP& r );
	void	operator=(const CSocketUDP& r);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	Disconnect
			(
			void
			);


	void	SendTo
			(
			const void*		pBuffer,
			int				nBufferLen,
			ConstCCharStringRef	rForeignAddress,
			unsigned short	nForeignPort
			);

	int		RecvFrom
			(
			void*		pBuffer,
			size_t		nBufferLen,
			CCharStringPtr	psSourceAddress,
			unsigned short*	pnSourcePort
			);

	void	SetMulticastTTL
			(
			unsigned char	cMulticastTTL
			);

	void	JoinGroup
			(
			ConstCCharStringRef	rMulticastGroup
			);

	void	LeaveGroup
			(
			ConstCCharStringRef	rMulticastGroup
			);


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef CSocketCommunicate	inherited;

//	private functions  --------------------------------------------------

	void	SetBroadcast
			(
			void
			);

	void	SetSharedPort
			(
			void
			);

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};



/*---------------------------------------------------------------------+\
|	CSocketICMP
\+---------------------------------------------------------------------*/


class DECL_CLASS CSocketICMP : public CSocket
{
//	class lifecycle  ----------------------------------------------------
public:
			CSocketICMP();
	virtual	~CSocketICMP();

protected:
			CSocketICMP( int type, int protocol );
			CSocketICMP( int nNewConnSD );

private:
	// prevent copy semantics
	CSocketICMP( const CSocketICMP& r );
	void	operator=(const CSocketICMP& r);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	Connect
			(
			ConstCCharStringRef	sForeignAddress,
			unsigned short		nForeignPort
			);

	void	Send
			(
			const void*	pBuffer,
			int			nBufferLength
			);

	int		Recv
			(
			void*	pBuffer,
			int		nBufferLength
			);

	CCharStringRef
			GetForeignAddress
			(
			void
			);

	unsigned short
			GetForeignPort
			(
			void
			);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CCharString		m_sForeignAddress;
	unsigned short	m_nForeignPort;

private:
//	private types  ------------------------------------------------------

	typedef CSocket	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

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



#endif /* _H_CSocket */

