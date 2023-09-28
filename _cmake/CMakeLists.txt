cmake_minimum_required(VERSION 3.0)
project(test)

add_subdirectory(external)

include(ExternalProject)
ExternalProject_Add(
    test_core
    DEPENDS wxWidgets
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
    BUILD_ALWAYS 1
    CMAKE_ARGS -DwxWidgets_ROOT_DIR=${wxWidgets_ROOT_DIR}
    INSTALL_COMMAND ""
)