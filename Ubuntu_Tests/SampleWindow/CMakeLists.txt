cmake_minimum_required(VERSION 3.8)

project(QtTests)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# List source files & resources
file (GLOB Sources *.cpp)
file (GLOB Headers *.hpp)

# Find package Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Use Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(QtTests ${Sources} ${Headers})

target_link_libraries(QtTests PRIVATE Qt5::Widgets Qt5::Core)
