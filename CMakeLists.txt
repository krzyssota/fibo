cmake_minimum_required(VERSION 3.14)
project(jnpFibo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")

add_executable(jnpFibo main.cpp fibo.cc fibo.h)
#add_executable(jnpFibo fibo.cc)
#add_executable(jnpFibo main.cpp)