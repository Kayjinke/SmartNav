cmake_minimum_required(VERSION 2.8)

project(Navigation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
include_directories(
    ${CMAKE_BINARY_DIR}/fidl/src-gen
    /usr/local/include/CommonAPI-3.1
    /usr/local/include/vsomeip
)

add_executable(NavigationClient
	NavigationClient.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationSomeIPDeployment.cpp
)
target_link_libraries(NavigationClient CommonAPI CommonAPI-SomeIP vsomeip)


add_executable(NavigationService
	NavigationService.cpp
	NavigationStubImpl.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationSomeIPStubAdapter.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationStubDefault.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationSomeIPDeployment.cpp
)

target_link_libraries(NavigationService CommonAPI CommonAPI-SomeIP vsomeip)


