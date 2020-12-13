FILE(GLOB SRC "*.cpp")
ADD_LIBRARY(client ${SRC})

ADD_EXECUTABLE(cli main.cpp)
TARGET_LINK_LIBRARIES(cli client)
