cmake_minimum_required(VERSION 3.22)

project("ApiProject" 
    VERSION 1.0.0
    LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Crow REQUIRED)

#add_compile_definitions(NOMINMAX)

# Add the src directory
add_subdirectory(src)

