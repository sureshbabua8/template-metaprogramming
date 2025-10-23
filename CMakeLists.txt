cmake_minimum_required(VERSION 3.23)

project(templateMetaprogrammingPractice)

set(CMAKE_CXX_STANDARD 20)
add_executable(typeListExample type_list.cpp)
add_executable(removeDupes rm_dupes.cpp)


target_include_directories(typeListExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(typeListExample PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(removeDupes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(removeDupes PRIVATE -Wall -Wextra -Wpedantic -Werror)