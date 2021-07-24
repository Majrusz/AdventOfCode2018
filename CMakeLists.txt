cmake_minimum_required(VERSION 3.17)
project(AdventOfCode2018)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(AdventOfCode2018 main.cpp common/file_loader.inl common/file_loader.h tasks/day01/day_01.cpp tasks/day01/day_01.h tasks/all_days.h tasks/day02/day_02.cpp tasks/day02/day_02.h common/pair_iterator.inl common/pair_iterator.h common/zipper.inl common/zipper.h)