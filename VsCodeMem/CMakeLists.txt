cmake_minimum_required(VERSION 3.15)
project(VsCodeMem)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_library(Json_LIB jsoncpp)

add_library(VsCodeMem SHARED library.cpp library.h VsPtr/VsPointer.h GarbageCollector/LinkedList.h client/JSON/jsonSerialize.cpp client/JSON/jsonSerialize.h
        GarbageCollector/GarbageCollector.cpp GarbageCollector/GarbageCollector.h client/ClientApp.cpp client/ClientApp.h client/network/ConnectServer.cpp
        client/network/ConnectServer.h)

target_link_libraries(VsCodeMem ${Json_LIB})