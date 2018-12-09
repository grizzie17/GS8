/*---------------------------------------------------------------------+\
|
|	CTrigger.h  --  cached result from an equation
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
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetName that uses descriptor to send the name instead
		of null terminated string.
	29-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CTrigger
#define _H_CTrigger
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VEquation.h"
#include "CVariantData.h"
#include "CDictionarySelector.h"
#include "CCharDescriptor.h"
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


typedef class CTrigger*			CTriggerPtr;
typedef class CTrigger&			CTriggerRef;
typedef const class CTrigger&	ConstCTriggerRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CTrigger : public VEquation
{
//	class lifecycle  ----------------------------------------------------
public:
					CTrigger();
					CTrigger( ConstCTriggerRef r );	// copy constructor
	virtual			~CTrigger();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CTriggerRef	operator=( ConstCTriggerRef r );		// assignment

	bool			Calculate( VDictionaryPtr pDict );

	bool			SetName( const char* sName );
	bool			SetName( Yogi::Core::ConstCCharDescriptorRef rName);
	bool			SetEquation( VEquationPtr pEquation );
	bool			Equals( VDictionaryPtr pDict, VDictionary::Selector ds );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CDictionarySelector	m_tSelector;
	VEquationPtr		m_pEquation;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VEquation
public:
	virtual CVariantData	GetValue(VDictionaryPtr pDict);
	virtual VEquationPtr	Clone( void );


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


#endif /* _H_CTrigger */
