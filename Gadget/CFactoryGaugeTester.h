/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2009 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CFactoryGaugeTester.h  --  THIS FILE IS RETIRED
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	15-Sep-2009			J.Griswold		(Reviewed by: xxxx)
		THIS FILE IS RETIRED
	01-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryGaugeTester
#define _H_CFactoryGaugeTester
#pragma once


#if 0	// RETIRED CONTENTS
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VFactoryGauge.h"
#include "CFactoryEquation.h"
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

typedef class CFactoryGaugeTester*		CFactoryGaugeTesterPtr;
typedef class CFactoryGaugeTester&		CFactoryGaugeTesterRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryGaugeTester : public VFactoryGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryGaugeTester();
					CFactoryGaugeTester( CFactoryGaugeTesterRef r );	// copy constructor
	virtual			~CFactoryGaugeTester();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CFactoryGaugeTesterRef	operator=( CFactoryGaugeTesterRef r );		// assignment

	void	SelectName( char* sName );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	CGaugePtr	Get_test();
	CGaugePtr	Get_simpletest();
	CGaugePtr	Get_slider();
	CGaugePtr	Get_sliderHider();
	CGaugePtr	Get_dial();

//	protected data  -----------------------------------------------------

	int					m_nSelected;
	CFactoryEquationPtr	m_pFactoryEquation;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	VGaugeFactoryTester
public:
	virtual CGaugePtr	Get( void );
	virtual CGaugePtr	Make( char* sName );

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


#endif	// retired contents

#endif /* _H_CFactoryGaugeTester */


