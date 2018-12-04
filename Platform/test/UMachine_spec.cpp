#include "stdafx.h"

#include "UMachine.h"

#include "igloo/igloo.h"
using namespace igloo;


// test UMachine macros

Context(UMachine_macros)
{
	Spec(it_has_macro_for_OS_type)
	{
#		if defined( OS_LINUX )
#		elif defined( OS_MSWIN )
#		elif defined( OS_UNIX )
#		elif defined( OS_MACINTOSH )
#		elif defined( OS_VMS )
#		else
		Assert::Failure( "UMachine does not defined an OS Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_CSTD)
	{
#		if defined( CSTD_CRTDEFS )
#		elif defined( CSTD_UNISTD )
#		else
		Assert::Failure( "UMachine does not defined a CSTD Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_THREADS)
	{
#		if defined( THREADS_WINDOWS )
#		elif defined( THREADS_POSIX )
#		else
		Assert::Failure( "UMachine does not defined a THREADS Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_SEMAPHORE)
	{
#		if defined( SEMAPHORE_WINDOWS )
#		elif defined( SEMAPHORE_POSIX )
#		else
		Assert::Failure( "UMachine does not defined a SEMAPHORE Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_SIGNAL)
	{
#		if defined( SIGNAL_WINDOWS )
#		elif defined( SIGNAL_POSIX )
#		else
		Assert::Failure( "UMachine does not defined a SIGNAL Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_SERIAL)
	{
#		if defined( SERIAL_WINDOWS )
#		elif defined( SERIAL_POSIX )
#		else
		Assert::Failure( "UMachine does not defined a SERIAL Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_DLL)
	{
#		if defined( DLL_WINDOWS )
#		elif defined( DLL_UNISTD )
#		else
		Assert::Failure( "UMachine does not defined a DLL Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_FILEIO)
	{
#		if defined( FILEIO_WINDOWS )
#		elif defined( FILEIO_UNISTD )
#		else
		Assert::Failure( "UMachine does not defined a FILEIO Macro for this OS" );
#		endif
#		if defined( FILEIO_STDIO )
#		else
		Assert::Failure( "UMachine does not defined a FILEIO_STDIO Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_TIME)
	{
#		if defined( TIME_WINDOWS )
#		elif defined( TIME_UNISTD )
#		else
		Assert::Failure( "UMachine does not defined a TIME Macro for this OS" );
#		endif
	}

	Spec(it_has_macro_for_EXE_path)
	{
#		if defined( EXE_WINDOWS )
#		elif defined( EXE_MACINTOSH )
#		elif defined( EXE_LINUX )
#		elif defined( EXE_UNIX )
#		else
		Assert::Failure( "UMachine does not defined an EXE Macro for this OS" );
#		endif
	}
};
