cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
include_directories(
    ${CMAKE_BINARY_DIR}/fidl/src-gen
    /usr/local/include/CommonAPI-3.1
    /usr/local/include/vsomeip
)

add_executable(DestinationInputClient
	DestinationInputClient.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputSomeIPDeployment.cpp
)
target_link_libraries(DestinationInputClient CommonAPI CommonAPI-SomeIP vsomeip)


#add_executable(DestinationInputService
#	DestinationInputService.cpp
#	DestinationInputStubImpl.cpp
#	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputSomeIPStubAdapter.cpp
#	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputStubDefault.cpp
#	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputSomeIPDeployment.cpp
#)

#target_link_libraries(DestinationInputService CommonAPI CommonAPI-SomeIP vsomeip)


