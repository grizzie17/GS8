/*---------------------------------------------------------------------+\
|	Delete this comment block
|
|	globally substitute "filename" to be the name of this file (no suffix).
|	globally substitute "dd-mmm-9999" to be today's date.
|	globally substitute "F.Lastname" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "DerivedClass" to be the name of this class.
|	globally substitute "IInterface" to be your interface-name.
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	filename.h  --  brief description of what filename.h is for
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_filename
#define _H_filename
#pragma once
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "VSupports.h"
#include "IInterface.h"
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

class DerivedClass : public VSupports,
					implements_ IInterface
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( DerivedClass );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,
			AnotherType	arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
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


#endif /* _H_filename */

