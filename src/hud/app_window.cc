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
#include <hud/utils.h>

using namespace hud::views;

namespace hud {
AppWindow::AppWindow(std::string title, const int w, const int h) : title(title) {
  if (!glfwInit()) {
    std::cout << "Could not initialized glfw" << std::endl;
    exit(1);
  }
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

  glfwSetKeyCallback(window, [](GLFWwindow *window, int codepoint, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
      char character = codepoint;
      char key = '\0';
      if (isprint(character)) {
        key = character;
      }
      KeyEvent event{ key, mods };
      AppWindow* app = (AppWindow*)glfwGetWindowUserPointer(window);
      app->keydown(event);
    }
  });

  bgfx::init(init);
}

AppWindow::~AppWindow() {
  view.reset();
}

void AppWindow::setView(std::shared_ptr<View> newView) {
  view = newView;
  Rect rect = { 0, 0, double(width), double(height) };
  view->resized(rect);
}

void AppWindow::leftClick() {
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  const ClickEvent event = { Point(x, y) };
  view->leftClick(event);
}

void AppWindow::keydown(const KeyEvent& event) {
  std::for_each(key_handlers.begin(), key_handlers.end(), [&](KeyHandler& handler) {
      handler(event);
  });
}

// Window handlers.
void AppWindow::resized(int new_width, int new_height) {
  width = new_width;
  height = new_height;
  bgfx::reset(width, height);
  Rect rect = { 0, 0, double(width), double(height) };
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

