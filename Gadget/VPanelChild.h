/*---------------------------------------------------------------------+\
|
|	VPanelChild.h  --  abstract base class for PanelDivs and Gauges
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
	07-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Implement new Layout function that deals with position and
		size calculation
	03-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Change to use 'Size' instead of separate Width and Height
		properties to be more compatible with V2 schema
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPanelChild
#define _H_VPanelChild
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VControl.h"

#include "CPosition.h"
#include "CSize.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
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
typedef class VPanelChild*		VPanelChildPtr;
typedef class VPanelChild&		VPanelChildRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPanelChild : public VControl
{
//	class lifecycle  ----------------------------------------------------
public:
					VPanelChild();
	virtual			~VPanelChild();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void			SetSize( long nWidth, long nHeight );
	void			SetPosition( CPositionPtr p );
	CPositionPtr	Position( void );
	CSizePtr		Size( void );
	void			SetCropped( bool b );

	virtual bool	Layout( VDictionaryPtr pDict );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CPositionPtr	m_pPosition;
	CSize			m_tSize;
	bool			m_bCropped;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
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



#endif /* _H_VPanelChild */

