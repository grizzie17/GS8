/*---------------------------------------------------------------------+\
|
|	CConsole.h  --  brief description of what CConsole.h is for
|
|	Purpose:
|	File Custodian:		F.Lastname
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CConsole
#define _H_CConsole
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CSerial.h"
#include "CMutex.h"
#include "CSemaphore.h"
#include "CSignal.h"
#include "UPlatform.h"
#include "UPlatformThreads.h"
#include "VDictionary.h"
#include "CApplicationGauge.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


#define TERMINATE		ENDSTATE
#define ENDSTATE		{ TPX_LAST, TPX_NEXT, TPX_NoAction, TPX_NoFunc }
#define NEXTSTATE		{ TPX_NEXTSTATE, TPX_NEXT, TPX_NoAction, TPX_NoFunc }




// Helper macros for identifying type/token  combinations
#define	TPX_C( c )				TPX_K_CHARACTER, (const char*)c
#define	TPX_T( string )			string
//#define	TPX_T( string )			TPX_K_TOKEN, string
#define TPX_ST( string )		string
//#define TPX_ST( string )		TPX_K_SUBTOKEN, string
#define TPX_Sub( state )		TPX_K_SUBSTATE, (const char*)state
#define TPX_Special( token )	TPX_K_SPECIAL, (const char*)token


//	tokens that return a length of zero
#define	TPX_LAMBDA		((const char*)1)		// always is true
//#define	TPX_LAMBDA		TPX_Special( TPX_K_LAMBDA )		// always is true
#define TPX_EOS			TPX_Special( TPX_K_EOS )

// the following are normally not used:
//		use NEXTSTATE and ENDSTATE instead
#define	TPX_NEXTSTATE	TPX_Special( TPX_K_NEXTSTATE )
#define	TPX_LAST		TPX_Special( TPX_K_LAST )


// special nextstate keywords
#define	TPX_NEXT		((XTransPtr)0)
#define	TPX_EXIT		((XTransPtr)0)
//#define	TPX_EXIT		((TPxStatePtr)-1)
#define TPX_FAIL		((XTransPtr)-2)
//#define TPX_FAIL		((TPxStatePtr)-2)
#define	TPX_LOOP		(0)



// -----
//	Action Macros
// -----
#define	TPX_Action( a, b )		(a), (b)
#define TPX_NoAction			0
//#define TPX_NoAction			TPX_K_NOOP, 0

#define	TPX_Reply( sValue )		sValue
//#define	TPX_Reply( sValue )		TPX_Action( TPX_K_REPLY, sValue )



#define	TPX_NoFunc				0, 0


// -------------------------------------------------------------
// Special Token keywords (only valid when TPX_Special is used
// -------------------------------------------------------------
#define	TPX_K_NEXTSTATE	1		// state separator
#define	TPX_K_LAST		0		// state terminator

// tokens that return a zero length
#define	TPX_K_LAMBDA	(-1)	// empty string
#define	TPX_K_EOS		(-2)	// end-of-string



// operation identifiers
#define	TPX_K_NOOP		0
#define	TPX_K_REPLY		1


/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CConsole*			CConsolePtr;
typedef class CConsole&			CConsoleRef;
typedef const class CConsole&	ConstCConsoleRef;



#define		TPX_K_SPECIAL	0
#define		TPX_K_CHARACTER	1
#define		TPX_K_TOKEN		2
#define		TPX_K_SUBTOKEN	3	// used to find a string in a string
#define		TPX_K_SUBSTATE	4



// structure used to create state/transition machine
typedef struct XTrans	XTrans;
typedef	XTrans*			XTransPtr;

typedef XTrans			TPxTrans;
typedef TPxTrans*		TPxTransPtr;

typedef	TPxTrans		TPxState;
typedef	TPxState*		TPxStatePtr;


typedef
	NResult	(*XTransFuncPtr)
			(
			CConsolePtr pCon,
			XTransPtr	pTrans,
			const char*	sToken,
			int			nTokenLen
			);


typedef struct XTrans
{
	const char*		sToken;		// sub-string for which we transition on
	const char*		sResponse;	// operation argument
	XTransPtr		pNextState;	// address of next state
	XTransFuncPtr	pFunc;
	const char*		pXdata;		// used by pfunc
} XTrans;

//typedef struct XTrans
//{
//	short			eType;		// identifies how "sToken" is used
//	const char*		sToken;		// sub-string for which we transition on
//	XTransPtr		pNextState;	// address of next state
//	int				nOperation;
//	const char*		sOperation;	// operation argument
//	XTransFuncPtr	pFunc;
//	const char*		pXdata;		// used by pfunc
//} XTrans;

/*
//  structures to capture the information for each transition
*/
//struct TParseTrans
//{
//	Byte			type;			/* specifies how token is used */
//	SignedByte		iToken;			/* char token or special */
//	CharPtr			token;			/* string token or address of substate */
//	TParseStatePtr	pNextState;		/* address of next state or transition */
//	long			operation;		/* 'ident' operation (set,or,and, ...) or status */
//	long			ident;			/* ident to be applied to 'blockOffset' */
//	long			blockOffset;	/* offset in TParseManager->pBlock to set ident */
//	TParseFuncPtr	func;			/* user function */
//	long			funcArg;		/* argument to pass to user function */
//};



/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CConsole
{
//	class lifecycle  ----------------------------------------------------
public:
			CConsole();
	virtual	~CConsole();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


	void	LoadSettings
			(
			CSerialPortSettingsPtr	p
			);

	void	SetPortName
			(
			const char*	s
			);

	void	SetServerIP
			(
			const char*	s
			);

	void	SetCallback
			(
			long			nIndex,
			CApplicationGaugePtr	p
			);


	bool	Start
			(
			VDictionaryPtr	pDictionary
			);


	bool	Stop
			(
			VDictionaryPtr	pDictionary
			);


	// determines current state and updates dictionary
	bool	Calculate
			(
			VDictionaryPtr	pDictionary
			);


	bool	Virginize
			(
			void
			);



public:
//	psuedo protected functions ------------------------------------------

	bool	WritePort
			(
			const char*	sBuffer,
			size_t		nCount
			);

	bool	CompareLastWritten
			(
			const char*	sBuffer,
			long		nCount
			);

	long	GetIndex
			(
			void
			);


	ConstCCharStringRef
			GetServerIP
			(
			void
			);


	bool	Notify
			(
			const char*	sComment
			);

	long	GetCount
			(
			void
			);

	void	SetCount
			(
			long	n
			);


	ConstCCharStringRef
			GetTestingIP
			(
			void
			);


	void	SetDspState
			(
			bool	b
			);



	void	SetFailureState
			(
			const char*	s
			);


	void	InitState
			(
			void
			);


protected:
//	protected types  ----------------------------------------------------

	typedef struct XProc	// processor condition
	{
		CCharString	sIP;			// IP address
		bool		bTest;			// status of last test
		long		nTests;			// count of tests
		long		nFailures;		// count of failed tests
		long		nMilli;			// milliseconds of last test

		XProc()
			:
			bTest( false ),
			nTests( 0 ),
			nFailures( 0 ),
			nMilli( 0 )
		{}
	} XProc;



//	protected functions  ------------------------------------------------

	static
	UThreadRtn
			ThreadRxGlue
			(
			void*	pThis
			);

	UThreadRtn
			ThreadRx
			(
			void
			);


	static
	UThreadRtn
			ThreadTxGlue
			(
			void*	pThis
			);

	UThreadRtn
			ThreadTx
			(
			void
			);


	CCharString
			BuildPath
			(
			const char* s
			);


	bool	ProcessStream
			(
			char*		sBuffer,
			long		nCount
			);

	bool	ProcessLine
			(
			const char*	sBuffer,
			long		nCount
			);

	bool	InputBusy
			(
			void
			);



//	protected data  -----------------------------------------------------

	CMutex		m_oMutex;
	CSemaphore	m_oSemaphore;
	//CSignal		m_oSignal;
	UThreadHdl	m_hThreadRx;
	UThreadHdl	m_hThreadTx;
	CSerial		m_oPort;
	CCharString	m_sPortName;
	CCharString	m_sServerIP;
	long		m_nPortIndex;

	size_t		m_nCount;
	size_t		m_nPrevCount;
	long		m_nDspIndex;

	bool		m_bOpen;
	long		m_ndsOpen;	// port status;
	long		m_ndsPortName;
	long		m_nState;
	long		m_ndsState;
	long		m_nTested;
	long		m_ndsTested;
	long		m_nActive;
	long		m_ndsActive;
	long		m_nFailed;
	long		m_ndsFailed;
	long		m_nMilli;
	long		m_ndsMilli;
	CCharString	m_sMessage;
	long		m_ndsMessage;
	XProc*		m_aProcessors;

	long		m_nMilliStart;	// milliseconds at Start


	XTransPtr	m_pFirstState;
	XTransPtr	m_pCurrentState;

	CCharString	m_sLogfile;
	FILE*		m_hLogfile;

	unsigned char	m_aWriteBuffer[256];
	size_t		m_nWriteCount;

	unsigned char	m_aLastWriteBuffer[256];
	size_t		m_nLastWriteCount;

	bool		m_bInputBusy;


	CApplicationGaugePtr	m_pApplication;
	VDictionaryPagePtr		m_pDataPage;		// D - Data Response Page
	VDictionaryPagePtr		m_pConstantsPage;	// K - Data Response Page


private:
//	private types  ------------------------------------------------------

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



#endif /* _H_CConsole */
