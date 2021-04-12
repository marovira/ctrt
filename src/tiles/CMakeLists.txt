# Slab information
set(NUM_TILES_HORIZONTAL 2)
set(NUM_TILES_VERTICAL 2)

math(EXPR TILE_WIDTH "${IMAGE_WIDTH} / ${NUM_TILES_HORIZONTAL}")
math(EXPR TILE_HEIGHT "${IMAGE_HEIGHT} / ${NUM_TILES_VERTICAL}")
math(EXPR LOOP_X_END "${NUM_TILES_HORIZONTAL} - 1")
math(EXPR LOOP_Y_END "${NUM_TILES_VERTICAL} - 1")

set(CTRT_TILE_ROOT ${CTRT_SOURCE_ROOT}/tiles)
set(TILE_INPUT_HEADER ${CTRT_TILE_ROOT}/tile.hpp.in)
set(TILE_INPUT_SOURCE ${CTRT_TILE_ROOT}/tile.cpp.in)

set(TILE_TARGET_LIST)
foreach(X RANGE 0 ${LOOP_X_END})
    foreach(Y RANGE 0 ${LOOP_Y_END})
        math(EXPR TILE_X_START "${X} * ${TILE_WIDTH}")
        math(EXPR TILE_Y_START "${Y} * ${TILE_HEIGHT}")
        math(EXPR TILE_X_END "${TILE_X_START} + ${TILE_WIDTH}")
        math(EXPR TILE_Y_END "${TILE_Y_START} + ${TILE_HEIGHT}")

        set(TILE_NAME tile_${X}_${Y})

        # Set the files for the library.
        set(TILE_INCLUDE ${CTRT_TILE_ROOT}/${TILE_NAME}.hpp)
        set(TILE_SOURCE ${CTRT_TILE_ROOT}/${TILE_NAME}.cpp)

        source_group("include" FILES ${TILE_INCLUDE})
        source_group("source" FILES ${TILE_SOURCE})

        # Now generate the files.
        configure_file(${TILE_INPUT_HEADER} ${TILE_INCLUDE})
        configure_file(${TILE_INPUT_SOURCE} ${TILE_SOURCE})

        # Set the library.
        add_library(${TILE_NAME} ${TILE_INCLUDE} ${TILE_SOURCE})
        target_include_directories(${TILE_NAME} PUBLIC ${CTRT_TILE_ROOT})
        target_link_libraries(${TILE_NAME} PUBLIC ctrt_tracer)
        target_compile_features(${TILE_NAME} PUBLIC cxx_std_17)
        target_compile_options(${TILE_NAME} PUBLIC ${CTRT_COMPILER_FLAGS})
        target_compile_options(${TILE_NAME} PUBLIC ${CTRT_DEBUG_FLAGS})
        target_compile_definitions(${TILE_NAME} PUBLIC ${CTRT_COMPILE_DEFINITIONS})
        set_target_properties(${TILE_NAME} PROPERTIES FOLDER "ctrt_tiles")

        if (MSVC)
            set_target_properties(${TILE_NAME} PROPERTIES LINK_FLAGS
                ${CTRT_LINKER_FLAGS})
        endif()

        # Append the new target to the list.
        list(APPEND TILE_TARGET_LIST ${TILE_NAME})
    endforeach()
endforeach()

set(TILE_NAME_LIST ${TILE_TARGET_LIST} PARENT_SCOPE)
