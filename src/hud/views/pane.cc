#include <hud/views/pane.h>

namespace hud::views {
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

void ImagePane::initRendering() {
  layout
    .begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
    .end();

  vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertexData, sizeof(vertexData)), layout);
  indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(faces, sizeof(faces)));

  textureColor = bgfx::createUniform("textureColor", bgfx::UniformType::Sampler);

  program = shader_utils::loadProgram("vs_pane", "fs_pane");
  bgfx::setViewClear(view_id, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
}

ImagePane::ImagePane(const bgfx::TextureHandle &handle) : View(), texture(handle) {
  initRendering();
  image_set = true;
}

ImagePane::ImagePane(std::string file_path) : ImagePane(loadTexture(file_path)) {}

ImagePane::~ImagePane() {
  bgfx::destroy(vertexBuffer);
  bgfx::destroy(indexBuffer);
  if (bgfx::isValid(texture))
    bgfx::destroy(texture);
  bgfx::destroy(textureColor);
  bgfx::destroy(program);
}

void ImagePane::render() const {
  bgfx::setVertexBuffer(0, vertexBuffer);
  bgfx::setIndexBuffer(indexBuffer);

  bgfx::setTexture(0, textureColor, texture);

  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(view_id, program);
}

}
