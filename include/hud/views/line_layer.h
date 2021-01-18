#ifndef H_LINE_LAYER
#define H_LINE_LAYER
#include "bgfx/bgfx.h"
#include <hud/views/view.h>

class LineLayer : public hud::views::View {
protected:
  bgfx::DynamicVertexBufferHandle vertex_buffer;
  bgfx::IndexBufferHandle index_buffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  std::array<float, 8> vertices;
  Point start_point = Point(0.0, 0.0), end_point = Point(1.0, 0.0);
  float line_width = 0.02;
  bool line_set = false;
public:
  LineLayer();
  ~LineLayer();
  void setLine(const Point& start, const Point& end);

  void render() const override;

private:
  void updateVertices();
};

#endif

