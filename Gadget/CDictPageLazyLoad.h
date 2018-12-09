/*---------------------------------------------------------------------+\
|
|	CDictPageLazyLoad.h  --  Lazy Load of Variables
|
|	Purpose:

		Dynamically creates variables when requesting selector.

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
	19-Aug-2009			J.Griswold
		Change class hierarchy so that we are sharing a common base class
		of CDictPageVariant
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageLazyLoad
#define _H_CDictPageLazyLoad
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
typedef class CDictPageLazyLoad*		CDictPageLazyLoadPtr;
typedef class CDictPageLazyLoad&		CDictPageLazyLoadRef;
typedef const class CDictPageLazyLoad&	ConstCDictPageLazyLoadRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageLazyLoad : public CDictPageVariant
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageLazyLoad();
	virtual			~CDictPageLazyLoad();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	// data provided by CDictPageVariant

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual long		LocateEntry( ConstCCharStringRef rName );

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



#endif /* _H_CDictPageLazyLoad */
