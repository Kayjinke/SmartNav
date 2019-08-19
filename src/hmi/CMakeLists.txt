cmake_minimum_required(VERSION 2.8)

project(NavigationHMI)

find_package(Qt5 COMPONENTS Core Gui Xml Multimedia REQUIRED)
find_package(Qt5Widgets)


SET(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src/da)


SET(NavigationHMI_SOURCES main.cpp widget.cpp destinationinput.cpp map.cpp UIChinaCity.cpp music.cpp)
SET(NavigationHMI_HEADERS widget.h destinationinput.h map.h UIChinaCity.h music.h)
SET(NavigationHMI_FORMS   widget.ui destinationinput.ui map.ui music.ui)

qt5_wrap_cpp(NavigationHMI_HEADERS_MOC ${NavigationHMI_HEADERS})
qt5_wrap_ui(NavigationHMI_FORMS_HEADERS ${NavigationHMI_FORMS})


add_executable(NavigationHMI ${NavigationHMI_SOURCES} ${NavigationHMI_HEADERS} ${NavigationHMI_HEADERS_MOC} ${NavigationHMI_HEADERS_MOC}
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/DestinationInputSomeIPDeployment.cpp    
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/RouteCalculationSomeIPDeployment.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/PositionSomeIPProxy.cpp
	${CMAKE_BINARY_DIR}/fidl/src-gen/v1/commonapi/PositionSomeIPDeployment.cpp
	)

QT5_USE_MODULES(NavigationHMI Core Gui Xml Widgets Multimedia)

target_link_libraries(NavigationHMI dataacess CommonAPI CommonAPI-SomeIP vsomeip)

install(TARGETS NavigationHMI DESTINATION bin)


