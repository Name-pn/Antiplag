cmake_minimum_required(VERSION 3.21)
project(antiplag_version_00 C)

set(CMAKE_C_STANDARD 23)

add_executable(antiplag_version_00 main.c libs/bin_tree/bt.c libs/bin_tree/bt.h libs/ht/ht.c libs/ht/ht.h)
