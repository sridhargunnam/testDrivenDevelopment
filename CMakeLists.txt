cmake_minimum_required(VERSION 3.17)
project(tdd)

set(CMAKE_CXX_STANDARD 20)

######################## Google-test start ################################################
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

######################## Google-test end ################################################
find_package(benchmark REQUIRED)
set(CMAKE_CXX_FLAGS --coverage)
set(CMAKE_CXX_FLAGS  -lpthread)


add_executable(tdd main.cpp sample1.cpp sample1.h testShuffle.cpp)
target_link_libraries(tdd gtest gtest_main benchmark::benchmark benchmark::benchmark_main)

add_executable(testShuffle  testShuffle.cpp shuffle.cpp shuffle.h)
target_link_libraries(testShuffle gtest gtest_main benchmark::benchmark benchmark::benchmark_main)