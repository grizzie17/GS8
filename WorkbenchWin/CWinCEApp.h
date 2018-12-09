/*---------------------------------------------------------------------+\
|
|	CWinCEApp.h  --  brief description of what CWinCEApp.h is for
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
	17-Dec-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CWinCEApp
#define _H_CWinCEApp
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "CWinCEDlg.h"


using namespace Yogi::Gadget;
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/
typedef class CWinCEApp*			CWinCEAppPtr;
typedef class CWinCEApp&			CWinCEAppRef;
typedef const class CWinCEApp&	ConstCWinCEAppRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class CWinCEApp
{
//	class lifecycle  ----------------------------------------------------
public:
			CWinCEApp();
	virtual	~CWinCEApp();

private:
			// disable this operators
			CWinCEApp( ConstCWinCEAppRef r );	// copy constructor
	CWinCEAppRef
			operator=( ConstCWinCEAppRef r );		// assignment

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	bool	InitInstance
			(
			HINSTANCE	hInstance,
			LPCTSTR		szWindowClass
			);

	void	Start();

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CWinCEDlg*	m_pDlg;

private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};

/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/




#endif /* _H_CWinCEApp */
