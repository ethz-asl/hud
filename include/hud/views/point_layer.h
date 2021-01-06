#ifndef H_POINT_LAYER
#define H_POINT_LAYER
#include <hud/views/view.h>
#include <hud/geometry.h>

using namespace hud;

namespace hud::views {

void createQuad(const Point& point, float width, float height, std::array<float, 20>& out);

class PointLayer : public hud::views::View {
protected:
  std::vector<Point> points;
  bgfx::DynamicVertexBufferHandle vertex_buffer;
  bgfx::IndexBufferHandle index_buffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  std::array<float, 20> point_quad;
  const float point_radius = 12.0;
public:
  PointLayer(int id, const std::vector<Point> p);
  ~PointLayer();

  void setPoints(std::vector<Point> newPoints);

  void resized(Rect newRect) override;
  void render() const;
private:
  void updateVertexBuffer();
};
}
#endif
