/*---------------------------------------------------------------------+\
|
|	eglThunk.h  --  brief description of what eglThunk.h is for
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
#ifndef _H_eglThunk
#define _H_eglThunk
#pragma once
/*---------------------------------------------------------------------+\
|						
|	Include Files		
|						
\+---------------------------------------------------------------------*/

#	include <EGL/egl.h>
#	include <GLES/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------+\
|						
|	Defines				
|						
\+---------------------------------------------------------------------*/
#ifndef IMPORTGL_API
#define IMPORTGL_API extern
#endif
#ifndef IMPORTGL_FNPTRINIT
#define IMPORTGL_FNPTRINIT
#endif

#define FNDEF(retType, funcName, args) IMPORTGL_API retType (*funcPtr_##funcName) args IMPORTGL_FNPTRINIT




FNDEF(EGLBoolean, eglChooseConfig, (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config));
FNDEF(EGLContext, eglCreateContext, (EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list));
FNDEF(EGLSurface, eglCreateWindowSurface, (EGLDisplay dpy, EGLConfig config, NativeWindowType window, const EGLint *attrib_list));
FNDEF(EGLBoolean, eglDestroyContext, (EGLDisplay dpy, EGLContext ctx));
FNDEF(EGLBoolean, eglDestroySurface, (EGLDisplay dpy, EGLSurface surface));
FNDEF(EGLBoolean, eglGetConfigAttrib, (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value));
FNDEF(EGLBoolean, eglGetConfigs, (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config));
FNDEF(EGLDisplay, eglGetDisplay, (NativeDisplayType display));
FNDEF(EGLint, eglGetError, (void));
FNDEF(__eglMustCastToProperFunctionPointerType, eglGetProcAddress, (const char *procname));
FNDEF(EGLBoolean, eglInitialize, (EGLDisplay dpy, EGLint *major, EGLint *minor));
FNDEF(EGLBoolean, eglMakeCurrent, (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx));
FNDEF(EGLBoolean, eglSwapBuffers, (EGLDisplay dpy, EGLSurface draw));
FNDEF(EGLBoolean, eglTerminate, (EGLDisplay dpy));

FNDEF(void, glBindTexture, (GLenum target, GLuint texture));
FNDEF(void, glBlendFunc, (GLenum sfactor, GLenum dfactor));
FNDEF(void, glClear, (GLbitfield mask));
FNDEF(void, glClearColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
FNDEF(void, glColor4f, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha));
FNDEF(void, glColorPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glDeleteTextures, (GLsizei n, const GLuint *textures));
FNDEF(void, glDisable, (GLenum cap));
FNDEF(void, glDisableClientState, (GLenum array));
FNDEF(void, glDrawArrays, (GLenum mode, GLint first, GLsizei count));
FNDEF(void, glEnable, (GLenum cap));
FNDEF(void, glEnableClientState, (GLenum array));
FNDEF(void, glFrustumx, (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar));
FNDEF(void, glGenTextures, (GLsizei n, GLuint *textures));
FNDEF(GLenum, glGetError, (void));
FNDEF(void, glGetIntegerv, (GLenum pname, GLint *params));
FNDEF(void, glLightxv, (GLenum light, GLenum pname, const GLfixed *params));
FNDEF(void, glLineWidth, (GLfloat width));
FNDEF(void, glLoadIdentity, (void));
FNDEF(void, glMaterialx, (GLenum face, GLenum pname, GLfixed param));
FNDEF(void, glMaterialxv, (GLenum face, GLenum pname, const GLfixed *params));
FNDEF(void, glMatrixMode, (GLenum mode));
FNDEF(void, glMultMatrixx, (const GLfixed *m));
FNDEF(void, glNormalPointer, (GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glOrthof, (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar));
FNDEF(void, glPopMatrix, (void));
FNDEF(void, glPushMatrix, (void));
FNDEF(void, glReadPixels, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels));
FNDEF(void, glRotatex, (GLfixed angle, GLfixed x, GLfixed y, GLfixed z));
FNDEF(void, glScalex, (GLfixed x, GLfixed y, GLfixed z));
FNDEF(void, glScissor, (GLint x, GLint y, GLsizei width, GLsizei height));
FNDEF(void, glShadeModel, (GLenum mode));
FNDEF(const GLubyte *, glGetString, (GLenum name));
FNDEF(void, glTexCoordPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glTexImage2D, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels));
FNDEF(void, glTexParameteri, (GLenum target, GLenum pname, GLint param));
FNDEF(void, glTranslatex, (GLfixed x, GLfixed y, GLfixed z));
FNDEF(void, glVertexPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height));


#undef FN
#define FNPTR(name) funcPtr_##name

#ifndef IMPORTGL_NO_FNPTR_DEFS


	// Redirect egl* and gl* function calls to funcPtr_egl* and funcPtr_gl*.

#define eglChooseConfig         FNPTR(eglChooseConfig)
#define eglCreateContext        FNPTR(eglCreateContext)
#define eglCreateWindowSurface  FNPTR(eglCreateWindowSurface)
#define eglDestroyContext       FNPTR(eglDestroyContext)
#define eglDestroySurface       FNPTR(eglDestroySurface)
#define eglGetConfigAttrib      FNPTR(eglGetConfigAttrib)
#define eglGetConfigs           FNPTR(eglGetConfigs)
#define eglGetDisplay           FNPTR(eglGetDisplay)
#define eglGetError             FNPTR(eglGetError)
#define eglGetProcAddress		FNPTR(eglGetProcAddress)
#define eglInitialize           FNPTR(eglInitialize)
#define eglMakeCurrent          FNPTR(eglMakeCurrent)
#define eglSwapBuffers          FNPTR(eglSwapBuffers)
#define eglTerminate            FNPTR(eglTerminate)

#define glBindTexture			FNPTR(glBindTexture)
#define glBlendFunc             FNPTR(glBlendFunc)
#define glClear                 FNPTR(glClear)
#define glClearColor            FNPTR(glClearColor)
#define glColor4f               FNPTR(glColor4f)
#define glColorPointer          FNPTR(glColorPointer)
#define glDeleteTextures		FNPTR(glDeleteTextures)
#define glDisable               FNPTR(glDisable)
#define glDisableClientState    FNPTR(glDisableClientState)
#define glDrawArrays            FNPTR(glDrawArrays)
#define glEnable                FNPTR(glEnable)
#define glEnableClientState     FNPTR(glEnableClientState)
#define glFrustumx              FNPTR(glFrustumx)
#define glGenTextures			FNPTR(glGenTextures)
#define glGetError              FNPTR(glGetError)
#define glGetIntegerv			FNPTR(glGetIntegerv)
#define glGetString				FNPTR(glGetString)
#define glLightxv               FNPTR(glLightxv)
#define glLineWidth				FNPTR(glLineWidth)
#define glLoadIdentity          FNPTR(glLoadIdentity)
#define glMaterialx             FNPTR(glMaterialx)
#define glMaterialxv            FNPTR(glMaterialxv)
#define glMatrixMode            FNPTR(glMatrixMode)
#define glMultMatrixx           FNPTR(glMultMatrixx)
#define glNormalPointer         FNPTR(glNormalPointer)
#define glOrthof				FNPTR(glOrthof)
#define glPopMatrix             FNPTR(glPopMatrix)
#define glPushMatrix            FNPTR(glPushMatrix)
#define glReadPixels			FNPTR(glReadPixels)
#define glRotatex               FNPTR(glRotatex)
#define glScalex                FNPTR(glScalex)
#define glScissor				FNPTR(glScissor)
#define glShadeModel            FNPTR(glShadeModel)
#define glTexCoordPointer		FNPTR(glTexCoordPointer)
#define glTexImage2D			FNPTR(glTexImage2D)
#define glTexParameteri			FNPTR(glTexParameteri)
#define glTranslatex            FNPTR(glTranslatex)
#define glVertexPointer         FNPTR(glVertexPointer)
#define glViewport              FNPTR(glViewport)

#endif


/*---------------------------------------------------------------------+\
|						
|	Type Definitions	
|						
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\
|						
|	External Variables	
|						
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||						
||	Function Prototypes	
||						
\+=====================================================================*/

extern void eglThunk( void );

/*=====================================================================+\
||						
||	Inline Functions	
||						
\+=====================================================================*/


#ifdef __cplusplus
};
#endif


#endif /* _H_eglThunk */

