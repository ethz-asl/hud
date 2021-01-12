#ifndef H_PANE
#define H_PANE
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <hud/texture_utils.h>
#include <hud/shader_utils.h>
#include <hud/views/view.h>

namespace hud::views {
class ImagePane : public View {
private:
  bgfx::TextureHandle texture;

  bgfx::VertexBufferHandle vertexBuffer;
  bgfx::IndexBufferHandle indexBuffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  bgfx::UniformHandle textureColor;

  bool image_set = false;
  void initRendering();

public:
  ImagePane(const bgfx::TextureHandle& handle);
  ImagePane(std::string file_path);
  ImagePane(const ImagePane&) = delete;
  ImagePane& operator=(const ImagePane&) = delete;
  ~ImagePane();

  void setTexture(const bgfx::TextureHandle& handle) {
    bgfx::destroy(texture);
    texture = handle;
  }

  // Rendering.
  void render() const override;

};
}
#endif
