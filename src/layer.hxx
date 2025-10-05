#pragma once
#include <GLFW/glfw3.h>

struct gui_layer {
    bool active = true;

    /// Callback to run before the main loop
    virtual void init(GLFWwindow* window) {}

    /// Per-frame state update callback
    virtual void update(GLFWwindow* window) {}

    /// Per-frame rendering callback
    virtual void render(GLFWwindow* window) {}

    /// Callback to run after the main loop
    virtual void destroy() {}
};

/// @brief A layer that can contain a bunch of other layers
struct meta_layer : gui_layer {
    std::vector<std::unique_ptr<gui_layer>> layers;

    void init(GLFWwindow* window) override {
        for (const auto& layer : layers) {
            layer->init(window);
        }
    }

    void update(GLFWwindow* window) override {
        for (const auto& layer : layers) {
            layer->update(window);
        }
    }

    void render(GLFWwindow* window) override {
        for (const auto& layer : layers) {
            layer->render(window);
        }
    }

    void destroy() override {
        for (const auto& layer : layers) {
            layer->destroy();
        }
    }
};
