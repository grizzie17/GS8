#ifndef _H_CheckLeaks
#define _H_CheckLeaks
#pragma once

#include <stdio.h>
#include "UMachine.h"
#include "UWarnings.h"


#if defined( _DEBUG )
// enable memory leak detection
#	if (defined( _WIN32 )  ||  defined( _WIN64 ))  // &&  ( ! defined(__GNUC__) )
#		ifndef _WIN32_WCE
#			define _CRTDBG_MAP_ALLOC
#			include <stdlib.h>
#			include <crtdbg.h>
#			define CHECK_LEAKS \
				_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#			define CHECK_WINDOWS
#		endif
#	elif defined( __linux__ )	\
		||	defined( _linux )	\
		||	defined( linux )
#		define CHECK_VALGRIND
#		include <valgrind/valgrind.h>
#		include <valgrind/memcheck.h>
#	endif
#endif // _DEBUG
#ifndef CHECK_LEAKS
#	define CHECK_LEAKS
#endif



class Leaks
{
public:
	Leaks()
	{
#ifdef _DEBUG
#	if defined( CHECK_WINDOWS )
		_CrtMemCheckpoint( &m_xStateBase );
#	elif defined( CHECK_VALGRIND )
		m_nBaseDefinite = 0;
		m_nBaseDubious = 0;
		m_nBaseReachable = 0;
		m_nBaseSuppressed = 0;
		if ( RUNNING_ON_VALGRIND )
		{
			VALGRIND_DO_LEAK_CHECK;
			VALGRIND_COUNT_LEAKS( m_nBaseDefinite, m_nBaseDubious, m_nBaseReachable, m_nBaseSuppressed );
		}
#	endif
#endif
	}

	~Leaks()
	{
//#if 0
		HasLeaks();
//#endif
	}

	bool	HasLeaks()
	{
		bool	bResult = false;
#if defined(_DEBUG)
#	if defined(CHECK_WINDOWS)
		_CrtMemCheckpoint( &m_xStateCheck );
		if ( _CrtMemDifference( &m_xStateDiff, &m_xStateBase, &m_xStateCheck ) )
		{
			bResult = true;
			_CrtMemDumpStatistics( &m_xStateDiff );
		}
#	elif defined(CHECK_VALGRIND)
		if ( RUNNING_ON_VALGRIND )
		{
			unsigned long	nLeaked = 0;
			unsigned long	nDubious = 0;
			unsigned long	nReachable = 0;
			unsigned long	nSuppressed = 0;

			//printf( "********************* VALGRIND *********************\n");
			VALGRIND_DO_LEAK_CHECK;
			VALGRIND_COUNT_LEAKS( nLeaked, nDubious, nReachable, nSuppressed );

			if ( m_nBaseDefinite != nLeaked
				||	m_nBaseDubious != nDubious
				||	m_nBaseReachable != nReachable
				||	m_nBaseSuppressed != nSuppressed )
			{
				bResult = true;
			}
		}
#	endif
#endif

		return bResult;
	}

protected:
#if defined( CHECK_WINDOWS )
	_CrtMemState	m_xStateBase;
	_CrtMemState	m_xStateCheck;
	_CrtMemState	m_xStateDiff;
#elif defined( CHECK_VALGRIND )
	unsigned long	m_nBaseDefinite;
	unsigned long	m_nBaseDubious;
	unsigned long	m_nBaseReachable;
	unsigned long	m_nBaseSuppressed;
#endif

};


#endif // _H_CheckLeaks
