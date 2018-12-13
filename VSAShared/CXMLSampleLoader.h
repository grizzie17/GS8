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
|	CXMLSampleLoader.h  --  brief description of what CXMLSampleLoader.h is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	05-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Adjust size of the working buffer
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add test generation of Alert data
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Integrate CFactoryVehicleData
	23-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CXMLSampleLoader
#define _H_CXMLSampleLoader
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

#include "CApplicationGauge.h"
#include "CFactoryVehicleData.h"
#include "TPointer.h"


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
typedef class CXMLSampleLoader*			CXMLSampleLoaderPtr;
typedef class CXMLSampleLoader&			CXMLSampleLoaderRef;
typedef const class CXMLSampleLoader&	ConstCXMLSampleLoaderRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CXMLSampleLoader
{
//	class lifecycle  ----------------------------------------------------
public:
					CXMLSampleLoader();
	virtual			~CXMLSampleLoader();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void		SetApplication( CApplicationGaugePtr p );

	void		UpdateActivePage( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	void		CalculateMilliTime( void );

//	protected data  -----------------------------------------------------

	CApplicationGaugePtr	m_pApplication;
	Yogi::Core::TPointer<CFactoryVehicleData>	m_pVehicleData;

	long					m_nMilliStart;
	long					m_nMilli;
	timeb					m_tTimeb;
	struct tm				m_tTm;

	GFLOAT					m_fHeading;
	char					m_sData[1024*4];

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

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



#endif /* _H_CXMLSampleLoader */
