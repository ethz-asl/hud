#include <stdio.h>
#include <iostream>
#include <chrono>
#include <bx/uint32_t.h>
#include <GLFW/glfw3.h>
#include <bgfx/platform.h>
#include <bgfx/bgfx.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include <hud/app_window.h>

using namespace views;

AppWindow::AppWindow(std::string title, const int w, const int h) : title(title) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!window) {
      std::cout << "Window could not be created!" << std::endl;
      exit(1);
    }
    bgfx::Init init;
    init.platformData.ndt = glfwGetX11Display();
    init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);

    glfwGetWindowSize(window, &width, &height);
    init.resolution.width = (uint32_t)width;
    init.resolution.height = (uint32_t)height;
    init.resolution.reset = BGFX_RESET_VSYNC;

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int newWidth, int newHeight) {
      AppWindow* app = (AppWindow*)glfwGetWindowUserPointer(window);
      app->resized(newWidth, newHeight);
    });

    bgfx::init(init);
  }

AppWindow::~AppWindow() {
  view.reset();
  bgfx::shutdown();
}

void AppWindow::setView(std::shared_ptr<View> newView) { view = newView; }

void AppWindow::resized(int newWidth, int newHeight) {
  width = newWidth; height = newHeight;
  bgfx::reset(width, height);
}

bool AppWindow::update() {
  if (glfwWindowShouldClose(window)) return false;

  ViewRect rect = {0, 0, width, height};
  view->render(rect);

  bgfx::frame();

  return true;
}

