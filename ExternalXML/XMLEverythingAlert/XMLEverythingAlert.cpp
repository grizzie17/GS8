/*---------------------------------------------------------------------+\
|
|	XMLEverythingAlert.cpp  --  Plugin to process touch screen points
|
|	Purpose:
|
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
	08-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Major cleanup to protect from generating bogus matrix
	04-Aug-2010			J.Griswold		(Reviewed by: xxxx)
        Fixed overflow problem when calculating touch matrix
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "XMLEverythingAlert.h"

#include "UPlatform.h"

#include "VPluginFactory.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

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
PLUGIN_CREATE_FACTORY( XMLEverythingAlert );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * XMLEverythingAlert - constructor

\+---------------------------------------------------------------------*/
XMLEverythingAlert::XMLEverythingAlert
		(
		void
		)
		: VPluginExternalXML()
		, m_nAlertCount( 0 )
{
}

XMLEverythingAlert::XMLEverythingAlert
		(
		ISupportsPtr	pOwner
		)
		: VPluginExternalXML( pOwner )
		, m_pDictionary( 0 )
		, m_nAlertCount( 0 )
{
}

XMLEverythingAlert::XMLEverythingAlert
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginExternalXML( sName, pOwner )
		, m_pDictionary( 0 )
		, m_nAlertCount( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~XMLEverythingAlert - destructor

\+---------------------------------------------------------------------*/
XMLEverythingAlert::~XMLEverythingAlert
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

void	XMLEverythingAlert::WriteLine
		(
		const char*	s
		)
{
	AppendData( s );
	AppendData( "\n" );
}


void	XMLEverythingAlert::WriteString
		(
		const char*	s
		)
{
	AppendData( s );
}



void	XMLEverythingAlert::WriteHeader
		(
		void
		)
{
	m_nAlertCount = 0;

	WriteLine( "<?xml version=\"1.0\"?>" );
	WriteLine(
		"<SimBase.Document Type=\"AceXML\" version=\"1,0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"Gauges.xsd\">" );

	WriteLine( "<SimGauge.Gauge id=\"alert-everything\">" );
	WriteLine( "<Update>" );
	WriteLine( "<Script>" );
	WriteLine( "height s0" );
	WriteLine( "</Script>" );
	WriteLine( "<Frequency>2</Frequency>" );
	WriteLine( "</Update>" );
	WriteLine( "<Element>" );
	WriteLine( "<Visibility>(N:Alerts Active) (U:FLASH) AND</Visibility>" );
}



void	XMLEverythingAlert::WriteFooter
		(
		void
		)
{
	WriteLine( "</Element>" );

	CCharString	t;

	t.Format( "<Size>400,%ld</Size>", m_nAlertCount * 24 );

	WriteLine( t.Pointer() );

	WriteLine( "</SimGauge.Gauge>" );
	WriteLine( "</SimBase.Document>" );
	AppendData( "\0", 1 );

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
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	XMLEverythingAlert::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginExternalXML::Load( pConfig, pLib );

	return bResult;
}

/*---------------------------------------------------------------------+\
|	IExternalXML
\+---------------------------------------------------------------------*/


bool	XMLEverythingAlert::Initialize
		(
		IExternalXMLServerPtr p
		)
{
	bool	bResult = VPluginExternalXML::Initialize( p );

	m_pDictionary = m_pApplication->Dictionary();

	return bResult;
}


typedef struct XAlert
{
	long			nLevel;
	CCharStringPtr	pName;

	XAlert() : nLevel( 0 ), pName( 0 ) {};
	XAlert( const XAlert& r )
		: nLevel( r.nLevel ),
		pName( r.pName )
	{
	}
	~XAlert()
	{
		//if ( pName )
		//	delete pName;
	};

	bool	operator < ( const XAlert& r )
	{
		if ( nLevel > r.nLevel )
			return true;
		else if ( r.nLevel > nLevel )
			return false;

		if ( 0 >= pName->CompareIgnoreCase( *r.pName ) )
			return false;

		return true;
	}

	XAlert&	operator = ( const XAlert& r )
	{
		pName = r.pName;
		nLevel = r.nLevel;
		return *this;
	}
} XAlert;



XMLLite::VReadCallBack*
		XMLEverythingAlert::GetCallBack
		(
		ConstCCharDescriptorRef	//rArg
		)
{
	VDictionaryEnumerator*	pEnum = m_pApplication->Dictionary()->GetPageEnumerator( 'N' );
	if ( pEnum )
	{
		WriteHeader();


		TArray<XAlert>	aList;

		CCharString	sName;

		while ( pEnum->MoveNext() )
		{
			sName = pEnum->Key();

			if ( sName != "Alerts Active" )
			{
				XAlert	x;
				x.pName = new CCharString( sName );

				CCharString	sLevel;
				sLevel.Format( "B:%s.Level", sName.Pointer() );

				VDictionary::Selector	sel = m_pDictionary->LocateEntry( sLevel );
				if ( sel )
				{
					ConstCVariantDataPtr	pv;
					pv = m_pDictionary->GetData( sel );
					if ( pv )
					{
						x.nLevel = *pv;
					}
				}

				aList.AppendData( &x );
			}
		}

		aList.Sort();

		m_nPosition = 0;
		m_nAlertCount = 0;

		XAlert*	px = aList.PointArray();
		XAlert*	pxEnd = px + aList.Length();

		while ( px < pxEnd )
		{
			++m_nAlertCount;

			WriteLine( "<Element Context='foreground'>" );
			WriteLine( "<Position X='0' Y='0' />" );

			m_nPosition += 24;
			WriteLine( "<Element>" );

			CCharString	sTemp;
			sTemp.Format( "<Visibility>(N:%s)</Visibility>\n", px->pName->Pointer() );
			WriteLine( sTemp.Pointer() );
			WriteString( "<GaugeText " );
			WriteString( "X='0' Y='r0 24 - s0' " );
			WriteString( "VerticalAlign='top' " );
			WriteString( "Font='sans-serif' Height='24' " );

			sTemp.Format( "Color=\"(B:%s.Color)\" ", px->pName->Pointer() );
			WriteString( sTemp.Pointer() );

			WriteLine( ">" );
			WriteString( "<String>" );
			WriteString( px->pName->Pointer() );
			WriteLine( "</String>" );
			WriteLine( "</GaugeText>" );
			WriteLine( "</Element>" );

			WriteLine( "</Element>" );

			++px;
		}
		px = aList.PointArray();
		pxEnd = px + aList.Length();
		while ( px < pxEnd )
		{
			delete px->pName;
			++px;
		}

		WriteFooter();

		//CCharString	sFilename = BuildPath( "XMLEverythingAlert" );
		//SaveData( sFilename.Pointer() );


		delete pEnum;
	}


	return (VReadCallBack*)this;
}


void	XMLEverythingAlert::ReleaseCallBack
		(
		XMLLite::VReadCallBack*	//p
		)
{
}






}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
