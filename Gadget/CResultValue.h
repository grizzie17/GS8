/*---------------------------------------------------------------------+\
|
|	CResultValue.h  --  cached result from an equation
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
	10-Nov-2010			J.Griswold		(Reviewed by: xxxx)
		Add accessors for the data
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	29-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetValueExclussive that will clear the equation if one
		is present.
	29-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CResultValue
#define _H_CResultValue
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEquation.h"
#include "CVariantData.h"
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


typedef class CResultValue*			CResultValuePtr;
typedef class CResultValue&			CResultValueRef;
typedef const class CResultValue&	ConstCResultValueRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CResultValue : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					CResultValue();
					CResultValue( ConstCResultValueRef r );	// copy constructor
	virtual			~CResultValue();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CResultValueRef	operator=( ConstCResultValueRef r );		// assignment

	bool			Calculate( VDictionaryPtr pDict );
	Yogi::Common::CVariantData
					GetCachedValue(void);
	bool			HasEquation( void );
	VEquationPtr	GetEquation( void );	// returns raw pointer to equation

	bool			SetEquation( VEquationPtr pEquation );
	bool			SetValue( Yogi::Common::ConstCVariantDataRef r);
	bool			SetValue( GFLOAT f );

	// if equation is set then clear it
	bool			SetValueExclussive( Yogi::Common::ConstCVariantDataRef r);
	bool			SetValueExclussive( GFLOAT f );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Common::CVariantData	m_vCachedData;
	VEquationPtr				m_pEquation;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VEquation
public:
	virtual Yogi::Common::CVariantData	GetValue(VDictionaryPtr pDict);
	virtual VEquationPtr				Clone( void );


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


#endif /* _H_CResultValue */
