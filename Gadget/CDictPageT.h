/*---------------------------------------------------------------------+\
|
|	CDictPageT.h  --  brief description of what CDictPageT.h is for
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
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Change the arguments to AddAlias to be 'const'
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement dummy enumerator
		Implement new globally standardized update functions
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageT
#define _H_CDictPageT
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionaryPage.h"

#include "CDictPageActive.h"
#include "CDictPageVariant.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CDictPageT*		CDictPageTPtr;
typedef class CDictPageT&		CDictPageTRef;
typedef const class CDictPageT&	ConstCDictPageTRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageT : public VDictionaryPage
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageT();
	virtual			~CDictPageT();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	static void		BumpValues();

	void			SetPageActive( CDictPageActivePtr p );
	void			SetPageBase( CDictPageVariantPtr p );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CDictPageActivePtr	m_pPageActive;
	CDictPageVariantPtr	m_pPageBase;

	long			m_nValue;
	long			m_nMilli;
	bool			m_bAscending;

	CVariantData	m_X;
	CVariantData	m_Y;
	CVariantData	m_Panel;
	CVariantData	m_Spin;
	CVariantData	m_Slider;
	CVariantData	m_SliderYellow;
	CVariantData	m_SliderRed;
	CVariantData	m_Milli;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual void	BeginCalculate( void );
	virtual long	LocateEntry( ConstCCharStringRef rName );
	virtual CVariantDataPtr	GetData( unsigned long nSel );
	virtual bool	PutData( unsigned long nSel, CVariantDataPtr pData );
	virtual bool	UpdateByName( CCharDescriptorRef rKey, CVariantDataRef rData );
	virtual bool	AddAlias( ConstCCharDescriptorRef rKey, ConstCCharDescriptorRef rAlias );
	virtual VDictionaryEnumerator*
					GetEnumerator( void );

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



#endif /* _H_CDictPageT */

