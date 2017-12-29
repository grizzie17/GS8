


#include "UPlatform.h"

#define IMPORTGL_NO_FNPTR_DEFS
#define IMPORTGL_FNPTRINIT = NULL
#include "eglThunk.h"

#include "UFile.h"
#include "CCharString.h"
#include "LogFile.h"

USING_NAMESPACE_COMMON


#define IMPORT_FUNC( funcName )		IMPORT_FUNCX( m_hGlesDLL, funcName )
#define IMPORT_FUNC_E( funcName )	IMPORT_FUNCX( m_hEglDLL, funcName )

#define IMPORT_FUNCX(hdl, funcName)		\
	do	\
	{	\
		void *procAddress = (void *)DLLGetProcedure(hdl, #funcName); \
		*((void **)&FNPTR(funcName)) = procAddress;		\
	} sequence




void	eglThunk()
{
	ULibraryHdl	m_hGlesDLL;
	ULibraryHdl	m_hEglDLL;

	CCharString	sAppFolder = GetApplicationFolder();
	char		sPath[512];

	PathBuild( sPath, sizeof(sPath), sAppFolder.Pointer(), "libGLESv1_CM.dll" );
	m_hGlesDLL = DLLOpen( sPath );
	if ( ! m_hGlesDLL )
	{
		char*	s = DLLErrorString();
		LogPrint( "Problem loading libGLESv1_CM.dll - %s\n", s );
	}

	PathBuild( sPath, sizeof(sPath), sAppFolder.Pointer(), "libEGL.dll" );
	m_hEglDLL = DLLOpen( sPath );
	if ( ! m_hEglDLL )
	{
		char*	s = DLLErrorString();
		LogPrint( "Problem loading libEGL.dll - %s\n", s );
	}

	IMPORT_FUNC_E(eglChooseConfig);
	IMPORT_FUNC_E(eglCreateContext);
	IMPORT_FUNC_E(eglCreateWindowSurface);
	IMPORT_FUNC_E(eglDestroyContext);
	IMPORT_FUNC_E(eglDestroySurface);
	IMPORT_FUNC_E(eglGetConfigAttrib);
	IMPORT_FUNC_E(eglGetConfigs);
	IMPORT_FUNC_E(eglGetDisplay);
	IMPORT_FUNC_E(eglGetError);
	IMPORT_FUNC_E(eglGetProcAddress);
	IMPORT_FUNC_E(eglInitialize);
	IMPORT_FUNC_E(eglMakeCurrent);
	IMPORT_FUNC_E(eglSwapBuffers);
	IMPORT_FUNC_E(eglTerminate);

	IMPORT_FUNC(glBindTexture);
	IMPORT_FUNC(glBlendFunc);
	IMPORT_FUNC(glClear);
	IMPORT_FUNC(glClearColor);
	IMPORT_FUNC(glColor4f);
	IMPORT_FUNC(glColorPointer);
	IMPORT_FUNC(glDeleteTextures);
	IMPORT_FUNC(glDisable);
	IMPORT_FUNC(glDisableClientState);
	IMPORT_FUNC(glDrawArrays);
	IMPORT_FUNC(glEnable);
	IMPORT_FUNC(glEnableClientState);
	IMPORT_FUNC(glFrustumx);
	IMPORT_FUNC(glGenTextures);
	IMPORT_FUNC(glGetError);
	IMPORT_FUNC(glGetIntegerv);
	IMPORT_FUNC(glGetString);
	IMPORT_FUNC(glLightxv);
	IMPORT_FUNC(glLineWidth);
	IMPORT_FUNC(glLoadIdentity);
	IMPORT_FUNC(glMaterialx);
	IMPORT_FUNC(glMaterialxv);
	IMPORT_FUNC(glMatrixMode);
	IMPORT_FUNC(glMultMatrixx);
	IMPORT_FUNC(glNormalPointer);
	IMPORT_FUNC(glOrthof);
	IMPORT_FUNC(glPopMatrix);
	IMPORT_FUNC(glPushMatrix);
	IMPORT_FUNC(glReadPixels);
	IMPORT_FUNC(glRotatex);
	IMPORT_FUNC(glScalex);
	IMPORT_FUNC(glScissor);
	IMPORT_FUNC(glShadeModel);
	IMPORT_FUNC(glTexCoordPointer);
	IMPORT_FUNC(glTexImage2D);
	IMPORT_FUNC(glTexParameteri);
	IMPORT_FUNC(glTranslatex);
	IMPORT_FUNC(glVertexPointer);
	IMPORT_FUNC(glViewport);

}





