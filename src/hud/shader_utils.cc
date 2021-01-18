#include <hud/shader_utils.h>

#include <iostream>
#include <filesystem>

namespace shader_utils {

std::string data_dir = "../";

void setDataDirectory(const std::string& dir) {
  data_dir = dir;
}

const bgfx::Memory* loadMemory(bx::FileReaderI* _reader, const char* _filePath) {
	if (bx::open(_reader, _filePath)) {
		uint32_t size = (uint32_t)bx::getSize(_reader);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		bx::read(_reader, mem->data, size);
		bx::close(_reader);
		mem->data[mem->size-1] = '\0';
		return mem;
	}
	return NULL;
}

bgfx::ShaderHandle loadShader(bx::FileReader *reader, const char* _name) {
	char filePath[512];

	std::string shaderPath = "";

	switch (bgfx::getRendererType()) {
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::OpenGL:     shaderPath = "compiled_shaders/glsl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "compiled_shaders/spirv/"; break;
	case bgfx::RendererType::Count:
		BX_ASSERT(false, "You should not be here!");
		break;
	}

	std::filesystem::path combined = std::filesystem::path(data_dir) / shaderPath;
	shaderPath = combined.string();

	bx::strCopy(filePath, BX_COUNTOF(filePath), shaderPath.c_str());
	bx::strCat(filePath, BX_COUNTOF(filePath), _name);
	bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");

	bgfx::ShaderHandle handle = bgfx::createShader(loadMemory(reader, filePath) );
	bgfx::setName(handle, _name);

	return handle;
}

bgfx::ProgramHandle loadProgram(const char* vertexShader, const char* fragmentShader) {
  bx::FileReader reader;
	bgfx::ShaderHandle vsh = loadShader(&reader, vertexShader);
	bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
	if (NULL != fragmentShader) {
		fsh = loadShader(&reader, fragmentShader);
	}

	return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
}

}
