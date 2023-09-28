cmake_minimum_required(VERSION 3.0)
project(test)

message(${wxWidgets_ROOT_DIR}/lib/cmake/wxWidgets)
find_package(wxWidgets REQUIRED PATHS ${wxWidgets_ROOT_DIR}/lib/cmake/wxWidgets)

find_package(OpenGL REQUIRED)


add_executable(test main.cpp)

target_link_libraries(test PRIVATE ${wxWidgets_LIBRARIES})