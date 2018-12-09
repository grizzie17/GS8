/*---------------------------------------------------------------------+\
|
|	CChoose.h  --  Implementation of a Choose/When construct
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
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CChoose
#define _H_CChoose
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VElement.h"

#include "CChooseWhen.h"

#include "CResultValue.h"
#include "VEquation.h"
#include "TArray.h"

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
typedef class CChoose*			CChoosePtr;
typedef class CChoose&			CChooseRef;
typedef const class CChoose&	ConstCChooseRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CChoose : public VElement
{
//	class lifecycle  ----------------------------------------------------
public:
					CChoose();
					CChoose( ConstCChooseRef r );	// copy constructor
	virtual			~CChoose();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CChooseRef	operator=( ConstCChooseRef r );		// assignment


	bool	AddWhen( CChooseWhenPtr	pCase );
	bool	SetOtherwise( CChooseWhenPtr pCase );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CChooseWhenPtr			m_pWhen;		// current case
	TArray<CChooseWhenPtr>	m_aList;
	CChooseWhenPtr			m_pOtherwise;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render(VDictionaryPtr pDict, VDrawPtr pDraw);
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



#endif /* _H_CChoose */
