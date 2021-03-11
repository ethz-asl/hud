#ifndef H_POINT_LAYER
#define H_POINT_LAYER
#include <hud/views/view.h>
#include <hud/geometry.h>
#include <eigen3/Eigen/Dense>

using namespace hud;
using namespace Eigen;

namespace hud::views {

const RowVector4d DefaultColor(1.0, 0.5, 0.5, 1.0);

class PointLayer : public hud::views::View {
protected:
  std::vector<Point> points;
  Matrix<double, Dynamic, 4, RowMajor> colors;
  bgfx::VertexBufferHandle vertex_buffer;
  bgfx::IndexBufferHandle index_buffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  std::array<float, 20> vertices;
  const float point_radius = 6.0;
public:
  PointLayer(const std::vector<Point> p);
  ~PointLayer();

  void setPoints(std::vector<Point> newPoints, const Matrix<double, Dynamic, 4>& colors = DefaultColor);
  void addPoint(const Point& point, const RowVector4d& color = DefaultColor);
  void setColors(const Matrix<double, Dynamic, 4, RowMajor>& colors);
  void pop();
  void clearPoints();
  int pointCount() const { return points.size(); };

  void resized(Rect newRect) override;
  void render() const override;
private:
  void updateVertexBuffer();
};
}
#endif
