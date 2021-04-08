cmake_minimum_required(VERSION 3.8)
project(transposition_matrix)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-pthread  -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pthread -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
SET(MYCOMPILE_FLAGS "-std=c11")

include_directories(project/include)

add_library(count_predicate_occur_sequential STATIC
    project/source/sequential_predicate.c
    project/source/error_msg.c
    project/include/error_msg.h
    project/include/count_predicate.h
    project/include/work_with_bin.h
    project/source/work_with_bin.c
    )

add_library(work_with_bin STATIC
    project/source/work_with_bin.c
    project/include/work_with_bin.h
    )

add_library(count_predicate_occur_parallel SHARED
    project/source/parallel_predicate.c
    project/source/error_msg.c
    project/include/error_msg.h
    project/include/work_with_bin.h
    project/source/work_with_bin.c
    )


add_executable(sequential
    project/source/main.c)

add_executable(parallel
    project/source/main.c)


target_link_libraries(sequential count_predicate_occur_sequential)
target_link_libraries(parallel count_predicate_occur_parallel)


enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})

add_executable(stress_test
	project/test/stresstesting.cpp
	project/source/sequential_predicate.c
	)

add_executable(test_sequential
	project/test/unit_testing.cpp
	project/source/sequential_predicate.c
	)
	
add_executable(test_parallel
	project/test/unit_testing.cpp
	project/source/parallel_predicate.c
	)

target_link_libraries(stress_test dl count_predicate_occur_sequential count_predicate_occur_parallel ${GTEST_LIBRARIES} work_with_bin)
target_link_libraries(test_sequential ${GTEST_LIBRARIES} count_predicate_occur_sequential work_with_bin)
target_link_libraries(test_parallel ${GTEST_LIBRARIES} count_predicate_occur_parallel work_with_bin)


