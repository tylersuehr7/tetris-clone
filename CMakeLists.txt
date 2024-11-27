cmake_minimum_required(VERSION 3.20)
project(tetris)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(raylib)

# Find all .cpp files in the src directory and add them to the executable
file(GLOB SOURCES "src/*.cpp")

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/
)

target_link_libraries(
    ${PROJECT_NAME} 
    raylib
)