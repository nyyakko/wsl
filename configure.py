import os
import sys

BUILD_TYPE = sys.argv[1] if len(sys.argv) >= 2 else 'debug'
TOOLCHAIN  = os.getenv('CMAKE_TOOLCHAIN_FILE')

if not os.path.exists('build'):
    os.mkdir('build')

os.system(f'cmake -DWSL_DISABLE_TESTS=FALSE -DCMAKE_BUILD_TYPE={BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE={TOOLCHAIN} -G Ninja -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -B./build/ -S./')
