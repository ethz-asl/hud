#include <string>
#include <bgfx/bgfx.h>
#include <exception>

struct texture_load_exception : public std::exception {
  virtual const char* what() const throw() {
    return "Could not read texture file";
  }
};

bgfx::TextureHandle loadTexture(std::string &);

