#ifndef H_TEXTURE_UTILS
#define H_TEXTURE_UTILS
#include <string>
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <exception>

struct texture_load_exception : public std::exception {
  virtual const char* what() const throw() {
    return "Could not read texture file";
  }
};


bgfx::TextureHandle loadTexture(const std::string &);
bgfx::TextureHandle imageToTexture(bimg::ImageContainer*);
#endif

