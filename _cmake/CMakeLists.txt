cmake_minimum_required(VERSION 3.0)
project(test)

message("CMAKE_CROSSCOMPILING ${CMAKE_CROSSCOMPILING}")

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

add_executable(client WIN32 ${SOURCE_DIR}/client/client.cpp main.exe.manifest)

file(GLOB_RECURSE SOURCE_FILES_CLIENT
"${SOURCE_DIR}/client/presentation/*.cpp" 
"${SOURCE_DIR}/client/logic/*.h"
"${SOURCE_DIR}/bridge/*.h"
)

target_sources(client PRIVATE ${SOURCE_FILES_CLIENT})

# Configure wxWidgets
find_package(wxWidgets PATHS ${CMAKE_CURRENT_SOURCE_DIR}/external/wxWidgets/${CMAKE_SYSTEM_NAME}_build/install/lib/cmake/wxWidgets)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)


# Configure Asio Standalone
add_library(asio INTERFACE)
target_include_directories(asio SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/asio/source/asio/asio/include)

target_compile_definitions( client PRIVATE ASIO_STANDALONE )
target_compile_options( client PRIVATE -pthread )
target_compile_options( client PRIVATE 
-Wall -Wextra -Wpedantic -Wshadow -Wnarrowing -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wnull-dereference -Wuseless-cast -Wunused -Woverloaded-virtual -Wformat=2 -Wconversion -Wsign-conversion -Wdouble-promotion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op
)

target_compile_definitions( client PRIVATE 
$<$<CONFIG:Debug>: _GLIBCXX_DEBUG _GLIBCXX_DEBUG_PEDANTIC ASIO_ENABLE_BUFFER_DEBUGGING>
)
target_compile_options( client PRIVATE 
$<$<CONFIG:Debug>: -fsanitize=undefined,address -fstack-usage -fstack-protector>
)
target_link_options( client PRIVATE 
$<$<CONFIG:Debug>: -fsanitize=undefined,address -fstack-usage -fstack-protector>
)


# Server Builds only on Linux

if(NOT CMAKE_CROSSCOMPILING)
    add_executable(server WIN32 ${SOURCE_DIR}/server/server.cpp)

    file(GLOB_RECURSE SOURCE_FILES_SERVER
    "${SOURCE_DIR}/bridge/*.h"
    )

    target_sources(server PRIVATE ${SOURCE_FILES_SERVER})

    target_compile_definitions( server PRIVATE ASIO_STANDALONE )
    target_compile_options( server PRIVATE -pthread )
    target_compile_options( server PRIVATE 
    -Wall -Wextra -Wpedantic -Wshadow -Wnarrowing -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wnull-dereference -Wuseless-cast -Wunused -Woverloaded-virtual -Wformat=2 -Wconversion -Wsign-conversion -Wdouble-promotion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op
    )

    target_compile_definitions( server PRIVATE 
    $<$<CONFIG:Debug>: _GLIBCXX_DEBUG _GLIBCXX_DEBUG_PEDANTIC ASIO_ENABLE_BUFFER_DEBUGGING>
    )
    target_compile_options( server PRIVATE 
    $<$<CONFIG:Debug>: -fsanitize=undefined,address -fstack-usage -fstack-protector>
    )
    target_link_options( server PRIVATE 
    $<$<CONFIG:Debug>: -fsanitize=undefined,address -fstack-usage -fstack-protector>
    )


    target_link_libraries(server PRIVATE asio)
endif()



target_link_libraries(client PRIVATE ${wxWidgets_LIBRARIES} asio)