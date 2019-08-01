cmake_minimum_required(VERSION 2.8)

project(Hello)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
include_directories(
    ${CMAKE_BINARY_DIR}/fidl/src-gen
    /usr/local/include/CommonAPI-3.1
    /usr/local/include/vsomeip
)

add_executable(HelloWorldClient
	HelloWorldClient.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/HelloWorldSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/HelloWorldSomeIPDeployment.cpp
)
target_link_libraries(HelloWorldClient CommonAPI CommonAPI-SomeIP vsomeip)

add_executable(HelloWorldService
	HelloWorldService.cpp
	HelloWorldStubImpl.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/HelloWorldSomeIPStubAdapter.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/HelloWorldStubDefault.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/HelloWorldSomeIPDeployment.cpp
)
target_link_libraries(HelloWorldService CommonAPI CommonAPI-SomeIP vsomeip)

