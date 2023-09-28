import os
import sys

keyword = sys.argv[1]

scripts = {
    "build": lambda: os.system("cmake -S . -B build/ && cmake --build ./build"),
    "run": lambda: os.system("./build/test_core-prefix/src/test_core-build/test"),
    "build-run": lambda: os.system("cmake -S . -B build/ && cmake --build ./build && ./build/test_core-prefix/src/test_core-build/test"),
}

scripts[keyword]()