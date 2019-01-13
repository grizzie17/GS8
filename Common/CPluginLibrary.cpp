/*---------------------------------------------------------------------+\
|
|	CPluginLibrary.cpp  --  brief description of what CPluginLibrary.cpp is for
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
	11-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CPluginLibrary.h"
#include "UMachine.h"
#include "CCharDescriptor.h"

namespace Yogi { namespace Common {
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
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * CPluginLibrary - constructor

\+---------------------------------------------------------------------*/

CPluginLibrary::CPluginLibrary
		(
		void
		)
		: inherited()
		, m_aContent()
		, m_sBaseFolder()
		, m_tLoader()
		, m_oMutex()
{
}

CPluginLibrary::CPluginLibrary
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_aContent()
		, m_sBaseFolder()
		, m_tLoader()
		, m_oMutex()
{
}

CPluginLibrary::CPluginLibrary
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_aContent()
		, m_sBaseFolder()
		, m_tLoader()
		, m_oMutex()
{
}




/*---------------------------------------------------------------------+\

 * ~CPluginLibrary - destructor

\+---------------------------------------------------------------------*/
CPluginLibrary::~CPluginLibrary
		(
		void
		)
{
	FactoryCampus*	p = m_aContent.PointArray();
	if ( p )
	{
		FactoryCampus*	pEnd = p + m_aContent.Length();

		while ( p < pEnd )
		{
			Yogi::Core::CMutexLocker	locker( &this->m_oMutex );
			if ( p->m_pFactory )
				p->m_pFactory->DestroyFactory();

			if ( p->m_hLibrary )
				DLLClose( p->m_hLibrary );
			++p;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Create -

\+---------------------------------------------------------------------*/
ISupportsPtr
		CPluginLibrary::Create
		(
		const char*		sLibraryname,
		ISupportsPtr	pOwner	// = 0
		)
{
	Yogi::Core::CCharDescriptor	tLib( (char*)sLibraryname );
	return Create( tLib, pOwner );
}


/*---------------------------------------------------------------------+\

 * Create -

\+---------------------------------------------------------------------*/
ISupportsPtr
		CPluginLibrary::Create
		(
		Yogi::Core::ConstCCharDescriptorRef rLibraryname,
		ISupportsPtr	pOwner	// = 0
		)
{
	ISupportsPtr		pISupports = 0;
	VPluginFactoryPtr	pFactory = GetFactory( rLibraryname );

	if ( pFactory )
	{
		//CMutexLocker( &this->m_oMutex );
		pISupports = pFactory->Make( pOwner );
	}

	return pISupports;
}


/*---------------------------------------------------------------------+\

 * SetBaseFolder -

\+---------------------------------------------------------------------*/
void	CPluginLibrary::SetBaseFolder
		(
		const char*	sFolder
		)
{
	m_sBaseFolder = sFolder;
	m_tLoader.SetPath( sFolder );
}


/*---------------------------------------------------------------------+\

 * SetRelativeFolder -

\+---------------------------------------------------------------------*/
void	CPluginLibrary::SetRelativeFolder
		(
		const char*	sFolder
		)
{
	const char	sSep[] = { FOLDER_SEPARATOR, 0 };

	Yogi::Core::CCharString	sNewFolder = m_sBaseFolder;
	if ( sFolder )
	{
		sNewFolder += sSep;
		sNewFolder += sFolder;
	}

	m_tLoader.SetPath( sNewFolder.Pointer() );
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * GetFactory -

\+---------------------------------------------------------------------*/
VPluginFactoryPtr
		CPluginLibrary::GetFactory
		(
		Yogi::Core::ConstCCharDescriptorRef rLibraryname
		)
{
	VPluginFactoryPtr		p = 0;
	Yogi::Core::CCharString	sLib = rLibraryname;
	FactoryCampus*			h = m_aContent.Find( sLib );
	if ( ! h )
	{
		ULibraryHdl	hLib;

		p = m_tLoader.LoadFactory( sLib.Pointer(), &hLib );
		if ( p )
		{
			Yogi::Core::CMutexLocker	locker( &this->m_oMutex );
			FactoryCampus	campus;
			campus.m_hLibrary = hLib;
			campus.m_pFactory = p;
			m_aContent.Add( sLib, campus );
		}
	}
	else
	{
		p = h->m_pFactory;
	}

	return p;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CPluginLibrary::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = VSupports::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IPluginLibrary )
			pI = INTERFACE_THIS( IPluginLibraryPtr );
		else
			pI = 0;
	}

	return pI;
}

#ifdef _DEBUG

/*---------------------------------------------------------------------+\

 * InternalAddRef -

\+---------------------------------------------------------------------*/
NRefCount
		CPluginLibrary::InternalAddRef
		(
		void
		)
{
	NRefCount	n = inherited::InternalAddRef();
	LOCAL_PRINT( "%s: refcount=%d\n", __FUNCTION__, m_nRefCount );
	return n;
}

/*---------------------------------------------------------------------+\

 * InternalRelease -

\+---------------------------------------------------------------------*/
NRefCount
		CPluginLibrary::InternalRelease
		(
		void
		)
{
	NRefCount	n = inherited::InternalRelease();
	LOCAL_PRINT( "%s: refcount=%d\n", __FUNCTION__, n );
	return n;
}


/*---------------------------------------------------------------------+\

 * FinalRelease -

\+---------------------------------------------------------------------*/
void	CPluginLibrary::FinalRelease
		(
		void
		)
{
	LOCAL_PRINT( "%s\n", __FUNCTION__ );
	inherited::FinalRelease();
}

#endif	// _DEBUG


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

