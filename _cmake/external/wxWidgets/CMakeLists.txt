find_package(wxWidgets QUIET PATHS ${CMAKE_CURRENT_BINARY_DIR}/install/lib/cmake/wxWidgets)

if(wxWidgets_FOUND)
    message(STATUS "WxWisgets IS FOUND!!!")
    add_library(wxWidgets INTERFACE)
else()
    message(STATUS "CANT FIND WxWisgets!!!")
    message(STATUS "Will install WxWidgets to ${CMAKE_CURRENT_BINARY_DIR}")
    include(ExternalProject)
    ExternalProject_Add(
        wxWidgets
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        STAMP_DIR  ${CMAKE_CURRENT_BINARY_DIR}/log
        TMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/log/tmp
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/download
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/download
        BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
        
        URL https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.2.1/wxWidgets-3.2.2.1.tar.bz2
        
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/install
    )

    set(wxWidgets_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR}/install)
    file(TO_NATIVE_PATH "${wxWidgets_ROOT_DIR}" wxWidgets_ROOT_DIR)
    set(wxWidgets_ROOT_DIR ${wxWidgets_ROOT_DIR} CACHE INTERNAL "wxWidgets installation dir")

    set(ENV_WX_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/build/wx-config)
    file(TO_NATIVE_PATH "${ENV_WX_CONFIG}" ENV_WX_CONFIG)
    set(ENV_WX_CONFIG ${ENV_WX_CONFIG} CACHE INTERNAL "wx-config dir")
    
endif()