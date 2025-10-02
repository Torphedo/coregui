#pragma once
#include <vector>
#include <memory>

#include <GLFW/glfw3.h>
#include "layer.hxx"

struct gui_app {
    GLFWwindow* window = nullptr;
    std::vector<std::unique_ptr<gui_layer>> layers;

    bool run(const char* window_title) noexcept;
};
