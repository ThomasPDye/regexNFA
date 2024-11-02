cmake_minimum_required(VERSION 3.5.0)
project(RegexNFA VERSION 0.1.0 LANGUAGES CXX)

include_directories(include)

enable_testing()
add_subdirectory(src)
