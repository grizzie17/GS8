/*---------------------------------------------------------------------+\
|
|	CDictHandlerTime.cpp  --  brief description of what CDictHandlerTime.cpp is for
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
	23-Jan-2010			M.Rose			(Reviewed by: N.Graham)
		Fix compile warning
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Forced the type to be Date/Time when loading the variant
		data for the GetData function
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		changed to gmtime_s to fix compiler warnings on MSVC
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	10-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDictHandlerTime.h"
#include "CDateTime.h"
#include "UPlatformTime.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

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

static bool			g_bCalculated = false;
static long			g_nMilli = 0;
static CDateTime	g_oTime;

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

 * DerivedClass - constructor

\+---------------------------------------------------------------------*/
CDictTimeBase::CDictTimeBase
		(
		void
		)
		: VDictPageHandler()
{
}


/*---------------------------------------------------------------------+\

 * ~DerivedClass - destructor

\+---------------------------------------------------------------------*/
CDictTimeBase::~CDictTimeBase
		(
		void
		)
{
}

bool	CDictTimeBase::BeginCalculate
		(
		CDictPageSystemPtr //pPage
		)
{
	if ( ! g_bCalculated )
	{
		g_bCalculated = true;
		g_nMilli = milliseconds();
		g_oTime = CDateTime::CurrentTime();
	}
	return true;
}

bool	CDictTimeBase::EndCalculate
		(
		CDictPageSystemPtr	//pPage
		)
{
	g_bCalculated = false;
	return true;
}


ConstCVariantDataPtr
		CDictTimeBase::GetData
		(
		CDictPageSystemPtr //pPage
		)
{
	return &m_tData;
}


bool	CDictTimeBase::PutData
		(
		CDictPageSystemPtr,
		ConstCVariantDataPtr
		)
{
	return false;	// no public put data allowed
}



ConstCVariantDataPtr
		CDictTime_Milli::GetData
		(
		CDictPageSystemPtr pPage
		)
{
	m_tData = g_nMilli;
	return CDictTimeBase::GetData( pPage );
}



ConstCVariantDataPtr
		CDictTime_Absolute_Time::GetData
		(
		CDictPageSystemPtr pPage
		)
{
	m_tData = g_oTime;
	return CDictTimeBase::GetData( pPage );
}



/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


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
