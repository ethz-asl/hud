#ifndef H_SHADER_UTILS
#define H_SHADER_UTILS
#include <bgfx/bgfx.h>
#include <bx/file.h>

namespace shader_utils {

const bgfx::Memory* loadMemory(bx::FileReaderI* _reader, const char* _filePath);
bgfx::ShaderHandle loadShader(bx::FileReader *reader, const char* _name);
bgfx::ProgramHandle loadProgram(const char* vertexShader, const char* fragmentShader);
}
#endif
