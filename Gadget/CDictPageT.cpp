/*---------------------------------------------------------------------+\
|
|	CDictPageT.cpp  --  'test' dictionary page
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
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Change the arguments to AddAlias to be 'const'
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement dummy enumerator
		Implement new globally standardized update functions
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	02-Sep-2009			R.Hosea
		Mods for gcc compatibility
	10-Jul-2009			J.Griswold
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
#include "CDictPageT.h"
#include "UPlatform.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

namespace Yogi { namespace Gadget {
//USING_NAMESPACE_COMMON

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
//static int GetMilliCount()
//{
//	// Something like GetTickCount but portable
//	// It rolls over every ~ 12.1 days (0x100000/24/60/60)
//	// Use GetMilliSpan to correct for rollover
//	timeb tb;
//	ftime( &tb );
//	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
//	return nCount;
//}
//
//static int GetMilliSpan( int nTimeStart )
//{
//	int nSpan = GetMilliCount() - nTimeStart;
//	if ( nSpan < 0 )
//		nSpan += 0x100000 * 1000;
//	return nSpan;
//}




/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictPageT - constructor

\+---------------------------------------------------------------------*/
CDictPageT::CDictPageT
		(
		void
		)
		: VDictionaryPage(),
		m_nValue( 0 ),
		m_nMilli( 0 ),
		m_bAscending( false ),
		m_X( 100.0f ),
		m_Y( 100.0f ),
		m_Panel(),
		m_Spin( 0.0f ),
		m_Slider( 0.0f ),
		m_SliderYellow( 45.0f ),
		m_SliderRed( 75.0f ),
		m_Milli( 0.0f )
{
	m_Panel = CCharDescriptor( "test" );
}


/*---------------------------------------------------------------------+\

 * ~CDictPageT - destructor

\+---------------------------------------------------------------------*/
CDictPageT::~CDictPageT
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


void	CDictPageT::BumpValues
		(
		void
		)
{
}


void	CDictPageT::SetPageActive
		(
		CDictPageActivePtr p
		)
{
	m_pPageActive = p;
}


void	CDictPageT::SetPageBase
		(
		CDictPageVariantPtr p
		)
{
	m_pPageBase = p;
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


void	CDictPageT::BeginCalculate
		(
		void
		)
{
	long	n = m_pDictionary->GetMilliseconds();
	m_nMilli = n;
	m_nValue = (n / 50) % 100;
	if ( ((n / 50) % 200) < 100 )
		m_bAscending = true;
	else
		m_bAscending = false;



}



long	CDictPageT::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	const char*	sName = rName.Pointer();
	if ( 0 == ::_stricmp( sName, "X" ) )
		return 1;
	else if ( 0 == ::_stricmp( sName, "PULSER" ) )
		return 2;
	else if ( 0 == ::_stricmp( sName, "PANEL" ) )
		return 3;
	else if ( 0 == ::_stricmp( sName, "SPIN" ) )
		return 4;
	else if ( 0 == ::_stricmp( sName, "SLIDER" ) )
		return 5;
	else if ( 0 == ::_stricmp( sName, "SLIDER.YELLOW" ) )
		return 6;
	else if ( 0 == ::_stricmp( sName, "SLIDER.RED" ) )
		return 7;
	else if ( 0 == ::_stricmp( sName, "MILLI" ) )
		return 8;
	return 0;
}





CVariantDataPtr
		CDictPageT::GetData
		(
		unsigned long nSel
		)
{
	long	y;
	switch ( nSel )
	{
	case 1:
		return &m_X;
	case 2:
		if ( m_bAscending )
		{
			y = m_nValue;
		}
		else
		{
			y = 100 - m_nValue;
		}
		m_Y = y;
		return &m_Y;
	case 3:
		return &m_Panel;
	case 4:
		{
			float	f;
			f = (3.141592654f*2) * float(m_nValue) / 100.0f;
			m_Spin = f;
		}
		return &m_Spin;
	case 5:
		{
			m_Slider = m_nValue;
		}
		return &m_Slider;
	case 6:
		return &m_SliderYellow;
	case 7:
		return &m_SliderRed;
	case 8:
		m_Milli = m_nMilli;
		return &m_Milli;
	default:
		return 0;
	}
}


bool	CDictPageT::PutData
		(
		unsigned long,			//nSel,
		CVariantDataPtr //pData
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageT::UpdateByName
		(
		CCharDescriptorRef		,//rKey,
		CVariantDataRef	//rData
		)
{
	return false;
}

/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageT::AddAlias
		(
		ConstCCharDescriptorRef	,//rKey,
		ConstCCharDescriptorRef	//rAlias
		)
{
	return true;
}





VDictionaryEnumerator*
		CDictPageT::GetEnumerator
		(
		void
		)
{
	return 0;
}





}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
