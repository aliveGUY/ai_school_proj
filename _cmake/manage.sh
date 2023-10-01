#!/bin/bash


command=$1
system=${2:-$OSTYPE}

flags=""

if [[ "$system" == *"windows"* ]]; then
  flags=-DCMAKE_TOOLCHAIN_FILE=$PWD/toolchain.cmake
fi

build(){
    cmake -Bbuild/$system $flags && cmake --build build/$system
}

deps_config(){
    cmake -Sexternal/wxWidgets/ -Bexternal/wxWidgets/cache/$system $flags && cmake --build external/wxWidgets/cache/$system
}

run(){
    ./build/$system/test
}

case $command in

    build)
        build
        ;;

    run)
        run
        ;;

    deps_config)
        deps_config
        ;;

    *)
        echo -n -e "unknown\n"
        ;;
esac