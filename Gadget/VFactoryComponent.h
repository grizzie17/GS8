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


#include "NamespaceGadget.h"

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
NAMESPACE_GADGET_BEGIN
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

class VFactoryComponent : public VFactoryLite
{
//	class lifecycle  ----------------------------------------------------
public:
					VFactoryComponent();
	virtual			~VFactoryComponent();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void			SetDictionary( VDictionaryPtr pDict );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	virtual
	VEquationPtr	MakeEquation
					(
					CFactoryEquation::FEquationTargets eTarget,
					CCharDescriptorRef rString
					);
	virtual
	VEquationPtr	MakeEquation
					(
					CFactoryEquation::FEquationTargets eTarget,
					const char* s,
					size_t		n
					);
	bool			ConstantEquation( void );
	char*			EquationErrorString( void );
	void			SetEquationPanelChild( VPanelChildPtr p );


	CActionPtr		ActionMap( XMLIteratorPtr pIt );
	CTriggerPtr		Trigger( XMLIteratorPtr pIt );
	//CCharStringPtr	KeyEvent( const char* sTag );
	VEquationPtr	ScriptContainer( XMLIteratorPtr pIt );
	VEquationPtr	Script( XMLIteratorPtr pIt );

	int				KeyName( CCharDescriptorRef rName );

	CKeyEventMapPtr	KeyEventMap( XMLIteratorPtr pIt );
	bool			OnKeyEvent( const char* sTag, CKeyEventMap::KeyEventArray* p, XMLIteratorPtr pIt );
	bool			OnKey( CKeyEventMap::KeyEventArray* p, XMLIteratorPtr pIt );

	bool			Update( VControlPtr pControl, XMLIteratorPtr pIt );


	bool	LoadNumberEquation
			(
			CResultValuePtr	pRValue,
			const char*		sAttr,
			XMLIteratorPtr	pIt
			);

	bool	GetAttributeEquation
			(
			VEquationPtr*	hEq,
			const char*		sAttr,
			XMLIteratorPtr	pIt
			);

	bool	LoadXY
			(
			VCoordinatePtr	pNode,
			XMLIteratorPtr	pIt
			);

	CPositionPtr	Position( XMLIteratorPtr pIt );

//	protected data  -----------------------------------------------------

	TPointer<CFactoryEquation>	m_pEqFactory;
	bool						m_bHasGVariables;
	TPointer<CKeyNames>			m_pKeyNames;
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

NAMESPACE_GADGET_END



#endif /* _H_VFactoryComponent */

