/*---------------------------------------------------------------------+\
|
|	CColor.cpp  --  brief description of what CColor.cpp is for
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
	02-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		add new function that will accept a color-long value
		that represents its data in 0x00RRGGBB
	19-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add an enumerator for the colors
		Add some new color names
		Dispose of some color names that were essentially duplicates
		based on values.
		Add new HSLfromRGB function that will give back a
		hue, saturation, lumen representation of the color
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Major change to CColor so that we can handle alpha-channel.
		Platform specific code should no longer be included.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
		And remove from Gauge namespace
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Compiler Warning corrections for GCC++
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ErrorColor static function that produces a really uggggly
		color to use in those cases that we want to highlight a problem.
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add ColorFromName that uses descriptor to send the name instead
		of null terminated string.
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <float.h>
#include <math.h>
#include <ctype.h>

#include "CColor.h"

#include "UFloat.h"
#include "UMath.h"

#include "UPlatform.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

#define NONCOLOR	(~0u)

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Core {

//typedef struct ColorName
//{
//	char*			sName;
//	RGBColorByte	value;
//} ColorName;

/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/

CColor CColor::g_tErrorColor( 0xFF, 0x66, 0x99 );


const ColorName g_aColorNames[]
= {
	{ "abbey",			{76, 79, 86} },		//
	{ "aeroblue",		{201, 255, 229} },	//
	{ "airforceblue",	{93, 138, 168} },		//
	{ "aliceblue",		{240, 248, 255} },
//	{ "alizarin",		{227, 38, 54} },		//
	{ "almond",			{239, 222, 205} },	// crayola
	{ "aluminium",		{169, 172, 182} },	//
	{ "amaranth",		{229, 43, 80} },		//
	{ "amaranthpink",	{241, 156, 187} },	//
	{ "amber",			{255, 191, 0} },		//
	{ "amber2",			{255, 126, 0} },		//
	{ "amethyst",		{153, 102, 204} },	//
	{ "antiquebrass",	{200, 138, 101} },	//
	{ "antiquebronze",	{112, 74, 7} },		//
	{ "antiquewhite",	{250, 235, 215} },
	{ "apple",			{79, 168, 61} },		//
	{ "applegreen",		{226, 243, 236} },	//
	{ "apricot",		{251, 206, 177} },	//
	{ "aqua",			{0, 255, 255} },
	{ "aquamarine",		{127, 255, 212} },
	{ "aquamarineblue",	{113, 217, 226} },	//
	{ "armygreen",		{75, 83, 32} },		//
	{ "arsenic",		{59, 68, 75} },		//
	{ "ash",			{198, 195, 181} },	//
	{ "asparagus",		{123, 160, 91} },		//
	{ "asphalt",		{19, 10, 6} },		//
//	{ "atomictangerine",{255, 164, 116} },	// crayola
	{ "auburn",			{109, 53, 26} },		//
	{ "azure",			{240, 255, 255} },
	{ "azuredark",		{0, 127, 255} },		//
//	{ "babyblue",		{224, 255, 255} },	//
	{ "background",		{0, 0, 0} },
	{ "bakerschocolate",{92, 51, 23} },		//
//	{ "bananamania",	{250, 231, 181} },	// crayola
	{ "battleshipgray",	{130, 143, 114} },	//
	{ "beaver",			{159, 129, 112} },	// crayola
//	{ "beeswax",		{254, 242, 199} },	//
	{ "beige",			{245, 245, 220} },
	{ "bisque",			{255, 228, 196} },
	{ "bistre",			{61, 43, 31} },		//
//	{ "bittersweet",	{253, 124, 110} },	// crayola
	{ "black",			{2, 2, 2} },
	{ "blackberry",		{77, 1, 53} },		//
	{ "blackrose",		{103, 3, 45} },		//
	{ "blanchedalmond",	{255, 235, 205} },
//	{ "blizzardblue",	{172, 229, 238} },	// crayola
	{ "blue",			{0, 0, 255} },
	{ "bluebell",		{162, 162, 208} },	// crayola
	{ "bluecrayola",	{31,117, 254} },		// crayola
	{ "bluegray",		{102, 153, 204} },	// crayola
	{ "bluegreen",		{0, 221, 221} },		//
	{ "blueviolet",		{138, 43, 226} },
//	{ "blush",			{222, 93, 131} },		// crayola
	{ "bole",			{121, 68, 59} },		//
	{ "bondiblue",		{0, 149, 182} },		//
	{ "bone",			{228, 209, 192} },	//
//	{ "brandeisblue",	{0, 112, 255} },		//
	{ "brass",			{181, 166, 66} },		//
	{ "brickred",		{203, 65, 84} },		// crayola
	{ "brightgreen",	{102, 255, 0} },		//
//	{ "brightpink",		{255, 0, 127} },		//
	{ "brightred",		{177, 0, 0} },		//
	{ "brightturquoise",{8, 232, 222} },		//
	{ "brilliantrose",	{255, 85, 163} },		//
	{ "brinkpink",		{251, 96, 127} },		//
	{ "britishracinggreen", {0, 66, 37} },	//
	{ "bronze",			{205, 127, 50} },		//
	{ "brown",			{165, 42, 42} },
	{ "buff",			{240, 220, 130} },	//
	{ "burgundy",		{128, 0, 32} },		//
	{ "burlywood",		{222, 184, 135} },
	{ "burntorange",	{204, 85, 0} },		//
	{ "burntsienna",	{233, 116, 81} },		//
	{ "burntumber",		{138, 51, 36} },		//
	{ "buttercup",		{243, 173, 22} },		//
//	{ "buttermilk",		{255, 241, 181} },	//
	{ "byzantium",		{112, 41, 99} },		//
	{ "cadetblue",		{95, 158, 160} },
	{ "cambridgeblue",	{163, 193, 173} },	//
	{ "camouflagegreen",{120, 134, 107} },	//
	{ "canary",			{255, 255, 153} },	// crayola
	{ "caputmortuum",	{89, 39, 32} },		//
	{ "cardinal",		{196, 30, 58} },		//
	{ "caribbeangreen",	{28, 211, 162} },		// crayola
	{ "carmine",		{150, 0, 24} },		//
	{ "carminepink",	{235, 76, 66} },		//
	{ "carnationpink",	{255, 170, 204} },	// crayola
	{ "carrotorange",	{237, 145, 33} },		//
	{ "cerulean",		{29, 172, 214} },		// crayola
	{ "ceruleanblue",	{42, 82, 190} },		//
	{ "champagne",		{247, 231, 206} },	//
	{ "charcoal",		{70, 70, 70} },		//
	{ "chartreuse",		{127, 255, 0} },
	{ "chartreusetraditional", {223, 255, 0} },	//
	{ "cherryblossompink",	{255, 183, 197} },	//
	{ "chocolate",		{210, 105, 30} },
	{ "coolcopper",		{217, 135, 25} },		//
	{ "copper",			{184, 115, 51} },		//
	{ "coral",			{255, 127, 80} },
//	{ "coralpink",		{248, 131, 121} },	//
	{ "coralred",		{255, 64, 64} },		//
	{ "corn",			{251, 236, 93} },		//
	{ "cornflowerblue",	{100, 149, 237} },
	{ "cornsilk",		{255, 248, 220} },
	{ "cottoncandy",	{255, 188, 217} },	// crayola
	{ "crimson",		{220, 20, 60} },
	{ "cyan",			{0, 255, 255} },
//	{ "dandelion",		{253, 219, 109} },	// crayola
	{ "darkblue",		{0, 0, 139} },
	{ "darkbrown",		{101, 67, 33} },		//
	{ "darkcerulean",	{8, 69, 126} },		//
	{ "darkcoral",		{205, 91, 69} },		//
	{ "darkcyan",		{0, 139, 139} },
	{ "darkgoldenrod",	{184, 134, 11} },
	{ "darkgray",		{169, 169, 169} },
	{ "darkgreen",		{0, 100, 0} },
	{ "darkgreen2",		{1, 50, 32} },		//
	{ "darkkhaki",		{189, 183, 107} },
	{ "darkmagenta",	{139, 0, 139} },
	{ "darkolivegreen",	{85, 107, 47} },
	{ "darkorange",		{255, 140, 0} },
	{ "darkorchid",		{153, 50, 204} },
	{ "darkpink",		{231, 84, 128} },		//
	{ "darkred",		{139, 0, 0} },
	{ "darksalmon",		{233, 150, 122} },
	{ "darkseagreen",	{143, 188, 139} },
	{ "darkslateblue",	{72, 61, 139} },
	{ "darkslategray",	{47, 79, 79} },
	{ "darktan",		{145, 129, 81} },		//
	{ "darkturquoise",	{0, 206, 209} },
	{ "darkviolet",		{148, 0, 211} },
	{ "davysgray",		{85, 85, 85} },		//
	{ "deepmagenta",	{205, 0, 204} },		//
	{ "deeppink",		{255, 20, 147} },
	{ "deepsaffron",	{255, 153, 51} },		//
	{ "deepskyblue",	{0, 191, 255} },
	{ "denim",			{43, 108, 196} },		// crayola
	{ "desertsand",		{239, 205, 184} },	// crayola
	{ "dimgray",		{105, 105, 105} },
	{ "dodgerblue",		{30, 144, 255} },
	{ "dukeblue",		{0, 0, 156} },		//
	{ "eggplant",		{97, 64, 81} },		//
//	{ "electricgreen",	{0, 255, 0} },		//
	{ "electriclime",	{206, 255, 29} },		// crayola
	{ "emerald",		{80, 200, 120} },		//
	{ "fallow",			{193, 154, 107} },	//
	{ "falured",		{128, 24, 24} },		//
	{ "feldgray",		{77, 93, 83} },		//
	{ "ferngreen",		{79, 121, 66} },		//
	{ "firebrick",		{178, 34, 34} },
	{ "fireenginered",	{206, 22, 32} },		//
	{ "floralwhite",	{255, 250, 240} },
	{ "forestgreen",	{34, 139, 34} },
	{ "fuchsia",		{255, 0, 255} },
	{ "fuchsiapink",	{255, 119, 255} },	//
	{ "gainsboro",		{220, 220, 220} },
	{ "ghostwhite",		{248, 248, 255} },
	{ "gold",			{255, 215, 0} },
	{ "goldenrod",		{218, 165, 32} },
	{ "goldmetallic",	{212, 175, 55} },		//
	{ "grannysmithapple",{168, 228, 160} },	// crayola
	{ "gray",			{128, 128, 128} },
	{ "green",			{0, 128, 0} },
	{ "greenyellow",	{240, 232, 145} },
	{ "honeydew",		{240, 255, 240} },
	{ "hotmagenta",		{248, 23, 62} },		// crayola
	{ "hotpink",		{255, 105, 180} },
	{ "huntergreen",	{53, 94, 59} },		//
	{ "inchworm",		{178, 236, 93} },		// crayola
	{ "indianred",		{205, 92, 92} },
	{ "indigo",			{75, 0, 130} },
	{ "indigodye",		{0, 65, 106} },		//
	{ "ivory",			{255, 255, 240} },
	{ "jade",			{0, 168, 107} },		//
	{ "junglegreen",	{59, 176, 143} },		// crayola
	{ "kellygreen",		{76, 187, 23} },		//
	{ "khaki",			{240, 230, 140} },
	{ "lavender",		{230, 230, 250} },
//	{ "lavenderblue",	{204, 204, 255} },	//
	{ "lavenderblush",	{255, 240, 245} },
	{ "lavendergray",	{196, 195, 208} },	//
	{ "lawngreen",		{124, 252, 0} },
	{ "lemon",			{253, 233, 16} },		//
	{ "lemonchiffon",	{255, 250, 205} },
	{ "lightblue",		{173, 216, 230} },
	{ "lightcoral",		{240, 128, 128} },
	{ "lightcyan",		{224, 255, 255} },
	{ "lightgoldenrodyellow",	{250, 250, 210} },
	{ "lightgray",		{211, 211, 211} },
	{ "lightgreen",		{144, 238, 144} },
//	{ "lightkhaki",		{240, 230, 140} },	//
	{ "lightpink",		{255, 182, 193} },
	{ "lightsalmon",	{255, 160, 122} },
	{ "lightseagreen",	{32, 178, 170} },
	{ "lightskyblue",	{135, 206, 250} },
	{ "lightslategray",	{119, 136, 153} },
	{ "lightsteelblue",	{176, 196, 222} },
	{ "lightyellow",	{255, 255, 224} },
	{ "lime",			{0, 255, 0} },
	{ "limegreen",		{50, 205, 50} },
	{ "linen",			{250, 240, 230} },
	{ "magenta",		{255, 0, 255} },
	{ "mahogany",		{205, 74, 76} },		// crayola
	{ "manatee",		{151, 154, 170} },	// crayola
	{ "maroon",			{128, 0, 0} },
	{ "mediumaquamarine",	{102, 205, 170} },
	{ "mediumblue",		{0, 0, 205} },
	{ "mediumorchid",	{186, 85, 211} },
	{ "mediumpurple",	{147, 112, 219} },
	{ "mediumseagreen",	{60, 179, 113} },
	{ "mediumslateblue",	{123, 104, 238} },
	{ "mediumspringgreen",	{0, 250, 154} },
	{ "mediumturquoise",	{72, 209, 204} },
	{ "mediumvioletred",	{199, 21, 133} },
	{ "metallicgold",	{212, 175, 55} },		//
	{ "midnightblue",	{25, 25, 112} },
	{ "mintcream",		{245, 255, 250} },
//	{ "mintgreen",		{152, 255, 152} },	//
	{ "mistyrose",		{255, 228, 225} },
	{ "moccasin",		{255, 228, 181} },
	{ "mossgreen",		{173, 223, 173} },	//
	{ "mustard",		{255, 219, 88} },		//
	{ "navajowhite",	{255, 222, 173} },
	{ "navy",			{0, 0, 128} },
	{ "ochre",			{204, 119, 34} },		//
//	{ "oldgold",		{207, 181, 59} },		//
	{ "oldlace",		{253, 245, 230} },
	{ "olive",			{128, 128, 0} },
	{ "olivedrab",		{107, 142, 35} },
	{ "orange",			{255, 165, 0} },
//	{ "orangepeel",		{255, 160, 0} },		//
	{ "orangered",		{255, 69, 0} },
	{ "orchid",			{218, 112, 214} },
	{ "outerspace",		{65, 74, 76} },		// crayola
//	{ "paleblue",		{175, 238, 238} },	//
	{ "palebrown",		{152, 118, 84} },		//
	{ "palegoldenrod",	{238, 232, 170} },
	{ "palegreen",		{152, 251, 152} },
	{ "paleturquoise",	{175, 238, 238} },
	{ "palevioletred",	{219, 112, 147} },
	{ "papayawhip",		{255, 239, 213} },
	{ "pastelgreen",	{119, 221, 119} },	//
//	{ "peach",			{255, 229, 180} },	//
	{ "peachorange",	{255, 204, 153} },	//
//	{ "peachpuff",		{255, 218, 185} },
	{ "periwinkle",		{204, 204, 255} },	//
	{ "persimmon",		{236, 88, 0} },		//
	{ "peru",			{205, 133, 63} },
	{ "pigmentblue",	{51, 51, 153} },		//
	{ "pigmentgreen",	{0, 165, 80} },		//
	{ "pigmentred",		{237, 28, 36} },		//
	{ "pinegreen",		{21, 128, 120} },		// crayola
	{ "pink",			{255, 192, 203} },
	{ "platinum",		{229, 228, 226} },	//
	{ "plum",			{221, 160, 221} },
	{ "powderblue",		{176, 224, 230} },
//	{ "processcyan",	{0, 183, 235} },		//
	{ "processmagenta",	{255, 0, 144} },		//
	{ "processyellow",	{255, 239, 0} },		//
	{ "puce",			{204, 136, 153} },	//
	{ "pumpkin",		{255, 117, 24} },		//
	{ "purple",			{128, 0, 128} },
	{ "rawumber",		{113, 75, 35} },		// crayola
	{ "red",			{255, 0, 0} },
	{ "redviolet",		{199, 21, 133} },		//
	{ "robineggblue",	{31, 206, 203} },		// crayola
	{ "rosybrown",		{188, 143, 143} },
	{ "royalblue",		{65, 105, 225} },
	{ "rust",			{183, 65, 14} },		//
	{ "saddlebrown",	{139, 69, 19} },
	{ "safetyorange",	{255, 102, 0} },		//
	{ "saffron",		{244, 196, 48} },		//
	{ "salmon",			{250, 128, 114} },
	{ "sandybrown",		{244, 164, 96} },
	{ "sapphire",		{8, 37, 103} },		//
//	{ "scarlet",		{255, 36, 0} },		//
//	{ "schoolbusyellow",{255, 216, 0} },		//
	{ "screamingreen",	{118, 255, 122} },	// crayola
	{ "seagreen",		{46, 139, 87} },
	{ "seashell",		{255, 245, 238} },
	{ "sienna",			{160, 82, 45} },
	{ "silver",			{192, 192, 192} },
	{ "skyblue",		{135, 206, 235} },
	{ "slateblue",		{106, 90, 205} },
	{ "slategray",		{112, 128, 144} },
	{ "snow",			{255, 250, 250} },
	{ "springgreen",	{0, 255, 127} },
	{ "steelblue",		{70, 130, 180} },
	{ "tan",			{210, 180, 140} },
	{ "tangerine",		{242, 133, 0} },		//
//	{ "tangerineyellow",{255, 204, 0} },		//
	{ "taupe",			{72, 60, 50} },		//
	{ "taupegray",		{139, 133, 137} },	//
//	{ "tawny",			{205, 87, 0} },		//
	{ "teagreen",		{208, 240, 192} },	//
	{ "teal",			{0, 128, 128} },
	{ "thistle",		{216, 191, 216} },
	{ "timberwolf",		{219, 215, 210} },	// crayola
	{ "tomato",			{255, 99, 71} },
	{ "transparent",	{0, 0, 0} },
//	{ "tropicalrainforest",{23, 128, 109} },	// crayola
	{ "turquoise",		{64, 224, 208} },
	{ "ultramarine",	{18, 10, 143} },		//
	{ "vegasgold",		{197, 179, 88} },		//
	{ "vermilion",		{227, 66, 51} },		//
	{ "violet",			{238, 130, 238} },
	{ "viridian",		{64, 130, 109} },		//
	{ "walnut",			{119, 63, 26} },		//
	{ "wheat",			{245, 222, 179} },
	{ "white",			{255, 255, 255} },
	{ "whitesmoke",		{245, 245, 245} },
	{ "wildblueyonder",	{162, 173, 208} },	// crayola
	{ "yellow",			{255, 255, 0} },
	{ "yellowgreen",	{197, 227, 132} },
	{ "yelloworange",	{255, 174, 66} }		// crayola

};






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

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		void
		)
		: m_tColor( NONCOLOR )
{
}

/*---------------------------------------------------------------------+\

 * CColor - copy constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		ConstCColorRef	r
		)
		: m_tColor( r.m_tColor )
{
}


/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		unsigned int r,
		unsigned int g,
		unsigned int b
		)
		: m_tColor( 0 )
{
	SetRGB( r, g, b );
}

/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		unsigned int r,
		unsigned int g,
		unsigned int b,
		unsigned int a
		)
		: m_tColor( 0 )
{
	SetRGBA( r, g, b, a );
}

/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		const COLORDATA&	r
		)
		: m_tColor( 0 )
{
	SetData( r );
}


/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		ConstRGBColorByteRef	r
		)
		: m_tColor( 0 )
{
	SetColorByte( r );
}

/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		ConstRGBAColorByteRef	r
		)
		: m_tColor( 0 )
{
	SetColorByte( r );
}

/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		const char*	sName
		)
		: m_tColor( NONCOLOR )
{
	m_tColor = ColorFromName( sName );
}

/*---------------------------------------------------------------------+\

 * CColor - constructor

\+---------------------------------------------------------------------*/
CColor::CColor
		(
		const char*		sName,
		unsigned int	a
		)
		: m_tColor( NONCOLOR )
{
	m_tColor = ColorFromNameAlpha( sName, a );
}



/*---------------------------------------------------------------------+\

 * ~CColor - destructor

\+---------------------------------------------------------------------*/
CColor::~CColor
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/






/*---------------------------------------------------------------------+\

 * SetRGB - assign based on Red, Green, Blue values

 * r,g,b are assumed to be byte values

\+---------------------------------------------------------------------*/
void	CColor::SetRGB
		(
		unsigned int r,
		unsigned int g,
		unsigned int b
		)
{
	SetRGBA( r, g, b, 0 );
}


/*---------------------------------------------------------------------+\

 * SetRGBA -

\+---------------------------------------------------------------------*/
void	CColor::SetRGBA
		(
		unsigned int r,
		unsigned int g,
		unsigned int b,
		unsigned int a
		)
{
	m_tColor
		=	(a << COLORDATA_V_ALPHA)
		|	(b << COLORDATA_V_BLUE)
		|	(g << COLORDATA_V_GREEN)
		|	(r << COLORDATA_V_RED);
}

/*---------------------------------------------------------------------+\

 * SetAlpha -

\+---------------------------------------------------------------------*/
void	CColor::SetAlpha
		(
		unsigned int a
		)
{
	m_tColor
		=	(a << COLORDATA_V_ALPHA)
		|	(m_tColor & COLORDATA_M_RGB);
}


/*---------------------------------------------------------------------+\

 * SetColorLong -

\+---------------------------------------------------------------------*/
void	CColor::SetColorLong
		(
		long	nValue
		)
{
	unsigned int	n = (unsigned int)nValue;
	unsigned int	a = (n & COLORLONG_M_ALPHA) >> COLORLONG_V_ALPHA;
	unsigned int	r = (n & COLORLONG_M_RED) >> COLORLONG_V_RED;
	unsigned int	g = (n & COLORLONG_M_GREEN) >> COLORLONG_V_GREEN;
	unsigned int	b = (n & COLORLONG_M_BLUE) >> COLORLONG_V_BLUE;

	SetRGBA( r, g, b, a );
}


/*---------------------------------------------------------------------+\

 * SetNonColor -

\+---------------------------------------------------------------------*/
void	CColor::SetNonColor
		(
		bool	b
		)
{
	if ( b )
		m_tColor = NONCOLOR;
	else
		m_tColor = 0;
}

/*---------------------------------------------------------------------+\

 * IsNonColor -

\+---------------------------------------------------------------------*/
bool	CColor::IsNonColor
		(
		void
		) const
{
	if ( m_tColor == (COLORDATA)NONCOLOR )
		return true;
	else
		return false;
}

/*---------------------------------------------------------------------+\

 * SetColorByte -

\+---------------------------------------------------------------------*/
void	CColor::SetColorByte
		(
		ConstRGBColorByteRef	r
		)
{
	SetRGB( r.red, r.green, r.blue );
}

/*---------------------------------------------------------------------+\

 * SetColorByte -

\+---------------------------------------------------------------------*/
void	CColor::SetColorByte
		(
		ConstRGBAColorByteRef	r
		)
{
	SetRGBA( r.red, r.green, r.blue, r.alpha );
}


/*---------------------------------------------------------------------+\

 * SetData -

\+---------------------------------------------------------------------*/
void	CColor::SetData
		(
		const char*	sName
		)
{
	m_tColor = ColorFromName( sName );
}


/*---------------------------------------------------------------------+\

 * Equals -

\+---------------------------------------------------------------------*/
bool	CColor::Equals
		(
		const CColor&	r
		) const
{
	return m_tColor == r.m_tColor;
}


/*---------------------------------------------------------------------+\

 * Equals -

\+---------------------------------------------------------------------*/
bool	CColor::Equals
		(
		const COLORDATA&	r
		) const
{
	return m_tColor == r;
}


/*---------------------------------------------------------------------+\

 * ColorFromName -

\+---------------------------------------------------------------------*/
//static
CColor	CColor::ColorFromName
		(
		const char *sNameInput
		)
{
	CCharDescriptor	tName( sNameInput, ::strlen(sNameInput) );
	return ColorFromName( tName );
}

/*---------------------------------------------------------------------+\

 * ColorFromNameAlpha -

\+---------------------------------------------------------------------*/
//static
CColor	CColor::ColorFromNameAlpha
		(
		const char*		sName,
		unsigned int	alpha
		)
{
	CCharDescriptor	tName( sName, ::strlen(sName) );
	return ColorFromNameAlpha( tName, alpha );
}


/*---------------------------------------------------------------------+\

 * ColorFromName -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
//static
CColor	CColor::ColorFromName
		(
		CCharDescriptorRef	rName
		)
{
	int			nTop = sizeof(g_aColorNames) / sizeof(ColorName) - 1;
	int			nMid;
	int			nLow = 0;
	int			nHigh = nTop;
	const char*	sName;
	char		sNameLC[40];
	size_t		nLen = rName.Length();
	if ( nLen < sizeof(sNameLC) )
	{
		char*		sOut = sNameLC;
		//char*		sOutEnd = sOut + sizeof(sNameLC);
		const char*	s = rName.Pointer();
		const char*	sEnd = s + rName.Length();
		while ( s < sEnd )
		{
			if ( ' ' != *s )
			{
				*sOut = static_cast<char>(::tolower( *s ));
				if ( 0 == *s )
					break;
				++sOut;
			}
			++s;
		}
		*sOut = 0;
		sName = sNameLC;
	}
	else
	{
		sName = rName.Pointer();
	}

	while ( nLow < nHigh )
	{
		nMid = nLow + ((nHigh - nLow) / 2);
		if ( 0 < ::strcmp( sName, g_aColorNames[nMid].sName ) )
			nLow = nMid + 1;
		else
			nHigh = nMid;
	}
	CColor	c;
	if ( nLow <= nTop  &&  0 == ::strcmp( g_aColorNames[nLow].sName, sName ) )
		c.SetColorByte( g_aColorNames[nLow].value );
	else
		c.SetNonColor( true );
	return c;
}
//END_OVERRUN_WARNING


/*---------------------------------------------------------------------+\

 * ColorFromNameAlpha -

\+---------------------------------------------------------------------*/
//static
CColor	CColor::ColorFromNameAlpha
		(
		CCharDescriptorRef	rName,
		unsigned int		alpha
		)
{
	CColor	c = ColorFromName( rName );
	if ( ! c.IsNonColor() )
		c.SetAlpha( alpha );
	return c;
}


/*---------------------------------------------------------------------+\

 * BackgroundColor -

\+---------------------------------------------------------------------*/
//static
CColor	CColor::BackgroundColor
		(
		void
		)
{
	return CColor( 0, 0, 0, 0 );
}


/*---------------------------------------------------------------------+\

 * ErrorColor -

\+---------------------------------------------------------------------*/
//static
CColor	CColor::ErrorColor
		(
		void
		)
{
	return g_tErrorColor;
}





/*---------------------------------------------------------------------+\

 * HSVfromRGB -

\+---------------------------------------------------------------------*/
void	CColor::HSVfromRGB
		(
		HSVColorFloatPtr pHSV,
		RGBColorBytePtr pRGB
		)
{
	float	r = pRGB->red / 255.0f;
	float	g = pRGB->green / 255.0f;
	float	b = pRGB->blue / 255.0f;
	float	x;
	float	h;
	float	s;
	float	v;

	x = umin( r, g );
	x = umin( x, b );

	v = umax( r, g );
	v = umax( v, b );

	if ( ::fabsf(v - x) < GFLOAT_EPSILON )
	{
		h = 0;
		s = 0;
		v = 0;
	}
	else
	{
		float	f = ( r == x ) ? g - b : (( g == x ) ? b - r : r - g );
		int		i = ( r == x ) ? 3 : (( g == x ) ? 5 : 1 );
		h = i - f / ( v - x );
		s = ( v - x ) / v;
	}
	pHSV->hue = h * 60;
	pHSV->saturation = s * 100;
	pHSV->value = v * 100;

}


/*---------------------------------------------------------------------+\

 * RGBfromHSV -

\+---------------------------------------------------------------------*/
void	CColor::RGBfromHSV
		(
		RGBColorBytePtr pRGB,
		HSVColorFloatPtr pHSV
		)
{

	float	h = pHSV->hue / 60.0f;
	float	s = pHSV->saturation / 100;
	float	v = pHSV->value / 100;

	if ( ::fabsf( h ) < GFLOAT_EPSILON )
	{
		pRGB->red = pRGB->green = pRGB->blue = (unsigned char)(v * 255);
	}
	else
	{
		float	r = 0;
		float	g = 0;
		float	b = 0;
		int		i = int(::floorf( h ));
		float	f = h - i;
		if ( 0 == (i % 2) )		// even
			f = 1 - f;
		float	m = v * (1 - s);
		float	n = v * (1 - s * f);
		switch ( i )
		{
		case 6:
		case 0:
			r = v;
			g = n;
			b = m;
			break;
		case 1:
			r = n;
			g = v;
			b = m;
			break;
		case 2:
			r = m;
			g = v;
			b = n;
			break;
		case 3:
			r = m;
			g = n;
			b = v;
			break;
		case 4:
			r = n;
			g = m;
			b = v;
			break;
		case 5:
			r = v;
			g = m;
			b = n;
			break;
		default:
			r = 0;
			g = 0;
			b = 0;
			break;
		}
		pRGB->red = (unsigned char)(r * 255);
		pRGB->green = (unsigned char)(g * 255);
		pRGB->blue = (unsigned char)(b * 255);
	}

}


/*---------------------------------------------------------------------+\

 * HSLfromRGB -

\+---------------------------------------------------------------------*/
//static
void	CColor::HSLfromRGB
		(
		HSLColorBytePtr pHSL,
		RGBColorBytePtr pRGB
		)
{
	float	r = (float) pRGB->red / 255.0f;
	float	g = (float) pRGB->green / 255.0f;
	float	b = (float) pRGB->blue / 255.0f;

	float	fMinColor;
	float	fMaxColor;
	float	fDiff;

    // find minium/maximum color values
	fMinColor = umin( r, umin( g, b ) );
	fMaxColor = umax( r, umax( g, b ) );
	fDiff = fMaxColor - fMinColor;

	if ( fabsf( fDiff ) < 0.001f )
	{
		// colors are same, so it is a shade of gray
		pHSL->light = pRGB->red;
		pHSL->saturation = 0;
		pHSL->hue = 0;
	}
	else
	{
		float	h;
		float	s;

		// compute luminance
		float	l = (fMinColor + fMaxColor) / 2.0f;

		// compute saturation
		if ( l < 0.5f )
			s = fDiff / (fMaxColor + fMinColor);
		else
			s = fDiff / (2.0f - fMaxColor - fMinColor);

		// compute hue
		if ( fabsf( fMaxColor - r ) < 0.001f )
			h = ( g - b ) / fDiff;
		else if ( fabsf( fMaxColor - g ) < 0.001f )
			h = 2.0f + ( b - r ) / fDiff;
		else
			h = 4.0f + ( r - g ) / fDiff;

		h /= 6.0f;

		if ( h < 0.0f )
			h += 1.0f;

		// convert back to 0 .. 255 range
		h *= 255.0f;
		s *= 255.0f;
		l *= 255.0f;

		pHSL->hue = (unsigned char)(h + 0.5f) & 0x00FFu;
		pHSL->saturation = (unsigned char)(s + 0.5f) & 0x00FFu;
		pHSL->light = (unsigned char)(l + 0.5f) & 0x00FFu;
	}
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
//static
CColorEnumerator
		CColor::GetEnumerator
		(
		void
		)
{
	return CColorEnumerator();
}


/*---------------------------------------------------------------------+\

 * CColorEnumerator::CColorEnumerator -

\+---------------------------------------------------------------------*/
CColorEnumerator::CColorEnumerator
		(
		void
		)
{
	m_pBegin = g_aColorNames;
	m_pEnd = m_pBegin + (sizeof(g_aColorNames) / sizeof(ColorName));
	m_pCurrent = 0;
}

/*---------------------------------------------------------------------+\

 * CColorEnumerator::~CColorEnumerator -

\+---------------------------------------------------------------------*/
CColorEnumerator::~CColorEnumerator
		(
		void
		)
{
	m_pCurrent = 0;
}

/*---------------------------------------------------------------------+\

 * CColorEnumerator::MoveNext -

\+---------------------------------------------------------------------*/
bool	CColorEnumerator::MoveNext
		(
		void
		)
{
	if ( m_pCurrent )
	{
		++m_pCurrent;
		if ( m_pCurrent < m_pEnd )
			return true;
		else
			return false;
	}
	else
	{
		m_pCurrent = m_pBegin;
		return true;
	}
}


/*---------------------------------------------------------------------+\

 * CColorEnumerator::Reset -

\+---------------------------------------------------------------------*/
void	CColorEnumerator::Reset
		(
		void
		)
{
	m_pCurrent = 0;
}


/*---------------------------------------------------------------------+\

 * CColorEnumerator::Current -

\+---------------------------------------------------------------------*/
const ColorName*
		CColorEnumerator::Current
		(
		void
		)
{
	if ( ! m_pCurrent )
		MoveNext();

	if ( m_pCurrent )
	{
		if ( m_pCurrent < m_pEnd )
			return m_pCurrent;
		else
			return 0;
	}
	else
	{
		return 0;
	}
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

