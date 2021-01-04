#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include "app_window.h"
#include "views/hstack.h"
#include "views/pane.h"

int main(void) {
  if (!glfwInit()) {
    std::cout << "Could not initialized glfw" << std::endl;
    exit(1);
  }
  AppWindow app("Hello", 1280, 600);

  auto leftPane = std::make_shared<views::ImagePane>(0, "../assets/left.jpg");
  auto rightPane = std::make_shared<views::ImagePane>(1, "../assets/right.jpg");
  auto hstack = std::make_shared<views::HStack>(2, [&](views::Layout &layout) {
    layout.views.push_back(leftPane);
    layout.views.push_back(rightPane);
  });
  app.setView(hstack);

  while (app.update()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    glfwWaitEvents();
  }

  return 0;
}
