cmake_minimum_required(VERSION 3.5)
project(doomU)

set(CMAKE_CXX_STANDARD 11)

file(GLOB project_sources src/doomu/*/*.c include/doomu/*/*.h)
set(SOURCE_FILES ${project_sources})

file(GLOB project_tests test/doomu/*/*.*pp test/Catch/catch.hpp)
set(TEST_FILES ${project_tests})


#### Dependencies ####

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

####

# Create executable for testing purposes
#add_executable(run_all_tests ${SOURCE_FILES})
add_executable(run_all_tests ${SOURCE_FILES} ${TEST_FILES})

target_link_libraries(run_all_tests ${CURL_LIBRARY})
