
#include "glerror.h"

const char *getErrorCodeName(GLenum errorCode) {
    switch(errorCode) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";

        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";

        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";

        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";

        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";

        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";

        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";

        case GL_CONTEXT_LOST:
            return "GL_CONTEXT_LOST";

        case GL_TABLE_TOO_LARGE:
            // Yes I know it was removed
            // No I don't care
            return "GL_TABLE_TOO_LARGE";

        default:
            return "UNKNOWN_ERROR_CODE";
    }

    return "ERROR_IN_GET_ERROR_CODE_NAME";
}

/// Variable to store the current OpenGL error in
/// when checking the last OpenGL call's status
GLenum errorCode;