cmake_minimum_required(VERSION 2.6)

project(QtSearcher)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(QtSearcher qtsearcher.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(QtSearcher Qt5::Widgets)