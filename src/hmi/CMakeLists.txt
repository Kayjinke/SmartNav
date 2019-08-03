cmake_minimum_required(VERSION 2.8)

project(NavigationHMI)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt5Widgets)

SET(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})


SET(NavigationHMI_SOURCES main.cpp widget.cpp destinationinput.cpp map.cpp)
SET(NavigationHMI_HEADERS widget.h destinationinput.h map.h)
SET(NavigationHMI_FORMS   widget.ui destinationinput.ui map.ui)

qt5_wrap_cpp(NavigationHMI_HEADERS_MOC ${NavigationHMI_HEADERS})
qt5_wrap_ui(NavigationHMI_FORMS_HEADERS ${NavigationHMI_FORMS})


add_executable(NavigationHMI ${NavigationHMI_SOURCES} ${NavigationHMI_HEADERS} ${NavigationHMI_HEADERS_MOC} ${NavigationHMI_HEADERS_MOC}
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/NavigationSomeIPDeployment.cpp    
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationSomeIPDeployment.cpp
	)

QT5_USE_MODULES(NavigationHMI Core Gui Widgets)

target_link_libraries(NavigationHMI CommonAPI CommonAPI-SomeIP vsomeip)

install(TARGETS NavigationHMI DESTINATION bin)


