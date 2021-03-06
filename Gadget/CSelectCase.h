/*---------------------------------------------------------------------+\
|
|	CSelectCase.h  --  Support Case tag inside Select tag
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
	27-Aug-2009			J.Griswold
		Allow the "Expression" tag to be used within a "Case" tag
	14-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CSelectCase
#define _H_CSelectCase
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
typedef class CSelectCase*			CSelectCasePtr;
typedef class CSelectCase&			CSelectCaseRef;
typedef const class CSelectCase&	ConstCSelectCaseRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CSelectCase : public VElement
{
//	class lifecycle  ----------------------------------------------------
public:
					CSelectCase();
					CSelectCase( ConstCSelectCaseRef r );	// copy constructor
	virtual			~CSelectCase();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CSelectCaseRef	operator=( ConstCSelectCaseRef r );		// assignment

	int				CalculateCase( VDictionaryPtr pDict );
	Yogi::Common::CVariantData	GetValue( VDictionaryPtr pDict );

	bool			SetEquation( VEquationPtr pEq );
	bool			SetValue( Yogi::Common::ConstCVariantDataRef v );

	bool			AddRenderable( VRenderablePtr p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue						m_tValue;
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



#endif /* _H_CSelectCase */
