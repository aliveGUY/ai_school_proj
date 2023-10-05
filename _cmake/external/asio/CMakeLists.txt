project(your_project_name)
cmake_minimum_required(VERSION 3.0)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
execute_process(
    COMMAND git clone https://github.com/chriskohlhoff/asio.git
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
