set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_FIND_ROOT_PATH /usr/bin)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Set the sysroot (optional)
set(CMAKE_SYSROOT /usr/bin)

# Add additional compiler and linker flags as needed
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -mwindows -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -mwindows -static-libgcc -static-libstdc++  -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Specify the path to the Windows libraries (optional)
# set(CMAKE_LIBRARY_PATH /path/to/your/windows/libraries)

# Specify the path to the Windows headers (optional)
# include_directories(/path/to/your/windows/headers)

# You can define variables or settings specific to your project here

# End of toolchain.cmake
