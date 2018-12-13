/*---------------------------------------------------------------------+\
|
|	VFactoryComponent.h  --  brief description of what VFactoryComponent.h is for
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
	08-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning that was caused by the deprecated operation
		of passing a string literal to a 'char*' it should be
		'const char*'
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Take advantage of the more descriptive errors returned
		by the equation factory.
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for passing the dictionary down to the Equation
		Factory so it can use it to validate the scripts.
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for update nodes that include frequency
	03-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFactoryComponent
#define _H_VFactoryComponent
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryLite.h"




#include "CFactoryEquation.h"
#include "TPointer.h"
#include "VDictionary.h"

#include "CAction.h"
#include "CTrigger.h"
#include "CPosition.h"
#include "CResultValue.h"
#include "CKeyNames.h"
#include "VCoordinate.h"
#include "VControl.h"

#include "CKeyEventMap.h"
#include "CKeyNames.h"


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
typedef class VFactoryComponent*		VFactoryComponentPtr;
typedef class VFactoryComponent&		VFactoryComponentRef;
typedef const class VFactoryComponent&	ConstVFactoryComponentRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VFactoryComponent : public Yogi::Common::VFactoryLite
{
//	class lifecycle  ----------------------------------------------------
public:
			VFactoryComponent();
	virtual	~VFactoryComponent();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	SetDictionary
			(
			VDictionaryPtr pDict	//!< [in] pointer to new dictionary object
			);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	virtual
	VEquationPtr
			MakeEquation
			(
			CFactoryEquation::FEquationTargets	eTarget,
			Yogi::Core::ConstCCharDescriptorRef	rString
			);
	virtual
	VEquationPtr
			MakeEquation
			(
			CFactoryEquation::FEquationTargets eTarget,
			const char* s,
			size_t		n
			);
	bool	ConstantEquation( void );
	char*	EquationErrorString( void );
	void	SetEquationPanelChild( VPanelChildPtr p );


	CActionPtr		ActionMap( Yogi::Common::XMLIteratorPtr pIt );
	CTriggerPtr		Trigger( Yogi::Common::XMLIteratorPtr pIt );
	//CCharStringPtr	KeyEvent( const char* sTag );
	VEquationPtr	ScriptContainer( Yogi::Common::XMLIteratorPtr pIt );
	VEquationPtr	Script( Yogi::Common::XMLIteratorPtr pIt );

	int				KeyName( Yogi::Core::ConstCCharDescriptorRef rName );

	CKeyEventMapPtr	KeyEventMap( Yogi::Common::XMLIteratorPtr pIt );
	bool			OnKeyEvent( const char* sTag, CKeyEventMap::KeyEventArray* p, Yogi::Common::XMLIteratorPtr pIt );
	bool			OnKey( CKeyEventMap::KeyEventArray* p, Yogi::Common::XMLIteratorPtr pIt );

	bool			Update( VControlPtr pControl, Yogi::Common::XMLIteratorPtr pIt );


	bool	LoadNumberEquation
			(
			CResultValuePtr	pRValue,
			const char*		sAttr,
			Yogi::Common::XMLIteratorPtr	pIt
			);

	bool	GetAttributeEquation
			(
			VEquationPtr*	hEq,
			const char*		sAttr,
			Yogi::Common::XMLIteratorPtr	pIt
			);

	bool	LoadXY
			(
			VCoordinatePtr	pNode,
			Yogi::Common::XMLIteratorPtr	pIt
			);

	CPositionPtr	Position( Yogi::Common::XMLIteratorPtr pIt );

//	protected data  -----------------------------------------------------

	Yogi::Core::TPointer<CFactoryEquation>	m_pEqFactory;
	bool						m_bHasGVariables;
	Yogi::Core::TPointer<CKeyNames>			m_pKeyNames;
	VPanelChildPtr				m_pPanelChild;
	VDictionaryPtr				m_pDictionary;

	GFLOAT						m_1000;

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



#endif /* _H_VFactoryComponent */
