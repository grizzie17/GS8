/*---------------------------------------------------------------------+\
|
|	CStyle.h  --  Encapsulate the style/symbology for lines
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
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse
	17-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CStyle
#define _H_CStyle
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VRenderable.h"
#include "CColor.h"
#include "CResultValue.h"
#include "IDraw.h"
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
typedef class CStyle*			CStylePtr;
typedef class CStyle&			CStyleRef;
typedef const class CStyle&	ConstCStyleRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CStyle : public VRenderable
{
//	class lifecycle  ----------------------------------------------------
public:
					CStyle();
					CStyle( ConstCStyleRef r );	// copy constructor
					CStyle( CStylePtr p );
	virtual			~CStyle();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CStyleRef	operator=( ConstCStyleRef r );		// assignment

	void		SetLineColor(Yogi::Core::ConstCColorRef r);
	void		SetLineColor( VEquationPtr p );

	void		SetFillColor(Yogi::Core::ConstCColorRef r);
	void		SetFillColor( VEquationPtr p );

	void		SetHaloColor(Yogi::Core::ConstCColorRef r);
	void		SetHaloColor( VEquationPtr p );

	void		SetNightColor(Yogi::Common::VDraw::ENightColorModes eMode);

	void		SetLineWidth( float f );
	void		SetLineWidth( VEquationPtr p );

	Yogi::Core::CColor		GetLineColor(void);
	GFLOAT		GetLineWidth( void );
	Yogi::Core::CColor		GetFillColor(void);
	Yogi::Core::CColor		GetHaloColor(void);

	CResultValuePtr	LineColor( void );
	CResultValuePtr	LineWidth( void );
	CResultValuePtr	FillColor( void );
	CResultValuePtr	HaloColor( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue	m_tLineColor;
	CResultValue	m_tLineWidth;
	CResultValue	m_tFillColor;
	CResultValue	m_tHaloColor;
	Yogi::Common::VDraw::ENightColorModes m_eNightColor;

private:
//	private types  ------------------------------------------------------

	typedef	VRenderable	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Layout( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render(VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw);
	virtual bool	GetSize( VDictionaryPtr, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );

	virtual
	bool	ProcessEvent
			(
			VDictionaryPtr			pDict,
			VDictionary::Selector	vEvent
			);

	/*
		Process a Mouse click.
	*/
	virtual
	bool	ProcessMouse
			(
			VDictionaryPtr	pDict,
			CMouseLocatePtr	pMouseLocate
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



#endif /* _H_CStyle */
