/*---------------------------------------------------------------------+\
|
|	VPolylist.h  --  brief description of what VPolylist.h is for
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
#ifndef _H_VPolylist
#define _H_VPolylist
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"
#include "TArray.h"
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

typedef class VPolylist*		VPolylistPtr;
typedef class VPolylist&		VPolylistRef;
typedef const class VPolylist&	ConstVPolylistRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPolylist : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					VPolylist();
					VPolylist( ConstVPolylistRef r );	// copy constructor
	virtual			~VPolylist();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VPolylistRef	operator=( ConstVPolylistRef r );		// assignment

	bool	AddPoint( CPointValuePtr pPoint );

	void		SetLineWidth( short nWidth );
	void		SetLineColor( ConstCColorRef tColor );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	short		m_nWidth;
	CColor		m_tColor;
	TArray<CPointValuePtr>	m_tPointList;

private:
//	private types  ------------------------------------------------------

	typedef	VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VGraphic-1
	//	VGraphic
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );

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


#endif /* _H_VPolylist */

