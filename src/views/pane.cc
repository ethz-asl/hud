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

ImagePane::ImagePane(int id, std::string file_path) : View(id) {
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
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
}

ImagePane::~ImagePane() {
  bgfx::destroy(vertexBuffer);
  bgfx::destroy(indexBuffer);
  bgfx::destroy(texture);
  bgfx::destroy(textureColor);
  bgfx::destroy(program);
}

void ImagePane::render(const ViewRect& rect) {
  (void)rect;

  bgfx::setVertexBuffer(0, vertexBuffer);
  bgfx::setIndexBuffer(indexBuffer);

  bgfx::setTexture(0, textureColor, texture);

  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(viewId, program);
}

}
