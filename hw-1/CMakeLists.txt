cmake_minimum_required(VERSION 3.8)
project(People)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
SET(MYCOMPILE_FLAGS "-std=c11")
set(LIB_SOURCE_FILES project/src/Person.c project/src/CheckInput.c)
add_library(study_std_lib STATIC ${LIB_SOURCE_FILES})
include_directories(project/include)
add_executable(hw-1
    project/include/CheckInput.h
    project/include/Person.h 
    project/src/main.c)
target_link_libraries(hw-1 study_std_lib)


enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR} )
message(${GTEST_LIBRARIES})
add_executable(tests project/tests/test.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests study_std_lib)
