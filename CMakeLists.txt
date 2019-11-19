cmake_minimum_required(VERSION 3.2)

project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

message("**** START CREATE MAKEFILE FOR ${PROJECT_NAME}: version=${PROJECT_VERSION}; build_number=${PROJECT_VERSION_PATCH} ****")
message("************************************************************************")

add_executable(print_ip main.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "halecky@mail.ru")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
