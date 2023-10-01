cmake_minimum_required(VERSION 3.19)

project(skip_list)

include_directories(".")

file(GLOB SOURCES "*.cpp" "*.tpp")

add_executable(skip_list ${SOURCES})

set_property(TARGET skip_list PROPERTY CXX_STANDARD 20)
