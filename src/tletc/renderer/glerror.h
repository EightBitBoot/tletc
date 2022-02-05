#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>

#include <GL/glew.h>

///
/// Get the human readable name of an OpenGL error
///
/// @param errorCode the error to get the name of
///
/// @return the human readable name of errorCode
///
const char *getErrorCodeName(GLenum errorCode);

// #define NO_OPENGL_ERRORS

#ifndef NO_OPENGL_ERRORS
/// Call an OpenGL function and check if an error arose from it
#define GL_CALL(func) func; if((errorCode = glGetError()) != GL_NO_ERROR) {fprintf(stderr, "OpenGL Error in function %s: %s:0x%08X %s:%d\n", #func, getErrorCodeName(errorCode), errorCode, __FILE__, __LINE__);}
#else
#define GL_CALL(func) func
#endif

extern GLenum errorCode;

#endif
