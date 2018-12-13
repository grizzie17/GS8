/*---------------------------------------------------------------------+\
|
|	CEqOpGreaterThan.h  --  brief description of what CEqOpGreaterThan.h is for
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
	24-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEqOpGreaterThan
#define _H_CEqOpGreaterThan
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VEqOpBinary.h"
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

typedef class CEquationOperatorGreaterThan*		CEquationOperatorGreaterThanPtr;
typedef class CEquationOperatorGreaterThan&		CEquationOperatorGreaterThanRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CEquationOperatorGreaterThan : public VEquationOperatorBinary
{
//	class lifecycle  ----------------------------------------------------
public:
					CEquationOperatorGreaterThan();
					CEquationOperatorGreaterThan( CEquationOperatorGreaterThanRef r );	// copy constructor
	virtual			~CEquationOperatorGreaterThan();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CEquationOperatorGreaterThanRef	operator=( CEquationOperatorGreaterThanRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VEquation
public:
	virtual Yogi::Common::CVariantData	GetValue( VDictionaryPtr pDict );
	virtual VEquationPtr				Clone( void );

	//	VEquationOperatorBinary

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


#endif /* _H_CEqOpGreaterThan */
