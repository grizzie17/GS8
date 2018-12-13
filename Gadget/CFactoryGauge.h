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




/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {


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



	bool			AttributeColor( CResultValuePtr pRValue, const char* sAttr, Yogi::Common::XMLIteratorPtr pIt );
	bool			AttributeRadius( CResultValuePtr p, Yogi::Common::XMLIteratorPtr pIt );
	bool			LoadStyles( VGraphicPtr p, Yogi::Common::XMLIteratorPtr pIt );

	bool			NodeStyles( VGraphicPtr p, Yogi::Common::XMLIteratorPtr pIt );


	CGaugePtr		Gauge( Yogi::Common::XMLIteratorPtr pIt );
	CGaugePtr		GaugeNotFound( const char* sName );
	CGaugePtr		GaugeProblem( const char* sName );

	CGaugePtr		SimBase_Document( Yogi::Common::XMLIteratorPtr pIt );
	CGaugePtr		SimGauge_Gauge( Yogi::Common::XMLIteratorPtr pIt );
	CGaugePtr		IncludeFile( Yogi::Common::XMLIteratorPtr pIt );

	CChoosePtr		Choose( Yogi::Common::XMLIteratorPtr pIt );
	CChooseWhenPtr	ChooseWhen( Yogi::Common::XMLIteratorPtr pIt );
	CElementPtr		Element( Yogi::Common::XMLIteratorPtr pIt );
	CForLoopPtr		ForLoop( Yogi::Common::XMLIteratorPtr pIt );
	CSelectPtr		Select( Yogi::Common::XMLIteratorPtr pIt );
	CSelectCasePtr	SelectCase( Yogi::Common::XMLIteratorPtr pIt );
	CVisiblePtr		Visible( Yogi::Common::XMLIteratorPtr pIt );
	CSizePtr		Size( Yogi::Common::XMLIteratorPtr pIt );
	Yogi::Common::CVariantData	ExpressionResult( Yogi::Common::XMLIteratorPtr pIt );
	VEquationPtr	Expression( Yogi::Common::XMLIteratorPtr pIt );

	CMouseAreaPtr	MouseArea( Yogi::Common::XMLIteratorPtr pIt );
	bool			MouseClick( CMouseAreaPtr p, Yogi::Common::XMLIteratorPtr pIt );


	CArcPtr			Arc( Yogi::Common::XMLIteratorPtr pIt );
	CCirclePtr		Circle( Yogi::Common::XMLIteratorPtr pIt );
	CGaugeStringPtr	GaugeString( Yogi::Common::XMLIteratorPtr pIt );
	VEquationPtr	GaugeStringParse( Yogi::Core::ConstCCharDescriptorRef r );
	VEquationPtr	GaugeStringFormat( const char* s, long* pnOut );
	CGaugeTextPtr	GaugeText( Yogi::Common::XMLIteratorPtr pIt );
	CImagePtr		Image( Yogi::Common::XMLIteratorPtr pIt );
	CLinePtr		Line( Yogi::Common::XMLIteratorPtr pIt );
	CPiePtr			Pie( Yogi::Common::XMLIteratorPtr pIt );
	CPointValuePtr	Point( Yogi::Common::XMLIteratorPtr pIt );
	CPolygonPtr		Polygon( Yogi::Common::XMLIteratorPtr pIt );
	CPolylinePtr	Polyline( Yogi::Common::XMLIteratorPtr pIt );
	CRectanglePtr	Rectangle( Yogi::Common::XMLIteratorPtr pIt );
	CVideoPtr		Video( Yogi::Common::XMLIteratorPtr pIt );

	CPositionPtr	FloatPosition( CPositionPtr pPos, Yogi::Common::XMLIteratorPtr pIt );
	CPositionPtr	LeftScript( CPositionPtr pPos, Yogi::Common::XMLIteratorPtr pIt );
	CPositionPtr	TopScript( CPositionPtr pPos, Yogi::Common::XMLIteratorPtr pIt );
	CRotationPtr	Rotation( CRotationPtr pRot, Yogi::Common::XMLIteratorPtr pIt );
	CShiftPtr		Shift( CShiftPtr pShift, Yogi::Common::XMLIteratorPtr pIt );
	CAxisPtr		Axis( Yogi::Common::XMLIteratorPtr pIt );

	VOwnershipPtr	grpElementContent( Yogi::Common::XMLIteratorPtr pIt );
	VRenderablePtr	grpElementControl( ControlObjects* pCtl, Yogi::Common::XMLIteratorPtr pIt );
	VGraphicPtr		grpGraphic( Yogi::Common::XMLIteratorPtr pIt );
	bool			grpOrigin( VCoordinatePtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpSize( VCoordinatePtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpStartAngle( CResultValuePtr pRV, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpEndAngle( CResultValuePtr pRV, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpRadius( CResultValuePtr pRV, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpLineStyle( VGraphicPtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpFillStyle( VGraphicPtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpHaloStyle( VGraphicPtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpFontColor( VGraphicPtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpFontHeight( CResultValuePtr pRV, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpBackgroundColor( VGraphicPtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpPosition( VCoordinatePtr pNode, Yogi::Common::XMLIteratorPtr pIt );
	bool			grpPoint( VCoordinatePtr pNode, Yogi::Common::XMLIteratorPtr pIt );


	bool	Float2FromNodeValue
			(
			VCoordinatePtr	pNode,
			Yogi::Common::XMLIteratorPtr	pIt
			);

	bool	ResultValueFromNodeValue
			( CResultValuePtr pResult, Yogi::Common::XMLIteratorPtr pIt );
	bool	ResultValueFromNodeValueFloat
			( CResultValuePtr pResult, Yogi::Common::XMLIteratorPtr pIt );
	bool	ResultValueFromNodeValueBool
			( CResultValuePtr pResult, Yogi::Common::XMLIteratorPtr pIt );
	bool	ResultValueFromNodeValueScript
			( CResultValuePtr pResult, Yogi::Common::XMLIteratorPtr pIt );
	bool	ResultValueFromNodeColorScript
			( CResultValuePtr pResult, Yogi::Common::XMLIteratorPtr pIt );
	bool	ResultValueFromNodeColorValue
			( CResultValuePtr pResult, Yogi::Common::XMLIteratorPtr pIt );




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
}}


#endif /* _H_CFactoryGauge */
