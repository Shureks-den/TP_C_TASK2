set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage --coverage")
set(CMAKE_CXX_STANDARD 17)
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${file}
    "${PROJECT_SOURCE_DIR}/test/main.cpp")
  target_link_libraries("${name}_tests" gtest_main Static_onethreaded)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()