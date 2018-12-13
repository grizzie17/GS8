/*---------------------------------------------------------------------+\
|
|	VDictionary.h  --  holder and distributor of engineering and program data
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|		Dictionary "Page" identifiers:
|

			A:	- Active [Engineering data] (readonly)
			B:	- Baseline [Related to Active] (readonly)
			C:	- Commands [asyncronous] (writeonly)
			D:	- Data/Response [feedback from Commands] (readonly)
			E:	- Events (read/write)
			F:	- Functions [syncronous] (writeonly)
			G:	- Gauge local (read/write)
			K:	- Constants for the C & D pages (readonly)
			I:	- Input (mouse, touch-screen, key) (readonly)
			M:	- Mouse/Touch-screen input (readonly)
			N:	- Notifications [Alerts, Warnings, Notifications] (readonly)
			P:	- Program preferences (read/write)
			S:	- System [such as system time, etc] (readonly)
			T:	- Test (readonly)
			U:	- Universal scope: global to all gauges, panels (read/write)
			V:	- Validity flags for the "A" page

		Flight Simulator "Page" identifiers

			A:	- Aircraft
			C:	- Custom
			E:	- Environment
			G:	- Gauge local
			K:	- Key commands
			L:	- Loadable (Global/Shared)
			M:	- Mouse/Touch-screen input
			P:	- Program (eg. English/Metric)


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
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for enumeration
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	13-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add GetMilliseconds function to be used in support of Frequency
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VDictionary
#define _H_VDictionary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CVariantData.h"
#include "CCharString.h"
#include "TEnumerator.h"
#include "CVariables.h"

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




class VDictionaryPage;			// forward reference
class VDictionaryEnumerator;	// forward reference

typedef class VDictionary*			VDictionaryPtr;
typedef class VDictionary&			VDictionaryRef;
typedef const class VDictionary&	ConstVDictionaryRef;


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VDictionary
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VDictionary(){};

public:
//	public types  -------------------------------------------------------

	typedef	unsigned long	Selector;	// high-byte is page, low-byte-tripplet is index

//	public functions  ---------------------------------------------------

	virtual void			BeginCalculate( void ) = 0;
	virtual void			EndCalculate( void ) = 0;


	virtual Selector		LocateEntry( Yogi::Core::ConstCCharStringRef rName ) = 0;
	virtual Selector		LocateEntry( const char* sName ) = 0;

	virtual Yogi::Common::CVariantDataPtr
							GetData(Selector nSel) = 0;
	virtual bool			PutData(Selector nSel, Yogi::Common::CVariantDataPtr pData) = 0;

	virtual bool			IsDataLocked( Selector nSel ) = 0;


	virtual	bool			PushDictionaryPage( VDictionaryPage* pDict ) = 0;
	virtual bool			PopDictionaryPage( void ) = 0;


	virtual bool			IsDirty( void ) = 0;
	virtual long			GetMilliseconds( void ) = 0;

	// type is returned as an integer letter
	virtual int				GetType( void ) = 0;	// return type of dictionary


	virtual VDictionaryEnumerator*
							GetEnumerator( void ) = 0;
	virtual VDictionaryEnumerator*
							GetPageEnumerator( char cPageID ) = 0;

	virtual Yogi::Common::VVariablePtr
							GetVariableIF(void) = 0;


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
	//	BaseClass-1
	//	BaseClass

};


class VDictionaryEnumerator : public Yogi::Core::TEnumerator<Yogi::Common::CVariantData>
{
public:
	virtual	~VDictionaryEnumerator( void ) {};

public:

	virtual bool						MoveNext( void ) = 0;
	virtual void						Reset( void ) = 0;
	virtual	const Yogi::Common::CVariantData*	Current(void) = 0;

	virtual long						ID( void ) = 0;
	virtual Yogi::Core::CCharString		Key(void) = 0;
	virtual Yogi::Common::CVariantData	Value(void) = 0;
	virtual char						Page( void ) = 0;
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

//template<>
inline
unsigned long
		THashValueFromKey//<VDictionary::Selector>
		(
		const VDictionary::Selector&	key
		)
{
	unsigned long	nHash = (unsigned long)key & 0x00FFFFFF;
	return nHash;
}



}}


#endif /* _H_VDictionary */
