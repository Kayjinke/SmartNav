cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
include_directories(
    ${CMAKE_BINARY_DIR}/fidl/src-gen
    /usr/local/include/CommonAPI-3.1
    /usr/local/include/vsomeip
)



add_executable(RouteInfoService
	RouteInfoService.cpp
	RouteInfoStubImpl.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteInfoSomeIPStubAdapter.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteInfoStubDefault.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteInfoSomeIPDeployment.cpp
)

target_link_libraries(RouteInfo CommonAPI CommonAPI-SomeIP vsomeip)


