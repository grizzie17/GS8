/*---------------------------------------------------------------------+\
|
|	UNResult.h  --  definitions for NResult
|
|	Purpose:
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
	07-Jul-2010			P.Hogan			(Reviewed by: J.Griswold)
		Add COMMunication status codes
	06-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Updated communication abbreviation macros/constants
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UNResult
#define _H_UNResult
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UTypes.h"

namespace Yogi { namespace Core {


typedef int32_t			NResult;
typedef	NResult*		NResultPtr;

//#define NR_(nr)			((Yogi::Core::NResult)(nr))


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

//	We use the same layout as the MS-Windows HRESULT value
//	(which is actually an inversion of the VAX/VMS status value


//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-+-----------------------------+
//  |S|i|C|R|r|   Facility          |F|             Code            |
//  +-+-+-+-+-+---------------------+-+-----------------------------+
//
//  where
//
//      S - is the severity code
//			0 - Success
//			1 - Fail
//
//		i - second bit of severity (value depends on severity bit)
//          00 - Success
//          01 - Informational
//          10 - Error/Warning
//          11 - Fatal
//
//      C - control (supress message from display)
//
//      R,r - are reserved bits
//
//      Facility - is the facility code (0-2047)
//
//		F - Code is unique to specified facility
//
//      Code - is the facility's status code (0-32767)

#define	NR_M_SEVERITY	0x80000000L
#define	NR_M_SEVERITYi	0xC0000000L
#define NR_K_SEVSUCCESS	0x00000000L
#define NR_K_SEVINFORM	0x40000000L
#define NR_K_SEVERROR	0x80000000L
#define NR_K_SEVFATAL	0xC0000000L

#define NR_V_SEVSUCCESS		0
#define	NR_V_SEVFAIL		1

#define NR_V_SEViSUCCESS	0
#define NR_V_SEViINFORM		1
#define	NR_V_SEViERROR		2
#define NR_V_SEViFATAL		3


#define NR_M_CONTROL	0x20000000L
#define NR_M_RESERVED	0x18000000L

#define NR_M_FACILITY	0x07FF0000L

#define NR_V_FACNULL	0		// global codes
#define NR_V_FACSYS		1		// codes from the operating system
#define NR_V_FACCOMM	2		// communication - ethernet, serial, etc.
#define NR_V_FACXCOM	20		// component object model
#define NR_V_FACPLUG	21		// plugin
#define NR_V_FACSTORAGE	3

#define NR_M_FCODE		0x00008000L
#define NR_M_CODE		0x00007FFFL




// generic tests for success or failure

#define NR_SUCCEEDED(nr)	(((nr) & NR_M_SEVERITY) == NR_K_SEVSUCCESS)
#define NR_FAILED(nr)		(((nr) & NR_M_SEVERITY) == NR_K_SEVERROR)

// get parts of NResult
#define NR_SEVERITY(nr)		(((nr) >> 31) & 0x01)
#define NR_SEVERITYi(nr)	(((nr) >> 30) & 0x03)
#define NR_FACILITY(nr)		(((nr) >> 16) & 0x07FF)
#define NR_CODE(nr)			((nr) & NR_M_CODE)


// macros to help make result codes
#define NR_MAKE_(sev,fac,code)		(((sev) << 31) | ((fac) << 16) | (code))
#define NR_MAKEi_(sevi,fac,code)	(((sevi) << 30) | ((fac) << 16) | (code))

#define NR_MAKE_SUCCESS_(code)		NR_MAKE_(NR_V_SEVSUCCESS,NR_V_FACNULL,code)
#define NR_MAKE_INFORM_(code)		NR_MAKEi_(NR_V_SEViINFORM,NR_V_FACNULL,code)

#define NR_MAKE_ERROR_(code)		NR_MAKE_(NR_V_SEVFAIL,NR_V_FACNULL,code)
#define NR_MAKE_FATAL_(code)		NR_MAKEi_(NR_V_SEViFATAL,NR_V_FACNULL,code)

#define NR_MAKE_SYSERROR_(code)		NR_MAKE_(NR_V_SEVFAIL,NR_V_FACSYS,(code|NR_M_FCODE))
#define NR_MAKE_COMMERROR_(code)	NR_MAKE_(NR_V_SEVFAIL,NR_V_FACCOMM,(code|NR_M_FCODE))
#define NR_MAKE_XCOMERROR_(code)	NR_MAKE_(NR_V_SEVFAIL,NR_V_FACXCOM,(code|NR_M_FCODE))
#define NR_MAKE_PLUGERROR_(code)	NR_MAKE_(NR_V_SEVFAIL,NR_V_FACPLUG,(code|NR_M_FCODE))






// some good statuses
const NResult NR_S_SUCCESS =	NR_MAKE_SUCCESS_(0);
const NResult NR_S_OK =			NR_S_SUCCESS;
const NResult NR_S_NOERROR =	NR_S_SUCCESS;
const NResult NR_I_TRUE =		NR_MAKE_INFORM_(0);
const NResult NR_I_FALSE =		NR_MAKE_INFORM_(1);


// universal error
const NResult NR_E_ERROR =		~0L;



//----------------------------------------------------------
//	Global codes
//----------------------------------------------------------


// unspecified failure
const NResult NR_E_FAIL =		NR_E_ERROR;

// catastrophic error
const NResult NR_E_UNEXPECTED =	NR_MAKE_FATAL_(0x7FFF);

// invalid pointer
const NResult NR_E_POINTER =	NR_MAKE_ERROR_(0x4003);

// data necessary to complete operation is not yet available
const NResult NR_E_PENDING =	NR_MAKE_ERROR_(0x000A);

// one or more arguments are invalid
const NResult NR_E_INVALIDARG =	NR_MAKE_ERROR_(0x0057);

// operation aborted
const NResult NR_E_ABORT =		NR_MAKE_ERROR_(0x4004);


//----------------------------------------------------------
//	Operating System codes
//----------------------------------------------------------

// incorrect function
const NResult NR_E_INVALIDFUNCTION =	NR_MAKE_SYSERROR_(1);

// system cannot find the file specified
const NResult NR_E_FILENOTFOUND =		NR_MAKE_SYSERROR_(2);

// system cannot find the path specified
const NResult NR_E_PATHNOTFOUND =		NR_MAKE_SYSERROR_(3);

// system cannot open the file
const NResult NR_E_TOOMANYOPENFILES =	NR_MAKE_SYSERROR_(4);

// general access denied error
const NResult NR_E_ACCESSDENIED =		NR_MAKE_SYSERROR_(5);

// invalid handle
const NResult NR_E_HANDLE =				NR_MAKE_SYSERROR_(6);

// out of memory
const NResult NR_E_OUTOFMEMORY =		NR_MAKE_SYSERROR_(8);

// attempt to load a program with an incorrect format
const NResult NR_E_BADFORMAT =			NR_MAKE_SYSERROR_(11);

// the data is invalid
const NResult NR_E_INVALIDDATA =		NR_MAKE_SYSERROR_(13);

// request is not supported
const NResult NR_E_NOTSUPPORTED =		NR_MAKE_SYSERROR_(50);


const NResult NR_E_NOTHREAD =			NR_MAKE_SYSERROR_(100);


//----------------------------------------------------------
//	Communication codes
//----------------------------------------------------------
const NResult NR_E_CONNECT_FAIL =       NR_MAKE_COMMERROR_(1);
const NResult NR_E_RX_FAIL =            NR_MAKE_COMMERROR_(2);
const NResult NR_E_TX_FAIL =            NR_MAKE_COMMERROR_(3);
const NResult NR_E_CHECKSUM_FAIL =      NR_MAKE_COMMERROR_(4);
const NResult NR_E_MQ_SEND_FAIL =		NR_MAKE_COMMERROR_(5);
const NResult NR_E_TIMEOUT =			NR_MAKE_COMMERROR_(6);
const NResult NR_E_BUFFER_OVERRUN =		NR_MAKE_COMMERROR_(7);
const NResult NR_E_BREAK =				NR_MAKE_COMMERROR_(8);
const NResult NR_E_FRAME =				NR_MAKE_COMMERROR_(9);
const NResult NR_E_IO =					NR_MAKE_COMMERROR_(10);
const NResult NR_E_MODE =				NR_MAKE_COMMERROR_(11);
const NResult NR_E_RXPARITY =			NR_MAKE_COMMERROR_(12);
const NResult NR_E_TXFULL =				NR_MAKE_COMMERROR_(13);

//----------------------------------------------------------
//	Component Object Model codes
//----------------------------------------------------------


// interface not implemented
const NResult NR_E_NOTIMPL =		NR_MAKE_XCOMERROR_(1);

// interface not available
const NResult NR_E_NOINTERFACE =	NR_MAKE_XCOMERROR_(2);


//----------------------------------------------------------
//	Plugin codes
//----------------------------------------------------------

// plugin library not loaded into memory
const NResult NR_E_NOTLOADED =		NR_MAKE_PLUGERROR_(1);

// requested library does not contain correct entry point
const NResult NR_E_NOTPLUGIN =		NR_MAKE_PLUGERROR_(2);

// the plugin library does not contain a factory
const NResult NR_E_NOFACTORY =		NR_MAKE_PLUGERROR_(3);

// unspecified error when creating the plugin
const NResult NR_E_PLUGINNOTCREATED =	NR_MAKE_PLUGERROR_(4);





#if ! defined( WRONG )
#define WRONG	NR_E_ERROR
#endif // !defined WRONG



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
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}



#endif /* _H_UNResult */

