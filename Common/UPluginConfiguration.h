/*---------------------------------------------------------------------+\
|
|	UPluginConfiguration.h  --  brief description of what UPluginConfiguration.h is for
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
	04-Oct-2010			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UPluginConfiguration
#define _H_UPluginConfiguration
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


#define ENUMPLUGIN(tname, elist)	\
	VPluginConfiguration::EnumDatum	tname[] = { elist }


#ifdef E_
#undef E_
#endif
#ifdef E2_
#undef E2_
#endif

#define	E_(ename)		EL_(ename)
#define	E2_(ename,val)	EL2_(ename,val)

//ENUMPLUGIN( XGEORGE, ELIST_GEORGE );

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
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
||	Function Macros														|
||																		|
\+=====================================================================*/


#endif /* _H_UPluginConfiguration */

