cmake_minimum_required(VERSION 3.10)
PROJECT(network)

#ADD_SUBDIRECTORY(src)

ADD_DEFINITIONS("-std=c++11")
SET(INCLUDE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs/gtest/include)
SET(LIBS ${CMAKE_SOURCE_DIR}/libs/gtest/libs)

INCLUDE_DIRECTORIES(${INCLUDE})
LINK_DIRECTORIES(${LIBS})
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(server)
ADD_SUBDIRECTORY(client)
ADD_SUBDIRECTORY(common)

ADD_EXECUTABLE(network main.cpp)
#TARGET_INCLUDE_DIRECTORIES(leetcode PUBLIC ${INCLUDE})
TARGET_LINK_LIBRARIES(network common server client test gtest)
