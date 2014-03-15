project(WakeOnLAN)

cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild)

include_directories($ENV{BOOST_ROOT}/)
set(Boost_USE_STATIC_LIBS ON)

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources main.cpp WakeOnLAN.cpp WakeOnLANTest.cpp)

add_executable(wol ${sources})

find_package(Boost $ENV{BOOST_VERSION} COMPONENTS filesystem system regex)
target_link_libraries(wol ${Boost_LIBRARIES})
target_link_libraries(wol gmock)
target_link_libraries(wol gtest)
target_link_libraries(wol pthread)

