cmake_minimum_required(VERSION 3.16)
project(ServerMemoryManager)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(PkgConfig REQUIRED)
find_library(Crypto_LIB cryptopp)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(SOURCE_FILES main.cpp messages/GarbageCollector/GarbageCollector.h messages/GarbageCollector/GarbageCollector.cpp messages/GarbageCollector/LinkedList.h messages/GarbageCollector/Node.h messages/GarbageCollector/VsPointer.h network/ServerListener.cpp network/ServerListener.h messages/ServerApp.cpp messages/ServerApp.h messages/json/jsonMachine.cpp messages/json/jsonMachine.h)
add_executable(ServerMemoryManager ${SOURCE_FILES})

target_link_libraries(ServerMemoryManager ${JSONCPP_LIBRARIES} "${Crypto_LIB}")

