cmake_minimum_required(VERSION 3.15)
set(PROJECT count_predicates)
project(&{PROJECT})

set(CMAKE_CXX_STANDARD 14)

set (HEADERS
	ERRORS/error_msg.h
	File_Work/work_with_bin.h
	interface/interface.h
	configuration/config.h
	)
	
set (SOURCES
	ERRORS/error_msg.c
	File_Work/work_with_bin.c
	interface/interface.c
	)
	
#Compilation flags
#Release
set(RELEASE_CXX_FLAGS "-std=c++14 -Wall -Werror -pedantic")
set(RELEASE_C_FLAGS "-std=c99 -Wall -Werror -pedantic")
#Debug
set(DEBUG_CXX_FLAGS "-std=c++14 -pthread -g3")
set(DEBUG_C_FLAGS "-std=c99 -pthread -g3")

set(CMAKE_CXX_OUTPUT_EXTENSION 1)
add_compile_options(-pthread)

#Options

#library type
option(BUILD_STATIC_LIBS "Build the static library" ON)
option(BUILD_SHARED_LIBS "Build the shared library" ON)

# build static and dynamic lib
if (BUILD_STATIC_LIBS MATCHES ON)
	message(STATUS "Type lib : STATIC LIB")
	add_library(count_predicate_occurance_sequential STATIC
		CalculatePredicate/sequential_predicate.h
		CalculatePredicate/sequential_predicate.c
		)
	target_include_directories(count_predicate_occurance_sequential PRIVATE "${PROJECT_SOURCE_DIR}")
endif()

if (BUILD_SHARED_LIBS MATCHES ON) 
	message(STATUS "Type lib : SHARED LIB")
	include(GenerateExportHeader)
	add_library(count_predicate_occurance_parallel SHARED
		CalculatePredicate/parallel_predicate.h
		CalculatePredicate/parallel_predicate.c
		)
	target_include_directories(count_predicate_occurance_parallel PRIVATE "${PROJECT_SOURCE_DIR}")
endif()

# target build

file(GLOB SRC_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/test"
	)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Debug)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_CXX_FLAGS}")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEBUG_C_FLAGS}")
	
	add_executable (&{PROJECT}
		main.c
		&{SOURCES}
		)
	
	TARGET_LINK_LIBRARIES(${PROJECT}
		count_predicate_occurance_sequential
		count_predicate_occurance_parallel
		)
	
elseif (CMAKE_BUILD_TYPE MATCHES Test)

	if (CMAKE_VERSION VERSION_LESS 3.2)
		set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
	else()
		set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
	endif()
	
	include(DownloadProject.cmake)
	download_project(PROJ googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG master
		${UPDATE_DISCONNECTED_IF_AVAILABLE}
		)
	
	set(gtest_forced_shared_crt ON CACHE BOOL "" FORCE)
	
	add_subdirectory(${googletest_SOURCE_DIR} ${google_BINARY_DIR})
	
	if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories("${gtest_SOURCE_DIR}/include"
			"${gmock_SOURCE_DIR}/include")
	endif()
	
	#set flags
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEBUG_C_FLAGS} -fprofile-arcs -ftest-coverage")
	
	
	add_executable(${PROJECT}
		test/stresstesting.cpp
		test/unit_testing.cpp
		test/launch_tests_main.cpp
		${SOURCES}
		)
	
	target_link_libraries(${PROJECT}
		gtest
		gmock_main
		count_predicate_occurance_sequential
		count_predicate_occurance_parallel
		)
		
	add_test(run_tests run_tests)
	
elseif (CMAKE_BUILD_TYPE MATCHES Release)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_CXX_FLAGS}")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RELEASE_C_FLAGS}")
	add_executable (${PROJECT}
		main.c
		${SOURCES}
		)

endif()

target_include_directories(${PROJECT} PUBLIC "${PROJECT_SOURCE_DIR}")


