/*---------------------------------------------------------------------+\
|
|	fixed_t.cpp  --  implementation of a fixed-point class
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
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	05-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <math.h>

#include "fixed_t.h"
#ifndef FIXED_USE_FLOAT
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/


#define TRIG_TABLE_SIZE 402

#define	RESOLUTION	fp_1

#define pgm_read_word(a) (*(a))
#define pgm_read_dword(a) (*(a))


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
#define fp_1           65536    // 1
#define fp_1_2         32768    // 1/2
#define fp_2           131072   // 2
#define fp_pi          205887   // pi
#define fp_pi_2        102943   // pi/2
#define fp_2_pi        411774   // 2pi
#define fp_e           178145   // e
#define fp_epsilon     65       // 0.001
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/


static local_fixed_t sin_table[]
= {
  0, 511, 1023, 1535, 2047, 2559, 3070, 3582, 4093, 4604, 5114, 5625, 6135, 6644, 7153, 7662,
  8170, 8678, 9185, 9692, 10198, 10703, 11208, 11712, 12216, 12718, 13220, 13721, 14221, 14721, 15219, 15717,
  16213, 16709, 17204, 17697, 18189, 18681, 19171, 19660, 20148, 20634, 21120, 21604, 22086, 22568, 23048, 23526,
  24004, 24479, 24953, 25426, 25897, 26367, 26835, 27301, 27766, 28228, 28690, 29149, 29607, 30063, 30517, 30969,
  31419, 31867, 32314, 32758, 33201, 33641, 34080, 34516, 34950, 35382, 35812, 36240, 36665, 37088, 37509, 37928,
  38344, 38758, 39170, 39579, 39986, 40391, 40793, 41192, 41589, 41984, 42375, 42765, 43151, 43535, 43917, 44295,
  44671, 45045, 45415, 45783, 46148, 46510, 46869, 47226, 47579, 47930, 48278, 48622, 48964, 49303, 49639, 49972,
  50301, 50628, 50951, 51272, 51589, 51903, 52214, 52522, 52827, 53128, 53426, 53721, 54013, 54301, 54586, 54868,
  55146, 55421, 55693, 55961, 56226, 56487, 56745, 56999, 57250, 57498, 57741, 57982, 58219, 58452, 58682, 58908,
  59131, 59349, 59565, 59776, 59985, 60189, 60390, 60587, 60780, 60970, 61156, 61338, 61516, 61691, 61862, 62029,
  62192, 62352, 62507, 62659, 62807, 62952, 63092, 63229, 63361, 63490, 63615, 63736, 63854, 63967, 64076, 64182,
  64283, 64381, 64475, 64564, 64650, 64732, 64810, 64884, 64954, 65020, 65082, 65140, 65195, 65245, 65291, 65333,
  65371, 65406, 65436, 65462, 65484, 65503, 65517, 65527, 65533, 65535, 65534, 65528, 65518, 65504, 65487, 65465,
  65439, 65410, 65376, 65338, 65296, 65251, 65201, 65147, 65090, 65028, 64963, 64893, 64820, 64742, 64661, 64575,
  64486, 64393, 64296, 64195, 64090, 63981, 63868, 63751, 63630, 63506, 63378, 63245, 63109, 62969, 62826, 62678,
  62526, 62371, 62212, 62049, 61883, 61712, 61538, 61360, 61178, 60993, 60804, 60611, 60414, 60214, 60010, 59802,
  59591, 59376, 59158, 58936, 58710, 58481, 58248, 58011, 57771, 57528, 57281, 57030, 56776, 56519, 56258, 55994,
  55726, 55455, 55180, 54902, 54621, 54337, 54049, 53758, 53463, 53165, 52864, 52560, 52253, 51942, 51628, 51311,
  50991, 50668, 50342, 50013, 49680, 49345, 49006, 48665, 48320, 47973, 47623, 47270, 46914, 46555, 46193, 45828,
  45461, 45091, 44718, 44342, 43964, 43583, 43199, 42813, 42424, 42032, 41638, 41241, 40842, 40441, 40037, 39630,
  39221, 38810, 38396, 37980, 37561, 37141, 36718, 36292, 35865, 35435, 35004, 34570, 34134, 33696, 33255, 32813,
  32369, 31923, 31475, 31025, 30573, 30119, 29663, 29206, 28747, 28286, 27823, 27359, 26892, 26425, 25955, 25485,
  25012, 24538, 24063, 23586, 23107, 22627, 22146, 21664, 21180, 20695, 20208, 19720, 19232, 18742, 18250, 17758,
  17265, 16770, 16275, 15778, 15281, 14783, 14283, 13783, 13282, 12780, 12278, 11775, 11271, 10766, 10261, 9755,
  9248, 8741, 8233, 7725, 7216, 6707, 6198, 5688, 5178, 4667, 4156, 3645, 3134, 2622, 2111, 1599,
  1087, 575, 63,
};

static local_fixed_t cos_table[]
= {
  65536, 65534, 65528, 65518, 65504, 65486, 65464, 65438, 65408, 65374, 65336, 65294, 65248, 65198, 65144, 65086,
  65024, 64958, 64889, 64815, 64737, 64655, 64570, 64480, 64387, 64289, 64188, 64083, 63974, 63861, 63744, 63623,
  63498, 63370, 63237, 63101, 62961, 62817, 62669, 62517, 62361, 62202, 62039, 61872, 61701, 61527, 61349, 61167,
  60981, 60792, 60599, 60402, 60201, 59997, 59789, 59578, 59363, 59144, 58922, 58696, 58466, 58233, 57997, 57756,
  57513, 57266, 57015, 56761, 56503, 56242, 55977, 55709, 55438, 55163, 54885, 54604, 54319, 54031, 53739, 53445,
  53147, 52846, 52541, 52234, 51923, 51609, 51292, 50971, 50648, 50322, 49992, 49659, 49324, 48985, 48644, 48299,
  47951, 47601, 47248, 46891, 46532, 46170, 45806, 45438, 45068, 44695, 44319, 43940, 43559, 43175, 42789, 42400,
  42008, 41614, 41217, 40817, 40416, 40011, 39605, 39196, 38784, 38370, 37954, 37535, 37115, 36691, 36266, 35839,
  35409, 34977, 34543, 34107, 33668, 33228, 32786, 32341, 31895, 31447, 30997, 30545, 30091, 29635, 29178, 28718,
  28257, 27794, 27330, 26864, 26396, 25926, 25455, 24983, 24509, 24033, 23556, 23077, 22598, 22116, 21634, 21150,
  20664, 20178, 19690, 19201, 18711, 18220, 17728, 17234, 16740, 16244, 15748, 15250, 14752, 14252, 13752, 13251,
  12749, 12247, 11743, 11239, 10735, 10229, 9723, 9217, 8709, 8202, 7693, 7185, 6676, 6166, 5656, 5146,
  4635, 4124, 3613, 3102, 2591, 2079, 1567, 1055, 543, 31, -480, -992, -1504, -2015, -2527, -3039,
  -3550, -4061, -4572, -5083, -5593, -6103, -6613, -7122, -7630, -8139, -8647, -9154, -9660, -10167, -10672, -11177,
  -11681, -12184, -12687, -13189, -13690, -14190, -14690, -15188, -15686, -16183, -16678, -17173, -17666, -18159, -18650, -19141,
  -19630, -20118, -20604, -21090, -21574, -22057, -22538, -23018, -23497, -23974, -24450, -24924, -25397, -25868, -26338, -26806,
  -27272, -27737, -28200, -28661, -29121, -29579, -30034, -30489, -30941, -31391, -31840, -32286, -32731, -33173, -33614, -34052,
  -34489, -34923, -35355, -35785, -36213, -36639, -37062, -37483, -37902, -38319, -38733, -39145, -39554, -39961, -40366, -40768,
  -41167, -41565, -41959, -42351, -42741, -43127, -43512, -43893, -44272, -44648, -45022, -45392, -45760, -46125, -46488, -46847,
  -47204, -47557, -47908, -48256, -48601, -48943, -49282, -49618, -49951, -50281, -50608, -50931, -51252, -51570, -51884, -52195,
  -52503, -52808, -53110, -53408, -53703, -53995, -54283, -54569, -54850, -55129, -55404, -55676, -55944, -56209, -56471, -56729,
  -56984, -57235, -57482, -57726, -57967, -58204, -58438, -58668, -58894, -59117, -59336, -59552, -59763, -59972, -60176, -60377,
  -60575, -60768, -60958, -61144, -61327, -61505, -61680, -61851, -62019, -62182, -62342, -62498, -62650, -62798, -62943, -63084,
  -63220, -63353, -63482, -63608, -63729, -63846, -63960, -64070, -64175, -64277, -64375, -64469, -64559, -64645, -64727, -64805,
  -64880, -64950, -65016, -65079, -65137, -65191, -65242, -65288, -65331, -65369, -65404, -65434, -65461, -65483, -65501, -65516,
  -65526, -65533, -65535,
};

static local_fixed_t tan_table[]
= {
  0, 512, 1024, 1536, 2048, 2561, 3074, 3587, 4101, 4615, 5130, 5645, 6162, 6678, 7196, 7715,
  8234, 8755, 9277, 9800, 10324, 10849, 11376, 11904, 12434, 12965, 13498, 14032, 14569, 15107, 15647, 16189,
  16734, 17280, 17829, 18380, 18933, 19489, 20048, 20609, 21173, 21740, 22310, 22883, 23459, 24038, 24621, 25207,
  25796, 26389, 26986, 27587, 28192, 28801, 29414, 30031, 30653, 31279, 31910, 32546, 33187, 33832, 34484, 35140,
  35802, 36470, 37143, 37823, 38508, 39200, 39899, 40604, 41316, 42035, 42761, 43495, 44236, 44986, 45743, 46509,
  47283, 48066, 48858, 49659, 50470, 51290, 52121, 52962, 53814, 54677, 55551, 56436, 57334, 58244, 59167, 60103,
  61053, 62016, 62994, 63986, 64994, 66018, 67057, 68114, 69188, 70279, 71389, 72519, 73668, 74837, 76027, 77239,
  78474, 79732, 81014, 82321, 83654, 85014, 86401, 87818, 89264, 90742, 92252, 93795, 95374, 96989, 98641, 100333,
  102066, 103841, 105661, 107528, 109443, 111408, 113427, 115500, 117632, 119825, 122080, 124403, 126795, 129261, 131804, 134429,
  137138, 139938, 142833, 145828, 148929, 152142, 155474, 158932, 162523, 166256, 170140, 174185, 178402, 182802, 187398, 192203,
  197235, 202508, 208043, 213859, 219979, 226429, 233237, 240434, 248056, 256142, 264738, 273894, 283668, 294127, 305345, 317411,
  330426, 344509, 359798, 376457, 394681, 414706, 436813, 461349, 488741, 519522, 554368, 594145, 639987, 693401, 756442, 831979,
  924150, 1039144, 1186657, 1382783, 1656331, 2064484, 2739124, 4067976, 7899218, 135453424, -8942250, -4327999, -2854640, -2129459, -1697919, -1411669,
  -1207885, -1055401, -936999, -842391, -765050, -700638, -646156, -599467, -559007, -523602, -492357, -464577, -439712, -417324, -397059, -378625,
  -361783, -346334, -332110, -318970, -306792, -295473, -284925, -275070, -265841, -257178, -249031, -241354, -234106, -227252, -220759, -214600,
  -208747, -203179, -197874, -192814, -187981, -183360, -178937, -174698, -170633, -166729, -162978, -159369, -155895, -152548, -149321, -146206,
  -143198, -140291, -137480, -134759, -132125, -129572, -127097, -124695, -122364, -120100, -117900, -115761, -113680, -111655, -109683, -107762,
  -105890, -104064, -102283, -100545, -98848, -97191, -95572, -93989, -92441, -90927, -89446, -87995, -86575, -85184, -83821, -82484,
  -81174, -79889, -78628, -77391, -76176, -74983, -73811, -72660, -71528, -70416, -69322, -68246, -67187, -66145, -65120, -64110,
  -63116, -62136, -61171, -60220, -59282, -58358, -57446, -56547, -55660, -54784, -53920, -53067, -52225, -51393, -50571, -49759,
  -48956, -48163, -47379, -46604, -45837, -45079, -44329, -43586, -42852, -42124, -41405, -40692, -39986, -39286, -38594, -37907,
  -37227, -36553, -35884, -35222, -34565, -33913, -33266, -32625, -31988, -31357, -30730, -30108, -29490, -28876, -28267, -27662,
  -27060, -26463, -25869, -25280, -24693, -24110, -23530, -22954, -22381, -21811, -21243, -20679, -20117, -19558, -19002, -18448,
  -17897, -17348, -16801, -16257, -15714, -15174, -14635, -14099, -13564, -13031, -12499, -11969, -11441, -10914, -10389, -9864,
  -9341, -8820, -8299, -7779, -7260, -6743, -6226, -5709, -5194, -4679, -4165, -3651, -3137, -2624, -2112, -1599,
  -1087, -575, -63,
};


/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
fixed_t	fixed_t::k_0		= fixed_t( true, 0 );			//	0
fixed_t	fixed_t::k_1		= fixed_t( true, fp_1 );		//	1
fixed_t	fixed_t::k_neg1		= fixed_t( -1.0f );				//	-1
fixed_t	fixed_t::k_1_2		= fixed_t( true, fp_1_2 );		//	1/2
fixed_t	fixed_t::k_neg1_2	= fixed_t( -0.5f );
fixed_t	fixed_t::k_1_10		= fixed_t( 0.1f );				//	1/10
fixed_t	fixed_t::k_2		= fixed_t( true, fp_2 );		//	2
fixed_t	fixed_t::k_PI		= fixed_t( true, fp_pi );		//	pi
fixed_t	fixed_t::k_PI_2		= fixed_t( true, fp_pi_2 );		//	pi/2
fixed_t	fixed_t::k_2PI		= fixed_t( true, fp_2_pi );		//	2*pi
fixed_t	fixed_t::k_10		= fixed_t( 10.0f );
fixed_t	fixed_t::k_180		= fixed_t( 180.0f );
fixed_t	fixed_t::k_360		= fixed_t( 360.0f );
fixed_t	fixed_t::k_e		= fixed_t( true, fp_e );		//	e

fixed_t	fixed_t::k_MAX		= fixed_t( true, 0x7FFFFFFFL );
fixed_t	fixed_t::k_MIN		= fixed_t( true, 0xFFFFFFFFL );
fixed_t	fixed_t::k_EPSILON	= fixed_t( true, 1 );			//

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
||	 local functions													|
\+=====================================================================*/

inline
local_fixed_t
		int2fp
		(
		const long i
		)
{
	return i << FP_DEC_BITS;
}

inline
long	fp2int
		(
		const local_fixed_t f
		)
{
	return f >> FP_DEC_BITS;
}

inline
local_fixed_t
		float2fp
		(
		const float f
		)
{
	return (local_fixed_t)(f * (((long_fixed_t)1)<<FP_DEC_BITS));
}

inline
float	fp2float
		(
		const local_fixed_t f
		)
{
	return (float)f / (float)(((long_fixed_t)1)<<FP_DEC_BITS);
}




int		fp_check_overflow
		(
		long_fixed_t f
		)
{
	if( fp_max_value < f>>FP_DEC_BITS )
		return 1;
	else
		return 0;
}

local_fixed_t
		fp_clamp_angle
		(
		local_fixed_t a
		)
{
	if(a < -fp_pi)
		return a + fp_2_pi * ((-a + fp_pi)/fp_2_pi);
	else if(a > fp_pi)
		return a - fp_2_pi * ((a + fp_pi)/fp_2_pi);
	else
		return a;
}



/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * fixed_t - copy constructor

\+---------------------------------------------------------------------*/
fixed_t::fixed_t
		(
		const long	n
		)
		: m_n( fx(n) )
{
}

fixed_t::fixed_t
		(
		const int		n
		)
		: m_n( fx(n) )
{
}

fixed_t::fixed_t
		(
		const short	n
		)
		: m_n( fx(n) )
{
}

fixed_t::fixed_t
		(
		const double	d
		)
{
	m_n = fx( d );
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::operator=
		(
		const double	d
		)
{
	m_n = fx( d );
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const int	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const unsigned int	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const long	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const unsigned long	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const short	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const unsigned short	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const char	n
		)
{
	m_n = fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator=
		(
		const unsigned char	n
		)
{
	m_n = fx(n);
	return *this;
}



/*---------------------------------------------------------------------+\

 * operator [type] - conversion to [type]

\+---------------------------------------------------------------------*/
fixed_t::operator float
		(
		void
		)
{
	return fp2float(m_n);
}

fixed_t::operator double
		(
		void
		)
{
	return fp2float(m_n);
}

fixed_t::operator long
		(
		void
		)
{
	return fp2int(m_n);
}

fixed_t::operator unsigned long
		(
		void
		)
{
	return (unsigned long)fp2int(m_n);
}

fixed_t::operator int
		(
		void
		)
{
	return (int)fp2int( m_n );
}

fixed_t::operator unsigned int
		(
		void
		)
{
	return (unsigned int)fp2int( m_n );
}

fixed_t::operator short
		(
		void
		)
{
	return (short)fp2int( m_n );
}

fixed_t::operator unsigned short
		(
		void
		)
{
	return (unsigned short)fp2int( m_n );
}




/*---------------------------------------------------------------------+\

 * operator == - equality

\+---------------------------------------------------------------------*/
bool	fixed_t::operator ==
		(
		const double	d
		) const
{
	return m_n == fx( d );
}

bool	fixed_t::operator ==
		(
		const int	n
		) const
{
	return m_n == fx(n);
}

bool	fixed_t::operator ==
		(
		const long	n
		) const
{
	return m_n == fx(n);
}

bool	fixed_t::operator ==
		(
		const short	n
		) const
{
	return m_n == fx(n);
}

/*---------------------------------------------------------------------+\

 * operator != - not equality

\+---------------------------------------------------------------------*/
bool	fixed_t::operator !=
		(
		const double	d
		) const
{
	return m_n != fx( d );
}

bool	fixed_t::operator !=
		(
		const int	n
		) const
{
	return m_n != fx(n);
}

bool	fixed_t::operator !=
		(
		const long	n
		) const
{
	return m_n != fx(n);
}

bool	fixed_t::operator !=
		(
		const short	n
		) const
{
	return m_n != fx(n);
}

/*---------------------------------------------------------------------+\

 * operator [less-than]

\+---------------------------------------------------------------------*/
bool	fixed_t::operator <
		(
		const double	d
		)
{
	return m_n < fx( d );
}

bool	fixed_t::operator <
		(
		const int	n
		)
{
	return m_n < fx(n);
}

bool	fixed_t::operator <
		(
		const long	n
		)
{
	return m_n < fx(n);
}

bool	fixed_t::operator <
		(
		const short	n
		)
{
	return m_n < fx(n);
}


/*---------------------------------------------------------------------+\

 * operator [less-than-equal]

\+---------------------------------------------------------------------*/
bool	fixed_t::operator <=
		(
		const double	d
		)
{
	return m_n <= fx( d );
}

bool	fixed_t::operator <=
		(
		const int	n
		)
{
	return m_n <= fx(n);
}

bool	fixed_t::operator <=
		(
		const long	n
		)
{
	return m_n <= fx(n);
}

bool	fixed_t::operator <=
		(
		const short	n
		)
{
	return m_n <= fx(n);
}


/*---------------------------------------------------------------------+\

 * operator [greater-than]

\+---------------------------------------------------------------------*/
bool	fixed_t::operator >
		(
		const double	d
		)
{
	return m_n > fx( d );
}

bool	fixed_t::operator >
		(
		const int	n
		)
{
	return m_n > fx(n);
}

bool	fixed_t::operator >
		(
		const long	n
		)
{
	return m_n > fx(n);
}

bool	fixed_t::operator >
		(
		const short	n
		)
{
	return m_n > fx(n);
}

/*---------------------------------------------------------------------+\

 * operator [greater-than-equal]

\+---------------------------------------------------------------------*/
bool	fixed_t::operator >=
		(
		const double	d
		)
{
	return m_n >= fx( d );
}

bool	fixed_t::operator >=
		(
		const int	n
		)
{
	return m_n >= fx(n);
}

bool	fixed_t::operator >=
		(
		const long	n
		)
{
	return m_n >= fx(n);
}

bool	fixed_t::operator >=
		(
		const short	n
		)
{
	return m_n >= fx(n);
}


/*---------------------------------------------------------------------+\

 * operator ++ - increment

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::operator ++
		(
		void
		)
{
	m_n += fp_1;
	return *this;
}


/*---------------------------------------------------------------------+\

 * operator -- - decrement

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::operator --
		(
		void
		)
{
	m_n -= fp_1;
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator - - unary negate

\+---------------------------------------------------------------------*/
fixed_t
fixed_t::operator -
		(
		void
		)
{
	return fixed_t( true, -m_n );
}

/*---------------------------------------------------------------------+\

 * operator + - add

\+---------------------------------------------------------------------*/
fixed_t
		fixed_t::operator +
		(
		const double	d
		)
{
	return fixed_t( true, m_n + fx( d ) );
}

fixed_t
		fixed_t::operator +
		(
		const int	n
		)
{
	return fixed_t( true, m_n + fx( n ) );
}

fixed_t
		fixed_t::operator +
		(
		const long	n
		)
{
	return fixed_t( true, m_n + fx( n ) );
}

fixed_t
		fixed_t::operator +
		(
		const short	n
		)
{
	return fixed_t( true, m_n + fx( n ) );
}


/*---------------------------------------------------------------------+\

 * operator - - subtract

\+---------------------------------------------------------------------*/
fixed_t
		fixed_t::operator -
		(
		const double	d
		)
{
	return fixed_t( true, m_n - fx( d ) );
}

fixed_t
		fixed_t::operator -
		(
		const int	n
		)
{
	return fixed_t( true, m_n - fx( n ) );
}

fixed_t
		fixed_t::operator -
		(
		const long	n
		)
{
	return fixed_t( true, m_n - fx( n ) );
}

fixed_t
		fixed_t::operator -
		(
		const short	n
		)
{
	return fixed_t( true, m_n - fx( n ) );
}


/*---------------------------------------------------------------------+\

 * operator * - multiply

\+---------------------------------------------------------------------*/
fixed_t
		fixed_t::Multiply
		(
		const fixed_t&	f
		)
{
	long_fixed_t i = (long_fixed_t)m_n * (long_fixed_t)f.m_n;
	return fixed_t( true, local_fixed_t( i >> FP_DEC_BITS) );
}

fixed_t
		fixed_t::operator *
		(
		const double	d
		)
{
	return Multiply( fixed_t( d ) );
}

fixed_t
		fixed_t::operator *
		(
		const int	n
		)
{
	return Multiply( fixed_t( n ) );
}

fixed_t
		fixed_t::operator *
		(
		const long	n
		)
{
	return Multiply( fixed_t( n ) );
}

fixed_t
		fixed_t::operator *
		(
		const short	n
		)
{
	return Multiply( fixed_t( n ) );
}


/*---------------------------------------------------------------------+\

 * operator / - divide

\+---------------------------------------------------------------------*/
fixed_t
		fixed_t::Divide
		(
		const fixed_t&	f
		)
{
	if ( 0 == f.m_n )
	{
		return fixed_t( true, ~0L );
	}
	else
	{
		long_fixed_t i = ((long_fixed_t)m_n << FP_DEC_BITS) / (long_fixed_t)f.m_n;
		return fixed_t( true, local_fixed_t(i) );
	}
}

fixed_t
		fixed_t::operator /
		(
		const double	d
		)
{
	return Divide( fixed_t( d ) );
}

fixed_t
		fixed_t::operator /
		(
		const int	n
		)
{
	return Divide( fixed_t( n ) );
}

fixed_t
		fixed_t::operator /
		(
		const long	n
		)
{
	return Divide( fixed_t( n ) );
}

fixed_t
		fixed_t::operator /
		(
		const short	n
		)
{
	return Divide( fixed_t( n ) );
}

/*---------------------------------------------------------------------+\

 * operator % - modulo

\+---------------------------------------------------------------------*/
fixed_t
		fixed_t::Modulo
		(
		const fixed_t&	f
		)
{
	if ( 0 == f.m_n )
	{
		return fixed_t( true, ~0L );
	}
	else
	{
		return fixed_t( true, m_n % f.m_n );
	}
}

fixed_t
		fixed_t::operator %
		(
		const double	d
		)
{
	return Modulo( fixed_t( d ) );
}

fixed_t
		fixed_t::operator %
		(
		const int	n
		)
{
	return Modulo( fixed_t( n ) );
}

fixed_t
		fixed_t::operator %
		(
		const long	n
		)
{
	return Modulo( fixed_t( n ) );
}

fixed_t
		fixed_t::operator %
		(
		const short	n
		)
{
	return Modulo( fixed_t( n ) );
}



/*---------------------------------------------------------------------+\

 * operator += - add to

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::operator +=
		(
		const double	d
		)
{
	m_n += fx(d);
	return *this;
}

fixed_t&
		fixed_t::operator +=
		(
		const int	n
		)
{
	m_n += fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator +=
		(
		const long	n
		)
{
	m_n += fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator +=
		(
		const short	n
		)
{
	m_n += fx(n);
	return *this;
}

/*---------------------------------------------------------------------+\

 * operator -= - subtract from

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::operator -=
		(
		const double	d
		)
{
	m_n -= fx(d);
	return *this;
}

fixed_t&
		fixed_t::operator -=
		(
		const int	n
		)
{
	m_n -= fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator -=
		(
		const long	n
		)
{
	m_n -= fx(n);
	return *this;
}

fixed_t&
		fixed_t::operator -=
		(
		const short	n
		)
{
	m_n -= fx(n);
	return *this;
}


/*---------------------------------------------------------------------+\

 * operator *= - multiply to

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::MultiplyIn
		(
		const fixed_t&	f
		)
{
	long_fixed_t i = (long_fixed_t)m_n * (long_fixed_t)f.m_n;
	m_n = local_fixed_t( i >> FP_DEC_BITS);
	return *this;
}

fixed_t&
		fixed_t::operator *=
		(
		const double	d
		)
{
	return MultiplyIn( fixed_t(d) );
}

fixed_t&
		fixed_t::operator *=
		(
		const int	n
		)
{
	return MultiplyIn( fixed_t(n) );
}

fixed_t&
		fixed_t::operator *=
		(
		const long	n
		)
{
	return MultiplyIn( fixed_t(n) );
}

fixed_t&
		fixed_t::operator *=
		(
		const short	n
		)
{
	return MultiplyIn( fixed_t(n) );
}



/*---------------------------------------------------------------------+\

 * operator /= - divide into

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::DivideIn
		(
		const fixed_t&	f
		)
{
	if ( 0 == f.m_n )
	{
		m_n = ~0L;
	}
	else
	{
		long_fixed_t i = ((long_fixed_t)m_n << FP_DEC_BITS) / (long_fixed_t)f.m_n;
		m_n = local_fixed_t(i);
	}

	return *this;
}

fixed_t&
		fixed_t::operator /=
		(
		const double	d
		)
{
	return DivideIn( fixed_t(d) );
}

fixed_t&
		fixed_t::operator /=
		(
		const int	n
		)
{
	return DivideIn( fixed_t(n) );
}

fixed_t&
		fixed_t::operator /=
		(
		const long	n
		)
{
	return DivideIn( fixed_t(n) );
}

fixed_t&
		fixed_t::operator /=
		(
		const short	n
		)
{
	return DivideIn( fixed_t(n) );
}



/*---------------------------------------------------------------------+\

 * abs - absolute value

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::abs
		(
		void
		)
{
	if ( m_n < 0 )
		m_n = -m_n;
	return *this;
}



/*---------------------------------------------------------------------+\

 * floor -

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::floor
		(
		void
		)
{
	if ( 0 <= m_n )
		m_n = m_n & ~FP_DEC_MASK;
	else
		m_n = m_n & ~FP_DEC_MASK;
	//m_n = ( 0 <= m_n ) ? (m_n>>FP_DEC_BITS) : ~((~m_n)>>FP_DEC_BITS);
	return *this;
}


/*---------------------------------------------------------------------+\

 * ceil - ceiling

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::ceil
		(
		void
		)
{
	if ( 0 != (m_n & FP_DEC_MASK) )
	{
		if ( 0 <= m_n )
			m_n = (m_n & ~FP_DEC_MASK) + fp_1;
		else
			m_n = (m_n & ~FP_DEC_MASK);
	}
	return *this;
}


/*---------------------------------------------------------------------+\

 * cos - cosine

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::cos
		(
		void
		)
{
	local_fixed_t	x = fp_clamp_angle( m_n );
	if ( x < 0 )
		x = pgm_read_fixed(&cos_table[(-x) >> fp_trig_shift]);
	else
		x = pgm_read_fixed(&cos_table[x >> fp_trig_shift]);
	m_n = x;
	return *this;
}



/*---------------------------------------------------------------------+\

 * sin - sine

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::sin
		(
		void
		)
{
	local_fixed_t	x = fp_clamp_angle( m_n );
	if ( x < 0 )
		x = -pgm_read_fixed(&sin_table[(-x) >> fp_trig_shift]);
	else
		x = pgm_read_fixed(&sin_table[x >> fp_trig_shift]);
	m_n = x;
	return *this;
}




/*---------------------------------------------------------------------+\

 * tan - tangent

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::tan
		(
		void
		)
{
	local_fixed_t	x = fp_clamp_angle( m_n );
	if ( x < 0 )
		x = -pgm_read_fixed(&tan_table[(-x) >> fp_trig_shift]);
	else
		x = pgm_read_fixed(&tan_table[x >> fp_trig_shift]);
	m_n = x;
	return *this;
}





/*---------------------------------------------------------------------+\

 * atan - arc-tangent

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::atan
		(
		void
		)
{
	int		nMin;
	int		nMax;
	int		nC;
	local_fixed_t	nDiff;
	local_fixed_t	x;

	x = m_n;

	if( 0 <= x )
	{
		nMin = 0;
		nMax = TRIG_TABLE_SIZE >> 1;
	}
	else
	{
		nMin = (TRIG_TABLE_SIZE >> 1) + 1;
		nMax = TRIG_TABLE_SIZE;
	}

	// do binary search on the tan table
	do
	{
		nC = (nMin + nMax) >> 1;
		nDiff = x - pgm_read_fixed(&tan_table[nC]);

		if( 0 < nDiff )
			nMin = nC + 1;
		else if( nDiff < 0 )
			nMax = nC - 1;

	} while ( (nMin <= nMax) && nDiff != 0 );

	//  x = (x < 0) ? int2fp(c) - fp_2_pi : int2fp(c); // exploit symmetric nature of arctan
	if( x < 0 )
		x = (nC << fp_trig_shift) - fp_pi;
	else
		x = (nC << fp_trig_shift);
	m_n = x;
	return *this;
}



/*---------------------------------------------------------------------+\

 * sqrt - square root

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::sqrt
		(
		void
		)
{
	local_fixed_t	x = m_n;

	//  if(x <= 0) return 0;
	if( m_n <= 1 )
		return k_0; // we can't divide 0x0001 in half

	fixed_t res = fixed_t( true, m_n >> 1); // start at x/2
	fixed_t max_err = *this * fixed_t( true, fp_epsilon); // maximum allowed error
	fixed_t	neg_max_err = max_err * k_neg1;
	fixed_t delta;
	fixed_t	two( 2 );

	do
	{
		delta = res * res - x;
		res -= delta / (two * res);
	} while(delta > max_err || delta < neg_max_err);

	m_n = res.m_n;
	return *this;
}


/*---------------------------------------------------------------------+\

 * square

\+---------------------------------------------------------------------*/
fixed_t&
		fixed_t::square
		(
		void
		)
{
	m_n *= m_n;
	return *this;
}







/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * fixed_t - Constructor (private)

\+---------------------------------------------------------------------*/
fixed_t::fixed_t
		(
		bool	,//bPrivate,
		const local_fixed_t	n
		)
		: m_n( n )
{
}


/*---------------------------------------------------------------------+\

 * fx - functions to help import data

\+---------------------------------------------------------------------*/
inline
local_fixed_t
		fixed_t::fx
		(
		const double	f
		) const
{
	if ( FXD_F_MAX < f )
		return FXD_MAX_LOCAL;
	else if ( f < -FXD_F_MAX )
		return FXD_MAX_LOCAL;
	else
		return (local_fixed_t)(f * (((long_fixed_t)1)<<FP_DEC_BITS));
}

inline
local_fixed_t
		fixed_t::fx
		(
		const int	n
		) const
{
	if ( FXD_MAX_INT < n )
		return FXD_MAX_LOCAL;
	else if ( n < -FXD_MAX_INT )
		return -FXD_MAX_LOCAL;
	else
		return n << FP_DEC_BITS;
}

inline
local_fixed_t
		fixed_t::fx
		(
		const unsigned int	n
		) const
{
	if ( FXD_MAX_INT < n )
		return FXD_MAX_LOCAL;
	else
		return n << FP_DEC_BITS;
}

inline
local_fixed_t
		fixed_t::fx
		(
		const long	n
		) const
{
	if ( FXD_MAX_INT < n )
		return FXD_MAX_LOCAL;
	else if ( n < -FXD_MAX_INT )
		return -FXD_MAX_LOCAL;
	else
		return n << FP_DEC_BITS;
}

inline
local_fixed_t
		fixed_t::fx
		(
		const unsigned long	n
		) const
{
	if ( FXD_MAX_INT < n )
		return FXD_MAX_LOCAL;
	else
		return n << FP_DEC_BITS;
}

inline
local_fixed_t
		fixed_t::fx
		(
		const short	n
		) const
{
	return local_fixed_t(n) << FP_DEC_BITS;
}

inline
local_fixed_t
		fixed_t::fx
		(
		const unsigned short	n
		) const
{
	if ( FXD_MAX_INT < n )
		return FXD_MAX_LOCAL;
	else
		return local_fixed_t(n) << FP_DEC_BITS;
}





#else
int	dummy_fixed_t = 0;	// just here to prevent a warning message
#endif


/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


//}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
