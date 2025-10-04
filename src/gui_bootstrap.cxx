#include <glad/glad.h>
#include "gui_bootstrap.hxx"
#include <cstdio>
#include <chrono>
#include <thread>

#include "gl_debug.h"

void glfw_error(int err_code, const char* msg) {
    printf("%s(): [code %d] %s\n", __func__, err_code, msg);
}

// TODO: Give layers a resize callback
void frame_resize_callback(GLFWwindow* window, int width, int height) {
    int framebuf_width = 0;
    int framebuf_height = 0;
    glfwGetFramebufferSize(window, &framebuf_width, &framebuf_height);
    glViewport(0, 0, framebuf_width, framebuf_height);
}

bool gui_app::run(const char* window_title) noexcept {
    glfwSetErrorCallback(glfw_error);

    // Setup GLFW
    if (!glfwInit()) {
        printf("gui_app::%s(): GLFW init failure!\n", __func__);
        return false;
    }

    // Use OpenGL Core 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Request a debug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4-sample MSAA
    
    const int width = 1280;
    const int height = 720;
    GLFWwindow* window = glfwCreateWindow(width, height, window_title, nullptr, nullptr);
    if (!window) {
        printf("gui_app::%s(): failed to create GLFW window of size %dx%d.\n", __func__, width, height);
        glfwTerminate();
        return false;
    }

    // Create the OpenGL context
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("gui_app::%s(): failed to initialize GLAD for OpenGL Core 3.3\n", __func__);
        glfwTerminate();
        return false;
    }
    
    gl_debug_setup();
    // Example code that will trigger a critical debug message:
    // glBindBuffer(GL_VERTEX_ARRAY_BINDING, 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); // Enable MSAA
    glEnable(GL_CULL_FACE); // Backface culling via winding order

    // Enable transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);


    // Set OpenGL viewport to size of window, handle resizing
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, frame_resize_callback);
    glfwSwapInterval(1); // VSync

    if (window == nullptr) {
        printf("Failed to setup GLFW\n");
        return false;
    }

    for (auto& layer : this->layers) {
        layer->init(window);
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            // Skip rendering if minimized
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        for (auto& layer : this->layers) {
            if (layer->active) {
                layer->update(window);
            }
        }

        // Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto& layer : this->layers) {
            if (layer->active) {
                layer->render(window);
            }
        }


        glfwSwapBuffers(window);
    }

    // Cleanup
    for (auto& layer : this->layers) {
        layer->destroy();
    }

    glfwTerminate();

    return true;
}
