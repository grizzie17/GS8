/*---------------------------------------------------------------------+\
|
|	CChooseWhen.h  --  Support When tag inside Choose tag
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
#ifndef _H_CChooseWhen
#define _H_CChooseWhen
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VElement.h"

#include "CVariantData.h"
#include "CResultValue.h"
#include "VRenderable.h"
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
typedef class CChooseWhen*			CChooseWhenPtr;
typedef class CChooseWhen&			CChooseWhenRef;
typedef const class CChooseWhen&	ConstCChooseWhenRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CChooseWhen : public VElement
{
//	class lifecycle  ----------------------------------------------------
public:
					CChooseWhen();
					CChooseWhen( ConstCChooseWhenRef r );	// copy constructor
	virtual			~CChooseWhen();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CChooseWhenRef	operator=( ConstCChooseWhenRef r );		// assignment

	int				CalculateWhen( VDictionaryPtr pDict );
	Yogi::Common::CVariantData	GetValue(VDictionaryPtr pDict);

	bool			SetEquation( VEquationPtr pEq );
	bool			SetValue( Yogi::Common::ConstCVariantDataRef v);

	bool			AddRenderable( VRenderablePtr p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue			m_tValue;
	Yogi::Core::TArray<VRenderablePtr>	m_aList;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render(VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw);
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



#endif /* _H_CChooseWhen */
