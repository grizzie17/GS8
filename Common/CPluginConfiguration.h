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
#include "CCharDescriptor.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CColor.h"
#include "CVariantData.h"

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
typedef class CPluginConfiguration*       CPluginConfigurationPtr;
typedef class CPluginConfiguration&       CPluginConfigurationRef;
typedef const class CPluginConfiguration& ConstCPluginConfigurationRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class COMMON_CLASS CPluginConfiguration : public VPluginConfiguration
{
    //	class lifecycle  ----------------------------------------------------
public:
    CPluginConfiguration();
    virtual ~CPluginConfiguration();

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

    void
    SetClass( Yogi::Core::ConstCCharDescriptorRef r );
    void
    SetGroup( Yogi::Core::ConstCCharDescriptorRef r );
    void
    SetID( Yogi::Core::ConstCCharDescriptorRef r );

    virtual VPluginConfiguration*
    SelectSingleNode( const char* sQuery );

    virtual Yogi::Core::ConstCCharStringRef
    GetClass( void ) const;
    virtual Yogi::Core::ConstCCharStringRef
    GetGroup( void ) const;
    virtual Yogi::Core::ConstCCharStringRef
    GetID( void ) const;

    virtual Yogi::Core::ConstCCharStringRef
    GetAttribute( const char* sKey );


    virtual ParamEnum
    GetParamEnum( void ) const;

    virtual FolderEnum
    GetFolderEnum( void ) const;

    virtual const CVariantData*
    GetParameter( const char* sKey ) const;

    virtual const CVariantData*
    GetParameter( Yogi::Core::ConstCCharStringRef sKey ) const;

    virtual long
    GetParameterAsInteger( const char* sKey, long nDefault = 0 ) const;

    virtual long
    GetParameterAsIntegerArray(  // [rtn] number of longs in parameter list
            long*       pArray,
            long        nAlloc,  // number of longs allocated in array
            const char* sKey ) const;

    virtual unsigned long
    GetParameterAsUnsigned(
            const char* sKey, unsigned long nDefault = 0 ) const;

    virtual GFLOAT
    GetParameterAsFloat( const char* sKey, GFLOAT fDefault = 0.0f ) const;

    virtual GFLOAT
    GetParameterAsFloatUnits( const char* sKey, const char* sUnitName,
            GFLOAT fDefault = 0.0f ) const;

    virtual Yogi::Core::ConstCCharStringRef
    GetParameterAsString( const char* sKey, const char* sDefault = 0 ) const;

    virtual long
    GetParameterAsEnum( const char* sKey, const EnumDatumPtr pEnumList,
            long nEnumCount, long nDefault = 0, long nError = 0 ) const;

    virtual bool
    GetParameterAsBool( const char* sKey, bool bDefault = false ) const;

    virtual Yogi::Core::CColor
    GetParameterAsColor( const char*   sKey,
            Yogi::Core::ConstCColorRef cDefault
            = Yogi::Core::CColor::ErrorColor() ) const;

    virtual Yogi::Core::CDateTime
    GetParameterAsDateTime( const char*   sKey,
            Yogi::Core::ConstCDateTimeRef tDefault
            = Yogi::Core::CDateTime() ) const;

    // end of VPluginConfiguration

    void
    AddParameter( Yogi::Core::ConstCCharDescriptorRef rName,
            ConstCVariantDataRef                      rData );
    void
    AddAttribute( Yogi::Core::ConstCCharDescriptorRef rName,
            Yogi::Core::ConstCCharDescriptorRef       rData );
    bool
    AddFolder( Yogi::Core::ConstCCharDescriptorRef rName,
            CPluginConfigurationPtr                pFolder );

    void
    PruneFolder( CPluginConfigurationPtr pConfig );

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

    Yogi::Core::CCharString m_sClass;
    Yogi::Core::CCharString m_sGroup;
    Yogi::Core::CCharString m_sID;
    Yogi::Core::CCharString m_sTemp;  // working space for GetParameter

    THashTable<Yogi::Core::CCharString, Yogi::Core::CCharString> m_aAttributes;
    THashTable<Yogi::Core::CCharString, CVariantData>            m_aParameters;

    THashTable<Yogi::Core::CCharString, VPluginConfigurationPtr> m_aFolders;
    long                                                         m_nFolderCount;

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

}}  // namespace Yogi::Common


#endif /* _H_CPluginConfiguration */
