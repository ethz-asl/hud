#include "bgfx/bgfx.h"
#include <hud/views/point_layer.h>
#include <hud/shader_utils.h>
#include <stdexcept>

using namespace Eigen;

namespace hud::views {

const uint16_t InstanceStride = 32;  // One 2d vector per point instance.

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
  colors.resize(points.size(), 4);
  for (int i=0; i < points.size(); i++) {
    colors.row(i) = DefaultColor;
  }
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

void PointLayer::setPoints(std::vector<Point> newPoints, const Matrix<double, Dynamic, 4>& c) {
  points = newPoints;
  setColors(c);
}

void PointLayer::addPoint(const Point& point, const RowVector4d& color) {
  int old_count = colors.rows();
  points.push_back(point);
  Eigen::Matrix<double, Dynamic, 4> newColors(old_count + 1, 4);
  newColors.block(0, 0, old_count, 4) = colors.block(0, 0, old_count, 4);
  newColors.row(old_count) = color;
  colors = newColors;
}

void PointLayer::clearPoints() {
  points.clear();
  colors.resize(0, 4);
}

void PointLayer::setColors(const Matrix<double, Dynamic, 4, RowMajor>& newColors) {
  if (newColors.rows() == points.size()) {
    colors = newColors;
  } else if (newColors.rows() == 1) {
    colors.resize(points.size(), 4);
    for (int i=0; i < points.size(); i++) {
      colors.row(i) = newColors;
    }
  } else {
    throw std::invalid_argument("Colors has to have 1 or the same amount of rows as points.");
  }
}

void PointLayer::pop() {
  if (!points.empty()) {
    points.pop_back();
  }
}

void PointLayer::resized(Rect newRect) {
  views::View::resized(newRect);
  updateVertexBuffer();
}

void PointLayer::render() const {
  if (points.empty()) return;
  bgfx::InstanceDataBuffer idb;

  float ndc_width = point_radius / rect.width * 0.5;
  float ndc_height = point_radius / rect.height * 0.5;

  int instance_spots = bgfx::getAvailInstanceDataBuffer(points.size(), InstanceStride);
  int num_instances = std::min(int(points.size()), instance_spots);

  bgfx::allocInstanceDataBuffer(&idb, num_instances, InstanceStride);
  uint8_t* instance_data = (uint8_t*)idb.data;

  assert(points.size() == colors.rows());
  for (int i=0; i < num_instances; i++) {
    float* vectors = (float*)instance_data;
    const Point& point = points[i];
    vectors[0] = float(point.x - ndc_width);
    vectors[1] = float(point.y + ndc_height);

    const RowVector4d& color = colors.row(i);
    vectors[2] = float(color[0]);
    vectors[3] = float(color[1]);
    vectors[4] = float(color[2]);
    vectors[5] = float(color[3]);
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
