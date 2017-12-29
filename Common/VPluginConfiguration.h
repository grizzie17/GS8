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
#include "CVariantData.h"
#include "THash.h"

#include "NamespaceCommon.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMON_BEGIN


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

	typedef THashTableEnumerator<CCharString, CVariantData>	ParamEnum;
	typedef THashTableEnumerator<CCharString, VPluginConfigurationPtr> FolderEnum;

//	public functions  ---------------------------------------------------

	virtual
	VPluginConfiguration*
			SelectSingleNode
			(
			const char*	sQuery
			) = 0;

	virtual
	CCharStringRef
			GetClass
			(
			void
			) = 0;

	virtual
	CCharStringRef
			GetGroup
			(
			void
			) = 0;

	virtual
	CCharStringRef
			GetID
			(
			void
			) = 0;

	virtual
	CCharStringRef
			GetAttribute
			(
			const char*	sKey
			) = 0;

	virtual
	ParamEnum
			GetParamEnum
			(
			void
			) = 0;

	virtual
	FolderEnum
			GetFolderEnum
			(
			void
			) = 0;

	virtual
	CVariantDataPtr
			GetParameter
			(
			const char* sKey
			) = 0;

	virtual
	CVariantDataPtr
			GetParameter
			(
			ConstCCharStringRef sKey
			) = 0;

	virtual
	long	GetParameterAsInteger
			(
			const char*	sKey,
			long		nDefault = 0
			) = 0;

	virtual
	long	GetParameterAsIntegerArray
			(						// [rtn] number of longs in parameter list
			long*		pArray,
			long		nAlloc,		// number of longs allocated in array
			const char*	sKey
			) = 0;

	virtual
	unsigned long
			GetParameterAsUnsigned
			(
			const char*		sKey,
			unsigned long	nDefault = 0
			) = 0;

	virtual
	GFLOAT	GetParameterAsFloat
			(
			const char*	sKey,
			GFLOAT		fDefault = 0.0f
			) = 0;

	virtual
	GFLOAT	GetParameterAsFloatUnits
			(
			const char*	sKey,
			const char*	sUnitName,
			GFLOAT		fDefault = 0.0f
			) = 0;

	virtual
	CCharStringRef
			GetParameterAsString
			(
			const char*	sKey,
			const char*	sDefault = 0
			) = 0;

	virtual
	long	GetParameterAsEnum
			(
			const char*			sKey,
			const EnumDatumPtr	pEnumList,
			const long			nEnumCount,
			const long			nDefault = 0,
			const long			nError = 0
			) = 0;

	virtual
	bool	GetParameterAsBool
			(
			const char*	sKey,
			const bool	bDefault = false
			) = 0;

	virtual
	CColor	GetParameterAsColor
			(
			const char*		sKey,
			const CColor	cDefault = CColor()
			) = 0;

	virtual
	CDateTime
			GetParameterAsDateTime
			(
			const char*		sKey,
			const CDateTime	tDefault = CDateTime()
			) = 0;

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

NAMESPACE_COMMON_END



#endif /* _H_VPluginConfiguration */

