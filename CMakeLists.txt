cmake_minimum_required(VERSION 3.19)

project(sparse_list)

include_directories(".")

file(GLOB SOURCES "*.cpp")

add_executable(sparse_list ${SOURCES})

set_property(TARGET sparse_list PROPERTY CXX_STANDARD 17)
