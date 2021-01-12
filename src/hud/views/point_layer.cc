#include "bgfx/bgfx.h"
#include <hud/views/point_layer.h>
#include <hud/shader_utils.h>

namespace hud::views {

const uint16_t InstanceStride = 2 * sizeof(float) * 8; // One 2d vector per point instance.

static const uint16_t faces[] = {
  0, 1, 2, 0, 2, 3
};

std::array<float, 20> createVertices(float width, float height) {
  float left = -width;
  float right = width;
  float top = height;
  float bottom = -height;
  return {
    right, bottom, -0.01, 1.0, -1.0,
    right, top, -0.01, 1.0, 1.0,
    left, top, -0.01, -1.0, 1.0,
    left, bottom, -0.01, -1.0, -1.0
  };
}

PointLayer::PointLayer(const std::vector<Point> p) : hud::views::View(), points(p) {
  layout
    .begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
    .end();

  vertices = createVertices(point_radius, 0.01);
  auto quad_ref = bgfx::makeRef(vertices.data(), sizeof(float) * 20);
  vertex_buffer = bgfx::createVertexBuffer(quad_ref, layout);
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
}

void PointLayer::addPoint(const Point& point) {
  points.push_back(point);
}

void PointLayer::resized(Rect newRect) {
  views::View::resized(newRect);
  updateVertexBuffer();
}

void PointLayer::render() const {
  bgfx::InstanceDataBuffer idb;

  bgfx::allocInstanceDataBuffer(&idb, points.size(), InstanceStride);
  uint8_t* instance_data = idb.data;
  float ndc_width = point_radius / rect.width;
  float ndc_height = point_radius / rect.height;
  for (int i=0; i < points.size(); i++) {
    float* vectors = (float*)instance_data;
    const Point& point = points[i];
    vectors[0] = float(point.x + ndc_width);
    vectors[1] = float(point.y - ndc_height);
    instance_data += InstanceStride;
  }

  bgfx::setVertexBuffer(0, vertex_buffer);
  bgfx::setIndexBuffer(index_buffer);
  bgfx::setInstanceDataBuffer(&idb);
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(view_id, program);
}

void PointLayer::updateVertexBuffer() {
  if (bgfx::isValid(vertex_buffer)) {
    bgfx::destroy(vertex_buffer);
  }
  float ndc_width = point_radius / rect.width;
  float ndc_height = point_radius / rect.height;
  vertices = createVertices(ndc_width, ndc_height);
  auto quad_ref = bgfx::makeRef(vertices.data(), sizeof(float) * vertices.size());
  vertex_buffer = bgfx::createVertexBuffer(quad_ref, layout);
}
}
