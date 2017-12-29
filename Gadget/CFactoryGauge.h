/*---------------------------------------------------------------------+\
|
|	CFactoryGauge.h  --  make CGauge objects from XML
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
		Also implement hover for mouse
	01-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Major changes to support V2 schema
	21-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changing Load "style" stuff to Attribute approach
	11-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that the special error gauges are identified
		as background context.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to support foreground/background context to data
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the Choose/When/Otherwise construct
	05-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the Rectangle object
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Progress towards GaugeXML 2.0
	10-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Reworked how we pass the GaugeNotFound routine the name of the
		file.  The previous method did not work because the correct
		data was not available at that point.
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Major overhaul to support XMLLite
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryGauge
#define _H_CFactoryGauge
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryGauge.h"

#include "CChoose.h"
#include "CChooseWhen.h"
#include "CElement.h"
#include "CForLoop.h"
#include "CGauge.h"
#include "CSelect.h"
#include "CSelectCase.h"

#include "CMouseArea.h"
#include "CMouseAreaList.h"

#include "CArc.h"
#include "CCircle.h"
#include "CGaugeString.h"
#include "CGaugeText.h"
#include "CImage.h"
#include "CLine.h"
#include "CPie.h"
#include "CPoint.h"
#include "CPolygon.h"
#include "CPolyline.h"
#include "CRectangle.h"
#include "CVideo.h"

#include "CAxis.h"
#include "CPosition.h"
#include "CRotation.h"
#include "CShift.h"
#include "CSize.h"
#include "CVisible.h"

#include "NamespaceGadget.h"


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN


#define	NOUPDATE	((void*)~0)

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CFactoryGauge*		CFactoryGaugePtr;
typedef class CFactoryGauge&		CFactoryGaugeRef;
typedef const class CFactoryGauge&	ConstCFactoryGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryGauge : public VFactoryGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryGauge();
	virtual			~CFactoryGauge();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual CGaugePtr	Make( const char* sName, int nNest = 0 );



protected:
//	protected types  ----------------------------------------------------

	typedef struct ControlObjects
	{
		CPositionPtr	pPosition;
		CRotationPtr	pRotation;
		CShiftPtr		pShift;

		ControlObjects( void )
			: pPosition( 0 ),
			pRotation( 0 ),
			pShift( 0 )
		{
		}

		VRenderablePtr	SetPosition( CPositionPtr p )
		{
			if ( p != NOUPDATE )
				pPosition = p;
			return p;
		}
		VRenderablePtr	SetRotation( CRotationPtr p )
		{
			if ( p != NOUPDATE )
				pRotation = p;
			return p;
		}
		VRenderablePtr	SetShift( CShiftPtr p )
		{
			if ( p != NOUPDATE )
				pShift = p;
			return p;
		}
	} ControlObjects;

//	protected functions  ------------------------------------------------



	bool			AttributeColor( CResultValuePtr pRValue, const char* sAttr, XMLIteratorPtr pIt );
	bool			AttributeRadius( CResultValuePtr p, XMLIteratorPtr pIt );
	bool			LoadStyles( VGraphicPtr p, XMLIteratorPtr pIt );

	bool			NodeStyles( VGraphicPtr p, XMLIteratorPtr pIt );


	CGaugePtr		Gauge( XMLIteratorPtr pIt );
	CGaugePtr		GaugeNotFound( const char* sName );
	CGaugePtr		GaugeProblem( const char* sName );

	CGaugePtr		SimBase_Document( XMLIteratorPtr pIt );
	CGaugePtr		SimGauge_Gauge( XMLIteratorPtr pIt );
	CGaugePtr		IncludeFile( XMLIteratorPtr pIt );

	CChoosePtr		Choose( XMLIteratorPtr pIt );
	CChooseWhenPtr	ChooseWhen( XMLIteratorPtr pIt );
	CElementPtr		Element( XMLIteratorPtr pIt );
	CForLoopPtr		ForLoop( XMLIteratorPtr pIt );
	CSelectPtr		Select( XMLIteratorPtr pIt );
	CSelectCasePtr	SelectCase( XMLIteratorPtr pIt );
	CVisiblePtr		Visible( XMLIteratorPtr pIt );
	CSizePtr		Size( XMLIteratorPtr pIt );
	CVariantData	ExpressionResult( XMLIteratorPtr pIt );
	VEquationPtr	Expression( XMLIteratorPtr pIt );

	CMouseAreaPtr	MouseArea( XMLIteratorPtr pIt );
	bool			MouseClick( CMouseAreaPtr p, XMLIteratorPtr pIt );


	CArcPtr			Arc( XMLIteratorPtr pIt );
	CCirclePtr		Circle( XMLIteratorPtr pIt );
	CGaugeStringPtr	GaugeString( XMLIteratorPtr pIt );
	VEquationPtr	GaugeStringParse( CCharDescriptorRef r );
	VEquationPtr	GaugeStringFormat( const char* s, long* pnOut );
	CGaugeTextPtr	GaugeText( XMLIteratorPtr pIt );
	CImagePtr		Image( XMLIteratorPtr pIt );
	CLinePtr		Line( XMLIteratorPtr pIt );
	CPiePtr			Pie( XMLIteratorPtr pIt );
	CPointValuePtr	Point( XMLIteratorPtr pIt );
	CPolygonPtr		Polygon( XMLIteratorPtr pIt );
	CPolylinePtr	Polyline( XMLIteratorPtr pIt );
	CRectanglePtr	Rectangle( XMLIteratorPtr pIt );
	CVideoPtr		Video( XMLIteratorPtr pIt );

	CPositionPtr	FloatPosition( CPositionPtr pPos, XMLIteratorPtr pIt );
	CPositionPtr	LeftScript( CPositionPtr pPos, XMLIteratorPtr pIt );
	CPositionPtr	TopScript( CPositionPtr pPos, XMLIteratorPtr pIt );
	CRotationPtr	Rotation( CRotationPtr pRot, XMLIteratorPtr pIt );
	CShiftPtr		Shift( CShiftPtr pShift, XMLIteratorPtr pIt );
	CAxisPtr		Axis( XMLIteratorPtr pIt );

	VOwnershipPtr	grpElementContent( XMLIteratorPtr pIt );
	VRenderablePtr	grpElementControl( ControlObjects* pCtl, XMLIteratorPtr pIt );
	VGraphicPtr		grpGraphic( XMLIteratorPtr pIt );
	bool			grpOrigin( VCoordinatePtr pNode, XMLIteratorPtr pIt );
	bool			grpSize( VCoordinatePtr pNode, XMLIteratorPtr pIt );
	bool			grpStartAngle( CResultValuePtr pRV, XMLIteratorPtr pIt );
	bool			grpEndAngle( CResultValuePtr pRV, XMLIteratorPtr pIt );
	bool			grpRadius( CResultValuePtr pRV, XMLIteratorPtr pIt );
	bool			grpLineStyle( VGraphicPtr pNode, XMLIteratorPtr pIt );
	bool			grpFillStyle( VGraphicPtr pNode, XMLIteratorPtr pIt );
	bool			grpHaloStyle( VGraphicPtr pNode, XMLIteratorPtr pIt );
	bool			grpFontColor( VGraphicPtr pNode, XMLIteratorPtr pIt );
	bool			grpFontHeight( CResultValuePtr pRV, XMLIteratorPtr pIt );
	bool			grpBackgroundColor( VGraphicPtr pNode, XMLIteratorPtr pIt );
	bool			grpPosition( VCoordinatePtr pNode, XMLIteratorPtr pIt );
	bool			grpPoint( VCoordinatePtr pNode, XMLIteratorPtr pIt );


	bool			Float2FromNodeValue
					(
					VCoordinatePtr	pNode,
					XMLIteratorPtr	pIt
					);

	bool			ResultValueFromNodeValue
					( CResultValuePtr pResult, XMLIteratorPtr pIt );
	bool			ResultValueFromNodeValueFloat
					( CResultValuePtr pResult, XMLIteratorPtr pIt );
	bool			ResultValueFromNodeValueBool
					( CResultValuePtr pResult, XMLIteratorPtr pIt );
	bool			ResultValueFromNodeValueScript
					( CResultValuePtr pResult, XMLIteratorPtr pIt );
	bool			ResultValueFromNodeColorScript
					( CResultValuePtr pResult, XMLIteratorPtr pIt );
	bool			ResultValueFromNodeColorValue
					( CResultValuePtr pResult, XMLIteratorPtr pIt );




//	protected data  -----------------------------------------------------

	int		m_nNest;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VFactoryComponent

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


#endif /* _H_CFactoryGauge */


