/*---------------------------------------------------------------------+\
|
|	CForLoop.h  --  brief description of what CForLoop.h is for
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	12-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CForLoop
#define _H_CForLoop
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VElement.h"
#include "VEquation.h"
#include "CResultValue.h"
#include "TPointer.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CForLoop*			CForLoopPtr;
typedef class CForLoop&			CForLoopRef;
typedef const class CForLoop&	ConstCForLoopRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CForLoop : public VElement
{
//	class lifecycle  ----------------------------------------------------
public:
					CForLoop();
					CForLoop( ConstCForLoopRef r );	// copy constructor
	virtual			~CForLoop();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CForLoopRef	operator=( ConstCForLoopRef r );		// assignment

	void	SetInitEquation( VEquationPtr pEq );
	void	SetTestEquation( VEquationPtr pEq );
	void	SetIncrEquation( VEquationPtr pEq );

	bool	AddRenderable( VRenderablePtr p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue						m_tInit;
	Yogi::Core::TPointer<VEquation>		m_pTest;
	Yogi::Core::TPointer<VEquation>		m_pIncr;
	Yogi::Core::TArray<VRenderablePtr>	m_aList;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );
	virtual int		GetChildContext( void );

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



#endif /* _H_CForLoop */
