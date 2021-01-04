macro(add_shaders ARG_TARGET)
  cmake_parse_arguments(ARG "" "" "SHADERS" ${ARGN})

  set(SHADER_DIRECTORY ${CMAKE_SOURCE_DIR}/compiled_shaders)
  file(MAKE_DIRECTORY ${SHADER_DIRECTORY}/glsl)
  file(MAKE_DIRECTORY ${SHADER_DIRECTORY}/spirv)

  set(BASE_OPTIONS INCLUDES ${BGFX_DIR}/src)
  unset(SHADER_COMMANDS)
  foreach(SHADER ${ARG_SHADERS})
    message("SHADER: ${SHADER}")
    if(${SHADER} MATCHES "vs_[^/]+\\.sc$")
      set(T VERTEX)
    elseif(${SHADER} MATCHES "fs_[^/]+\\.sc$")
      set(T FRAGMENT)
    else()
      message(FATAL_ERROR "Unknown shader type")
    endif()

    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)

    # GLSL
    shaderc_parse(OUT FILE "shaders/${SHADER}" OUTPUT "${SHADER_DIRECTORY}/glsl/${SHADER_NAME}.bin" ${T} VARYINGDEF "shaders/varying.def.sc" LINUX PROFILE 420 ${BASE_OPTIONS})
    list(APPEND SHADER_COMMANDS COMMAND "$<TARGET_FILE:shaderc>" ${OUT})

    # spirv
    # shaderc_parse(OUT FILE "shaders/${SHADER}" OUTPUT "${SHADER_DIRECTORY}/spirv/${SHADER_NAME}.bin" ${T} LINUX PROFILE spirv ${BASE_OPTIONS})
    # list(APPEND SHADER_COMMANDS COMMAND "$<TARGET_FILE:shaderc>" ${OUT})

    list(APPEND SHADER_SOURCE_FILES "shaders/${SHADER}")
  endforeach()

  add_custom_target(shaders ALL ${SHADER_COMMANDS}
    DEPENDS shaderc
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Compiling shaders")

  target_sources(main PRIVATE ${SHADER_SOURCE_FILES})
  add_dependencies(main shaders)
endmacro()
