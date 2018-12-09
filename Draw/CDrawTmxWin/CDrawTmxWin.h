/*---------------------------------------------------------------------+\
|
|	CDrawTmxWin.h  --  Base class for Draw objects
|
|	Purpose:
|
|	Restrictions/Warnings:

		The draw object assumes that the coordinate system is based upon
		the 0,0 coordinate being located in the upper-left corner of the
		screen/window and ascending Y is down the screen.

		Any other systems need to override the InitialMatrix function
		and provide a matrix that will provide the needed interface.  The
		default implementation simply returns the identity matrix.

|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawTmxWin
#define _H_CDrawTmxWin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregate.h"
#include "IDrawTmx.h"

#include "CColor.h"
#include "CMatrix3x3.h"
#include "TArray.h"
#include "UMath.h"
#include "UFloat.h"
#include "UMachine.h"


namespace Yogi { namespace Common {
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


typedef class CDrawTmxWin*			CDrawTmxWinPtr;
typedef class CDrawTmxWin&			CDrawTmxWinRef;
typedef const class CDrawTmxWin&	ConstCDrawTmxWinRef;

#if defined(OS_MSWIN)

#	define	CDrawTmxWinPOINT	POINT
#	define	CDrawTmxWinVALUE	LONG
#	define	CDrawTmxWinCAST_VALUE( x )	intFromFloat( x )

#elif defined(OS_LINUX)

#	define	CDrawTmxWinPOINT	CDrawTmxWin::FPoint
#	define	CDrawTmxWinVALUE	float
#	define	CDrawTmxWinCAST_VALUE( x )	((CDrawTmxWinVALUE)(x))

#else
#endif



/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDrawTmxWin : public VPluginWithAggregate,
				implements_ IDrawTmx2
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawTmxWin );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IDrawTmx

	virtual bool	begin( void );
	virtual bool	end( void );

	virtual bool	margin
					(
					int		nLeft,
					int		nTop,
					int		nRight,
					int		nBottom
					);

	virtual bool	push
					(
					GFLOAT	xPosition,
					GFLOAT	yPosition,
					GFLOAT	xShift,
					GFLOAT	yShift,
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	rotation,
					GFLOAT	scale
					);
	virtual bool	pop( void );



	//	IDrawTmx2
	virtual void	SetInitialMatrix
					(
					CMatrix3x3&	r
					);

	virtual void	TransformPoint
					(
					GFLOAT&	rfXOut,
					GFLOAT&	rfYOut,
					GFLOAT	fXIn,
					GFLOAT	fYIn
					);

	virtual GFLOAT	TransformLength
					(
					GFLOAT	fInLength
					);

	virtual void	GenActiveMatrix( void );
	virtual void	ResetWorld( void );

	virtual GFLOAT	normalizeAngle( GFLOAT r );	// input is radians


protected:
//	protected types  ----------------------------------------------------

	typedef struct World
	{
		GFLOAT	xPosition;
		GFLOAT	yPosition;
		GFLOAT	xShift;
		GFLOAT	yShift;
		GFLOAT	xAxis;
		GFLOAT	yAxis;
		GFLOAT	rotation;
		GFLOAT	scale;
	} World;

//	protected functions  ------------------------------------------------

	virtual CMatrix3x3
					InitialMatrix( void );

	//virtual void	TransformPoint
	//				(
	//				GFLOAT&	rfXOut,
	//				GFLOAT&	rfYOut,
	//				GFLOAT	fXIn,
	//				GFLOAT	fYIn
	//				);

	//virtual float	TransformLength
	//				(
	//				GFLOAT	fInLength
	//				);

	//virtual void	GenActiveMatrix( void );
	//void			ResetWorld( void );

	//int				intFromFloat( GFLOAT x );
	//GFLOAT			normalizeAngle( GFLOAT r );	// input is radians

//	protected data  -----------------------------------------------------


	bool				m_bMatrixDirty;
	bool				m_bMatrixAffine;
	CMatrix3x3			m_tMatrixActive;
	CMatrix3x3			m_tMatrixBase;
	int					m_nMatrixTop;
	TArray<CMatrix3x3>	m_tMatrixStack;
	World				m_tWorld;

	// margin
	int					m_nLeft;
	int					m_nTop;
	int					m_nRight;
	int					m_nBottom;

private:
//	private types  ------------------------------------------------------

	typedef VPluginWithAggregate	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

	//	IPluginLoadConfiguration
public:

	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr		pLib
			);


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


#endif /* _H_CDrawTmxWin */
