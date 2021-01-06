#include <hud/shader_utils.h>
#include <hud/views/line_layer.h>

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

LineLayer::LineLayer(int view_id) : View(view_id) {
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

LineLayer::~LineLayer() {
  bgfx::destroy(vertex_buffer);
  bgfx::destroy(index_buffer);
  bgfx::destroy(program);
}

void LineLayer::render() const {
  bgfx::setVertexBuffer(0, vertex_buffer);
  bgfx::setIndexBuffer(index_buffer);
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(view_id, program);
}

