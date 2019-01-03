/*---------------------------------------------------------------------+\
|
|	VDesk.h  --  brief description of what VDesk.h is for
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
	16-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VDesk
#define _H_VDesk
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "VSupports.h"
#include "IDesk.h"

namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class VDesk : public Yogi::Common::VSupports,
					implements_ IDesk
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VDesk );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IDesk
	virtual
	Yogi::Core::NResult
		OnActivate
		(
		);

	virtual
	Yogi::Core::NResult
		OnDeactivate
		(
		);

	virtual
	Yogi::Core::NResult
		OnRender
		(
		Yogi::Common::VDrawPtr	pDraw
		);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef Yogi::Common::VSupports	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
			);

};

/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/
}}


#endif /* _H_VDesk */
