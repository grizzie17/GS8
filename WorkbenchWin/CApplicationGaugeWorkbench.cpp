/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWorkbench.cpp  --  brief description of what CApplicationGaugeWorkbench.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	26-Jan-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for setting the window title
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to call Size instead of SetSize on draw object
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changes to support foreground/background (double-buffer) drawing.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Dispose of unnecessary functions
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	05-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CApplicationGaugeWorkbench.h"

#if defined( OS_MSWIN )
#include "CDictionary.h"
#include "CFactoryScreen.h"
#include "CFactoryConfiguration.h"
#include "LogFile.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CApplicationGaugeWorkbench - constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::CApplicationGaugeWorkbench
		(
		void
		)
		: inherited()
		, m_pDialog( 0 )
{
}

/*---------------------------------------------------------------------+\

 * ~CApplicationGaugeWorkbench - destructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::~CApplicationGaugeWorkbench
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * SetCView -

\+---------------------------------------------------------------------*/
void	CApplicationGaugeWorkbench::SetVPostCalculate
		(
		VPostCalculate*	p
		)
{
	m_pDialog = p;
}



/*---------------------------------------------------------------------+\

 * SetConfiguration -

\+---------------------------------------------------------------------*/
void	CApplicationGaugeWorkbench::SetConfiguration
		(
		VConfigurationPtr	p
		)
{
	m_pConfiguration = p;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * WindowTitle -

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWorkbench::WindowTitle
		(
		ConstCCharDescriptorRef rChar
		)
{
	if ( m_pDialog )
	{
		char	s[128];
		rChar.CopyTo( s, sizeof(s) );

		m_pDialog->SetWindowTitle( s );
	}

	return true;
}



/*---------------------------------------------------------------------+\

 * PostCalculateNeeded -

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWorkbench::PostCalculateNeeded
		(
		void
		)
{
	if ( m_pDialog )
		m_pDialog->PostCalculateNeeded();
	return true;
}




/*---------------------------------------------------------------------+\

 * MakeConfiguration -

\+---------------------------------------------------------------------*/
VConfigurationPtr
		CApplicationGaugeWorkbench::MakeConfiguration
		(
		void
		)
{
	CCharString	sName( "configurationWB" );
	CFactoryConfiguration	factory;
	factory.SetRelativePath( "dictionary" );
	VConfigurationPtr	pConfig = factory.Make( sName.Pointer() );

	CCharString		sOS = OS_NAME;
	CVariantData	v = sOS;
	pConfig->AddEntry( "OS", v );

	return pConfig;
}





}}



#endif	//	OS_MSWIN
