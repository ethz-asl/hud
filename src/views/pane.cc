#include "views/pane.h"

namespace views {
static const float vertexData[] = {
  -1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
  -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
   1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
   1.0f,  1.0f, 0.0f, 0.0f, 0.0f
};

static const uint16_t faces[] = {
  0, 3, 1,
  0, 2, 3
};

ImagePane::ImagePane(std::string file_path) {
  layout
    .begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
    .end();

  vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertexData, sizeof(vertexData)), layout);
  indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(faces, sizeof(faces)));

  textureColor = bgfx::createUniform("textureColor", bgfx::UniformType::Sampler);
  texture = loadTexture(file_path);

  program = shader_utils::loadProgram("vs_pane", "fs_pane");
}

ImagePane::~ImagePane() {
  bgfx::destroy(vertexBuffer);
  bgfx::destroy(indexBuffer);
  bgfx::destroy(texture);
  bgfx::destroy(textureColor);
  bgfx::destroy(program);
}

void ImagePane::Render() {
  uint64_t state = BGFX_STATE_DEFAULT;
	bgfx::touch(0);

  bgfx::setVertexBuffer(0, vertexBuffer);
  bgfx::setIndexBuffer(indexBuffer);

  bgfx::setTexture(0, textureColor, texture);

  bgfx::setState(state);
  bgfx::submit(0, program);
}

}
