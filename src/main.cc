#include <functional>
#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include <hud/app_window.h>
#include <hud/views/hstack.h>
#include <hud/views/zstack.h>
#include <hud/views/pane.h>
#include <hud/views/view.h>
#include <hud/views/point_layer.h>
#include <hud/views/line_layer.h>

using namespace hud;

class StereoLabel {
  private:
  AppWindow app;
  std::shared_ptr<views::View> left_pane, right_pane;
  std::shared_ptr<views::ImagePane> left_image_pane;
  public:
  StereoLabel() : app("StereoLabel", 1280, 600) {
    createViews();
  }

  void run() {
    while (app.update()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      app.waitEvents();
    }
  }

  protected:
  void createViews() {
    left_image_pane = std::make_shared<views::ImagePane>(0, "../assets/left.jpg");
    auto right_image_pane = std::make_shared<views::ImagePane>(1, "../assets/right.jpg");
    std::vector<Point> points = { Point(-0.8, 0.0) };

    auto left_point_layer = std::make_shared<views::PointLayer>(4, points);
    left_pane = std::make_shared<views::ZStack>(3, [=](views::LayoutContext *layout) {
        layout->add(left_image_pane);
        layout->add(left_point_layer);
    });

    auto line_layer = std::make_shared<LineLayer>(5);
    right_pane = std::make_shared<views::ZStack>(3, [=](views::LayoutContext *layout) {
        layout->add(right_image_pane);
        layout->add(line_layer);
    });

    auto hstack = std::make_shared<views::HStack>(2, [=](views::LayoutContext *layout) {
      layout->add(left_pane);
      layout->add(right_pane);
    });

    left_image_pane->addClickHandler([=](const views::ClickEvent &click) {
        auto rect = left_image_pane->getRect();
        auto point = hud::utils::toNormalizedDeviceCoordinates(click.p, left_image_pane->getRect());
        std::cout << "left pane clicked! " << point << std::endl;
        left_point_layer->addPoint(point);
        return true;
    });
    right_pane->addClickHandler([&](const views::ClickEvent &click) {
        std::cout << "right pane clicked! x: " << click.p.x << " y: " << click.p.y << std::endl;
        return true;
    });

    app.setView(hstack);
  }
};

int main(void) {
  {
    StereoLabel app;
    app.run();
  }

  utils::shutdown();

  return 0;
}

