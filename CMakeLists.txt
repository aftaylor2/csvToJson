cmake_minimum_required(VERSION 3.10)
project(CSVToJson C)

set(CMAKE_C_STANDARD 99)

# Add source files
set(SOURCES
    src/csvToJSON.c
    src/csvToJSON_lib.c
    src/test_csvToJSON.c
)

# Create executable
add_executable(csvToJSON ${SOURCES})

# Link libraries
find_package(CURL REQUIRED)
target_link_libraries(csvToJSON CURL::libcurl)
