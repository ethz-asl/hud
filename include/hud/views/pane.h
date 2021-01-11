#ifndef H_PANE
#define H_PANE
#include <bgfx/bgfx.h>
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

public:
  ImagePane(int id, std::string file_path);
  ImagePane(const ImagePane&) = delete;
  ImagePane& operator=(const ImagePane&) = delete;
  ~ImagePane();

  // Rendering.
  void render() const override;

};
}
#endif
