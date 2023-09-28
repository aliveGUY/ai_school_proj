cmake_minimum_required(VERSION 3.0)
project(test)

set(CUSTOM_DIR ${CMAKE_SOURCE_DIR}/lib/install/lib/cmake/wxWidgets)


message(${CUSTOM_DIR})
find_package(wxWidgets REQUIRED COMPONENTS core base PATHS ${CUSTOM_DIR})

add_executable(test main.cpp)
target_link_libraries(test ${wxWidgets_LIBRARIES})