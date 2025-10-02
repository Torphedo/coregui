#pragma once
#include "layer.hxx"

struct layer_imgui : gui_layer {
    void init(GLFWwindow* window) override;
    void update(GLFWwindow* window) override;
    void render(GLFWwindow* window) override;
    void destroy() override;
};
