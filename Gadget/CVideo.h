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
namespace Yogi { namespace Gadget {

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
	void			SetAlign( Yogi::Common::VDraw::EAlignments e );
	void			SetVertAlign( Yogi::Common::VDraw::EVerticalAlignments e );
	void			SetFitment( Yogi::Common::VDraw::EFitments e );
	CResultValuePtr	Mirror( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------


//	protected data  -----------------------------------------------------

	CResultValue	m_tSource;
	CPointValue		m_tOrigin;
	CSize			m_tSize;
	Yogi::Common::VDraw::EAlignments	m_eAlign;
	Yogi::Common::VDraw::EVerticalAlignments
						m_eVertAlign;
	Yogi::Common::VDraw::EFitments	m_eFitment;
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
	virtual bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );

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


#endif /* _H_CVideo */
