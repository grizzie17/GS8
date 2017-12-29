/*---------------------------------------------------------------------+\
|
|	CDictionaryMemory.h  --  Wrapper class to implement storage registers for expressions
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:

		This class should be called from the CGauge ONLY

|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the psuedo-interface VVariable
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Increase number of registers from 10 to 16
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add GetMilliseconds
	20-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictionaryMemory
#define _H_CDictionaryMemory
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDictionary.h"
//#include "CVariantData.h"
#include "VControl.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CDictionaryMemory*		CDictionaryMemoryPtr;
typedef class CDictionaryMemory&		CDictionaryMemoryRef;
typedef const class CDictionaryMemory&	ConstCDictionaryMemoryRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictionaryMemory : public VDictionary
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictionaryMemory();
					CDictionaryMemory( VDictionaryPtr p );
					CDictionaryMemory
							(
							VDictionaryPtr	pDict,
							VControlPtr		pControl
							);
	virtual			~CDictionaryMemory();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CDictionaryMemoryRef	operator=( VDictionaryPtr p );		// assignment

	void			SetDictionary( VDictionaryPtr p );
	void			SetVControl( VControlPtr p );
	
	void			Store( int nRegister, CVariantDataRef rData );
	CVariantData	Recall( int nRegister );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VDictionaryPtr	m_pDict;
	VControlPtr		m_pControl;
	CVariantData	m_aRegisters[16];

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionary
public:
	virtual void			BeginCalculate( void );
	virtual void			EndCalculate( void );


	virtual VDictionary::Selector
							LocateEntry( ConstCCharStringRef rName );
	virtual VDictionary::Selector
							LocateEntry( const char* sName );
	virtual CVariantDataPtr	GetData( VDictionary::Selector nSel );
	virtual bool			PutData( VDictionary::Selector nSel, CVariantDataPtr pData );
	virtual bool			IsDataLocked( Selector nSel );

	virtual	bool			PushDictionaryPage( VDictionaryPage* pDict );
	virtual bool			PopDictionaryPage( void );

	virtual bool			IsDirty( void );
	virtual long			GetMilliseconds( void );

	// memory dictionary is type = 'M'
	virtual int				GetType( void );	// return type of dictionary

	virtual VDictionaryEnumerator*
							GetEnumerator( void );
	virtual VDictionaryEnumerator*
							GetPageEnumerator( char cPageID );
	virtual VVariablePtr	GetVariableIF( void );

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


inline
void	CDictionaryMemory::SetDictionary
		(
		VDictionaryPtr	p
		)
{
	m_pDict = p;
}


inline
void	CDictionaryMemory::SetVControl
		(
		VControlPtr		p
		)
{
	m_pControl = p;
}



NAMESPACE_GADGET_END



#endif /* _H_CDictionaryMemory */

