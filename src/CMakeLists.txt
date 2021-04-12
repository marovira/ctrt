# Image dimensions
set(IMAGE_WIDTH 600)
set(IMAGE_HEIGHT 400)

add_subdirectory(${CTRT_SOURCE_ROOT}/tracer)
add_subdirectory(${CTRT_SOURCE_ROOT}/tiles)

set(TILE_INCLUDE_STRINGS)
set(TILE_GETTER_STRINGS_WITH_COMMA)
foreach(TILE_NAME ${TILE_NAME_LIST})
    list(APPEND TILE_INCLUDE_STRINGS "#include <tiles/${TILE_NAME}.hpp>\n")
    list(APPEND TILE_GETTER_STRINGS_WITH_COMMA "get_${TILE_NAME}, ")
endforeach()

# Strip the comma from the getter list.
string(FIND "${TILE_GETTER_STRINGS_WITH_COMMA}" ", " LAST_COMMA REVERSE)
string(SUBSTRING "${TILE_GETTER_STRINGS_WITH_COMMA}" 0 ${LAST_COMMA}
    TILE_GETTER_STRINGS)

# Now strip the ;
string(REPLACE ";" "" TILE_INCLUDE_LIST "${TILE_INCLUDE_STRINGS}")
string(REPLACE ";" "" TILE_GETTER_LIST "${TILE_GETTER_STRINGS}")

set(CTRT_SOURCE ${CTRT_SOURCE_ROOT}/ctrt.cpp)

source_group("source" FILES ${CTRT_SOURCE})

configure_file(${CTRT_SOURCE_ROOT}/ctrt.cpp.in ${CTRT_SOURCE})

add_executable(ctrt ${CTRT_SOURCE})
target_link_libraries(ctrt PUBLIC ${TILE_NAME_LIST})
target_compile_features(ctrt PUBLIC cxx_std_17)
target_compile_options(ctrt PUBLIC ${CTRT_COMPILER_FLAGS})
target_compile_options(ctrt PUBLIC ${CTRT_DEBUG_FLAGS})
target_compile_definitions(ctrt PUBLIC ${CTRT_COMPILE_DEFINITIONS})
set_target_properties(ctrt PROPERTIES FOLDER "ctrt")

if (MSVC)
    set_target_properties(ctrt PROPERTIES LINK_FLAGS
        ${CTRT_LINKER_FLAGS})
endif()



