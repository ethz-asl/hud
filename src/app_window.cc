#include <stdio.h>
#include <iostream>
#include <chrono>
#include <bx/uint32_t.h>
#include <GLFW/glfw3.h>
#include <bgfx/platform.h>
#include <bgfx/bgfx.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include "app_window.h"

const int WindowWidth = 800;
const int WindowHeight = 600;

AppWindow::AppWindow(std::string title) : title(title) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(WindowWidth, WindowHeight, title.c_str(), nullptr, nullptr);
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

    bgfx::init(init);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
  }

AppWindow::~AppWindow() {
  bgfx::shutdown();
}

void AppWindow::addPane(std::shared_ptr<Pane> pane) {
  if (panes.size() == 0) {
    Rect rect = {0, 0, uint16_t(width), uint16_t(height)};
    panes.push_back(std::make_pair(rect, pane));
  } else {
    std::cout << "Only one pane is currently supported!" << std::endl;
  }
}

bool AppWindow::update() {
  glfwPollEvents();
  if (glfwWindowShouldClose(window)) return false;

  for (std::pair<Rect, std::shared_ptr<Pane>> pair : panes) {
    Rect rect = pair.first;
    std::shared_ptr<Pane> pane = pair.second;
    bgfx::setViewRect(0, rect.x, rect.y, rect.width, rect.height);
    pane->Render();
  }

  // Advance to next frame. Rendering thread will be kicked to
  // process submitted rendering primitives.
  bgfx::frame();

  return true;
}

