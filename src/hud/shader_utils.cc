#include <hud/shader_utils.h>

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace shader_utils {

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

	// program location is the path to the Python executable.
	// Assume that the shaders are in the Python env under the share/hud folder.
	boost::filesystem::path program_location = boost::dll::program_location();
	boost::filesystem::path data_dir;
	if (program_location.string().find("python") != std::string::npos) {
	  data_dir = program_location.parent_path().parent_path() / "share" / "hud";
	  if (!boost::filesystem::exists(data_dir)) {
	    // If the folder doesn't exist, it likely is using the system Python and the library is installed in the home directory.

	    data_dir = boost::filesystem::path(getenv("HOME")) / ".local" / "share" / "hud";
	  }
	} else {
	  // Assume that we are running the binary from the build folder. Compiled shaders are at
	  // ../compiled_shaders.
	  data_dir = program_location.parent_path().parent_path();
	}
	boost::filesystem::path combined = data_dir / shaderPath;
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
