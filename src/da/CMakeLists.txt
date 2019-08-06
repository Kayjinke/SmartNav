cmake_minimum_required(VERSION 2.8)

add_library(dataacess SHARED dataaccess.cpp)

target_link_libraries(dataacess PocoXML PocoFoundation)

add_executable(dataacess_test main.cpp)

target_link_libraries(dataacess_test dataacess)




add_library(datareadLib SHARED dataread.cpp)

add_executable(dataread main2.cpp dataread.cpp)

target_link_libraries(dataread datareadLib dataacess)

install(TARGETS dataacess DESTINATION bin)
install(TARGETS dataacess_test DESTINATION bin)
install(TARGETS dataread DESTINATION bin)
