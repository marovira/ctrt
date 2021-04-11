set(CTRT_INCLUDE_FILES
    ${CTRT_SOURCE_ROOT}/tracer/vector.hpp
    ${CTRT_SOURCE_ROOT}/tracer/utils.hpp
    ${CTRT_SOURCE_ROOT}/tracer/ray.hpp
    ${CTRT_SOURCE_ROOT}/tracer/camera.hpp
    ${CTRT_SOURCE_ROOT}/tracer/image.hpp
    ${CTRT_SOURCE_ROOT}/tracer/scene.hpp
    ${CTRT_SOURCE_ROOT}/tracer/shapes.hpp
    ${CTRT_SOURCE_ROOT}/tracer/materials.hpp
    ${CTRT_SOURCE_ROOT}/tracer/renderer.hpp
    ${CTRT_SOURCE_ROOT}/tracer/lights.hpp
    ${CTRT_SOURCE_ROOT}/tracer/brdf.hpp
    )

set(CTRT_SOURCE_FILES
    ${CTRT_SOURCE_ROOT}/tracer/assert.cpp
    )

source_group("include" FILES ${CTRT_INCLUDE_FILES})
source_group("source" FILES ${CTRT_SOURCE_FILES})

add_library(ctrt_tracer ${CTRT_INCLUDE_FILES} ${CTRT_SOURCE_FILES})
target_include_directories(ctrt_tracer PUBLIC ${CTRT_SOURCE_ROOT})
target_link_libraries(ctrt_tracer PUBLIC zeus::zeus stb)
target_compile_features(ctrt_tracer PUBLIC cxx_std_17)
target_compile_options(ctrt_tracer PUBLIC ${CTRT_COMPILER_FLAGS})
target_compile_options(ctrt_tracer PUBLIC ${CTRT_DEBUG_FLAGS})
target_compile_definitions(ctrt_tracer PUBLIC ${CTRT_COMPILE_DEFINITIONS})
set_target_properties(ctrt_tracer PROPERTIES FOLDER "ctrt")

if (MSVC)
    set_target_properties(ctrt_tracer PROPERTIES LINK_FLAGS ${CTRT_LINKER_FLAGS})
endif()

