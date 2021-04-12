#================================
# Project setup.
#================================
cmake_minimum_required(VERSION 3.19)
project(ctrt VERSION 1.0.0 LANGUAGES CXX)

if (APPLE)
    message(ERROR "CTRT does not support Apple platforms.")
endif()

if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#================================
# Option variables.
#================================
option(CTRT_BUILD_TESTS "Build CTRT unit tests" ON)
option(CTRT_RENDER_STATIC "Perform render at compile-time" OFF)
set(CTRT_RENDER_SCENE "CTRT_RENDER_SCENE_1" CACHE STRING "Scene to render")

# Make sure Zeus does not make the clang-format target and disable the
# unit tests for it.
set(ZEUS_CLANG_FORMAT_TARGET OFF CACHE INTERNAL "")
set(ZEUS_BUILD_TESTS OFF CACHE INTERNAL "")

#================================
# Directory variables.
#================================
set(CTRT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(CTRT_SOURCE_ROOT ${CTRT_SOURCE_DIR}/src)
set(CTRT_TEST_ROOT ${CTRT_SOURCE_DIR}/test)
set(CTRT_EXTERNAL_ROOT ${CTRT_SOURCE_DIR}/external)

#================================
# Find Packages.
#================================
include(FetchContent)

# Declare fetch content for all packages.
FetchContent_Declare(
    zeus
    GIT_REPOSITORY https://github.com/marovira/zeus
    GIT_TAG 531afeb2f6c7ac2a7c4057c3d7278868324cc584
    )

find_package(zeus QUIET)

if (NOT zeus_FOUND AND NOT zeus_POPULATED)
    FetchContent_Populate(zeus)
    add_subdirectory(${zeus_SOURCE_DIR} ${zeus_BINARY_DIR})
endif()

#================================
# Compiler flags.
#================================
if (MSVC)
    set(CTRT_COMPILER_FLAGS /W4 /WX /MP /constexpr:steps2147483647 /bigobj)
    set(CTRT_DEBUG_FLAGS "$<$<CONFIG:DEBUG>:/ZI>")
    set(CTRT_COMPILE_DEFINITIONS -DNOMINMAX)
    set(CTRT_LINKER_FLAGS /STACK:10000000)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL
        "GNU")
    set(CTRT_COMMON_FLAGS -Wall -Wextra -pedantic -Werror)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CTRT_COMPILER_FLAGS ${CTRT_COMMON_FLAGS})
    else()
        set(CTRT_COMPILER_FLAGS ${CTRT_COMMON_FLAGS} -stdlib=libstdc++)
    endif()
    set(CTRT_DEBUG_FLAGS "$<$<CONFIG:DEBUG>:-g>")
    set(CTRT_LINKER_FLAGS)
endif()

if (CTRT_RENDER_STATIC)
    set(CTRT_COMPILE_DEFINITIONS ${CTRT_COMPILE_DEFINITIONS}
        -DCTRT_DO_STATIC_RENDER)
endif()

set(CTRT_COMPILE_DEFINITIONS ${CTRT_COMPILE_DEFINITIONS} "-D${CTRT_RENDER_SCENE}")
message(STATUS ${CTRT_COMPILE_DEFINITIONS})

#================================
# Add subdirectories.
#================================
add_subdirectory(${CTRT_EXTERNAL_ROOT}/stb)
set_target_properties(stb PROPERTIES FOLDER "ctrt")

add_subdirectory(${CTRT_SOURCE_ROOT})



#if (CTRT_BUILD_TESTS)
    #FetchContent_Declare(
        #catch2
        #GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        #GIT_TAG 5d32ce26f4c18588f9eac3342aea122a38b8fed3
        #)

    #find_package(Catch2 QUIET)
    #if (NOT Catch2_FOUND AND NOT catch2_POPULATED)
        #FetchContent_Populate(catch2)
        #add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
        #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${catch2_SOURCE_DIR}/contrib)
    #endif()

    #add_subdirectory(${CTRT_TEST_ROOT})

    #source_group("source" FILES ${CTRT_TEST_SOURCE})

    #add_executable(ctrt_test ${CTRT_TEST_SOURCE})
    #target_include_directories(ctrt_test PUBLIC ${CTRT_SOURCE_ROOT})
    #target_link_libraries(ctrt_test Catch2::Catch2 zeus::zeus)
    #set_target_properties(ctrt_test PROPERTIES FOLDER "ctrt")

    #include(CTest)
    #include(Catch)
    #catch_discover_tests(ctrt_test)
#endif()
