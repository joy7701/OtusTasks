cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(src/version.h.in ${CMAKE_SOURCE_DIR}/src/version.h)

include_directories(src)
add_executable(helloworld src/main.cpp)
add_library(helloworld_lib
	src/lib.cpp
	src/lib.h
)
add_executable(test_version src/test_version.cpp)

set_target_properties(helloworld test_version PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)
set_target_properties(test_version PROPERTIES
COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
# include build directory to use when compiling given target
target_include_directories(helloworld PRIVATE ${CMAKE_BINARY_DIR})

#linker link API with libraries
target_link_libraries(helloworld PRIVATE helloworld_lib)

target_link_libraries(test_version
	Boost::unit_test_framework
	helloworld_lib)

target_include_directories(helloworld PRIVATE ${Boost_INCLUDE_DIRS})

#installation rules for the project
install(TARGETS helloworld DESTINATION bin)

#Debian package
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT phyaroslavtsev@gmail.com)

#module generates binary and source installers
include(CPack)

enable_testing()

add_test(test_version test_version)
