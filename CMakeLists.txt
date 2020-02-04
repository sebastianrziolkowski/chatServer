cmake_minimum_required(VERSION 3.15)
project(chatServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(chatServer main.cpp resources/static/functionalNames.h resources/static/staticSymbols.h resources/static/serverInfo.h services/stringServices.h models/client.h resources/properties.h services/socketServices.h)

target_link_libraries(chatServer wsock32 ws2_32)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")