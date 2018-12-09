/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeOpenGL.h  --  brief description of what CApplicationGaugeOpenGL.h is for
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
    14-Dec-2009         R.Hosea        (Reviewed by: J.Griswold)
        Fixed gcc compile problem for omniscape
	09-Dec-2009			C. Cason		(Reviewed by: R.Hosea)
		Initial Revision - baselined from CApplicationGaugeVDDS.h
|
\+---------------------------------------------------------------------*/
#ifndef _H_CApplicationGaugeOpenGL
#define _H_CApplicationGaugeOpenGL
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CApplicationGauge.h"
#include "UMachine.h"
#if defined( OS_LINUX_BLUERING )
#include "CDrawOpenGL.h"
#include "CFactoryConfiguration.h"

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
typedef class CApplicationGaugeOpenGL*			CApplicationGaugeOpenGLPtr;
typedef class CApplicationGaugeOpenGL&			CApplicationGaugeOpenGLRef;
typedef const class CApplicationGaugeOpenGL&	ConstCApplicationGaugeOpenGLRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CApplicationGaugeOpenGL : public CApplicationGauge
{
//	class lifecycle  ----------------------------------------------------
public:
					CApplicationGaugeOpenGL();
					CApplicationGaugeOpenGL( ConstCApplicationGaugeOpenGLRef r );	// copy constructor
	virtual			~CApplicationGaugeOpenGL();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CApplicationGaugeOpenGLRef	operator=( ConstCApplicationGaugeOpenGLRef r );		// assignment

	CDrawOpenGLPtr		DrawOpenGL( void );
	void 				SetPort(unsigned int port);
	CConfigurationPtr	MakeConfiguration(void);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------
	unsigned int m_port;

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	CApplicationGauge-1
	//	CApplicationGauge
public:
// 	virtual bool	Initialize
// 					(
// 					void
// 					);

protected:
	virtual VDrawPtr					MakeDraw( void );
	virtual VDictionaryPageServerPtr	MakeDictionary( void );
	virtual CScreenPtr					MakeScreen( void );

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


#endif	// OS_LINUX

#endif /* _H_CApplicationGaugeOpenGL */
