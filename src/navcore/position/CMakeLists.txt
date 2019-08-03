cmake_minimum_required(VERSION 2.8)

project(Position)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
include_directories(
    ${CMAKE_BINARY_DIR}/fidl/src-gen
    /usr/local/include/CommonAPI-3.1
    /usr/local/include/vsomeip
)

add_executable(PositionService
	PositionService.cpp
	PositionStubImpl.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/PositionSomeIPStubAdapter.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/PositionStubDefault.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/PositionSomeIPDeployment.cpp
)

target_link_libraries(PositionService CommonAPI CommonAPI-SomeIP vsomeip)

install(TARGETS PositionService DESTINATION bin)
