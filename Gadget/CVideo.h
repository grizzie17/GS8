/*---------------------------------------------------------------------+\
|
|	CVideo.h  --  brief description of what CVideo.h is for
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
	28-Mar-2010			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CVideo
#define _H_CVideo
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"

#include "CPoint.h"
#include "CSize.h"
#include "CResultValue.h"

#include "NamespaceGadget.h"
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

typedef class CVideo*		CVideoPtr;
typedef class CVideo&		CVideoRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CVideo : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					CVideo();
					CVideo( CVideoRef r );	// copy constructor
	virtual			~CVideo();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CVideoRef	operator=( CVideoRef r );		// assignment

	CResultValuePtr	Source( void );
	CPointValuePtr	Origin( void );
	CSizePtr		Size( void );
	void			SetAlign( VDraw::EAlignments e );
	void			SetVertAlign( VDraw::EVerticalAlignments e );
	void			SetFitment( VDraw::EFitments e );
	CResultValuePtr	Mirror( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


//	protected data  -----------------------------------------------------

	CResultValue	m_tSource;
	CPointValue		m_tOrigin;
	CSize			m_tSize;
	VDraw::EAlignments	m_eAlign;
	VDraw::EVerticalAlignments
						m_eVertAlign;
	VDraw::EFitments	m_eFitment;
	CResultValue	m_tMirror;

private:
//	private types  ------------------------------------------------------

	typedef	VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
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


#endif /* _H_CVideo */

