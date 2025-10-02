#pragma once
#include <GLFW/glfw3.h>

struct gui_layer {
    /// Callback to run before the main loop
    virtual void init() {}

    /// Per-frame state update callback
    virtual void update(GLFWwindow* window) {}

    /// Per-frame rendering callback
    virtual void render(GLFWwindow* window) {}

    /// Callback to run after the main loop
    virtual void destroy() {}
};
