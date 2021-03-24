cmake_minimum_required(VERSION 3.8)
project(Homework1)

set(CMAKE_C_FLAGS "--coverage -Wall -Werror -Wpedantic -g -pthread")

set(CMAKE_C_STANDARD 11)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(Static_onethreaded STATIC ${PROJECT_SOURCE_DIR}/src/find_average_salary.c 
${PROJECT_SOURCE_DIR}/src/sort_data.c ${PROJECT_SOURCE_DIR}/src/utils.c)

#add_library(multi_thread SHARED ${PROJECT_SOURCE_DIR}/src/sort_data_thread.c)

add_executable(prog ${PROJECT_SOURCE_DIR}/src/main.c)
target_link_libraries(prog Static_onethreaded)