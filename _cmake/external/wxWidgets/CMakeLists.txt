cmake_minimum_required(VERSION 3.0)
project(wxWidgets)

message("CMAKE_CROSSCOMPILING: ${CMAKE_CROSSCOMPILING}")
message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
find_package(wxWidgets PATHS ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}_build/install/lib/cmake/wxWidgets)

if(wxWidgets_FOUND)
    message("FOUND PACKAGE: wxWidgets")
else()
    message("CANT FIND A PACKAGE: wxWidgets")
    set(CONFIGURATIONS Debug Release)
    
    set(INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}_build/install)
    set(EXTERNAL_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}_build/source)
    set(EXTERNAL_PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}_build/build)

    include(ExternalProject)
    function(build_external_project CONFIG)
        ExternalProject_Add(
            ${PROJECT_NAME}_${CONFIG}
            PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}_build/external_project
            DOWNLOAD_DIR ${EXTERNAL_PROJECT_BINARY_DIR}
            SOURCE_DIR ${EXTERNAL_PROJECT_SOURCE_DIR}
            BINARY_DIR ${EXTERNAL_PROJECT_BINARY_DIR}
            INSTALL_DIR ${INSTALL_DIR}
            GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
            GIT_TAG master
            CMAKE_ARGS
                -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
                -DCMAKE_BUILD_TYPE=${CONFIG}
                -DwxBUILD_SHARED=OFF
                -DwxBUILD_SAMPLES=ALL
                -DwxBUILD_DEMOS=ON
                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
            )
    endfunction()
    foreach(CONFIG ${CONFIGURATIONS})
        build_external_project(${CONFIG})
    endforeach()
endif()
