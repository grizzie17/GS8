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
#include "VConfiguration.h"

#include "TDictionaryIndexed.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "UTypes.h"

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

class CConfiguration : public VConfiguration
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

	virtual long	LocateEntry( Yogi::Core::ConstCCharStringRef rName );

	virtual CVariantDataPtr
					GetData( index_t nSel );
	virtual bool	PutData( index_t nSel, CVariantDataPtr pData );

	virtual bool	AddAlias
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
			);

	virtual
	CVariantDataPtr	
			GetEntry
			( 
			Yogi::Core::ConstCCharStringRef sKey 
			);

	virtual
	long	GetEntryAsInteger
			(
			const char*	sKey,
			long		nDefault = 0
			);

	virtual
	unsigned long
			GetEntryAsUnsigned
			(
			const char*		sKey,
			unsigned long	nDefault = 0
			);

	virtual
	GFLOAT	GetEntryAsFloat
			(
			const char*	sKey,
			GFLOAT		fDefault = 0.0f
			);

	virtual
	GFLOAT	GetEntryAsFloatUnits
			(
			const char*	sKey,
			const char*	sUnitName,
			GFLOAT		fDefault = 0.0f
			);

	virtual
	Yogi::Core::CCharString		
			GetEntryAsString
			(
			const char*	sKey,
			const char*	sDefault = 0
			);

	virtual
	long	GetEntryAsEnum
			(
			const char*			sKey,
			const EnumDatumPtr	pEnumList,
			const long			nEnumCount,
			const long			nDefault = 0,
			const long			nError = 0
			);

	virtual
	bool	GetEntryAsBool
			(
			const char*	sKey,
			const bool	bDefault = false
			);

	virtual
	Yogi::Core::CColor
			GetEntryAsColor
			(
			const char*		sKey,
			const Yogi::Core::CColor	cDefault = Yogi::Core::CColor()
			);


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

