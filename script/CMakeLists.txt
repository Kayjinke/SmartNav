cmake_minimum_required(VERSION 2.8)

install(PROGRAMS start_services.sh DESTINATION bin)
install(PROGRAMS stop_services.sh DESTINATION bin)
install(PROGRAMS start_hmi.sh DESTINATION bin)

install(PROGRAMS stop_hmi.sh DESTINATION bin)
install(PROGRAMS start_all.sh DESTINATION bin)
install(PROGRAMS stop_all.sh DESTINATION bin)

