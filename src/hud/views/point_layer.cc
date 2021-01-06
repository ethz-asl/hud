#include <hud/views/point_layer.h>
#include <hud/shader_utils.h>

namespace hud::views {
static const uint16_t faces[] = {
  0, 1, 2, 0, 2, 3
};

void createQuad(const Point& point, float width, float height, std::array<float, 20>& out) {
  float left = point.x - width;
  float right = point.x + width;
  float top = point.y + height;
  float bottom = point.y - height;
  out = {
    right, bottom, -0.01, 1.0, -1.0,
    right, top, -0.01, 1.0, 1.0,
    left, top, -0.01, -1.0, 1.0,
    left, bottom, -0.01, -1.0, -1.0
  };
}

PointLayer::PointLayer(int id, const std::vector<Point> p) : hud::views::View(id), points(p) {
  layout
    .begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
    .end();

  auto quad_ref = bgfx::makeRef(point_quad.data(), sizeof(float) * 20);
  vertex_buffer = bgfx::createDynamicVertexBuffer(quad_ref, layout);
  index_buffer = bgfx::createIndexBuffer(bgfx::makeRef(faces, sizeof(faces)));
  program = shader_utils::loadProgram("vs_point_layer", "fs_point_layer");
}

PointLayer::~PointLayer() {
  bgfx::destroy(vertex_buffer);
  bgfx::destroy(index_buffer);
  bgfx::destroy(program);
}

void PointLayer::setPoints(std::vector<Point> newPoints) {
  points = newPoints;
  if (rect.width == 0.0 || rect.height == 0.0) return;

  updateVertexBuffer();
}

void PointLayer::resized(Rect newRect) {
  views::View::resized(newRect);
  updateVertexBuffer();
}

void PointLayer::render() const {
  bgfx::setVertexBuffer(0, vertex_buffer);
  bgfx::setIndexBuffer(index_buffer);
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(view_id, program);
}

void PointLayer::updateVertexBuffer() {
  float ndc_width = point_radius / rect.width;
  float ndc_height = point_radius / rect.height;
  createQuad(points[0], ndc_width, ndc_height, point_quad);
  auto quad_ref = bgfx::makeRef(point_quad.data(), sizeof(float) * 20);
  bgfx::update(vertex_buffer, 0, quad_ref);
}
}
