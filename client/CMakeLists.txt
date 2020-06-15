cmake_minimum_required(VERSION 3.16)
project(ClientSide)
set(CMAKE_CXX_STANDARD 14)

find_library(Json_LIB jsoncpp)

set(SOURCE_FILES main.cpp network/ConnectServer.cpp network/ConnectServer.h ClientApp.cpp ClientApp.h JSON/jsonSerialize.cpp JSON/jsonSerialize.h JSON/Nodo.h)

add_executable(ClientSide ${SOURCE_FILES})
target_link_libraries(ClientSide ${Json_LIB})