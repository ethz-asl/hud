cmake_minimum_required(VERSION 3.10)
project(XRay)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/shaders.cmake)

set(BGFX_BUILD_TOOLS ON)
set(BGFX_BUILD_EXAMPLES OFF)

include_directories(include)
add_subdirectory(submodules/bgfx)


file(GLOB SOURCE_FILES src/**/*.cc src/hud/**/*.cc src/*.cc)
add_executable(main ${SOURCE_FILES})
target_link_libraries(main bgfx bx bimg glfw)

add_shaders(main SHADERS vs_pane.sc fs_pane.sc point_layer/vs_point_layer.sc point_layer/fs_point_layer.sc)
