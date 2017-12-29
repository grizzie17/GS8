/*---------------------------------------------------------------------+\
|
|	VPluginExternalXML.cpp  --  base class for command plugins
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
	28-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VPluginExternalXML.h"

NAMESPACE_GADGET_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * VPluginExternalXML - constructor

\+---------------------------------------------------------------------*/
VPluginExternalXML::VPluginExternalXML
		(
		void
		)
		: inherited(),
		m_sID(),
		m_pApplication( 0 ),
		m_sData()
{
	m_sData.SetBlockSize( 1024 );
}

VPluginExternalXML::VPluginExternalXML
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_sID(),
		m_pApplication( 0 ),
		m_sData()
{
}

VPluginExternalXML::VPluginExternalXML
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_sID(),
		m_pApplication( 0 ),
		m_sData()
{
}

/*---------------------------------------------------------------------+\

 * ~VPluginExternalXML - destructor

\+---------------------------------------------------------------------*/
VPluginExternalXML::~VPluginExternalXML
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\
|	IApplicationUser
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	VPluginExternalXML::SetApplication
		(
		CApplicationGaugePtr	p	// IN:	application pointer
		)
{
	m_pApplication = p;
	return true;
}



/*----------------------------------------------------------------------+\
|	IExternalXML
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	VPluginExternalXML::Initialize
		(
		IExternalXMLServerPtr pIExt
		)
{
	m_nDataIndex = 0;
	return pIExt->Register( m_sID.Pointer(), ROOT_ISUPPORTS(this) );
}


/*---------------------------------------------------------------------+\

 * GetCallBack -

\+---------------------------------------------------------------------*/


XMLLite::VReadCallBack*
		VPluginExternalXML::GetCallBack
		(
		const char*	sArg
		)
{
	CCharDescriptor	tArg( sArg );

	return GetCallBack( tArg );
}

XMLLite::VReadCallBack*
		VPluginExternalXML::GetCallBack
		(
		ConstCCharDescriptorRef	//rArg
		)
{
	return 0;
}

/*---------------------------------------------------------------------+\

 * ReleaseCallBack -

\+---------------------------------------------------------------------*/
void	VPluginExternalXML::ReleaseCallBack
		(
		XMLLite::VReadCallBack*	//p
		)
{
}


/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	VPluginExternalXML::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	m_sID = pConfig->GetID();
	return inherited::Load( pConfig, pLib );
}



/*----------------------------------------------------------------------+\
|	XMLLite::VReadCallBack
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
size_t	VPluginExternalXML::Read		// RTN:	returns number of bytes actually read
		(
		void*			pBuffer,		// OUT: buffer to receive data
		size_t			nBytesToRead,	// IN:	number of bytes to read
		XMLLite::ETEXT_FORMAT	//eFmt	// IN:	target format
		)
{
	size_t	nResult = 0;

	if ( pBuffer  &&  0 < nBytesToRead )
	{
		char*	p = m_sData.PointArray( m_nDataIndex );
		index_t	n = (index_t)m_sData.Length() - m_nDataIndex;

		nResult = umin( nBytesToRead, static_cast<size_t>(n) );

		m_nDataIndex += nResult;

		memcpy( pBuffer, p, nResult );

	}
	return nResult;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
/*
	Gets the size of the file (stream)
*/
size_t	VPluginExternalXML::GetSize		// RTN:	return file (stream) size in bytes
		(
		void
		)
{
	return m_sData.Length();
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
/*
	Get a name associated with the call-back stream.
	For files this should be name of the file or
	at least a partial path with name.
*/
size_t	VPluginExternalXML::GetName		// RTN:	string length of name
		(
		char*			sTarget,	// OUT:	buffer to receive name
		size_t			nSizeTarget	// IN:	size of target
		)
{
	if ( sTarget )
		m_sID.CopyTo( sTarget, nSizeTarget );
	return m_sID.Length();;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	VPluginExternalXML::AppendData
		(
		const char *s
		)
{
	size_t	n = ::strlen( s );
	AppendData( s, n );
}

void	VPluginExternalXML::AppendData
		(
		const char *s,
		size_t		n
		)
{
	size_t	j = m_sData.Length();
	m_sData.LoadDataAt( (index_t)j, s, n );
}




/*---------------------------------------------------------------------+\

 * SaveData -

\+---------------------------------------------------------------------*/
bool	VPluginExternalXML::SaveData
		(
		const char*	sFilePath
		)
{
	bool	bResult = false;

	if ( sFilePath )
	{
#ifdef _DEBUG
		FILE*	pf;

		if ( 0 == fopen_s( &pf, sFilePath, "w" ) )
		{
			fwrite( m_sData.PointArray(), 1, m_sData.Length(), pf );
			fclose( pf );
			bResult = true;
		}
#endif // _DEBUG
	}
	return bResult;

}






/*---------------------------------------------------------------------+\

 * BuildPath -

\+---------------------------------------------------------------------*/
CCharString
		VPluginExternalXML::BuildPath
		(
		const char*	sFilename
		)
{
	char		sPath[1024];
	CCharString	sUserID;
	CCharString	sName;

	const char*	s = GetUserConfigFolder();

	sUserID = m_pApplication->GetUserID();

	sName.Format( "%s%s.txt",
				sFilename,
				(0 < sUserID.Length() ? sUserID.Pointer() : "") );

	PathBuild( sPath, sizeof(sPath), s, sName.Pointer() );

	return CCharString( sPath );
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
void*	VPluginExternalXML::FindInternalInterface
		(
		ConstIXIDRef rIID
		)
{
	void*	p = inherited::FindInternalInterface( rIID );
	if ( p )
		return p;

	if ( rIID == IXID_IApplicationUser )
		return INTERFACE_THIS( IApplicationUserPtr );
	else if ( rIID == IXID_IExternalXML )
		return INTERFACE_THIS( IExternalXMLPtr );
	else
		return 0;
}


NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

