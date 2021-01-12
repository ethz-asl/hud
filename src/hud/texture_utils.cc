#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/file.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>
#include <hud/texture_utils.h>

static bx::DefaultAllocator allocator;

static void imageReleaseCb(void* ptr, void *userData) {
  BX_UNUSED(ptr);
  bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)userData;
  bimg::imageFree(imageContainer);
}

bgfx::TextureHandle loadTexture(std::string &filePath) {
  bx::FileReader reader;
  bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
  bx::Error error;
  void *data;
  if (reader.open(filePath.c_str(), &error)) {
    uint32_t size = (uint32_t)bx::getSize(&reader);
    data = BX_ALLOC(&allocator, size);
    bx::read(&reader, data, size, &error);
    bx::close(&reader);
    bimg::ImageContainer *imageContainer = bimg::imageParse(&allocator, data, size);
    if (!error.isOk()) {
      throw texture_load_exception();
    }
    const bgfx::Memory* mem = bgfx::makeRef(imageContainer->m_data,
	imageContainer->m_size, imageReleaseCb, imageContainer);

    BX_FREE(&allocator, data);

    handle = bgfx::createTexture2D(uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
	1 < imageContainer->m_numMips,
	imageContainer->m_numLayers,
	bgfx::TextureFormat::Enum(imageContainer->m_format),
	BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE,
	mem);
  }

  return handle;
}

