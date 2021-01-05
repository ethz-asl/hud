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

using namespace hud::views;

namespace hud {
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
  glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int new_width, int new_height) {
    AppWindow* app = (AppWindow*)glfwGetWindowUserPointer(window);
    app->resized(new_width, new_height);
  });

  glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
      AppWindow* app = (AppWindow*)glfwGetWindowUserPointer(window);
      app->leftClick();
    }
  });

  bgfx::init(init);
}

AppWindow::~AppWindow() {
  view.reset();
  bgfx::shutdown();
}

void AppWindow::setView(std::shared_ptr<View> newView) {
  view = newView;
  Rect rect = { 0, 0, width, height };
  view->resized(rect);
}

void AppWindow::leftClick() {
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  ClickEvent event { x, y };
  std::cout << "User clicked x: " << event.x << " y: " << event.y << std::endl;
}

// Window handlers.
void AppWindow::resized(int new_width, int new_height) {
  width = new_width;
  height = new_height;
  bgfx::reset(width, height);
  Rect rect = {0, 0, width, height};
  view->resized(rect);
}

// Rendering.
bool AppWindow::update() {
  if (glfwWindowShouldClose(window)) return false;

  auto rect = view->getRect();
  bgfx::setViewRect(view->view_id, rect.x, rect.y, rect.width, rect.height);
  view->render();

  bgfx::frame();

  return true;
}
}

