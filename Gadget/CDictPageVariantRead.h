/*---------------------------------------------------------------------+\
|
|	CDictPageVariantRead.h  --  Contained Data is CVariantData
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
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageVariantRead
#define _H_CDictPageVariantRead
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "CDictPageVariant.h"
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
typedef class CDictPageVariantRead*			CDictPageVariantReadPtr;
typedef class CDictPageVariantRead&			CDictPageVariantReadRef;
typedef const class CDictPageVariantRead&	ConstCDictPageVariantReadRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageVariantRead : public CDictPageVariant
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageVariantRead();
	virtual			~CDictPageVariantRead();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	bool			LockData( bool bLock );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	bool			m_bLocked;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual bool	PutData( unsigned long nSel, const Yogi::Common::CVariantData* pData );
	virtual bool	IsDataLocked( unsigned long nSel );

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



#endif /* _H_CDictPageVariantRead */
