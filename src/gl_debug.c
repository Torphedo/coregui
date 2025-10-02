#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void APIENTRY gl_debug_msg(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
    char* source_str = "";
    char* type_str = "";
    char* severity_str = "";
    
    switch (source) {
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
        source_str = "shader compiler";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
        source_str = "windowing system";
        break;
    case GL_DEBUG_SOURCE_API_ARB:
        source_str = "API";
        break;
    case GL_DEBUG_SOURCE_APPLICATION_ARB:
        source_str = "application";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
        source_str = "third-party";
        break;
    case GL_DEBUG_SOURCE_OTHER_ARB:
        source_str = "[other source]";
        break;
    default:
        source_str = "[unknown source]";
        break;
    }
    
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        type_str = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type_str = "DEPRECATED";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type_str = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type_str = "UNDEFINED BEHAVIOUR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type_str = "PORTABILITY WARNING";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type_str = "OTHER";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        type_str = "PUSH GROUP";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        type_str = "POP GROUP";
        break;
    default:
        type_str = "other type";
        break;
    }
    
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH_ARB:
        severity_str = "CRITICAL";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM_ARB:
        severity_str = "WARNING";
        break;
    case GL_DEBUG_SEVERITY_LOW_ARB:
        severity_str = "LOW";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity_str = "NOTIFICATION";
        break;
    default:
        severity_str = "DEBUG";
        break;
    }
    printf("%s(): OpenGL %s message [%s] [%s] ", __func__, source_str, severity_str, type_str);
    printf("[id %d]: %s\n", id, message);
}

void gl_debug_setup() {
    if (!glfwExtensionSupported("GL_ARB_debug_output")) {
        printf("%s(): Missing GL_ARB_debug_output extension, debug messages won't work.\n", __func__);
        return;
    }
    else {
        printf("%s(): OpenGL debug messages enabled\n", __func__);
        int flags = 0;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            // Debug callbacks will be on the same thread
            // See this page for info on this flag:
            // https://www.khronos.org/opengl/wiki/Debug_Output#Getting_messages
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallbackARB(gl_debug_msg, NULL);

            // Don't filter out any messages
            glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        }
        else {
            printf("%s(): It looks like we're not in a debug context...\n", __func__);
            printf("%s(): Use a GLFW window hint to enable the debug context first.\n", __func__);
        }
    }
}

