/*---------------------------------------------------------------------+\
|
|	CMouseArea.h  --  brief description of what CMouseArea.h is for
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
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for MouseDown, MouseUp, and MouseMove
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetEvent that uses descriptor to send the name instead
		of null terminated string.
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMouseArea
#define _H_CMouseArea
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEquation.h"
#include "CCharDescriptor.h"
#include "CResultValue.h"
#include "CMouseLocate.h"
#include "CVisible.h"
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
typedef class CMouseArea*			CMouseAreaPtr;
typedef class CMouseArea&			CMouseAreaRef;
typedef const class CMouseArea&	ConstCMouseAreaRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CMouseArea
{
//	class lifecycle  ----------------------------------------------------
public:
					CMouseArea();
					CMouseArea( ConstCMouseAreaRef r );	// copy constructor
	virtual			~CMouseArea();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CMouseAreaRef	operator=( ConstCMouseAreaRef r );		// assignment

	void		SetArea
				(
				float	fLeft,
				float	fTop,
				float	fRight,
				float	fBottom
				);

	void		SetVisibility( VEquationPtr pEq );
	void		SetVisibility( CVisiblePtr pVis );
	void		SetEquation( VEquationPtr pEq );
	void		SetEvent( const char* sEvent );
	void		SetEvent( Yogi::Core::ConstCCharDescriptorRef rEvent );

	void		SetClickType( CMouseLocate::E_TYPE t );

	bool		Calculate( VDictionaryPtr pDict );
	bool		ProcessMouse( VDictionaryPtr pDict, CMouseLocatePtr pMouselocate );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	float				m_fLeft;
	float				m_fTop;
	float				m_fRight;
	float				m_fBottom;

	CMouseLocate::E_TYPE
						m_eClickType;

	Yogi::Core::TPointer<CVisible>	m_pVisibility;
	Yogi::Core::TPointer<VEquation>	m_pEquation;


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



#endif /* _H_CMouseArea */
