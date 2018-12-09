/*---------------------------------------------------------------------+\
|
|	XMLEverythingGauge.cpp  --  Plugin to process touch screen points
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
#include "XMLEverythingGauge.h"

#include "UPlatform.h"
#include "UPlatformString.h"

#include "VPluginFactory.h"

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
PLUGIN_CREATE_FACTORY( XMLEverythingGauge );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * XMLEverythingGauge - constructor

\+---------------------------------------------------------------------*/
XMLEverythingGauge::XMLEverythingGauge
		(
		void
		)
		: VPluginExternalXML(),
		m_nAlertCount( 0 ),
		m_sBuffer()
{
}

XMLEverythingGauge::XMLEverythingGauge
		(
		ISupportsPtr	pOwner
		)
		: VPluginExternalXML( pOwner ),
		m_pDictionary( 0 ),
		m_nAlertCount( 0 ),
		m_sBuffer()
{
}

XMLEverythingGauge::XMLEverythingGauge
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginExternalXML( sName, pOwner ),
		m_pDictionary( 0 ),
		m_nAlertCount( 0 ),
		m_sBuffer()
{
}



/*---------------------------------------------------------------------+\

 * ~XMLEverythingGauge - destructor

\+---------------------------------------------------------------------*/
XMLEverythingGauge::~XMLEverythingGauge
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

void	XMLEverythingGauge::BufferAppend
		(
		const char *s
		)
{
	size_t	c = ::strlen( s );
	size_t	n = m_sBuffer.Length();
	m_sBuffer.LoadDataAt( (index_t)n, s, c );
}



void	XMLEverythingGauge::BufferLine
		(
		const char*	s
		)
{
	BufferAppend( s );
	BufferAppend( "\n" );
}


void	XMLEverythingGauge::BufferString
		(
		const char*	s
		)
{
	BufferAppend( s );
}

void	XMLEverythingGauge::BufferString
		(
		ConstCCharStringRef r
		)
{
	BufferAppend( r.Pointer() );
}





void	XMLEverythingGauge::WriteLine
		(
		const char*	s
		)
{
	AppendData( s );
	AppendData( "\n" );
}


void	XMLEverythingGauge::WriteString
		(
		ConstCCharStringRef	s
		)
{
	AppendData( s.Pointer() );
}


void	XMLEverythingGauge::WriteString
		(
		const char*	s
		)
{
	AppendData( s );
}



void	XMLEverythingGauge::WriteHeader
		(
		void
		)
{
	m_nAlertCount = 0;

	WriteLine( "<?xml version=\"1.0\"?>" );
	WriteLine(
		"<SimBase.Document Type=\"AceXML\" version=\"1,0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"Gauges.xsd\">" );

	WriteLine(
		"<SimGauge.Gauge id=\"everything\">" );
	WriteLine(  "<Element>" );

}


		typedef struct XEverything
		{
			long			nLevel;
			CCharStringPtr	pName;

			XEverything() : nLevel( 0 ), pName( 0 ) {};
			XEverything( const XEverything& r )
				: nLevel( r.nLevel ),
				pName( r.pName )
			{
			}
			~XEverything()
			{
				//if ( pName )
				//	delete pName;
			};

			void	SetName( ConstCCharDescriptorRef rName )
			{
				if ( pName )
					delete pName;
				pName = new CCharString( rName );
			}

			bool	operator < ( const XEverything& r )
			{
				//if ( nLevel > r.nLevel )
				//	return true;
				//else if ( r.nLevel > nLevel )
				//	return false;

				if ( 0 < pName->CompareIgnoreCase( *r.pName ) )
					return false;

				return true;
			}

			XEverything&	operator = ( const XEverything& r )
			{
				pName = r.pName;
				nLevel = r.nLevel;
				return *this;
			}
		} XEverything;

void	XMLEverythingGauge::WriteAlerts
		(
		void
		)
{
	VDictionaryEnumerator*	pEnum = m_pApplication->Dictionary()->GetPageEnumerator( 'N' );
	if ( pEnum )
	{


		TArray<XEverything>	aList;

		CCharString	sName;

		while ( pEnum->MoveNext() )
		{
			sName = pEnum->Key();

			if ( sName != "Alerts Active" )
			{
				XEverything	x;
				x.SetName( sName );

				CCharString	sLevel;
				sLevel.Format( "B:%s.Level", sName.Pointer() );

				VDictionary::Selector	sel = m_pDictionary->LocateEntry( sLevel );
				if ( sel )
				{
					CVariantDataPtr	pv;
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



		WriteLine( "<Element Context='background'>" );
		WriteLine( "<Position X='0' Y='0' />" );
		WriteLine( "<Line LineColor='gray' LineWidth='1'>" );
		WriteLine( "<Point X='0' Y='0' />" );
		WriteLine( "<Point X='0' Y='600' />" );
		WriteLine( "</Line>" );
		m_nPosition = 0;


		XEverything*	px = aList.PointArray();
		XEverything*	pxEnd = px + aList.Length();


		CCharString	sTemp;
		while ( px < pxEnd )
		{

			++m_nAlertCount;


			m_nPosition += 18;
			WriteString(  "<GaugeText " );

			sTemp.Format( "X='10' Y='%ld' ", m_nPosition );
			WriteString( sTemp );
			WriteString( "Font='sans-serif' Height='18' " );

			sTemp.Format( "B:%s.Color", px->pName->Pointer() );

			VDictionary::Selector	sel;

			sel = m_pDictionary->LocateEntry( sTemp );
			if ( sel )
			{
				sTemp.Format( "Color=\"(B:%s.Color) 'white' (N:%s) ?\" ", px->pName->Pointer(), px->pName->Pointer() );
			}
			else
			{
				sTemp.Format( "Color=\"'red' 'white' (N:%s) ?\" ", px->pName->Pointer() );
			}

			WriteString( sTemp );
			WriteLine( ">\n" );
			WriteString( "<String>" );
			WriteString( px->pName->Pointer() );
			WriteLine( "</String>\n" );
			WriteLine( "</GaugeText>\n" );

			++px;

		}

		px = aList.PointArray();
		pxEnd = px + aList.Length();
		while ( px < pxEnd )
		{
			delete px->pName;
			++px;
		}

		WriteLine( "</Element>" );

		delete pEnum;
	}


}



		typedef struct XParam
		{
			long			nLevel;
			CCharStringPtr	pName;

			XParam() : nLevel( 0 ), pName( 0 ) {};
			XParam( const XParam& r )
				: nLevel( r.nLevel ),
				pName( r.pName )
			{
			}
			~XParam()
			{
				//if ( pName )
				//	delete pName;
			};

			void	SetName( ConstCCharDescriptorRef rName )
			{
				if ( pName )
					delete pName;
				pName = new CCharString( rName );
			}

			bool	operator < ( const XParam& r )
			{
				//if ( nLevel > r.nLevel )
				//	return true;
				//else if ( r.nLevel > nLevel )
				//	return false;

				if ( 0 < pName->CompareIgnoreCase( *r.pName ) )
					return false;

				return true;
			}

			XParam&	operator = ( const XParam& r )
			{
				pName = r.pName;
				nLevel = r.nLevel;
				return *this;
			}
		} XParam;


void	XMLEverythingGauge::WriteActive
		(
		void
		)
{
	VDictionaryEnumerator*	pEnum = m_pApplication->Dictionary()->GetPageEnumerator( 'A' );
	if ( pEnum )
	{



		TArray<XParam>	aList;

		CCharString	sName;

		while ( pEnum->MoveNext() )
		{
			sName = pEnum->Key();

			XParam	x;
			x.SetName( sName );


			aList.AppendData( &x );
		}

		aList.Sort();



		WriteLine( "<Element>" );
		WriteLine( "<Position X='375' Y='0' />" );
		WriteLine( "<Line LineColor='gray' LineWidth='1'>" );
		WriteLine( "<Point X='0' Y='0' />" );
		WriteLine( "<Point X='0' Y='600' />" );
		WriteLine( "</Line>" );

		BufferLine( "<Element Context='foreground'>" );
		BufferLine( "<Position X='250' Y='0' />" );

		WriteLine( "<Element Context='background'>" );
		WriteLine( "<Position X='10' Y='0' />" );

		XParam*	px = aList.PointArray();
		XParam*	pxEnd = px + aList.Length();

		m_nPosition = 0;

		CCharString	tColorRange;
		CCharString	sTemp;
		char		sWorking[128];
		while ( px < pxEnd )
		{
			tColorRange = "white";



			m_nPosition += 24;
			//::fprintf( m_pOutfile,  );
			WriteString( "<GaugeText " );
			sTemp.Format( "X='0' Y='%ld' ", m_nPosition );
			WriteString( sTemp );
			WriteString( "Font='sans-serif' Height='24' " );
			sTemp.Format( "Color=\"%s\" ", tColorRange.Pointer() );
			WriteString( sTemp );
			WriteString( ">\n" );
			WriteString( "<String>" );
			WriteString( px->pName->Pointer() );
			WriteString( "</String>\n" );
			WriteLine( "</GaugeText>" );
			//::fprintf( m_pOutfile, "</Element>\n" );




			BufferString( "<GaugeText " );
			sprintf_s( sWorking, sizeof(sWorking), "X='0' Y='%ld' ", m_nPosition );
			BufferString( sWorking );
			BufferString( "Font='sans-serif' Height='24' " );
			sprintf_s( sWorking, sizeof(sWorking), "Color=\"%s\" ", tColorRange.Pointer() );
			BufferString( sWorking );
			BufferLine( ">" );

			CVariantData::V_TYPE	eType = CVariantData::T_STRING;
			sTemp.Format( "A:%s", px->pName->Pointer() );

			VDictionary::Selector	sel = m_pDictionary->LocateEntry( sTemp );
			if ( sel )
			{
				CVariantDataPtr	pv;
				pv = m_pDictionary->GetData( sel );
				if ( pv )
				{
					eType = pv->GetType();
				}
			}


			BufferString( "<String>" );
			if ( CVariantData::T_BOOL == eType )
			{
				sTemp.Format( "%%('true' 'false' (A:%s) ?)%%!s!", px->pName->Pointer() );
				BufferString( sTemp );
			}
			else
			{
				sTemp.Format( "%%((A:%s))%%", px->pName->Pointer() );
				BufferString( sTemp );
				switch ( eType )
				{
				case CVariantData::T_BOOL:
				case CVariantData::T_INTEGER:
					BufferString( "!d!" );
					break;
				case CVariantData::T_FLOAT:
					BufferString( "!3.4f!" );
					break;
				case CVariantData::T_DATETIME:
					BufferString( "!t!" );
					break;
				case CVariantData::T_STRING:
				default:
					BufferString( "!s!" );
					break;
				}
			}
			BufferString( "</String>" );
			BufferLine( "</GaugeText>" );

			++px;
		}

		WriteLine( "</Element>" );	// background

		BufferLine( "</Element>" );
		AppendData( m_sBuffer.PointArray(), m_sBuffer.Length() );	// foreground
		WriteLine( "</Element>" );

		px = aList.PointArray();
		pxEnd = px + aList.Length();
		while ( px < pxEnd )
		{
			delete px->pName;
			++px;
		}


		//CCharString	sFilename = BuildPath( "XMLEverythingGauge" );
		//SaveData( sFilename.Pointer() );

		delete pEnum;
	}

}



void	XMLEverythingGauge::WriteFooter
		(
		void
		)
{
	WriteLine( "</Element>" );

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
bool	XMLEverythingGauge::Load
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


bool	XMLEverythingGauge::Initialize
		(
		IExternalXMLServerPtr p
		)
{
	bool	bResult = VPluginExternalXML::Initialize( p );

	m_pDictionary = m_pApplication->Dictionary();

	return bResult;
}


XMLLite::VReadCallBack*
		XMLEverythingGauge::GetCallBack
		(
		ConstCCharDescriptorRef	//rArg
		)
{
	WriteHeader();
	WriteAlerts();
	WriteActive();
	WriteFooter();

	return (VReadCallBack*)this;
}


void	XMLEverythingGauge::ReleaseCallBack
		(
		XMLLite::VReadCallBack*	//p
		)
{
}





}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
