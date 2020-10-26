/*---------------------------------------------------------------------+\
|
|	UMachine.h  --  #define symbols for different machine types
|
|	Purpose:

		This file defines a set of preprocessor symbols that identify
		the type of machine, operating system and some of the
		characteristics of that environment.

		The main symbols that are created are:

			OS_xxxxxx		- operating system
			GUI_xxxxxx		- graphical user interface
			GL_xxxxxx		- graphic library
			ENDIAN_xxx		- memory order
			BITFIELDS_xxx	- bit order for bitfields in structures
			NEWLINE_xxx		- line feed separators
			CPU_xxxxxx		- hardware processor

		The following are the actual symbols that are defined.

			CPU_xxxxxxx

				CPU_ALPHA
				CPU_CLIPPER
				CPU_HP700
				CPU_INTELx86		- 386, 486, Pentium
				CPU_MC68000			- 000, 020, 030, 040
					CPU_MC68K
				CPU_MIPS
				CPU_POWERPC
				CPU_RS6000
				CPU_SPARC
				CPU_VAX

			OS_xxxx

				OS_MACINTOSH
				OS_MSDOS
				OS_MSWIN
					OS_MSWIN_WCE
					OS_WIN31
					OS_WIN32
						OS_WINNT
						OS_WIN32_WCE - windows CE
					OS_WIN64
					OS_WIN_MACPORT	- windows (wings) porting tool
					OS_MSWIN_FAKE	- MFC implemented on the Macintosh
					GL_GDI
					GL_DIRECTX
				OS_OS2 - not implemented
				OS_UNIX
					OS_UNIX_BSD
						OS_SUNOS
					OS_UNIX_SVID
						OS_CLIX
						OS_PC_UNIX
						OS_SCO_UNIX
						OS_SOLARIS
				OS_LINUX
					OS_LINUX_VDDS
					GL_OPENGL
				OS_VMS

			GUI_xxxx

				GUI_ENV5
				GUI_GLUT
				GUI_MACINTOSH
				GUI_MOTIF
				GUI_MSWINDOWS
					GUI_WIN_MACPORT
				GUI_OS2 - not implemented
				GUI_XWINDOWS

			ENDIAN_xxx

				ENDIAN_BIG
				ENDIAN_LITTLE

			BITFIELDS_xxx

				BITFIELDS_ASCEND
				BITFIELDS_DESCEND

			NEWLINE_xxx

				NEWLINE_CR
				NEWLINE_CRLF
				NEWLINE_LF

|	Restrictions/Warnings:
|
|		Please take note that some of the preprocessor symbols depend
|		on C compiler command line -Dname to be set.
|
|		OS_SOLARIS		-Dsolaris
|		OS_WINNT		-DwinNT
|		OS_WIN32		-DWIN32
|		OS_WIN_MACPORT	-D_MAC
|		OS_LINUX		-D__VDDS_LINUX__
|		GL_OPENGL_VDDS	-D__VDDS_LINUX__
|		GL_OPENGL		-D_OPENGL_
|		GL_OPENGL_ES	-D_OPENGL_ES_
|		GUI_XWINDOWS	-DXWindow if OS_CLIX
|
|	Formats:
|	References:
|	Notes:
|
|		It should be noted that this file must be modified to accomodate
|		additional compilers or changes to the predefined preprocessor
|		symbols provided by the various compilers.
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	12-Feb-2013			J.Griswold
		Modernize the macro tests to use more contemporary values
	17-Jan-2013			J.Griswold
		Modify the Apple Macintosh stuff to work with more modern compilers
	12-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for "graphic library" GL_xxxxx defines
	29-Jul-2009			J.Griswold
		Add support for FOLDER_SEPARATOR
	01-Jul-2009			J.Griswold
		Add support for LINUX
	02-Aug-1997			J.Griswold
		Make sure that _X86_ is defined if this is compiling
		on an intel box.
	12-Feb-1997			J.Griswold
		Move alignment information to align.h
	31-Mar-1996
		Make sure OS_WIN32 is defined when OS_WINNT is defined.
		Also define OS_MACOS in addition to OS_MACINTOSH.
	24-Mar-1996
		oops, I had not changed the #if that used to be first to a
		#elif.  That now works a whole lot better.
	21-Mar-1996
		Switch os order so MSWIN is before Macintosh.  This was done
		so we can define WIN32 to create a fake MFC class library to
		build apps on the Macintosh.
	31-Oct-1995
		Add support for MetroWerks Win32/x86 cross compiler
	27-Sep-1995
		Add "mw_rez" to the list of compiler flags for the mac, to
		support the MetroWerks "rez" compiler.
	04-Apr-1995
		Remove the 'sco' symbol that was only provided for the Intergraph
		'ris' product.  This file should not become a kludge for a particular
		product.  Another file should be created to map our OS_xxx symbols
		into the product specific symbols.
	17-Mar-1995
		add SYMANTEC_CPLUS to the list of compiler flags for the mac.
		This is necessary for SC++ 8.
	12-Dec-1994
		changed OS_MAC_WINPORT to be OS_WIN_MACPORT which is more descriptive.
		I also changed it so it will only get defined in the windows env.
	19-Jul-1994
		add windows to mac portability symbols for "Wings" product
	03-Jul-1994
		add NEWLINE_xxx definitions
	23-Jun-1994
		Major cleanup and additional definitions
	22-Sep-1993
		forgot the line continuation character on some macros.
	02-Aug-1993
		Add BITFIELDS_ASCEND and BITFIELDS_DESCEND
	01-Aug-1993
		Add the definitions for rs6000
	17-Oct-1989			J.Griswold
		Original version
|
\+---------------------------------------------------------------------*/
#ifndef _H_UMachine
#define _H_UMachine
#pragma once


/*
//	The operating system OS_xxxx and processor CPU_xxxx are identified
//	in this section.
*/

/*=====================================================================+\
|	Windows
\+=====================================================================*/
#if defined( winNT )  || defined( WINNT )			\
		||	defined( _WIN32 )  ||  defined( WIN32 )	\
		||	defined( _WIN64 )  ||  defined( WIN64 )	\
		||	defined( _WIN32_WCE )  ||  defined( _MSC_VER )


#	ifdef		msdos	/* we don't do no dos */
#		undef	msdos
#	endif
#	ifdef		MSDOS
#		undef	MSDOS
#	endif


#	define	OS_MSWIN		1
#	define	OS_MSWINDOWS	1
#	if defined( GLUT )
#		define GUI_GLUT			1
#		define GL_OPENGL 		1
#	else
#		define	GUI_MSWINDOWS	1
#		define	GL_GDI			1
#		define	GL_DIRECTX		1
#	endif

#	undef OS_LINUX
#	undef OS_MACINTOSH
#	undef OS_MACOS
#	undef OS_UNIX
#	undef unix
#	undef __unix
#	undef __unix__

#	if defined( __MSYS__ )
#		define	OS_MSWIN_MSYS	1
#	elif defined( __MINGW64__ )
#		define  OS_MSWIN_MINGW	1
#	elif defined( __GNUC__ )
#		define	OS_MSWIN_GNU	1
#	endif

#	if defined( _OPENGL_ES_ )  ||  defined( OPENGLES )
#		define	GL_OPENGL_ES	1
#		define	GL_WINGL_ES		1
#	elif defined( _OPENGL_ )  ||  defined( OPENGL )
#		define	GL_OPENGL	1
#		define	GL_WINGL	1
#	endif

#	if defined( _WIN64 )  ||  defined( WIN64 )

#		define	OS_WIN64		1
#		define	OS_NAME			"MSWIN64"
#		define	CPU_INTELx64	1
#		if !defined( _x64_ )
#			define	_x64_		1
#		endif

#	elif defined( _WIN32_WCE )

#		define	OS_WIN32_WCE	1
#		define	OS_MSWIN_WCE	1
#		define	OS_NAME			"MSWIN_WCE"
#		if ! defined( GL_OPENGL_ES )
#			define	GL_OPENGL_ES	1
#			define	GL_WINGL_ES		1
#		endif


#	else
#		define	OS_WIN32		1
#		define	OS_NAME			"MSWIN32"
#		define	CPU_INTELx86	1
#		if !defined( _X86_ )
#			define _X86_		1
#		endif
#	endif

#	if defined( _MAC )				/* Wings: Macintosh porting stuff */
#		define	OS_WIN_MACPORT	1
#		define	GUI_WIN_MACPORT	1
#		define	GUI_MACINTOSH	1
#		undef	GUI_MSWINDOWS
#	endif





/*=====================================================================+\
|	LINUX
\+=====================================================================*/
#elif defined( __linux__ )	\
	||	defined( _linux )	\
	||	defined( linux )    \
	||	defined( __MSYS__ )	\
	||	defined( ELF )

#	define	OS_LINUX	1
#	define	OS_NAME		"LINUX"
#	undef	OS_MSWIN
#	undef	OS_MSWINDOWS
#	undef	OS_MACOS
#	undef	OS_MACINTOSH

#	if defined( _VDDS_LINUX_ )	\
		||  defined( __VDDS_LINUX__ )	\
		||	defined( LINUX_VDDS )
#		define	OS_LINUX_VDDS	1		// DRS-TEM
#		define	GL_OPENGL_VDDS	1
#	endif
#	if defined( _OPENGL_ )  ||  defined( OPENGL )
#		define	GL_OPENGL	1
#	elif defined( _OPENGL_ES_ )  ||  defined( OPENGLES )
#		define	GL_OPENGL_ES	1
#	endif
#	if defined( _GTK_ )  ||  defined( GTK )
#		define	GL_GTK	1
#	endif
	/*-------------------------------------------- MSYS (POSIX) */
#	if defined( __MSYS__ )
#		define	OS_MSYS			1
#		define	OS_LINUX_MSYS	1
#	endif

//#	define _POSIX_ASYNCHRONOUS_IO 1
#	include <semaphore.h>





/*=====================================================================+\
|	Macintosh
\+=====================================================================*/
#elif defined( __APPLE__ )  ||  defined( __MACH__ )

#	include "TargetConditionals.h"

#	if TARGET_OS_IPHONE
#	elif TARGET_IPHONE_SIMULATOR
#	elif TARGET_OS_MAC

#		define	OS_MACINTOSH	1
#		define	OS_MACOS		1
#		define	OS_NAME			"MACOS"
#		define	GUI_MACINTOSH	1
#		if defined( powerpc )			\
			||  defined( powerc )	\
			||  defined( __powerc )	\
			||	defined( __POWERPC__ )
#			define	CPU_POWERPC	1
#		elif defined( __amd64__ )
#			define	CPU_AMD64	1
#		else
#			define	CPU_MC68000	1
#			define	CPU_MC68K	1
#		endif

#	else
#		error "unrecognized Apple platform"
#	endif


/*=====================================================================+\
|	MSDOS
\+=====================================================================*/
#elif defined( pm386 )  ||  defined( MSDOS )

#	define	OS_MSDOS		1
#	define	OS_NAME			"MSDOS"
#	define	CPU_INTELx86	1




/*=====================================================================+\
|	Unix
\+=====================================================================*/
#elif defined( unix )			\
		||	defined( __unix )	\
		||	defined( __unix__ )	\
		||	defined( __UNIX__ )

#	define	OS_UNIX		1
#	define	OS_NAME		"UNIX"

#	if defined( _OPENGL_ )  ||  defined( OPENGL )
#		define	GL_OPENGL	1
#	elif defined( _OPENGL_ES_ )  ||  defined( OPENGLES )
#		define	GL_OPENGL_ES	1
#	endif
#	if defined( _GTK_ )  ||  defined( GTK )
#		define	GL_GTK	1
#	endif

	/*-------------------------------------------- Intergraph Clipper */
#	if defined( __clipper )  ||  defined( __clipper__ )

#		define	OS_CLIX			1
#		define	OS_UNIX_SVID	1
#		define	CPU_CLIPPER		1
#		ifdef XWindow
#			define	GUI_XWINDOWS	1
#		else
#			define	GUI_ENV5		1
#		endif

	/*-------------------------------------------- AIX */
#	elif defined( _AIX )

#		define	OS_AIX				1
#		define	OS_UNIX_AIX			1

	/*-------------------------------------------- BSD */
#	elif defined( __FreeBSD__ )	\
			||	defined( __NetBSD__ )	\
			||	defined( __OpenBSD__ )

#		define	OS_UNIX_BSD			1

	/*-------------------------------------------- MSYS (POSIX) */
#	elif defined( __MSYS__ )

#		define	OS_MSYS			1
#		define	OS_UNIX_MSYS	1

	/*-------------------------------------------- Cygwin (POSIX) */
#	elif defined( __CYGWIN__ )

#		define	OS_CYGWIN		1
#		define	OS_UNIX_CYGWIN	1

	/*-------------------------------------------- Sun Sparc */
#	elif defined( __sun )			\
			||  defined( __SVR4 )

#		define	OS_SOLARIS		1
#		define	OS_UNIX_SOLARIS	1
#		define	OS_UNIX_SVID	1

	/*-------------------------------------------- SCO */
#	elif defined( M_I386 )

#		define	OS_UNIX_PC		1
#		define	OS_UNIX_SCO		1
#		define	OS_UNIX_SVID	1
#		define	CPU_INTELx86	1

	/*-------------------------------------------- HP */
#	elif defined( __hpux )

#		define	OS_UNIX_HPUX	1

	/*-------------------------------------------- IBM/RS6000 */
#	elif defined( __XLC121__ )

#		define	CPU_RS6000		1
		/* NEEDS_WORK: add SVID or BSD definition */

#	else
#		error "machine.h--Undefined unix elif definition"
#	endif




/*=====================================================================+\
|	VMS
\+=====================================================================*/
#elif defined( vms )  ||  defined( VMS )

#	define	OS_VMS	1
#	define	OS_NAME	"VMS"
#	if defined( vax )
#		define	CPU_VAX
#	else
#		error "machine.h--undefined cpu for VMS"
	/*
	//	NEEDS_WORK: add stuff for the ALPHA processor
	*/
#	endif


/*=====================================================================+\
|	????
\+=====================================================================*/
#else
#	error "umachine.h--undefined operating system definition"
#endif
/*================================================*/


/* define this for compatibility with older machine.h */
#ifdef CPU_INTELx86
#	define CPU_INTEL386		1
#endif


#if defined( __mips )  ||  defined( mips )
#	ifndef CPU_MIPS
#		define  CPU_MIPS	1
#	endif
#elif defined( rs6000 )
#	ifndef CPU_RS6000
#		define	CPU_RS6000	1
#	endif
#endif


/* define constants for windowing system used */
#if defined( CPU_SPARC )			\
		|| defined( CPU_VAX )		\
		|| defined( CPU_HP700 )		\
		|| defined( OS_PC_UNIX )	\
		|| defined( CPU_RS6000 )	\
		|| defined( CPU_MIPS )
#	if ! defined( GUI_XWINDOWS )  &&  ! defined( GUI_MSWINDOWS )
#		define	GUI_XWINDOWS	1
#	endif
#endif

/*---------------------------------------------------------------------+\
|	 End of defining the machine identification constants.				|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|																		|
|	Platform specific capabilities										|
|																		|
\+---------------------------------------------------------------------*/
/*
//	define text new-line symbols
*/
#if defined( OS_MSDOS )  ||  defined( OS_MSWIN )
#	define	NEWLINE_CRLF	1
#elif defined( OS_UNIX )  ||  defined( OS_LINUX )
#	define	NEWLINE_LF		1
#elif defined( OS_MACINTOSH )  ||  defined( OS_WIN_MACPORT )
#	define	NEWLINE_CR		1
#else
#	error "umachine.h--undefined new-line definition"
#endif


/*
//	define directory/folder separator
*/
#if defined( OS_MSDOS )  ||  defined( OS_MSWIN )
#	define FOLDER_BACKSLASH		1
#	define FOLDER_SEPARATOR_C	'\\'
#	define FOLDER_SEPARATOR_S	"\\"
#elif defined( OS_LINUX )  ||  defined( OS_UNIX )  ||  defined( OS_MACINTOSH )
#	define FOLDER_SLASH			1
#	define FOLDER_SEPARATOR_C	'/'
#	define FOLDER_SEPARATOR_S	"/"
#elif defined( OS_MACINTOSH )
	/*	note new macintosh uses unix style folder separators */
#	define FOLDER_COLON			1
#	define FOLDER_SEPARATOR_C	':'
#	define FOLDER_SEPARATOR_S	":"
#else
#	error "UMachine.h--undefined directory separator"
#endif

#define FOLDER_SEPARATOR	FOLDER_SEPARATOR_C

/*
//	identify the memory order
*/
#if defined( CPU_HP700 )			\
		||	defined( CPU_MC68000 )	\
		||	defined( CPU_MC68K )	\
		||	defined( CPU_POWERPC )	\
		||	defined( CPU_RS6000 )	\
		||	defined( CPU_SPARC )
#	define	ENDIAN_BIG			1
#	define	BITFIELDS_DESCEND	1
#	define	BIG_ENDIAN				/* compatibility with ustn */
#	define	BITFIELDS_REVERSED		/* compatibility with ustn */
#else
#	define	ENDIAN_LITTLE		1
#endif
#if ! defined( BITFIELDS_DESCEND )
#	define BITFIELDS_ASCEND		1
#endif

/*
//	identify CSTD
*/
#if defined( OS_LINUX )  ||  defined( OS_UNIX )  ||  defined( OS_MACINTOSH )  ||  defined( OS_MSWIN_GNU )
#	define	CSTD_UNISTD		1
#	include <unistd.h>
#elif defined( OS_MSWIN )
#	define	CSTD_CRTDEFS	1
#endif

/*
//	identify File I/O
*/
#if defined( OS_MSWIN )
#	define FILEIO_WINDOWS	1
#	define FILEIO_STDIO		1
#elif defined( OS_LINUX )  ||  defined( OS_UNIX )  ||  defined( OS_MACINTOSH )
#	define FILEIO_UNISTD	1
#	define FILEIO_STDIO		1
#else
#	error "FILEIO_xxxx macro is undefined"
#endif


/*
//	identify time
*/
#if defined( OS_MSWIN )
#	define TIME_WINDOWS		1
#elif defined( OS_LINUX )  ||  defined( OS_UNIX )  ||  defined( OS_MACINTOSH )  ||  defined( OS_MSWIN_GNU )
#	define TIME_UNISTD		1
#else
#	error "TIME_xxxx macro is undefined"
#endif


/*
//	identify signals
*/
#if defined( OS_MSWIN )
#	define SIGNAL_WINDOWS	1
#elif defined( _POSIX_REALTIME_SIGNALS )
#	define SIGNAL_POSIX		1
#else
#	error "undefined SIGNAL_xxx macro"
#endif

/*
//	identify serial i/o
*/
#if defined( OS_MSWIN )
#	define SERIAL_WINDOWS	1
#elif defined( _POSIX_ASYNCHRONOUS_IO )
#	define SERIAL_POSIX		1
#else
#	error "SERIAL_xxxx macro is undefined"
#endif

/*
//	identify semaphores
*/
#if defined( OS_MSWIN )
#	define SEMAPHORE_WINDOWS	1
#elif defined( _POSIX_SEMAPHORES )
#	define	SEMAPHORE_POSIX		1
#elif defined( OS_MACINTOSH )
#	define SEMAPHORE_MACINTOSH	1
#else
#	error "SEMAPHORE_xxxx macro is undefined"
#endif


/*
//	identify executable path
*/
#if defined( OS_MSWIN )
#	define	EXE_WINDOWS		1
#elif defined( OS_MACINTOSH )
#	define	EXE_MACINTOSH	1
#elif defined( OS_LINUX )
#	define	EXE_LINUX		1
#elif defined( OS_UNIX )
#	define	EXE_UNIX		1
#else
#	error "EXE_xxxx macro is undefined"
#endif

/*
//	identify thread processing
*/
#if defined( OS_MSWIN )
#	define	THREADS_WINDOWS	1
#elif defined( _POSIX_THREADS )
#	define	THREADS_POSIX	1
#else
#	error "THREADS_xxxx macro is undefined"
#endif

#if defined( OS_MSWIN )
#	define	DLL_WINDOWS	1
#else
#	define	DLL_UNISTD	1
#endif

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Function Macros														|
||																		|
\+=====================================================================*/


#endif  /* _H_machine */
