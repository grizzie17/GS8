/*---------------------------------------------------------------------+\
|
|	CPluginConfiguration.h  --  brief description of what CPluginConfiguration.h is for
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
	13-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Allow for prunning of the hierarchy
	05-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Fixed a problem where deleting the string returned from the
		GetParameterAsString would corrupt the heap.  This was caused
		by two different heaps one for the DLL and the other for the App.
	09-May-2010			J.Griswold		(Reviewed by: P.Hogan) [1]
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPluginConfiguration
#define _H_CPluginConfiguration
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginConfiguration.h"

//#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"


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
typedef class CPluginConfiguration*			CPluginConfigurationPtr;
typedef class CPluginConfiguration&			CPluginConfigurationRef;
typedef const class CPluginConfiguration&	ConstCPluginConfigurationRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPluginConfiguration : public VPluginConfiguration
{
//	class lifecycle  ----------------------------------------------------
public:
					CPluginConfiguration();
	virtual			~CPluginConfiguration();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void			SetClass( CCharDescriptorRef r );
	void			SetGroup( CCharDescriptorRef r );
	void			SetID( CCharDescriptorRef r );

	virtual
	VPluginConfiguration*
			SelectSingleNode
			(
			const char*	sQuery
			);

	virtual
	CCharStringRef	GetClass( void );
	virtual
	CCharStringRef	GetGroup( void );
	virtual
	CCharStringRef	GetID( void );

	void			AddParameter( CCharDescriptorRef rName, CVariantDataRef rData );
	void			AddAttribute( CCharDescriptorRef rName, CCharDescriptorRef rData );
	bool			AddFolder( CCharDescriptorRef rName, CPluginConfigurationPtr pFolder );

	void			PruneFolder( CPluginConfigurationPtr pConfig );

	virtual
	ParamEnum		GetParamEnum( void );

	virtual
	FolderEnum		GetFolderEnum( void );

	virtual
	CCharStringRef
			GetAttribute
			(
			const char*	sKey
			);


	virtual
	CVariantDataPtr	GetParameter
					(
					const char* sKey
					);

	virtual
	CVariantDataPtr	GetParameter
					(
					ConstCCharStringRef sKey
					);

	virtual
	long			GetParameterAsInteger
					(
					const char*	sKey,
					long		nDefault = 0
					);

	virtual
	long			GetParameterAsIntegerArray
					(						// [rtn] number of longs in parameter list
					long*		pArray,
					long		nAlloc,		// number of longs allocated in array
					const char*	sKey
					);

	virtual
	unsigned long	GetParameterAsUnsigned
					(
					const char*		sKey,
					unsigned long	nDefault = 0
					);

	virtual
	GFLOAT			GetParameterAsFloat
					(
					const char*	sKey,
					GFLOAT		fDefault = 0.0f
					);

	virtual
	GFLOAT			GetParameterAsFloatUnits
					(
					const char*	sKey,
					const char*	sUnitName,
					GFLOAT		fDefault = 0.0f
					);

	virtual
	CCharStringRef	GetParameterAsString
					(
					const char*	sKey,
					const char*	sDefault = 0
					);

	virtual
	long			GetParameterAsEnum
					(
					const char*			sKey,
					const EnumDatumPtr	pEnumList,
					const long			nEnumCount,
					const long			nDefault = 0,
					const long			nError = 0
					);

	virtual
	bool			GetParameterAsBool
					(
					const char*	sKey,
					const bool	bDefault = false
					);

	virtual
	CColor			GetParameterAsColor
					(
					const char*		sKey,
					const CColor	cDefault = CColor()
					);

	virtual
	CDateTime		GetParameterAsDateTime
					(
					const char*		sKey,
					const CDateTime	tDefault = CDateTime()
					);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CCharString		m_sClass;
	CCharString		m_sGroup;
	CCharString		m_sID;
	CCharString		m_sTemp;	// working space for GetParameter

	THashTable<CCharString, CCharString>			m_aAttributes;
	THashTable<CCharString, CVariantData>			m_aParameters;

	THashTable<CCharString, VPluginConfigurationPtr>	m_aFolders;
	long												m_nFolderCount;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

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



#endif /* _H_CPluginConfiguration */

