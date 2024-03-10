cmake_minimum_required(VERSION 3.10)

project(code_factory)

add_executable(tuple2pod pod_tuple_transfer/tuple2pod.cpp)

add_executable(integer_sequence integer_sequence/main.cpp)