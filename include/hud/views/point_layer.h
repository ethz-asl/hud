#ifndef H_POINT_LAYER
#define H_POINT_LAYER
#include <hud/views/view.h>
#include <hud/geometry.h>

using namespace hud;

namespace hud::views {

class PointLayer : public hud::views::View {
protected:
  std::vector<Point> points;
  bgfx::VertexBufferHandle vertex_buffer;
  bgfx::IndexBufferHandle index_buffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  std::array<float, 20> vertices;
  const float point_radius = 6.0;
public:
  PointLayer(const std::vector<Point> p);
  ~PointLayer();

  void setPoints(std::vector<Point> newPoints);
  void addPoint(const Point& point);

  void resized(Rect newRect) override;
  void render() const override;
private:
  void updateVertexBuffer();
};
}
#endif
