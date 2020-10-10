cmake_minimum_required(VERSION 3.10)
project(IpFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(src)
add_executable(ip_filter src/ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
# include build directory to use when compiling given target
target_include_directories(ip_filter PRIVATE ${CMAKE_BINARY_DIR})

target_include_directories(ip_filter PRIVATE ${Boost_INCLUDE_DIRS})

#installation rules for the project
install(TARGETS ip_filter DESTINATION bin)

#Debian package
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT phyaroslavtsev@gmail.com)

#module generates binary and source installers
include(CPack)

