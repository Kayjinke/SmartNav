cmake_minimum_required(VERSION 2.8)

if (${ARCH} STREQUAL "arm")

message(STATUS "set aarch64 toolchain")

set(TOOLCHAIN_DIR /home/rueco/workspace/uaes/gcc-linaro-4.9.4-2017.01-x86_64_aarch64-linux-gnu)
set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-g++)

target_link_libraries()

endif()
