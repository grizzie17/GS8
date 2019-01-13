/*---------------------------------------------------------------------+\
|
|	VFactoryLite.cpp  --  brief description of what VFactoryLite.cpp is for
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the psuedo-interface VVariable
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	15-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add looking for GaugeXML folder in a application relative
		location if the GAUGEXML environment variable does not exist.
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Conversion to new hierarcy that uses the XMLParser as the
		base class
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Convert to getenv_s to resolve compiler MSVC
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	09-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change EatNode so it can be called whether for begin node or not.
		Change hierarchy
	02-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision - copy of previous VFactory
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "VFactoryLite.h"

#include "UMachine.h"
#include "LogFile.h"
#include "UPlatform.h"
#include "IExternalXML.h"

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

 * VFactoryLite - constructor

\+---------------------------------------------------------------------*/
VFactoryLite::VFactoryLite
		(
		void
		)
		: VFactory()
		, m_sRelativePath()
		, m_pVariable( 0 )
		, m_pIExternalXML( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~VFactoryLite - destructor

\+---------------------------------------------------------------------*/
VFactoryLite::~VFactoryLite
		(
		void
		)
{
	if ( m_pIExternalXML )
		m_pIExternalXML->Release();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


void	VFactoryLite::SetRelativePath
		(
		const char *s
		)
{
	m_sRelativePath = s;
}


Yogi::Core::CCharString
		VFactoryLite::GetRelativePath
		(
		void
		)
{
	return m_sRelativePath;
}


void	VFactoryLite::SetVariableIF
		(
		VVariablePtr p
		)
{
	m_pVariable = p;
}


void	VFactoryLite::SetExternalXMLIF
		(
		ISupportsPtr p
		)
{
	IExternalXMLPtr	pPrev = m_pIExternalXML;
	if ( p )
		m_pIExternalXML = QI_( p, IExternalXML );
	else
		m_pIExternalXML = 0;

	if ( pPrev )
		pPrev->Release();
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * OpenFile -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	VFactoryLite::OpenFile
		(
		const char*	s
		)
{
	bool		bResult = false;
	Yogi::Core::CCharString	sName;


	if ( m_pVariable )
	{
		CVariables	var( m_pVariable );
		sName = var.Substitute( Yogi::Core::CCharDescriptor( (char*)s ) );
	}
	else
	{
		sName = s;
	}

	LOCAL_PRINT( "VFactoryLite::OpenFile = %s\n", sName.Pointer());

	if ( '@' == *sName.Pointer() )
	{
		if ( m_pIExternalXML )
		{
			XMLLite::VReadCallBack*	pReader = 0;

			pReader = m_pIExternalXML->GetCallBack( sName );
			if ( pReader )
			{
				bResult = ProcessCallBack( pReader );
				m_pIExternalXML->ReleaseCallBack( pReader );
			}
			else
			{
				Yogi::Core::LogPrint( "VFactoryLite::OpenFile - unable to access external data - '%s'\n", sName.Pointer() );
			}
		}
		else
		{
			Yogi::Core::LogPrint( "VFactoryLite::OpenFile - External XML reference but no handler specified\n" );
		}
	}
	else
	{
		Yogi::Core::CCharString	sFilePath = BuildFilePath( sName.Pointer() );

		XMLLite::CReadFile reader;

		bResult = reader.Open( sFilePath.Pointer() );
		if ( bResult )
		{
			bResult = ProcessCallBack( &reader );
			if ( bResult )
				reader.Close();		// the read actually took place in the previous call
		}
		else
		{
			Yogi::Core::LogPrint( "VFactoryLite::OpenFile - unable to open xml file \n'%s'\n", sFilePath.Pointer() );
		}
	}


	return bResult;
}

//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * BuildFilePath -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

Yogi::Core::CCharString
		VFactoryLite::BuildFilePath
		(
		const char*	sName
		)
{
	char	sTemp[1024] = { 0 };
//	size_t	nTemp;

	char	cSep = FOLDER_SEPARATOR;
	char	cOtherSep;
	if ( cSep == '/' )
		cOtherSep = '\\';
	else
		cOtherSep = '/';

	//if ( 0 != getenv_s( &nTemp, sTemp, sizeof(sTemp), "GAUGEXML" ) )
	//	sTemp[0] = 0;

	if ( ! sTemp[0] )
	{
		const char*	sa = ApplicationFolder();
		if ( sa )
		{
			::strcpy_s( sTemp, sizeof(sTemp), sa );
		}
	}
	if ( sTemp[0] )
	{
		char*	s = sTemp;
		char*	sEnd = s + ::strlen( s );

		if ( cSep != *(sEnd-1)  &&  cOtherSep != *(sEnd-1) )
		{
			*sEnd++ = cSep;
			*sEnd = '\0';
		}

		m_sRelativePath.ConcatenateTo( sTemp, sizeof(sTemp) );

		sEnd = s + ::strlen( s );
		*sEnd++ = cSep;
		*sEnd = '\0';

		::strcat_s( sTemp, sizeof(sTemp), sName );
		sEnd = s + ::strlen(s);
		if ( 0 != ::_stricmp( sEnd - 4, ".xml" ) )
			::strcat_s( sTemp, sizeof(sTemp), ".xml" );

		while ( s < sEnd )
		{
			if ( cOtherSep == *s )
				*s = cSep;
			++s;
		}
	}

	return Yogi::Core::CCharString( sTemp );
}

//END_OVERRUN_WARNING





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
