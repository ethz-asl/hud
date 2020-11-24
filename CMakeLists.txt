cmake_minimum_required(VERSION 3.10)
project(XRay)

set(CMAKE_CXX_STANDARD 20)

include(cmake/shaders.cmake)

include_directories(include)
add_subdirectory(submodules/bgfx)


file(GLOB SOURCE_FILES src/*.cc)
add_executable(main ${SOURCE_FILES})
target_link_libraries(main bgfx bx bimg glfw)

add_shaders(main SHADERS vs_pane.sc fs_pane.sc)
