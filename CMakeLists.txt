cmake_minimum_required(VERSION 3.8)
project(Future)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(SOURCE_FILES main.cpp Future.h exceptions/NoData.h exceptions/AbandonFuture.h FutureImplementation.hpp Promise.h SharedState.h PromiseImplementation.hpp)
add_executable(Future ${SOURCE_FILES})
