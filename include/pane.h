#ifndef H_PANE
#define H_PANE
#include <bgfx/bgfx.h>
#include "texture_utils.h"
#include "shader_utils.h"

class Pane {
public:
  virtual void Render() = 0;
};
class ImagePane : public Pane {
private:
  bgfx::TextureHandle texture;

  bgfx::VertexBufferHandle vertex_buffer;
  bgfx::IndexBufferHandle index_buffer;
  bgfx::VertexLayout layout;
  bgfx::ProgramHandle program;

public:
  ImagePane(std::string file_path);
  void Render();
};

#endif
