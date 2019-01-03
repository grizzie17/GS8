/*---------------------------------------------------------------------+\
|
|	CImage.h  --  brief description of what CImage.h is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CImage
#define _H_CImage
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"

#include "CPoint.h"
#include "CCharString.h"
#include "CSize.h"


namespace Yogi { namespace Gadget {
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

typedef class CImage*		CImagePtr;
typedef class CImage&		CImageRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CImage : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					CImage();
					CImage( CImageRef r );	// copy constructor
	virtual			~CImage();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CImageRef	operator=( CImageRef r );		// assignment

	Yogi::Core::ConstCCharStringPtr	File( void ) const;
	bool			SetFile( Yogi::Core::ConstCCharDescriptorRef );
	CPointValuePtr	Origin( void );
	CSizePtr		Size( void );
	void			SetAlign( Yogi::Common::VDraw::EAlignments e );
	void			SetVertAlign( Yogi::Common::VDraw::EVerticalAlignments e );
	void			SetFitment( Yogi::Common::VDraw::EFitments e );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString		m_sFile;
	CPointValue					m_tOrigin;
	CSize						m_tSize;
	Yogi::Common::IDraw::EAlignments	m_eAlign;
	Yogi::Common::IDraw::EVerticalAlignments
								m_eVertAlign;
	Yogi::Common::IDraw::EFitments	m_eFitment;

	Yogi::Common::IDraw::VImagePtr	m_pImage;



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


#endif /* _H_CImage */
