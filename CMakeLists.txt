cmake_minimum_required(VERSION 3.10)

project(YourProjectName)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Ellen: had to add standard, otherwise my make throws errors that havent been an issue since c++ 98
set(CMAKE_CXX_STANDARD 17)

# produce non-optimized code with debug symbols, !!this is possibly not needed
set(CMAKE_BUILD_TYPE Debug)

# Add your source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp" "fonts/*.ttf" "textures/*.png" "assets/*.csv")

# Exclude map.cpp and map.hpp
#list(FILTER SOURCES EXCLUDE REGEX "src/map.cpp")
#list(FILTER SOURCES EXCLUDE REGEX "include/map.hpp")

# Create executable
add_executable(TD ${SOURCES})

# Link SFML
target_link_libraries(TD PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Set include directories
target_include_directories(TD PRIVATE include)