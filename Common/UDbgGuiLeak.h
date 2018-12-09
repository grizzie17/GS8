/*---------------------------------------------------------------------+\
|
|	UDbgGuiLeak.h  --  Detect GDI Object leaks
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
	03-Jul-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UDbgGuiLeak
#define _H_UDbgGuiLeak
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"


namespace Yogi { namespace Common {
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
typedef class CDbgGuiLeak*			CDbgGuiLeakPtr;
typedef class CDbgGuiLeak&			CDbgGuiLeakRef;
typedef const class CDbgGuiLeak&	ConstCDbgGuiLeakRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class CDbgGuiLeak
{
//	class lifecycle  ----------------------------------------------------
public:
	explicit CDbgGuiLeak()
	{
		m_nResCount = ::GetGuiResources( ::GetCurrentProcess(), GR_GDIOBJECTS );
	}

	~CDbgGuiLeak()
	{
		unsigned nLeaks = ::GetGuiResources( ::GetCurrentProcess(), GR_GDIOBJECTS )
					- m_nResCount;
		if ( 0 != nLeaks )
		{
			LogPrint( "Gui Resource Leaked: %ld\n", nLeaks );
		}
	}

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

	unsigned long	m_nResCount;


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

}}



#endif /* _H_UDbgGuiLeak */
