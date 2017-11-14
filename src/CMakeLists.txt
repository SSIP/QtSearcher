cmake_minimum_required(VERSION 2.6)

project(QtSearcher)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(QtSearcher qtsearcher.cpp statuswindow.cpp helpers.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(QtSearcher Qt5::Widgets)

add_library(libimse SHARED IMPORTED)
set_target_properties(libimse PROPERTIES IMPORTED_LOCATION /usr/local/lib/libimse.so)
target_link_libraries(QtSearcher libimse)
SET(GCC_COVERAGE_COMPILE_FLAGS "-g -rdynamic") 