#include <bx/allocator.h>
#include <pybind11/numpy.h>
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

namespace hud::numpy_utils {

void imageReleaseCb(void* ptr, void *userData) {
  BX_UNUSED(ptr);
  bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)userData;
  bimg::imageFree(imageContainer);
}

static bx::DefaultAllocator default_allocator;

bgfx::TextureHandle arrayToTexture(const pybind11::array_t<uint8_t> &image) {
  bimg::ImageContainer container;
  container.m_allocator = &default_allocator;
  container.m_format  = bimg::TextureFormat::RGB8;
  container.m_orientation = bimg::Orientation::R0;
  container.m_size = image.shape(0) * image.shape(1) * image.shape(2);
  container.m_height = image.shape(0);
  container.m_width = image.shape(1);
  container.m_depth = image.shape(2);
  container.m_numLayers = 1;
  container.m_numMips = 1;
  container.m_hasAlpha = false;
  container.m_offset = 0;
  container.m_data = (void*)image.data();

  const bgfx::Memory * mem = bgfx::copy(container.m_data, container.m_size);

  return bgfx::createTexture2D(uint16_t(container.m_width), uint16_t(container.m_height),
	false,
	container.m_numLayers,
	bgfx::TextureFormat::Enum(container.m_format),
	BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE,
	mem);
}

}
