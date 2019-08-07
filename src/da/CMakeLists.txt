cmake_minimum_required(VERSION 2.8)

project(da)

add_library(dataacess dataacess.cpp)

add_executable(da_compiler da_compiler.cpp da_compiler_util.cpp)

target_link_libraries(da_compiler PocoXML PocoFoundation)

add_executable(da_test da_test.cpp)

target_link_libraries(da_test dataacess)

install(TARGETS da_compiler DESTINATION bin)
install(TARGETS da_test DESTINATION bin)
