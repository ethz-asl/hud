#include <functional>
#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include <hud/app_window.h>
#include <hud/views/hstack.h>
#include <hud/views/pane.h>
#include <hud/views/view.h>

using namespace hud;

class StereoLabel {
  private:
  AppWindow app;
  std::shared_ptr<views::ImagePane> left_pane, right_pane;
  public:
  StereoLabel() : app("StereoLabel", 1280, 600) {
    createViews();
  }

  void run() {
    while (app.update()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      glfwWaitEvents();
    }
  }

  protected:
  void createViews() {
    left_pane = std::make_shared<views::ImagePane>(0, "../assets/left.jpg");
    right_pane = std::make_shared<views::ImagePane>(1, "../assets/right.jpg");
    auto hstack = std::make_shared<views::HStack>(2, [&](views::LayoutContext &layout) {
      layout.add(left_pane);
      layout.add(right_pane);
    });

    left_pane->addClickHandler([&](const views::ClickEvent &click) {
        return true;
    });

    app.setView(hstack);
  }
};

int main(void) {
  if (!glfwInit()) {
    std::cout << "Could not initialized glfw" << std::endl;
    exit(1);
  }
  StereoLabel app;
  app.run();

  return 0;
}

