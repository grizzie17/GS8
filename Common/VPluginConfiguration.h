/*---------------------------------------------------------------------+\
|
|	VPluginConfiguration.h  --  brief description of what VPluginConfiguration.h is for
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
	10-May-2010			J.Griswold		(Reviewed by: S.Snider) [1]
		Add GetAttribute function
	05-Jun-2010			J.Griswold		(Reviewed by: PJH)
		Fixed a problem where deleting the string returned from the
		GetParameterAsString would corrupt the heap.  This was caused
		by two different heaps one for the DLL and the other for the App.
	10-May-2010			J.Griswold		(Reviewed by: P.Hogan) [1]
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginConfiguration
#define _H_VPluginConfiguration
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharString.h"
#include "CCharDescriptor.h"
#include "CDateTime.h"
#include "CVariantData.h"
#include "THash.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {


#define	E_(ename)		EX_(ename)
#define	E2_(ename,val)	EX2_(ename,val)


#define	EX_(n)		n
#define	EX2_(n,v)	n = v

#define	EL_(n)		{n,#n}
#define	EL2_(n,v)	{n,#n}


#define ENUMTYPE(tname, elist)	\
	typedef enum tname { elist } tname



/*
#define ELIST_GEORGE	\
			E_(ITEM1),	\
			E_(ITEM2),	\
			E2_(ITEM3,3333),	\
			E_(ITEM4)
*/



/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VPluginConfiguration*			VPluginConfigurationPtr;
typedef class VPluginConfiguration&			VPluginConfigurationRef;
typedef const class VPluginConfiguration&	ConstVPluginConfigurationRef;


#ifdef E_
#undef E_
#endif
#ifdef E2_
#undef E2_
#endif

#define	E_(ename)		EX_(ename)
#define	E2_(ename,val)	EX2_(ename,val)


//ENUMTYPE( EGEORGE, ELIST_GEORGE );


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPluginConfiguration
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VPluginConfiguration(){};

public:
//	public types  -------------------------------------------------------

	typedef struct EnumDatum
	{
		long		nValue;
		const char*	sKey;
	} EnumDatum;
	typedef EnumDatum*	EnumDatumPtr;
	typedef	EnumDatum*	EnumData;

	typedef THashTableEnumerator<Yogi::Core::CCharString, CVariantData>	ParamEnum;
	typedef THashTableEnumerator<Yogi::Core::CCharString, VPluginConfigurationPtr> FolderEnum;

//	public functions  ---------------------------------------------------

	virtual
	VPluginConfiguration*
			SelectSingleNode
			(
			const char*	sQuery
			) = 0;

	virtual
	Yogi::Core::ConstCCharStringRef
			GetClass
			(
			void
			) const = 0;

	virtual
	Yogi::Core::ConstCCharStringRef
			GetGroup
			(
			void
			) const = 0;

	virtual
	Yogi::Core::ConstCCharStringRef
			GetID
			(
			void
			) const = 0;

	virtual
	Yogi::Core::ConstCCharStringRef
			GetAttribute
			(
			const char*	sKey
			) = 0;

	virtual
	ParamEnum
			GetParamEnum
			(
			void
			) const = 0;

	virtual
	FolderEnum
			GetFolderEnum
			(
			void
			) const = 0;

	virtual
	const CVariantData*
			GetParameter
			(
			const char* sKey
			) const = 0;

	virtual
	const CVariantData*
			GetParameter
			(
			Yogi::Core::ConstCCharStringRef sKey
			) const = 0;

	virtual
	long	GetParameterAsInteger
			(
			const char*	sKey,
			long		nDefault = 0
			) const = 0;

	virtual
	long	GetParameterAsIntegerArray
			(						// [rtn] number of longs in parameter list
			long*		pArray,
			long		nAlloc,		// number of longs allocated in array
			const char*	sKey
			) const = 0;

	virtual
	unsigned long
			GetParameterAsUnsigned
			(
			const char*		sKey,
			unsigned long	nDefault = 0
			) const = 0;

	virtual
	GFLOAT	GetParameterAsFloat
			(
			const char*	sKey,
			GFLOAT		fDefault = 0.0f
			) const = 0;

	virtual
	GFLOAT	GetParameterAsFloatUnits
			(
			const char*	sKey,
			const char*	sUnitName,
			GFLOAT		fDefault = 0.0f
			) const = 0;

	virtual
	Yogi::Core::ConstCCharStringRef
			GetParameterAsString
			(
			const char*	sKey,
			const char*	sDefault = 0
			) const = 0;

	virtual
	long	GetParameterAsEnum
			(
			const char*			sKey,
			const EnumDatumPtr	pEnumList,
			const long			nEnumCount,
			const long			nDefault = 0,
			const long			nError = 0
			) const = 0;

	virtual
	bool	GetParameterAsBool
			(
			const char*	sKey,
			const bool	bDefault = false
			) const = 0;

	virtual
	Yogi::Core::CColor
			GetParameterAsColor
			(
			const char*		sKey,
			Yogi::Core::ConstCColorRef	cDefault = Yogi::Core::CColor()
			) const = 0;

	virtual
	Yogi::Core::CDateTime
			GetParameterAsDateTime
			(
			const char*		sKey,
			Yogi::Core::ConstCDateTimeRef	tDefault = Yogi::Core::CDateTime()
			) const = 0;

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



#endif /* _H_VPluginConfiguration */

