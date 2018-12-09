/*---------------------------------------------------------------------+\
|
|	VDrawTmx.h  --  Base class for Draw objects
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
#ifndef _H_VDrawTmx
#define _H_VDrawTmx
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


typedef class VDrawTmx*			VDrawTmxPtr;
typedef class VDrawTmx&			VDrawTmxRef;
typedef const class VDrawTmx&	ConstVDrawTmxRef;

#if defined(OS_MSWIN)

#	define	VDrawTmxPOINT	POINT
#	define	VDrawTmxVALUE	LONG
#	define	VDrawTmxCAST_VALUE( x )	intFromFloat( x )

#elif defined(OS_LINUX)

#	define	VDrawTmxPOINT	VDrawTmx::FPoint
#	define	VDrawTmxVALUE	float
#	define	VDrawTmxCAST_VALUE( x )	((VDrawTmxVALUE)(x))

#else
#endif



/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VDrawTmx : public VPluginWithAggregate,
				implements_ IDrawTmx
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VDrawTmx );

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

	virtual void	TransformPoint
					(
					GFLOAT&	rfXOut,
					GFLOAT&	rfYOut,
					GFLOAT	fXIn,
					GFLOAT	fYIn
					);

	virtual float	TransformLength
					(
					GFLOAT	fInLength
					);

	virtual void	GenActiveMatrix( void );
	void			ResetWorld( void );

	int				intFromFloat( GFLOAT x );
	GFLOAT			normalizeAngle( GFLOAT r );	// input is radians

//	protected data  -----------------------------------------------------


	bool				m_bMatrixDirty;
	bool				m_bMatrixAffine;
	CMatrix3x3			m_tMatrixActive;
	CMatrix3x3			m_tMatrixBase;
	int					m_nMatrixTop;
	Yogi::Core::TArray<CMatrix3x3>	m_tMatrixStack;
	World				m_tWorld;

	// margin
	int					m_nMarginLeft;
	int					m_nMarginTop;
	int					m_nMarginRight;
	int					m_nMarginBottom;

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


inline
int		VDrawTmx::intFromFloat
		(
		GFLOAT	x
		)
{
	return (int)(x + (x < GFLOAT_0 ? GFLOAT_NEG1_2 : GFLOAT_1_2 ));
}





}}


#endif /* _H_VDrawTmx */
