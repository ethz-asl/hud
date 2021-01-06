#ifndef H_LINE_LAYER
#define H_LINE_LAYER
#include <hud/views/view.h>

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
  LineLayer(int view_id);

  ~LineLayer();

  void render() const override;
};

#endif

