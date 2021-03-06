/*---------------------------------------------------------------------+\
|
|	VConfiguration.h  --  Access configuration file
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
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Copy CConfiguration and make it a pure virtual class
	27-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VConfiguration
#define _H_VConfiguration
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharString.h"
#include "CVariables.h"
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
typedef class VConfiguration*       VConfigurationPtr;
typedef class VConfiguration&       VConfigurationRef;
typedef const class VConfiguration& ConstVConfigurationRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class COMMON_CLASS VConfiguration : public VVariable
{
    //	class lifecycle  ----------------------------------------------------
public:
    virtual ~VConfiguration() {};

public:
    //	public types  -------------------------------------------------------

    typedef struct EnumDatum
    {
        long        nValue;
        const char* sKey;
    } EnumDatum;
    typedef EnumDatum* EnumDatumPtr;
    typedef EnumDatum* EnumData;

    //	public functions  ---------------------------------------------------

    virtual bool
    AddEntry( const char* sKey, ConstCVariantDataRef rData )
            = 0;

    virtual CVariantDataPtr
    GetEntry( const char* sKey ) const = 0;

    virtual CVariantDataPtr
    GetEntry( Yogi::Core::ConstCCharStringRef sKey ) const = 0;

    virtual long
    GetEntryAsInteger( const char* sKey, long nDefault = 0 ) const = 0;

    virtual unsigned long
    GetEntryAsUnsigned(
            const char* sKey, unsigned long nDefault = 0 ) const = 0;

    virtual GFLOAT
    GetEntryAsFloat( const char* sKey, GFLOAT fDefault = 0.0f ) const = 0;

    virtual GFLOAT
    GetEntryAsFloatUnits( const char* sKey, const char* sUnitName,
            GFLOAT fDefault = 0.0f ) const = 0;

    virtual Yogi::Core::CCharString
    GetEntryAsString( const char* sKey, const char* sDefault = 0 ) const = 0;

    virtual long
    GetEntryAsEnum( const char* sKey, const EnumDatumPtr pEnumList,
            const long nEnumCount, const long nDefault = 0,
            const long nError = 0 ) const = 0;


    virtual bool
    GetEntryAsBool( const char* sKey, const bool bDefault = false ) const = 0;

    virtual Yogi::Core::CColor
    GetEntryAsColor( const char*     sKey,
            const Yogi::Core::CColor cDefault
            = Yogi::Core::CColor() ) const = 0;

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

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


#endif /* _H_VConfiguration */
