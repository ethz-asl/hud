#include "pane.h"

static const float vertices[] = {
  -1.0f, -1.0f, 0.0f,
  -1.0f,  1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f
};

static const uint16_t faces[] = {
  0, 3, 1,
  0, 2, 3
};

ImagePane::ImagePane(std::string file_path) {
  //texture = loadTexture(file_path);

  layout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).end();

  vertex_buffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), layout);
  index_buffer = bgfx::createIndexBuffer(bgfx::makeRef(faces, sizeof(faces)));

  program = shader_utils::loadProgram("vs_pane", "fs_pane");
}

void ImagePane::Render() {

  uint64_t state = 0;
  bgfx::setVertexBuffer(0, vertex_buffer);
  bgfx::setIndexBuffer(index_buffer);
  bgfx::setState(state);
  bgfx::submit(0, program);
}

