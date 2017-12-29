/*---------------------------------------------------------------------+\
|
|	CDrawTmxWin.cpp  --  brief description of what CDrawTmxWin.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	27-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for display margin.  This is usually used
		to deal with monitors that have strange displays that
		the normal coordinates do not always show.
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <math.h>
#include "CDrawTmxWin.h"
#include "VPluginFactory.h"

NAMESPACE_COMMON_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( CDrawTmxWin );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDrawTmxWin - constructor

\+---------------------------------------------------------------------*/
CDrawTmxWin::CDrawTmxWin
		(
		void
		)
		: inherited(),
		m_bMatrixDirty( true ),
		m_bMatrixAffine( true ),
		m_tMatrixActive(),
		m_tMatrixBase(),
		m_nMatrixTop( 0 ),
		m_tMatrixStack(),
		m_tWorld(),
		m_nLeft( 0 ),
		m_nTop( 0 ),
		m_nRight( 0 ),
		m_nBottom( 0 )
{
}

CDrawTmxWin::CDrawTmxWin
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_bMatrixDirty( true ),
		m_bMatrixAffine( true ),
		m_tMatrixActive(),
		m_tMatrixBase(),
		m_nMatrixTop( 0 ),
		m_tMatrixStack(),
		m_tWorld(),
		m_nLeft( 0 ),
		m_nTop( 0 ),
		m_nRight( 0 ),
		m_nBottom( 0 )
{
}

CDrawTmxWin::CDrawTmxWin
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_bMatrixDirty( true ),
		m_bMatrixAffine( true ),
		m_tMatrixActive(),
		m_tMatrixBase(),
		m_nMatrixTop( 0 ),
		m_tMatrixStack(),
		m_tWorld(),
		m_nLeft( 0 ),
		m_nTop( 0 ),
		m_nRight( 0 ),
		m_nBottom( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDrawTmxWin - destructor

\+---------------------------------------------------------------------*/
CDrawTmxWin::~CDrawTmxWin
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	CDrawTmxWin::begin
		(
		void
		)
{
	//m_tMatrixBase = InitialMatrix();
	m_bMatrixDirty = false;

	ResetWorld();
	m_nMatrixTop = 0;
	CMatrix3x3		mInit = CMatrix3x3::_Translate( GFLOAT(m_nLeft), GFLOAT(m_nTop) );
	CMatrix3x3Ptr	p = m_tMatrixStack.PointItem( m_nMatrixTop );
	if ( p )
	{
		(*p) = mInit;
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	CDrawTmxWin::end
		(
		void
		)
{
	m_nMatrixTop = 0;
	ResetWorld();
	return true;
}


/*---------------------------------------------------------------------+\

 * margin -

\+---------------------------------------------------------------------*/
bool	CDrawTmxWin::margin
		(
		int		nLeft,
		int		nTop,
		int		nRight,
		int		nBottom
		)
{
	m_nLeft = nLeft;
	m_nTop = nTop;
	m_nRight = nRight;
	m_nBottom = nBottom;
	ResetWorld();
	return true;
}




/*---------------------------------------------------------------------+\

 * push -

\+---------------------------------------------------------------------*/
bool	CDrawTmxWin::push
		(
		GFLOAT	xPosition,
		GFLOAT	yPosition,
		GFLOAT	xShift,
		GFLOAT	yShift,
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	rotation,
		GFLOAT	scale
		)
{
	m_tWorld.xPosition = xPosition;
	m_tWorld.yPosition = yPosition;
	m_tWorld.xShift = xShift;
	m_tWorld.yShift = yShift;
	m_tWorld.xAxis = xAxis;
	m_tWorld.yAxis = yAxis;
	m_tWorld.rotation = normalizeAngle( rotation );
	m_tWorld.scale = scale;
	m_bMatrixDirty = true;
	GenActiveMatrix();
	return true;
}

/*---------------------------------------------------------------------+\

 * pop -

\+---------------------------------------------------------------------*/
bool	CDrawTmxWin::pop
		(
		void
		)
{
	if ( 0 < m_nMatrixTop )
	{
		--m_nMatrixTop;
	}
	//ResetWorld();
	CMatrix3x3Ptr	p = m_tMatrixStack.PointItem( m_nMatrixTop );
	m_tMatrixActive = *p;
	m_tMatrixActive *= m_tMatrixBase;
	return true;
}





/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * GenActiveMatrix -

\+---------------------------------------------------------------------*/
void	CDrawTmxWin::GenActiveMatrix
		(
		void
		)
{
	if ( m_bMatrixDirty )
	{
		CMatrix3x3	mT;
		CMatrix3x3	mWorking;
#if 1

		CMatrix3x3Ptr	pLastTop = m_tMatrixStack.PointArray( m_nMatrixTop );
		mWorking = *pLastTop;
		if ( GFLOAT_0 != m_tWorld.rotation
				||  GFLOAT_0 != m_tWorld.scale
				||
					( GFLOAT_0 != m_tWorld.xShift  ||  GFLOAT_0 != m_tWorld.yShift )
				)
		{
			GFLOAT	x;
			GFLOAT	y;
			bool	bRotTrn = false;

			pLastTop->Transform( x, y, GFLOAT_0, GFLOAT_0 );
			if ( GFLOAT_0 != x  ||  GFLOAT_0 != y )
			{
				bRotTrn = true;
				mT *= CMatrix3x3::_Translate( -x, -y );
			}
			if ( GFLOAT_0 != m_tWorld.xShift  ||  GFLOAT_0 != m_tWorld.yShift )
				mT *= CMatrix3x3::_Translate( m_tWorld.xShift, -m_tWorld.yShift );
			if ( GFLOAT_0 != m_tWorld.scale )
				mT *= CMatrix3x3::_Scale( m_tWorld.scale );
			if ( GFLOAT_0 != m_tWorld.rotation )
				mT *= CMatrix3x3::_Rotate( m_tWorld.rotation );
			if ( bRotTrn )
				mT *= CMatrix3x3::_Translate( x, y );
		}
		if ( GFLOAT_0 != m_tWorld.xPosition  ||  GFLOAT_0 != m_tWorld.yPosition )
		{
			mT *= CMatrix3x3::_Translate( m_tWorld.xPosition, m_tWorld.yPosition );
		}
		//if ( 0.0 != m_tWorld.xShift  ||  0.0 != m_tWorld.yShift )
		//{
		//	mT *= CMatrix3x3::_Translate( m_tWorld.xShift, -m_tWorld.yShift );
		//}
		if ( GFLOAT_0 != m_tWorld.xAxis  ||  GFLOAT_0 != m_tWorld.yAxis )
		{
		}
		mWorking *= mT;
		++m_nMatrixTop;
		CMatrix3x3Ptr	p = m_tMatrixStack.PointItem( m_nMatrixTop );
		*p = mWorking;
		m_tMatrixActive = mWorking;
		m_tMatrixActive *= m_tMatrixBase;
#else
		CMatrix3x3	mId = InitialMatrix();
		//CMatrix3x3	mTr = CMatrix3x3::_Translate( 200, 200 );
		//CMatrix3x3	mTrBack = CMatrix3x3::_Translate( -200, -200 );
		//CMatrix3x3	mR = CMatrix3x3::_Rotate( 3.14f / 4.0f );
		m_tActiveMatrix = mId;
		//m_tActiveMatrix *= mTrBack;
		///m_tActiveMatrix *= mR;
		//m_tActiveMatrix *= mTr;
		//m_tActiveMatrix = mId * mTrBack * mR * mTr;
#endif
		m_bMatrixDirty = false;
		m_bMatrixAffine = m_tMatrixActive.IsAffine();
	}
}


/*---------------------------------------------------------------------+\

 * ResetWorld -

\+---------------------------------------------------------------------*/
void	CDrawTmxWin::ResetWorld
		(
		void
		)
{
	m_tWorld.xPosition = 0;
	m_tWorld.yPosition = 0;
	m_tWorld.xShift = 0;
	m_tWorld.yShift = 0;
	m_tWorld.xAxis = 0;
	m_tWorld.yAxis = 0;
	m_tWorld.rotation = GFLOAT_0;
	m_tWorld.scale = GFLOAT_0;
	m_bMatrixDirty = true;
}



/*---------------------------------------------------------------------+\

 * SetInitialMatrix -

\+---------------------------------------------------------------------*/
void	CDrawTmxWin::SetInitialMatrix
		(
		CMatrix3x3&	r
		)
{
	m_tMatrixBase = r;
	m_bMatrixDirty = true;
}



/*---------------------------------------------------------------------+\

 * InitialMatrix -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CDrawTmxWin::InitialMatrix
		(
		void
		)
{
	return CMatrix3x3();
}


/*---------------------------------------------------------------------+\

 * TransformPoint -

\+---------------------------------------------------------------------*/
void	CDrawTmxWin::TransformPoint
		(
		GFLOAT&	rfXOut,
		GFLOAT&	rfYOut,
		GFLOAT	fXIn,
		GFLOAT	fYIn
		)
{
	if ( m_bMatrixDirty )
		GenActiveMatrix();
	m_tMatrixActive.Transform( rfXOut, rfYOut, fXIn, fYIn );
}


/*---------------------------------------------------------------------+\

 * TransformLength -

\+---------------------------------------------------------------------*/
float	CDrawTmxWin::TransformLength
		(
		GFLOAT	fInLength
		)
{
	GFLOAT	x1;
	GFLOAT	y1;
	GFLOAT	x2;
	GFLOAT	y2;

	TransformPoint( x1, y1, GFLOAT_0, GFLOAT_0 );
	TransformPoint( x2, y2, GFLOAT_0, fInLength );

	GFLOAT	xd = x1 - x2;
	GFLOAT	yd = y1 - y2;

	GFLOAT	f = float(::sqrt(double(xd*xd + yd*yd)));
	return f;
}


/*---------------------------------------------------------------------+\

 * normalizeAngle -

\+---------------------------------------------------------------------*/
GFLOAT	CDrawTmxWin::normalizeAngle
		(
		GFLOAT r
		)
{

	if ( r < GFLOAT_0 )
	{
		while ( r < GFLOAT_0 )
			r += GFLOAT_2PI;
	}
	else
	{
		while ( GFLOAT_2PI < r )
			r -= GFLOAT_2PI;
	}
	return r;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	VSupports
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CDrawTmxWin::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDrawTmx )
			pI = INTERFACE_THIS( IDrawTmxPtr );
		else if ( rIID == IXID_IDrawTmx2 )
			pI = INTERFACE_THIS( IDrawTmx2Ptr );
		else
			pI = 0;
	}

	return pI;
}




/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * Load - Load parameters from XML

\+---------------------------------------------------------------------*/
bool	CDrawTmxWin::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		// TODO: Insert load configuration code here


	}

	return bResult;
}



NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

