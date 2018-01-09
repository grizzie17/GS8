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

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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
		TDictionaryIndexedEnumerator< NAMESPACE_ROOT_PREFIX CCharString, CVariantData >
		Enumerator;


//	public functions  ---------------------------------------------------

	virtual long	LocateEntry( NAMESPACE_ROOT_PREFIX ConstCCharStringRef rName );

	virtual CVariantDataPtr
					GetData( index_t nSel );
	virtual bool	PutData( index_t nSel, CVariantDataPtr pData );

	virtual bool	AddAlias
					( 
					NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef rKey, 
					NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef rAlias 
					);

	virtual Enumerator
					GetEnumerator( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TDictionaryIndexed< NAMESPACE_ROOT_PREFIX CCharString, CVariantData>	m_aContent;

	//THashTable< CCharString, CVariantData >	m_aContent;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VVariable
public:
	virtual
	NAMESPACE_ROOT_PREFIX CCharString
			ResolveVariable
			(
			NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef	r
			);

	//	VConfiguration
public:
	virtual
	bool			AddEntry( const char* sKey, ConstCVariantDataRef rData );

	virtual
	CVariantDataPtr	GetEntry( const char* sKey );

	virtual
	CVariantDataPtr	GetEntry( NAMESPACE_ROOT_PREFIX ConstCCharStringRef sKey );

	virtual
	long			GetEntryAsInteger
					(
					const char*	sKey,
					long		nDefault = 0
					);

	virtual
	unsigned long	GetEntryAsUnsigned
					(
					const char*		sKey,
					unsigned long	nDefault = 0
					);

	virtual
	GFLOAT			GetEntryAsFloat
					(
					const char*	sKey,
					GFLOAT		fDefault = 0.0f
					);

	virtual
	GFLOAT			GetEntryAsFloatUnits
					(
					const char*	sKey,
					const char*	sUnitName,
					GFLOAT		fDefault = 0.0f
					);

	virtual
	NAMESPACE_ROOT_PREFIX CCharString		
					GetEntryAsString
					(
					const char*	sKey,
					const char*	sDefault = 0
					);

	virtual
	long			GetEntryAsEnum
					(
					const char*			sKey,
					const EnumDatumPtr	pEnumList,
					const long			nEnumCount,
					const long			nDefault = 0,
					const long			nError = 0
					);

	virtual
	bool			GetEntryAsBool
					(
					const char*	sKey,
					const bool	bDefault = false
					);

	virtual
	CColor			GetEntryAsColor
					(
					const char*		sKey,
					const CColor	cDefault = CColor()
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

NAMESPACE_COMMON_END



#endif /* _H_CConfiguration */

