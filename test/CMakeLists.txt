FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 5d32ce26f4c18588f9eac3342aea122a38b8fed3
    )

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND AND NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${catch2_SOURCE_DIR}/contrib)
endif()

set(CTRT_TEST_SOURCE
    ${CTRT_TEST_ROOT}/test_main.cpp
    )

source_group("source" FILES ${CTRT_TEST_SOURCE})

add_executable(ctrt_test ${CTRT_TEST_SOURCE})
target_link_libraries(ctrt_test Catch2::Catch2)
set_target_properties(ctrt_test PROPERTIES FOLDER "ctrt")

include(CTest)
include(Catch)
catch_discover_tests(ctrt_test)
