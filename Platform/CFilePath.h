/*---------------------------------------------------------------------+\
|
|	CFilePath.h  --  class for abstracting the file-path
|
|	Purpose:

		Encapsulate a "somewhat" normalized file-path

		Our goal is to handle the following OS or specifications
		and to allow some cross-specification tolerance

		URI		- uniform resource identifier
		LINUX	- linux/unix file specifiers
		MSWIN	- ms-windows long file specifiers
		UNC		- uniform naming convention

|
|	Restrictions/Warnings:

		The CFilePath is more restrictive than the native OS
		regarding reserved or special characters

		The safest character set for file or directory names
		is upper- and lower-case letters (A-Za-z), numeric (0-9),
		underscore (_) and dash (-).

|	Formats:

		The file-path is composed of the following components.  Not
		all are required to specify a unique file-path.

		PROTOCOL	- access method (http, ftp, file, etc.)
		HOST		- hostname, IP address, domain, or LAN
		DEVICE		- port, socket, drive, root mount point, disc, volume
		DIRECTORY	- directory/folder tree
		FILE		- base name of the file
		TYPE		- the file suffix indicating content type
		VERSION		- revision of the file (not supported)

		The following are the list of reserved characters and their meainings

		/	slash	- directory path separator
		\	backslash - directory path separator
		|	vert-bar- directory path separator (should be avoided)
		:	colon	- used as a PROTOCOL, HOST, or DEVICE separator
						may also be used as a directory path separator
		.	period	- used to delineate the TYPE from the FILE
						also used as the "current" directory or the
						up directory (two periods)
						must not be used as the first or only character
						in a FILE

		?	question- wild-card character specifying a single character
		*	astersk	- wild-card character specifying multiple characters

		$	dollar	- variable substitution
						if the dollar is followed by an open parenthesis
						then the variable name is considered to be enclosed
						in parenthesis.
						if no parens then the variable name is delineated
						by one of the other reserved characters.
		%	percent	- escape character for URIs specifying a special name or
						a hex number.


|	Examples:

		URI
			PROTOCOL://HOST:DEVICE/DIRECTORY/FILE.TYPE

		LINUX
			FILE.TYPE
			/DIRECTORY/FILE.TYPE
			DIRECTORY/FILE.TYPE
			./DIRECTORY/FILE.TYPE
			../FILE.TYPE
			~/DIRECTORY/FILE.TYPE

		MSWIN
			FILE.TYPE
			DEVICE:FILE.TYPE
			DEVICE:\DIRECTORY\FILE.TYPE
			DIRECTORY\FILE.TYPE
			.\DIRECTORY\FILE.TYPE
			..\FILE.TYPE

		UNC
			\\HOST\DIRECTORY\FILE.TYPE

		MAC
			FILE.TYPE
			DEVICE:DIRECTORY:FILE.TYPE
			:DIRECTORY:FILE.TYPE


|	References:

		http://en.wikipedia.org/wiki/Path_(computing)

|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	20-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFilePath
#define _H_CFilePath
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharDescriptor.h"

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CFilePath*		CFilePathPtr;
typedef class CFilePath&		CFilePathRef;
typedef const class CFilePath&	ConstCFilePathRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFilePath
{
//	class lifecycle  ----------------------------------------------------
public:
					CFilePath();
					CFilePath( ConstCFilePathRef r );	// copy constructor
	virtual			~CFilePath();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CFilePathRef	operator=( ConstCFilePathRef r );		// assignment

	bool			Assign( ConstCCharDescriptorRef r );
	bool			Assign( const char* s );

	CCharDescriptorRef	GetProtocol( void );
	CCharDescriptorRef	GetHost( void );
	CCharDescriptorRef	GetDevice( void );
	CCharDescriptorRef	GetDirectory( void );
	CCharDescriptorRef	GetFile( void );
	CCharDescriptorRef	GetType( void );
	CCharDescriptorRef	GetVersion( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CCharDescriptor		m_sProtocol;
	CCharDescriptor		m_sHost;
	CCharDescriptor		m_sDevice;
	CCharDescriptor		m_sDirectory;
	CCharDescriptor		m_sFile;
	CCharDescriptor		m_sType;
	CCharDescriptor		m_sVersion;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};

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
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}



#endif /* _H_CFilePath */

