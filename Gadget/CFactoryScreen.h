/*---------------------------------------------------------------------+\
|
|	CFactoryScreen.h  --  make a screen and all of its panels and gauges
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
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite parser
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryScreen
#define _H_CFactoryScreen
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/


#include "VFactoryScreen.h"
#include "VFactoryPanel.h"

#include "CFactoryEquation.h"

#include "CPanel.h"


//#include "CAction.h"
//#include "CTrigger.h"


#include "CResultValue.h"



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

typedef class CFactoryScreen*		CFactoryScreenPtr;
typedef class CFactoryScreen&		CFactoryScreenRef;
typedef const class CFactoryScreen&	ConstCFactoryScreenRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryScreen : public VFactoryScreen
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryScreen();
	virtual			~CFactoryScreen();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual CScreenPtr	Make( const char* sName );



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


	//VEquationPtr	MakeEquation( CFactoryEquation::FEquationTargets eTarget, const char* s );
	CPanelPtr		MakePanel( CCharDescriptorRef rName );

	//bool			ConstantEquation( void );

	//bool			LoadNumberEquation( CResultValuePtr pRValue, char* sAttr );
	//bool			LoadColor( CResultValuePtr pRValue, char* sAttr );
	//bool			LoadXY( VCoordinatePtr p );
	//bool			LoadRadius( CResultValuePtr p );

	CScreenPtr		Screen( XMLIteratorPtr pIt );

	CPanelPtr		PanelInstance( XMLIteratorPtr pIt );

	//CActionPtr		ActionMap( const char* sTagname );
	//CTriggerPtr		Trigger( void );
	//CCharStringPtr	KeyEvent( const char* sTag );
	//VEquationPtr	Script( void );






//	protected data  -----------------------------------------------------

	//CFactoryEquationPtr	m_pEqFactory;
	VFactoryPanelPtr	m_pPnlFactory;
	//bool				m_bHasGVariables;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VFactoryPanel
protected:
	virtual VFactoryPanelPtr
						FactoryPanel( void );


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


#endif /* _H_CFactoryScreen */
