#ifndef H_SHADER_UTILS
#define H_SHADER_UTILS
#include <string>
#include <bgfx/bgfx.h>
#include <bx/file.h>

namespace shader_utils {


void setDataDirectory(const std::string&);

const bgfx::Memory* loadMemory(bx::FileReaderI* _reader, const char* _filePath);
bgfx::ShaderHandle loadShader(bx::FileReader *reader, const char* _name, const std::string& data_dir);
bgfx::ProgramHandle loadProgram(const char* vertexShader, const char* fragmentShader);
}
#endif
