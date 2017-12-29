/*---------------------------------------------------------------------+\
|
|	XMLEverythingColor.cpp  --  Plugin to process touch screen points
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
#include "XMLEverythingColor.h"

#include "UPlatform.h"
#include "UPlatformString.h"

#include "VPluginFactory.h"
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
XMLEverythingColor::SORTFIELD	g_eSort = XMLEverythingColor::SORT_HUE;



/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
static char	g_sWhite[] = "white";
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
PLUGIN_CREATE_FACTORY( XMLEverythingColor );



/*=====================================================================+\
||	 ColorEntry functions
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * ColorEntry::operator [LT] -

\+---------------------------------------------------------------------*/
bool	XMLEverythingColor::ColorEntry::operator <
		(
		const ColorEntry&	b
		)
{
	bool	bResult = false;

	if ( SORT_HUE == g_eSort )
	{
		int		aHue = hsl.hue / (256 / 32);
		int		bHue = b.hsl.hue / (256 / 32);
		if ( 29 <= aHue )
			aHue -= 32;
		if ( 29 <= bHue )
			bHue -= 32;
		if ( aHue < bHue )
			bResult = true;
		//if ( hsl.hue < b.hsl.hue )
		//	bResult = true;
	}
	else if ( SORT_LIGHT == g_eSort )
	{
		if ( hsl.light < b.hsl.light )
			bResult = true;
	}
	else // SORT_SATURATION
	{
		if ( hsl.saturation < b.hsl.saturation )
			bResult = true;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ColorEntry::operator = -

\+---------------------------------------------------------------------*/
XMLEverythingColor::ColorEntry&
		XMLEverythingColor::ColorEntry::operator =
		(
		const ColorEntry&	r
		)
{
	data.sName = r.data.sName;
	data.value.red = r.data.value.red;
	data.value.green = r.data.value.green;
	data.value.blue = r.data.value.blue;
	hsl.hue = r.hsl.hue;
	hsl.saturation = r.hsl.saturation;
	hsl.light = r.hsl.light;
	return *this;
}




/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * XMLEverythingColor - constructor

\+---------------------------------------------------------------------*/
XMLEverythingColor::XMLEverythingColor
		(
		void
		)
		: VPluginExternalXML(),
		m_pDictionary( 0 )
{
}

XMLEverythingColor::XMLEverythingColor
		(
		ISupportsPtr	pOwner
		)
		: VPluginExternalXML( pOwner ),
		m_pDictionary( 0 )
{
}

XMLEverythingColor::XMLEverythingColor
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginExternalXML( sName, pOwner ),
		m_pDictionary( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~XMLEverythingColor - destructor

\+---------------------------------------------------------------------*/
XMLEverythingColor::~XMLEverythingColor
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






void	XMLEverythingColor::WriteLine
		(
		const char*	s
		)
{
	AppendData( s );
	AppendData( "\n" );
}


void	XMLEverythingColor::WriteString
		(
		const char*	s
		)
{
	AppendData( s );
}



void	XMLEverythingColor::WriteHeader
		(
		void
		)
{

	WriteLine( "<?xml version=\"1.0\"?>" );
	WriteLine(
		"<SimBase.Document Type=\"AceXML\" version=\"1,0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"Gauges.xsd\">" );

	WriteLine(
		"<SimGauge.Gauge id=\"everything-color\">" );

}





/*---------------------------------------------------------------------+\

 * WriteColorEntry -

\+---------------------------------------------------------------------*/
void	XMLEverythingColor::WriteColorEntry
		(
		ColorEntry*	pe,
		long		nCol,
		long		nRow
		)
{
	char	sBuf[128];

	sprintf_s( sBuf, sizeof(sBuf), "<Rectangle X='%ld' Y='%ld' ", nCol, nRow );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "%s", "Height='18' Width='18' " );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "FillColor='%s' />\n", pe->data.sName );
	WriteString( sBuf );

	sprintf_s( sBuf, sizeof(sBuf), "<GaugeText X='%ld' Y='%ld' ", nCol + 22, nRow );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "LineColor='%s' ", (pe->hsl.light < 90) ? g_sWhite : pe->data.sName );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "Font='sans-serif' Height='18' " );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "VerticalAlign='top' >\n" );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "<String>%s</String>\n", pe->data.sName );
	WriteString( sBuf );
	sprintf_s( sBuf, sizeof(sBuf), "</GaugeText>\n" );
	WriteString( sBuf );
}




/*---------------------------------------------------------------------+\

 * WriteKeyMap -

\+---------------------------------------------------------------------*/
void	XMLEverythingColor::WriteKeyMap
		(
		void
		)
{
	WriteLine("<KeyMap>" );

	WriteLine("<Trigger>");
	WriteLine("<KeyEvent>E:MOVE LEFT</KeyEvent>");
	WriteLine("<Script>(G:XPOSITION) 175 + 0 min (=G:XPOSITION)</Script>");
	WriteLine("</Trigger>");

	WriteLine("<Trigger>");
	WriteLine("<KeyEvent>E:MOVE RIGHT</KeyEvent>");
	WriteLine("<Script>(G:XPOSITION) 175 - (=G:XPOSITION)</Script>");
	WriteLine("</Trigger>");

	WriteLine("<Trigger>");
	WriteLine("<KeyEvent>E:MOVE HOME</KeyEvent>");
	WriteLine("<Script>0 (=G:XPOSITION)</Script>");
	WriteLine("</Trigger>");

	WriteLine( "</KeyMap>" );
}





void	XMLEverythingColor::WriteActive
		(
		void
		)
{
	int		nLineSpacing = 19;
	int		nColumnWidth = 175;
	int		nPageHeight = 610;
	int		nMargin = 4;

	TArray<ColorEntry>	aGrays;
	TArray<ColorEntry>	aPureGrays;
	TArray<ColorEntry>	aColors;

	CColorEnumerator	clrs = CColor::GetEnumerator();

	WriteLine( "<Element Context='background'>" );
	WriteLine( "<Position X='(G:XPOSITION)' Y='(G:YPOSITION)' />");

	while ( clrs.MoveNext() )
	{
		const ColorName*	p = clrs.Current();
		ColorEntry	e;
		e.data = *p;
		CColor::HSLfromRGB( &e.hsl, &e.data.value );
		if ( e.hsl.saturation < 4 )
		{
			aPureGrays.AppendData( &e );
		}
		else
		{
			aColors.AppendData( &e );

			if ( e.hsl.light < 24 )
				aGrays.AppendData( &e );
			else if ( 256 - 24 < e.hsl.light )
				aGrays.AppendData( &e );
			else if ( e.hsl.saturation < 32 )
				aGrays.AppendData( &e );
			else if ( e.hsl.saturation < 64
					&&  256 - 48 < e.hsl.light )
				aGrays.AppendData( &e );
			else if ( e.hsl.saturation < 16*3
					&&	256 - 80 < e.hsl.light )
				aGrays.AppendData( &e );
		}
	}
	g_eSort = SORT_LIGHT;
	aPureGrays.Sort();

	g_eSort = SORT_HUE;
	aGrays.Sort();
	g_eSort = SORT_SATURATION;
	aGrays.Sort();
	g_eSort = SORT_LIGHT;
	aGrays.Sort();

	g_eSort = SORT_SATURATION;
	aColors.Sort();
	g_eSort = SORT_LIGHT;
	aColors.Sort();
	g_eSort = SORT_HUE;
	aColors.Sort();


	int	nCol;
	int	nRow;

	nCol = nMargin;
	nRow = nMargin;

	ColorEntry*	pe = aPureGrays.PointArray();
	ColorEntry*	peEnd = pe + aPureGrays.Length();

	while ( pe < peEnd )
	{
		WriteColorEntry( pe, nCol, nRow );

		nRow += nLineSpacing;

		if ( nPageHeight < nRow )
		{
			nRow = nMargin;
			nCol += nColumnWidth;
		}

		++pe;
	}

	nRow += nLineSpacing * 2;
	if ( nPageHeight < nRow )
	{
		nRow = nMargin;
		nCol += nColumnWidth;
	}

	pe = aGrays.PointArray();
	peEnd = pe + aGrays.Length();

	while ( pe < peEnd )
	{
		WriteColorEntry( pe, nCol, nRow );

		nRow += nLineSpacing;

		if ( nPageHeight < nRow )
		{
			nRow = nMargin;
			nCol += nColumnWidth;
		}

		++pe;
	}

	nRow += nLineSpacing * 2;

	if ( nPageHeight < nRow )
	{
		nRow = nMargin;
		nCol += nColumnWidth;
	}

	pe = aColors.PointArray();
	peEnd = pe + aColors.Length();

	while ( pe < peEnd )
	{
		WriteColorEntry( pe, nCol, nRow );

		nRow += nLineSpacing;

		if ( nPageHeight < nRow )
		{
			nRow = nMargin;
			nCol += nColumnWidth;
		}

		++pe;
	}
	WriteLine( "</Element>" );




}



void	XMLEverythingColor::WriteFooter
		(
		void
		)
{

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
bool	XMLEverythingColor::Load
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


bool	XMLEverythingColor::Initialize
		(
		IExternalXMLServerPtr p
		)
{
	bool	bResult = VPluginExternalXML::Initialize( p );

	m_pDictionary = m_pApplication->Dictionary();

	return bResult;
}


XMLLite::VReadCallBack*
		XMLEverythingColor::GetCallBack
		(
		ConstCCharDescriptorRef	//rArg
		)
{
	WriteHeader();
	WriteActive();
	WriteKeyMap();
	WriteFooter();

	return (VReadCallBack*)this;
}


void	XMLEverythingColor::ReleaseCallBack
		(
		XMLLite::VReadCallBack*	//p
		)
{
}





NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

