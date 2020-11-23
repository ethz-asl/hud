#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include "app_window.h"
#include "pane.h"

int main(void) {
  if (!glfwInit()) {
    std::cout << "Could not initialized glfw" << std::endl;
    exit(1);
  }
  AppWindow app("Hello");


  auto image_pane = std::make_shared<ImagePane>("../left.jpg");
  app.addPane(image_pane);

  while (app.update()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
