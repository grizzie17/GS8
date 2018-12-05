/*---------------------------------------------------------------------+\
|
|	CSocket.cpp  --  brief description of what CSocket.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UOSIncludes.h"
#if defined( OS_MSWIN )
#	define INCL_WINSOCK_API_TYPEDEFS	1
	BEGIN_IGNORE_WARNING(4365)
#	include <ws2tcpip.h>
	END_IGNORE_WARNING
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/if.h>
#	include <sys/ioctl.h>
#	include <netdb.h>
#	include <arpa/inet.h>
#	include <unistd.h>
#	include	<netinet/in.h>
#endif

#include <errno.h>

#include "CSocket.h"
#include "UNResult.h"
#include "LogFile.h"

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
#if defined( OS_MSWIN )

typedef	int		socklen_t;
typedef char	raw_type;

#else

typedef	void	raw_type;

#endif

/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/

bool	CSocket::g_bInitialized = false;
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * fillAddr -

\+---------------------------------------------------------------------*/
static
void	fillAddr
		(
		ConstCCharStringRef	rAddress,
		unsigned short		nPort,
		sockaddr_in&		addr
		)
{
	memset(&addr, 0, sizeof(addr));  // Zero out address structure
	addr.sin_family = AF_INET;       // Internet address

	hostent *host;  // Resolve name
	if ((host = gethostbyname(rAddress.Pointer())) == NULL)
	{
		// strerror() will not work for gethostbyname() and hstrerror()
		// is supposedly obsolete
		LOCAL_PRINT("Failed to resolve name (gethostbyname())\n");
	}
	addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

	addr.sin_port = htons(nPort);     // Assign port in network byte order
}

/*=====================================================================+\
||																		|
||	 CSocket implementation
||																		|
\+=====================================================================*/

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CSocket - constructor

\+---------------------------------------------------------------------*/
CSocket::CSocket
		(
		SOCKETHDL	nSockDesc
		)
		: m_nSockDesc( nSockDesc ),
		m_nError( 0 )
{
}

CSocket::CSocket
		(
		const CSocket&	//r
		)
		: m_nSockDesc( 0 ),
		m_nError( 0 )
{
}


CSocket::CSocket
		(
		int type,
		int protocol
		)
		: m_nSockDesc( 0 ),
		m_nError( 0 )
{
#if defined( OS_MSWIN )
	if ( ! g_bInitialized )
	{
		WORD	wReqVersion = MAKEWORD( 2, 2 );		// request WinSock v2.2
		WSADATA	tData;

		if ( 0 != WSAStartup( wReqVersion, &tData ) )
		{
			LOCAL_PRINT( "Unable to load WinSock DLL\n" );
			InternalError();
		}

		g_bInitialized = true;
	}

#endif

	m_nSockDesc = socket( PF_INET, type, protocol );
	if ( NOT_SOCKETHDL(m_nSockDesc) )
	{
		LOCAL_PRINT( "Socket creation failed\n" );
		InternalError();
	}
}




/*---------------------------------------------------------------------+\

 * ~CSocket - destructor

\+---------------------------------------------------------------------*/
CSocket::~CSocket
		(
		void
		)
{
#if defined( OS_MSWIN )
	::closesocket( m_nSockDesc );
#else
	::close( m_nSockDesc );
#endif
	m_nSockDesc = SOCKETHDL(-1);
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * GetLocalAddress -

\+---------------------------------------------------------------------*/
CCharString
		CSocket::GetLocalAddress
		(
		void
		)
{
	sockaddr_in	addr;
	size_t		nAddrLen = sizeof(addr);
	CCharString		s;

	if ( getsockname( m_nSockDesc, (sockaddr*)&addr, (socklen_t *) &nAddrLen) < 0 )
	{
		LOCAL_PRINT( "Fetch of local address failed\n" );
		InternalError();
	}
	s = inet_ntoa( addr.sin_addr );
	return s;
}

/*---------------------------------------------------------------------+\

 * GetLocalPort -

\+---------------------------------------------------------------------*/
unsigned short
		CSocket::GetLocalPort
		(
		void
		)
{
	sockaddr_in	addr;
	size_t		nAddrLen = sizeof(addr);

	if ( ::getsockname( m_nSockDesc, (sockaddr*)&addr, (socklen_t *) &nAddrLen) < 0 )
	{
		LOCAL_PRINT( "Fetch of local address failed\n" );
		InternalError();
		return 0;
	}
	else
	{
		return ntohs( addr.sin_port );
	}
}

/*---------------------------------------------------------------------+\

 * SetLocalPort -

\+---------------------------------------------------------------------*/
void	CSocket::SetLocalPort
		(
		unsigned short	n
		)
{
	sockaddr_in	tAddr;

	memset( &tAddr, 0, sizeof(tAddr) );
	tAddr.sin_family = AF_INET;
	tAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	tAddr.sin_port = htons(n);

	if ( bind( m_nSockDesc, (sockaddr*)&tAddr, sizeof(tAddr) ) < 0 )
	{
		LOCAL_PRINT( "failed to bind local port\n" );
		InternalError();
	}
}


/*---------------------------------------------------------------------+\

 * SetLocalAddressAndPort -

\+---------------------------------------------------------------------*/
void	CSocket::SetLocalAddressAndPort
		(
		ConstCCharStringRef	rAddress,
		unsigned short		nPort	// = 0
		)
{
	sockaddr_in	tAddr;

	fillAddr( rAddress, nPort, tAddr );

	if ( bind( m_nSockDesc, (sockaddr*)&tAddr, sizeof(tAddr) ) < 0 )
	{
		LOCAL_PRINT("bind of local address and port failed\n" );
		InternalError();
	}

}


/*---------------------------------------------------------------------+\

 * LastError -

\+---------------------------------------------------------------------*/
int		CSocket::LastError
		(
		void
		)
{
	return	m_nError;
}


/*---------------------------------------------------------------------+\

 * CleanUp -

\+---------------------------------------------------------------------*/
void	CSocket::CleanUp
		(
		void
		)
{
#if defined( OS_MSWIN )
	if ( 0 != WSACleanup() )
		LOCAL_PRINT( "WSACleanup failed\n" );
#endif
}


/*---------------------------------------------------------------------+\

 * ResolveService -

\+---------------------------------------------------------------------*/
unsigned short
		CSocket::ResolveService
		(
		ConstCCharStringRef rService,
		ConstCCharStringRef rProtocol //= "tcp"
		)
{
	struct servent*	pServ;

	pServ = getservbyname(rService.Pointer(), rProtocol.Pointer() );
	if ( ! pServ )
		return (unsigned short)atoi( rService.Pointer() );
	else
		return (unsigned short)ntohs( (unsigned short)pServ->s_port );
}


/*---------------------------------------------------------------------+\

 * InternalError -

\+---------------------------------------------------------------------*/
int		CSocket::InternalError
		(
		void
		)
{
#if defined( OS_MSWIN )
	m_nError = WSAGetLastError();
#else
	errno_t	er = errno;
	m_nError = errno;
#	if defined( _DEBUG )
	if ( 0 != m_nError )
	{
		char*	s = ::strerror( m_nError );
		LOCAL_PRINT( "CSocket::errno = %ld : %s\n", m_nError, s );
	}
#	endif
	if ( 0 == er )
	{
		m_nError = NR_S_NOERROR;
	}
	else
	{
		switch ( er )
		{
		case EOVERFLOW:
			m_nError = NR_E_BUFFER_OVERRUN;
			break;
		default:
			m_nError = NR_E_ERROR;
			break;
		}
	}

#endif
	return m_nError;
}



/*=====================================================================+\
||																		|
||	 CSocketCommunicate implementation
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * CSocketCommunicate -

\+---------------------------------------------------------------------*/
CSocketCommunicate::CSocketCommunicate
		(
		int type,
		int protocol
		)
		: inherited( type, protocol ),
		m_sForeignAddress(),
		m_nForeignPort( 0 )
{
}


CSocketCommunicate::CSocketCommunicate
		(
		SOCKETHDL nNewConnSD
		)
		: inherited( nNewConnSD ),
		m_sForeignAddress(),
		m_nForeignPort( 0 )
{
}


CSocketCommunicate::~CSocketCommunicate
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * Connect -

\+---------------------------------------------------------------------*/
void	CSocketCommunicate::Connect
		(
		ConstCCharStringRef	sForeignAddress,
		unsigned short		nForeignPort
		)
{
	sockaddr_in	tDestAddr;

	m_sForeignAddress = sForeignAddress;
	m_nForeignPort = nForeignPort;

	fillAddr( sForeignAddress, nForeignPort, tDestAddr );

	if ( ::connect( m_nSockDesc, (sockaddr*)&tDestAddr, sizeof(tDestAddr) ) < 0 )
	{
		LOCAL_PRINT( "Connect failed\n" );
		InternalError();
	}
}



/*---------------------------------------------------------------------+\

 * Send -

\+---------------------------------------------------------------------*/
void	CSocketCommunicate::Send
		(
		const void*	pBuffer,
		size_t		nBufferLength
		)
{
	if ( ::send( m_nSockDesc, (raw_type*)pBuffer, (int)nBufferLength, 0 ) < 0 )
	{
		LOCAL_PRINT( "Send failed\n" );
		InternalError();
	}
}


/*---------------------------------------------------------------------+\

 * Recv -

\+---------------------------------------------------------------------*/
int		CSocketCommunicate::Recv
		(
		void*	pBuffer,
		size_t	nBufferLength
		)
{
	int	nResult;

	nResult = ::recv( m_nSockDesc, (raw_type*)pBuffer, (int)nBufferLength, 0 );
	if ( nResult < 0 )
	{
		LOCAL_PRINT( "Recv failed\n" );
		InternalError();
	}

	return nResult;
}



CCharStringRef
		CSocketCommunicate::GetForeignAddress
		(
		void
		)
{
	return m_sForeignAddress;
}

unsigned short
		CSocketCommunicate::GetForeignPort
		(
		void
		)
{
	return m_nForeignPort;
}




/*=====================================================================+\
||																		|
||	 CSocketTCP implementation
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * CSocketTCP -

\+---------------------------------------------------------------------*/
CSocketTCP::CSocketTCP
		(
		void
		)
		: inherited( SOCK_STREAM, IPPROTO_TCP )
{
}


CSocketTCP::CSocketTCP
		(
		ConstCCharStringRef rForeignAddress,
		unsigned short		nForeignPort
		)
		: inherited( SOCK_STREAM, IPPROTO_TCP )
{
	Connect( rForeignAddress, nForeignPort );
}


CSocketTCP::CSocketTCP
		(
		SOCKETHDL nNewConnSD
		)
		: inherited( nNewConnSD )
{
}


CSocketTCP::~CSocketTCP
		(
		void
		)
{
}



/*=====================================================================+\
||																		|
||	 CSocket implementation
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * CSocketTCPServer -

\+---------------------------------------------------------------------*/
CSocketTCPServer::CSocketTCPServer
		(
		unsigned short	nLocalPort,
		int				nQueueLen //= 5
		)
		: inherited( SOCK_STREAM, IPPROTO_TCP )
{
	SetLocalPort( nLocalPort );
	SetListen( nQueueLen );
}


CSocketTCPServer::CSocketTCPServer
		(
		ConstCCharStringRef	rLocalAddress,
		unsigned short		nLocalPort,
		int					nQueueLen //= 5
		)
		: inherited( SOCK_STREAM, IPPROTO_TCP )
{
	SetLocalAddressAndPort( rLocalAddress, nLocalPort );
	SetListen( nQueueLen );
}


CSocketTCPServer::~CSocketTCPServer
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * Accept -

\+---------------------------------------------------------------------*/
CSocketTCP*
		CSocketTCPServer::Accept
		(
		void
		)
{
	SOCKETHDL	nNewConnSD = ::accept( m_nSockDesc, NULL, 0 );

	if ( NOT_SOCKETHDL(nNewConnSD) )
	{
		LOCAL_PRINT( "Accept failed\n" );
		InternalError();
		return 0;
	}
	else
	{
		return new CSocketTCP( nNewConnSD );
	}
}


/*---------------------------------------------------------------------+\

 * SetListen -

\+---------------------------------------------------------------------*/
void	CSocketTCPServer::SetListen
		(
		int	nQueueLen
		)
{
	if ( ::listen( m_nSockDesc, nQueueLen ) < 0 )
	{
		LOCAL_PRINT( "Set listening socket failed\n" );
		InternalError();
	}
}






/*=====================================================================+\
||																		|
||	 CSocketUDP implementation
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * CSocketUDP -

\+---------------------------------------------------------------------*/
CSocketUDP::CSocketUDP
		(
		void
		)
		: inherited( SOCK_DGRAM, IPPROTO_UDP )
{
	SetBroadcast();
}


CSocketUDP::CSocketUDP
		(
		unsigned short	nLocalPort,
		bool			bSharePort	// = false
		)
		: inherited( SOCK_DGRAM, IPPROTO_UDP )
{
	if ( bSharePort )
		SetSharedPort();
	SetLocalPort( nLocalPort );
	SetBroadcast();
}


CSocketUDP::CSocketUDP
		(
		ConstCCharStringRef	rLocalAddress,
		unsigned short		nLocalPort,
		bool				bSharePort	// = false
		)
		: inherited( SOCK_DGRAM, IPPROTO_UDP )
{
	if ( bSharePort )
		SetSharedPort();
	SetLocalAddressAndPort( rLocalAddress, nLocalPort );
	SetBroadcast();
}


CSocketUDP::~CSocketUDP
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * SetBroadcast -

\+---------------------------------------------------------------------*/
void	CSocketUDP::SetBroadcast
		(
		void
		)
{
	if ( m_nSockDesc )
	{
		int	nPermission = 1;
		if ( setsockopt( m_nSockDesc, SOL_SOCKET, SO_BROADCAST,
					(raw_type*)&nPermission, sizeof(nPermission) ) < 0 )
		{
			InternalError();
		}
	}
}


/*---------------------------------------------------------------------+\

 * SetSharedPort -

\+---------------------------------------------------------------------*/
void	CSocketUDP::SetSharedPort
		(
		void
		)
{
	if ( m_nSockDesc )
	{
		unsigned int opt = 1;
		if ( setsockopt( m_nSockDesc, SOL_SOCKET, SO_REUSEADDR,
					(raw_type*)&opt, sizeof(opt) ) < 0 )
		{
			InternalError();
		}
	}
}



/*---------------------------------------------------------------------+\

 * Disconnect -

\+---------------------------------------------------------------------*/
void	CSocketUDP::Disconnect
		(
		void
		)
{
	sockaddr_in	tNullAddr;
#if defined( OS_MSWIN )
#	define	NOSUPPORT	WSAEAFNOSUPPORT
#else
#	define	NOSUPPORT	EAFNOSUPPORT
#endif

	memset(&tNullAddr, 0, sizeof(tNullAddr));
	tNullAddr.sin_family = AF_UNSPEC;

	// Try to disconnect
	if (::connect(m_nSockDesc, (sockaddr *) &tNullAddr, sizeof(tNullAddr)) < 0)
	{
		if ( NOSUPPORT != InternalError() )
		{
			LOCAL_PRINT( "Disconnect failed\n" );
		}
	}
}


/*---------------------------------------------------------------------+\

 * SendTo -

\+---------------------------------------------------------------------*/
void	CSocketUDP::SendTo
		(
		const void*	pBuffer,
		int			nBufferLen,
		ConstCCharStringRef rForeignAddress,
		unsigned short		nForeignPort
		)
{
	sockaddr_in tDestAddr;

	fillAddr(rForeignAddress, nForeignPort, tDestAddr);

	// Write out the whole buffer as a single message.
	if ( nBufferLen != sendto(m_nSockDesc, (raw_type *) pBuffer, nBufferLen, 0,
			 (sockaddr *) &tDestAddr, sizeof(tDestAddr)) )
	{
		LOCAL_PRINT( "send failed\n" );
		InternalError();
	}
}


/*---------------------------------------------------------------------+\

 * RecvFrom -

\+---------------------------------------------------------------------*/
int		CSocketUDP::RecvFrom
		(
		void*			pBuffer,
		size_t			nBufferLen,
		CCharStringPtr	psSourceAddress,
		unsigned short*	pnSourcePort
		)
{
	int		nResult = 0;
	sockaddr_in clntAddr;
	socklen_t	addrLen = sizeof(clntAddr);

	nResult = recvfrom(m_nSockDesc, (raw_type *) pBuffer, (int)nBufferLen, 0,
					  (sockaddr *) &clntAddr, (socklen_t *) &addrLen );
	if ( nResult < 0 )
	{
		LOCAL_PRINT("Receive failed (recvfrom())\n");
		InternalError();
	}
	else if ( nResult == (int)nBufferLen )
	{
		// most likely truncated
		nResult = NR_E_BUFFER_OVERRUN;
	}
	if ( psSourceAddress )
		*psSourceAddress = inet_ntoa(clntAddr.sin_addr);
	if ( pnSourcePort )
		*pnSourcePort = ntohs(clntAddr.sin_port);

	return nResult;
}


/*---------------------------------------------------------------------+\

 * SetMulticastTTL -

\+---------------------------------------------------------------------*/
void	CSocketUDP::SetMulticastTTL
		(
		unsigned char cMulticastTTL
		)
{
	if (setsockopt(m_nSockDesc, IPPROTO_IP, IP_MULTICAST_TTL,
				 (raw_type *) &cMulticastTTL, sizeof(cMulticastTTL)) < 0)
	{
		LOCAL_PRINT("Multicast TTL set failed (setsockopt())\n");
		InternalError();
	}
}


/*---------------------------------------------------------------------+\

 * JoinGroup -

\+---------------------------------------------------------------------*/
void	CSocketUDP::JoinGroup
		(
		ConstCCharStringRef rMulticastGroup
		)
{
	struct ip_mreq mr;
	::memset( &mr, 0, sizeof(mr) );

	char	sTemp[128] = {0};
	rMulticastGroup.CopyTo( sTemp, sizeof(sTemp) );
#if defined( OS_MSWIN )
	mr.imr_interface.s_addr = htonl(INADDR_ANY);
	mr.imr_multiaddr.s_addr = inet_addr(sTemp);
#else
	struct ifreq ifr;
	strcpy( ifr.ifr_name, "eth0" );
	//strcpy( ifr.ifr_name, "eth 0.OmniScape" );
	ifr.ifr_ifru.ifru_addr.sa_family = AF_INET;

	int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); // temporary socket variable
	if ( sock ) // just to get local host address
	{
		if ( -1 < ioctl(sock, SIOCGIFADDR, &ifr) )
		{
			mr.imr_interface.s_addr = ((struct sockaddr_in*)&ifr.ifr_ifru.ifru_addr)->sin_addr.s_addr;
			//char* sIp = inet_ntoa(m_mreq.imr_interface);	debugging
		}

		close(sock); // yes, close every time, temporary socket only
	}
	inet_aton(sTemp,(in_addr*)&mr.imr_multiaddr.s_addr);
#endif



	if (setsockopt(m_nSockDesc, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		(raw_type *) &mr, sizeof(mr)) < 0)
	{
		LOCAL_PRINT("Multicast group (%s) join failed (setsockopt())\n", sTemp);
		InternalError();
	}
}


/*---------------------------------------------------------------------+\

 * LeaveGroup -

\+---------------------------------------------------------------------*/
void	CSocketUDP::LeaveGroup
		(
		ConstCCharStringRef rMulticastGroup
		)
{
	struct ip_mreq multicastRequest;

	multicastRequest.imr_multiaddr.s_addr = inet_addr(rMulticastGroup.Pointer());
	multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(m_nSockDesc, IPPROTO_IP, IP_DROP_MEMBERSHIP,
			(raw_type *) &multicastRequest,
			sizeof(multicastRequest)) < 0)
	{
		LOCAL_PRINT("Multicast group leave failed (setsockopt())\n");
		InternalError();
	}
}





/*=====================================================================+\
||																		|
||	 CSocketICMP implementation
||																		|
\+=====================================================================*/


CSocketICMP::CSocketICMP
		(
		void
		)
		: inherited( SOCK_RAW, IPPROTO_ICMP ),
		m_sForeignAddress(),
		m_nForeignPort( 0 )
{
}




CSocketICMP::~CSocketICMP
		(
		void
		)
{
}




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

