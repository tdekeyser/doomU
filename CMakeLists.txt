cmake_minimum_required(VERSION 3.5)
project(doomU)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

file(GLOB project_sources src/*/*.c include/*.h)
set(SOURCE_FILES ${project_sources})

file(GLOB project_tests test/*/*.*pp test/Catch/catch.hpp)
set(TEST_FILES ${project_tests})


#### Dependencies ####
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)


#### Build executable
option(SOURCE "Only builds executable with source files." OFF)
option(TEST "Compile all tests and build executable that runs all tests." OFF)

if (SOURCE)
    add_executable(doomU ${SOURCE_FILES} src/main.c)
    target_link_libraries(doomU ${CURL_LIBRARY})
endif()
if (TEST) # Create executable for testing purposes
    add_executable(doomU_test ${SOURCE_FILES} ${TEST_FILES} test/main_test.cpp)
    target_link_libraries(doomU_test ${CURL_LIBRARY})
endif()

