/*---------------------------------------------------------------------+\
|
|	VFactoryGauge.h  --  Abstract class for factory
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature on "Make" so we can track how deeply
		nested we are when we identify an "Include" tag
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Overhaul to support the XMLLite parser
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VFactoryGauge
#define _H_VFactoryGauge
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryComponent.h"


#include "CGauge.h"
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

typedef class VFactoryGauge*		VFactoryGaugePtr;
typedef class VFactoryGauge&		VFactoryGaugeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VFactoryGauge : public VFactoryComponent
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			 	~VFactoryGauge(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual CGaugePtr	Make( const char* sName, int nNest = 0 ) = 0;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


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


#endif /* _H_VFactoryGauge */
