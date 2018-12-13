/*---------------------------------------------------------------------+\
|
|	VControl.h  --  Base for all classes that can handle events
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
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add update frequency support
	11-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VControl
#define _H_VControl
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VOwnership.h"

#include "CCharString.h"
#include "VAction.h"
#include "CMouseLocate.h"
#include "TPointer.h"
#include "VEquation.h"


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
typedef class VControl*			VControlPtr;
typedef class VControl&			VControlRef;
typedef const class VControl&	ConstVControlRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VControl : public VOwnership
{
//	class lifecycle  ----------------------------------------------------
public:
					VControl();
	virtual			~VControl();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	Yogi::Core::CCharStringPtr	Name( void );
	bool			SetUpdate( VEquationPtr p );
	bool			SetUpdateFrequency( int n );
	VActionPtr		Action( void );
	bool			SetAction( VActionPtr p );

	int				MouseAreas( void );
	int				IncrementMouseAreas( int n = 1 );


	virtual bool	ProcessEvent( VDictionaryPtr pDict, VDictionary::Selector vEvent );
	virtual bool	ProcessMouse( VDictionaryPtr pDict, CMouseLocatePtr pMouseLocate );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	// looks at the m_nFrequency and m_nNextUpdate to determine
	//	if Calculate is to be performed.
	bool			CanCalculate( VDictionaryPtr pDict );

//	protected data  -----------------------------------------------------

	Yogi::Core::TPointer<Yogi::Core::CCharString>	m_pName;
	Yogi::Core::TPointer<VEquation>		m_pUpdate;		// always called for Calculate
	int						m_nFrequency;	// update frequency
	long					m_nNextUpdate;	// the millisecond timing of the next update
	Yogi::Core::TPointer<VAction>		m_pAction;		// action object
	int						m_nMouseAreas;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );


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



#endif /* _H_VControl */
