cmake_minimum_required(VERSION 2.8)

project(Route)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
include_directories(
    ${CMAKE_BINARY_DIR}/fidl/src-gen
    /usr/local/include/CommonAPI-3.1
    /usr/local/include/vsomeip

)
include_directories(${CMAKE_SOURCE_DIR}/src/da)

add_executable(RouteCalculationService
	RouteCalculationService.cpp
	RouteCalculationStubImpl.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationSomeIPStubAdapter.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationStubDefault.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationSomeIPDeployment.cpp
)

target_link_libraries(RouteCalculationService dataacess CommonAPI CommonAPI-SomeIP vsomeip)

install(TARGETS RouteCalculationService DESTINATION bin)


