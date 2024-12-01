cmake_minimum_required(VERSION 3.10)
project(Regex VERSION 0.2.0 LANGUAGES CXX)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include)

enable_testing()
add_subdirectory(src)
