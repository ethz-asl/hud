#ifndef H_PANE
#define H_PANE
#include <bgfx/bgfx.h>
#include "../texture_utils.h"
#include "../shader_utils.h"
#include "view.h"


namespace views {
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
  ~ImagePane();
  void render(const ViewRect&);
};
}
#endif
