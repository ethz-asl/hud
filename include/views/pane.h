#ifndef H_PANE
#define H_PANE
#include <bgfx/bgfx.h>
#include "texture_utils.h"
#include "shader_utils.h"


namespace views {
class Pane {
public:
  virtual void Render() = 0;
};
class ImagePane : public Pane {
private:
  bgfx::TextureHandle texture;

  bgfx::VertexBufferHandle vertexBuffer;
  bgfx::IndexBufferHandle indexBuffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;
  bgfx::UniformHandle textureColor;

public:
  ImagePane(std::string file_path);
  ~ImagePane();
  void Render();
};
}
#endif
