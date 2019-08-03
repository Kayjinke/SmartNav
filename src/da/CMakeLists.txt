cmake_minimum_required(VERSION 2.8)

add_library(dataacess SHARED dataaccess.cpp)

target_link_libraries(dataacess PocoXML PocoFoundation)

add_executable(dataacess_test main.cpp)

target_link_libraries(dataacess_test dataacess)

install(TARGETS dataacess DESTINATION bin)
install(TARGETS dataacess_test DESTINATION bin)
