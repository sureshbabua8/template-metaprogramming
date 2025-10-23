cmake_minimum_required(VERSION 3.23)

project(templateMetaprogrammingPractice)

set(CMAKE_CXX_STANDARD 20)
add_executable(templateMetaprogrammingPractice type_list.cpp)
target_include_directories(templateMetaprogrammingPractice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(templateMetaprogrammingPractice PRIVATE -Wall -Wextra -Wpedantic -Werror)