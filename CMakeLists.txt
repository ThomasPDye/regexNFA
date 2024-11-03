cmake_minimum_required(VERSION 3.5.0)
<<<<<<< HEAD
project(RegexNFA VERSION 0.1.0 LANGUAGES CXX)
=======
project(RegexNFA VERSION 0.2.0 LANGUAGES CXX)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic)
>>>>>>> 54b58f8 (updated to remove infinite loop)

include_directories(include)

enable_testing()
add_subdirectory(src)
