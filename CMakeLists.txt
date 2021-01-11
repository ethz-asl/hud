cmake_minimum_required(VERSION 3.10)
project(XRay)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/shaders.cmake)

set(BGFX_BUILD_TOOLS ON)
set(BGFX_BUILD_EXAMPLES OFF)

add_subdirectory(submodules/bgfx)
add_subdirectory(submodules/pybind11)

include_directories(include)
include_directories(submodules/pybind11/include)

file(GLOB SOURCE_FILES src/hud/**/*.cc src/hud/*.cc)
add_library(shared_lib ${SOURCE_FILES})
target_link_libraries(shared_lib bgfx bx bimg glfw)

add_executable(main src/main.cc)
target_link_libraries(main shared_lib)

pybind11_add_module(hud bindings/main.cc)
target_link_libraries(hud PRIVATE shared_lib)

add_shaders(main SHADERS vs_pane.sc fs_pane.sc point_layer/vs_point_layer.sc point_layer/fs_point_layer.sc
    line_layer/vs_line_layer.sc line_layer/fs_line_layer.sc)

