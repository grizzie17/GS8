/*==================================================================*//**
*
*	@file	CConfiguration.h
*	@brief	Access configuration file
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		change class hierarchy
	27-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CConfiguration_Common
#define _H_CConfiguration_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "TDictionaryIndexed.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "UTypes.h"

#include "VConfiguration.h"
#include "UDeclCommon.h"

namespace Yogi { namespace Common {
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
typedef class CConfiguration*		CConfigurationPtr;
typedef class CConfiguration&		CConfigurationRef;
typedef const class CConfiguration&	ConstCConfigurationRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS CConfiguration : public VConfiguration
{
//	class lifecycle  ----------------------------------------------------
public:
					CConfiguration();
	virtual			~CConfiguration();

public:
//	public types  -------------------------------------------------------

	typedef
		TDictionaryIndexedEnumerator< Yogi::Core::CCharString, CVariantData >
		Enumerator;


//	public functions  ---------------------------------------------------

	virtual long
			LocateEntry
			(
			Yogi::Core::ConstCCharStringRef rName
			) const;

	virtual ConstCVariantDataPtr
			GetData
			(
			index_t nSel
			) const;
	virtual bool
			PutData
			(
			index_t nSel,
			const Yogi::Common::CVariantData* pData
			);

	virtual bool
			AddAlias
			(
			Yogi::Core::ConstCCharDescriptorRef rKey,
			Yogi::Core::ConstCCharDescriptorRef rAlias
			);

	virtual Enumerator
			GetEnumerator( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< Yogi::Core::CCharString, CVariantData>	m_aContent;

	//THashTable< CCharString, CVariantData >	m_aContent;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VVariable
public:
	virtual
	Yogi::Core::CCharString
			ResolveVariable
			(
			Yogi::Core::ConstCCharDescriptorRef	r
			);

	//	VConfiguration
public:
	virtual
	bool	AddEntry
			(
			const char* sKey,
			ConstCVariantDataRef rData
			);

	virtual
	CVariantDataPtr
			GetEntry
			(
			const char* sKey
			) const;

	virtual
	CVariantDataPtr
			GetEntry
			(
			Yogi::Core::ConstCCharStringRef sKey
			) const;

	virtual
	long	GetEntryAsInteger
			(
			const char*	sKey,
			long		nDefault = 0
			) const;

	virtual
	unsigned long
			GetEntryAsUnsigned
			(
			const char*		sKey,
			unsigned long	nDefault = 0
			) const;

	virtual
	GFLOAT	GetEntryAsFloat
			(
			const char*	sKey,
			GFLOAT		fDefault = 0.0f
			) const;

	virtual
	GFLOAT	GetEntryAsFloatUnits
			(
			const char*	sKey,
			const char*	sUnitName,
			GFLOAT		fDefault = 0.0f
			) const;

	virtual
	Yogi::Core::CCharString
			GetEntryAsString
			(
			const char*	sKey,
			const char*	sDefault = 0
			) const;

	virtual
	long	GetEntryAsEnum
			(
			const char*			sKey,
			const EnumDatumPtr	pEnumList,
			const long			nEnumCount,
			const long			nDefault = 0,
			const long			nError = 0
			) const;

	virtual
	bool	GetEntryAsBool
			(
			const char*	sKey,
			const bool	bDefault = false
			) const;

	virtual
	Yogi::Core::CColor
			GetEntryAsColor
			(
			const char*		sKey,
			const Yogi::Core::CColor	cDefault = Yogi::Core::CColor()
			) const;


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



#endif /* _H_CConfiguration */
