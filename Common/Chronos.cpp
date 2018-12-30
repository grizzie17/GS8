
#include "stdafx.h"
#include "Chronos.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformTime.h"

#include "UDeclCommon.h"

#undef DECL_CLASS
#define DECL_CLASS

#undef DECL_API
#define DECL_API(t)		t

namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|
|	Private Global Variables
|
\+---------------------------------------------------------------------*/

Chronos::ChronosLogEntry   Chronos::g_aLog[TE_MAX+1] = {{0}};







DECL_CLASS
Chronos::Chronos()
		: m_nStart(0)
		, m_nID(0)
{
	StartTimer();
}

DECL_CLASS
Chronos::Chronos
		(
		int nID
		)
		: m_nStart(0)
		, m_nID( nID )
{
	StartTimer();
}

DECL_CLASS 
Chronos::Chronos
		(
		int nID,
		const char* sName
		)
		: m_nStart(0)
		, m_nID( nID )
{
	g_aLog[nID].sName = sName;
	StartTimer();
}

DECL_CLASS
Chronos::~Chronos()
{
	StopTimer();
}


DECL_API(time_t)
		Chronos::StartTimer()
{
#if defined( OS_MSWIN )
	LARGE_INTEGER	pc;
	QueryPerformanceCounter( &pc );
	return m_nStart = (time_t)pc.QuadPart;
#elif defined( OS_LINUX )
	timeval		tv;

	gettimeofday( &tv, NULL );
	return m_nStart = tv.tv_sec * 1000000 + tv.tv_usec;

#endif
}

DECL_API(time_t)
		Chronos::StopTimer()
{
	time_t	nDelta = 0;
#if defined( OS_MSWIN )
	LARGE_INTEGER	pc;
	QueryPerformanceCounter( &pc );
	nDelta = (time_t)pc.QuadPart - m_nStart;
#elif defined( OS_LINUX )
	timeval	tv;
	gettimeofday( &tv, NULL );
	nDelta = (tv.tv_sec * 1000000 + tv.tv_usec) - m_nStart;
#endif
	g_aLog[m_nID].nCount ++;
	g_aLog[m_nID].nElapsedTime += nDelta;
	return nDelta;

}

//static
DECL_API(time_t)
		Chronos::Frequency()
{
#if defined( OS_MSWIN )
	LARGE_INTEGER  frq;

	QueryPerformanceFrequency(&frq);
	return (time_t)frq.QuadPart;
#elif defined( OS_LINUX )
	return 1000;
#endif
}

//static
DECL_API(void)
		Chronos::PrintLog()
{
#ifdef USE_CHRONOS

	ChronosLogEntry*  p = g_aLog;
	ChronosLogEntry*  pEnd = p + TE_MAX;
	LogPrint( "Chronos log\n");
	const char sUnk[] = "Unknown";
	double            freq = (double)Frequency() / 1000.0;

	LogPrint( "calls, ticks, milli, milli per call, function\n");
	while ( p < pEnd )
	{
		const char* s = p->sName ? p->sName : sUnk;
		double   dMilli = (double)p->nElapsedTime / freq;
		double   dPerCall = 0 < p->nCount ? dMilli / (double)p->nCount : 0.0;

		LogPrint( "%10ld, %16llu, %0.6f, %0.6f, %s\n", p->nCount, p->nElapsedTime, dMilli, dPerCall, s );
		p++;
	}
	LogPrint( "Chronos done\n");

#endif
}


}}
