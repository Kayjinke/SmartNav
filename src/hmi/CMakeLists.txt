cmake_minimum_required(VERSION 2.8)

project(NavigationHMI)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt5Widgets)

#SET(CMAKE_AUTOMOC ON)
#SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})


SET(NavigationHMI_SOURCES main.cpp widget.cpp)
SET(NavigationHMI_HEADERS widget.h)
SET(NavigationHMI_FORMS   widget.ui)

QT5_WRAP_CPP(NavigationHMI_HEADERS_MOC ${NavigationHMI_HEADERS})
QT5_WRAP_UI(NavigationHMI_FORMS_HEADERS ${NavigationHMI_FORMS})

add_executable(NavigationHMI ${NavigationHMI_SOURCES} ${NavigationHMI_HEADERS} ${NavigationHMI_HEADERS_MOC} ${NavigationHMI_HEADERS_MOC})

target_link_libraries(NavigationHMI ${QT_LIBRARIES})


