/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|   110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|        																|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|	Delete this comment block
|
|	globally substitute "filename" to be the name of this file (no suffix).
|	globally substitute "dd-mmm-9999" to be today's date.
|	globally substitute "F.Lastname" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "DerivedClass" to be the name of this class.
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	filename.cpp  --  brief description of what filename.cpp is for
|
|	Purpose:
|	File Custodian:		F.Lastname
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "DerivedClass.h"
#include "VPluginFactory.h"

#include "NamespaceVideoSource.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_VIDEOSOURCE_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( DerivedClass );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - constructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		)
		: VCameraControlBase()
{
}


/**--------------------------------------------------------------------+\

 * <summary>~DerivedClass - destructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		ISupportsPtr	pOwner
		)
		: VCameraControlBase(pOwner)
{
}


/**--------------------------------------------------------------------+\

 * <summary>~DerivedClass - destructor</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
DerivedClass::~DerivedClass()
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/**--------------------------------------------------------------------+\

 * <summary>Load - XML data loader override</summary>

 * <remarks/>

 * (author)F.Lastname  --  15-Jun-2010

\+---------------------------------------------------------------------*/
//bool	DerivedClass::Load
//		(
//		VPluginConfigurationPtr pConfig,
//		VPluginLibraryPtr pLib
//		)
//{
//	bool	bResult = true;
//
//	bResult = VCameraControlBase::Load( pConfig, pLib );
//	if ( bResult )
//	{
//		// Add code to load member data from XML
//		//
//		m_memberData = pConfig->GetParameterAsInteger("Member Data Key", -1);
//	}
//
//    return bResult;
//}


/**--------------------------------------------------------------------+\

 * <summary>DoBrightness - Change camera brightness</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult	DerivedClass::DoBrightness
		(
		int		requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasBrightness() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera brightness code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoContrast - Change camera contrast</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult	DerivedClass::DoContrast
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasContrast() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera contrast code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoSharpness - Change camera sharpness</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoSharpness
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasSharpness() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera sharpness code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoZoomMode - Change camera zoom mode</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoZoomMode
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasZoomMode() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera zoom mode code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoZoom - Change camera zoom</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoZoom
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasZoom() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera zoom mode code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoAutoCalibration - Change camera auto calibration (enable/disable)</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoAutoCalibration
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasAutoCalibration() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera auto-calibration enable/disable code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoOnePointCalibration - Execute camera one-point calibration</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoOnePointCalibration
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasOnePointCalibration() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera one point calibration code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoPolarity - Change camera polarity</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoPolarity
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasPolarity() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera polarity code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoShutter - Change camera shutter</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoShutter
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasShutter() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera shutter code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoLAPMode - Change camera LAP mode</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult DerivedClass::DoLAPMode
		(
		int requestID,
		ConstCVariantDataRef vData
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasLAPMode() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera LAP mode code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}


/**--------------------------------------------------------------------+\

 * <summary>DoShutdown - Execute camera shutdown</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/
NResult	DerivedClass::DoShutdown
		(
		int requestID
		)
{
	NResult nr = CAMERA_OP_FAIL;

	if (HasShutdown() != ICameraControl::UNSUPPORTED)
	{
		// Insert camera shutdown code here

		nr = CAMERA_OP_SUCCESS;
	}

    return nr;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/



/*=====================================================================+\
||																		|
||	 Overrides														|
||																		|
\+=====================================================================*/


NAMESPACE_VIDEOSOURCE_END


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)F.Lastname  --  dd-mmm-9999

\+---------------------------------------------------------------------*/

