cmake_minimum_required(VERSION 3.0)
project(test)

message("CMAKE_CROSSCOMPILING ${CMAKE_CROSSCOMPILING}")

find_package(wxWidgets PATHS ${CMAKE_CURRENT_SOURCE_DIR}/external/wxWidgets/${CMAKE_SYSTEM_NAME}_build/install/lib/cmake/wxWidgets)
find_package(OpenGL REQUIRED)

add_executable(test WIN32 main.cpp)

target_link_libraries(test PRIVATE ${wxWidgets_LIBRARIES})