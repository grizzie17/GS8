/*---------------------------------------------------------------------+\
|
|	CLine.h  --  brief description of what CLine.h is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CLine
#define _H_CLine
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"
#include "CPoint.h"
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
NAMESPACE_GADGET_BEGIN

typedef class CLine*		CLinePtr;
typedef class CLine&		CLineRef;
typedef const class CLine&	ConstCLineRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CLine : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
				CLine();
				CLine( ConstCLineRef r );	// copy constructor
	virtual		~CLine();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CLineRef	operator=( ConstCLineRef r );		// assignment

	void		SetBegin( CPointValueRef tBegin );
	void		SetEnd( CPointValueRef tEnd );

	CPointValuePtr
				Begin( void );
	CPointValuePtr
				End( void );

	void		SetLineWidth( short nWidth );
	void		SetLineColor( ConstCColorRef tColor );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CPointValue	m_tBegin;
	CPointValue	m_tEnd;
	short		m_nWidth;
	CColor		m_tColor;



private:
//	private types  ------------------------------------------------------

	typedef	VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VGraphic-1
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );


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


#endif /* _H_CLine */

