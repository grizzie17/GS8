/*---------------------------------------------------------------------+\
|
|	UVehicleData.h  --  brief description of what UVehicleData.h is for
|
|	Purpose:
|	File Custodian:		M.Rose
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Dec-2009			M.Rose			(Reviewed by: P.Hogan)
		Add sequence number to vehicle data messaging so that
		stale data does not trigger updates.
	13-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Setup multicast configuration done via
		vehicledataconfiguration.xml file.
	05-Nov-2009			M.Rose			(Reviewed by: R.Hosea)
		Make MSWIN OS Vehicle data reader a separate thread
	26-Oct-2009			M.Rose			(reviewed by: P.Hogan)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UVehicleData
#define _H_UVehicleData
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

namespace Yogi { namespace Gadget {
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

typedef struct VDMsg_t
	{
	unsigned int	nSeq;
	char*			pMsg;
	long			nLen;
	bool			bReady;
	} VDMsg_t;

typedef struct VDMessages_t
	{
	unsigned int	maxSiz;
	VDMsg_t			msg1;
	VDMsg_t			msg2;
	} VDMessages_t;

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
extern VDMessages_t			gVDMsgs;

#if defined ( OS_LINUX )

extern pthread_mutex_t		mutex_save_vdr; // saved vehicle data

#elif defined ( OS_MSWIN )

#	include <windows.h>
#	include <process.h>

extern HANDLE				mutex_save_vdr;
extern LPCWSTR				p_mutexName;

#endif
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

#endif /* _H_UVehicleData */
