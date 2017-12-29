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
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
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
|	filename.h  --  brief description of what filename.h is for
|
|	Purpose:
|	File Custodian:		F.Lastname
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_filename
#define _H_filename
#pragma once

/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VCameraControlBase.h"

#include "NamespaceVideoSource.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_VIDEOSOURCE_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class DerivedClass*			DerivedClassPtr;
typedef class DerivedClass&			DerivedClassRef;
typedef const class DerivedClass&	ConstDerivedClassRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DerivedClass : public VCameraControlBase
{
//	class lifecycle  ----------------------------------------------------
	COM_LIFECYCLE( DerivedClass );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

    // Uncomment supported capabilities and change the capability type as
	// appropriate.
	//
//	virtual ICameraControl::CameraCapabilities HasBrightness() { return ICameraControl::CONTROL; }
//	virtual ICameraControl::CameraCapabilities HasContrast() { return ICameraControl::CONTROL; }
//	virtual ICameraControl::CameraCapabilities HasSharpness() { return ICameraControl::CONTROL; }
//	virtual ICameraControl::CameraCapabilities HasZoomMode() { return ICameraControl::TOGGLE_ONLY; }
//	virtual ICameraControl::CameraCapabilities HasZoom() { return ICameraControl::CONTROL; }
//	virtual ICameraControl::CameraCapabilities HasAutoCalibration() { return ICameraControl::TOGGLE_ONLY; }
//	virtual ICameraControl::CameraCapabilities HasOnePointCalibration() { return ICameraControl::TOGGLE_ONLY; }
//	virtual ICameraControl::CameraCapabilities HasPolarity() { return ICameraControl::TOGGLE_ONLY; }
//	virtual ICameraControl::CameraCapabilities HasShutter() { return ICameraControl::CONTROL; }
//	virtual ICameraControl::CameraCapabilities HasLAPMode() { return ICameraControl::TOGGLE_ONLY; }
//	virtual ICameraControl::CameraCapabilities HasShutdown() { return ICameraControl::TOGGLE_ONLY; }

	virtual NResult	DoBrightness( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoContrast( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoSharpness( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoZoomMode( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoZoom( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoAutoCalibration( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoOnePointCalibration( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoPolarity( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoShutter( int requestID, ConstCVariantDataRef vData );
	virtual NResult DoLAPMode( int requestID, ConstCVariantDataRef vData );
	virtual NResult	DoShutdown( int requestID );

	// Override Load() when private data is added that needs to be loaded from
	// XML file.
	//
//	virtual bool Load( VPluginConfigurationPtr pConfig, VPluginLibraryPtr pLib );

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
	//	VCameraControlBase-1
	//	VCameraControlBase

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

NAMESPACE_VIDEOSOURCE_END



#endif /* _H_DerivedClass */


