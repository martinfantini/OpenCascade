cmake_minimum_required(VERSION 3.8)

project(QtVtkViewer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# List source files & resources
file (GLOB Sources *.cpp)
file (GLOB Headers *.h)
file (GLOB Resources *.qrc)
file (GLOB UIs *.ui)

# Find package Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# OpenCascade
find_package(OpenCASCADE EXACT PATHS /usr/local/lib)

# Use Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find package VTK
find_package(VTK
    9.0
    REQUIRED
    COMPONENTS
        InteractionStyle
        RenderingOpenGL2
        CommonCore
        RenderingCore
        CommonExecutionModel
        GUISupportQt
        IOLegacy)

if (NOT OpenCASCADE_FOUND)
    message (FATAL_ERROR "coult not find OpenCASCADE, please set OpenCASCADE_DIR variable" )
else()
    message (STATUS "Using OpenCASCADE from \"${OpenCASCADE_INSTALL_PREFIX}\"" )
    message (STATUS "OpenCASCADE_INCLUDE_DIR=${OpenCASCADE_INCLUDE_DIR}")
    message (STATUS "OpenCASCADE_LIBRARY_DIR=${OpenCASCADE_LIBRARY_DIR}")
    INCLUDE_DIRECTORIES(${OpenCASCADE_INCLUDE_DIR})
endif()

# Build executable
add_executable(QtVtkViewer WIN32 ${Sources} ${Headers} ${Resources} ${UIs})

target_link_libraries(QtVtkViewer PRIVATE Qt5::Widgets Qt5::OpenGL VTK::GUISupportQt VTK::IOLegacy ${OpenCASCADE_LIBRARIES})

vtk_module_autoinit(
    TARGETS QtVtkViewer
    MODULES VTK::GUISupportQt VTK::IOLegacy)
