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

using namespace hud;

std::array<float, 8> createVertices(const Point& start, const Point& end, float line_width) {
  float w = line_width / 2.0;
  return {
    float(start.x), float(start.y) - w,
    float(start.x), float(start.y) + w,
    float(end.x), float(end.y) - w,
    float(end.x), float(end.y) + w
  };
}

static const uint16_t faces[] = {
  0, 2, 3, 0, 3, 1
};

class LineLayer : public hud::views::View {
protected:
  bgfx::VertexBufferHandle vertex_buffer;
  bgfx::IndexBufferHandle index_buffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  std::array<float, 8> vertices;
  Point start_point, end_point;
  float line_width = 0.02;
public:
  LineLayer(int view_id) : View(view_id) {
    start_point = Point(-1.0, 0.0);
    end_point = Point(1.0, 0.0);

    layout.begin()
      .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
      .end();

    vertices = createVertices(start_point, end_point, line_width);
    auto ref = bgfx::makeRef(vertices.data(), sizeof(float) * 8);
    vertex_buffer = bgfx::createVertexBuffer(ref, layout);
    index_buffer = bgfx::createIndexBuffer(bgfx::makeRef(faces, sizeof(faces)));
    program = shader_utils::loadProgram("vs_line_layer", "fs_line_layer");
  }

  ~LineLayer() {
    bgfx::destroy(vertex_buffer);
    bgfx::destroy(index_buffer);
    bgfx::destroy(program);
  }

  void render() const override {
    bgfx::setVertexBuffer(0, vertex_buffer);
    bgfx::setIndexBuffer(index_buffer);
    bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::submit(view_id, program);
  }
};

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
      glfwWaitEvents();
    }
  }

  protected:
  void createViews() {
    left_image_pane = std::make_shared<views::ImagePane>(0, "../assets/left.jpg");
    auto right_image_pane = std::make_shared<views::ImagePane>(1, "../assets/right.jpg");
    std::vector<Point> points = { Point(-0.8, 0.0) };

    auto left_point_layer = std::make_shared<views::PointLayer>(4, points);
    left_pane = std::make_shared<views::ZStack>(3, [=, this](views::LayoutContext &layout) {
        layout.add(left_image_pane);
        layout.add(left_point_layer);
    });

    auto line_layer = std::make_shared<LineLayer>(5);
    right_pane = std::make_shared<views::ZStack>(3, [=, this](views::LayoutContext &layout) {
        layout.add(right_image_pane);
        layout.add(line_layer);
    });

    auto hstack = std::make_shared<views::HStack>(2, [=, this](views::LayoutContext &layout) {
      layout.add(left_pane);
      layout.add(right_pane);
    });

    left_image_pane->addClickHandler([=, this](const views::ClickEvent &click) {
        auto rect = left_image_pane->getRect();
        auto point = hud::utils::toNormalizedDeviceCoordinates(click.p, left_image_pane->getRect());
        std::cout << "left pane clicked! " << point << std::endl;
        left_point_layer->addPoint(point);
        return true;
    });
    right_pane->addClickHandler([=, this](const views::ClickEvent &click) {
        std::cout << "right pane clicked! x: " << click.p.x << " y: " << click.p.y << std::endl;
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

