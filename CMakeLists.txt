cmake_minimum_required(VERSION 3.16)

project(cwk2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)

qt_add_executable(quaketool
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/sample.cpp
    ${CMAKE_SOURCE_DIR}/src/dataset.cpp
    ${CMAKE_SOURCE_DIR}/src/model.cpp
    ${CMAKE_SOURCE_DIR}/src/window.cpp
    ${CMAKE_SOURCE_DIR}/src/stats.cpp
    ${CMAKE_SOURCE_DIR}/src/homepage.cpp
    ${CMAKE_SOURCE_DIR}/src/overviewpage.cpp
    ${CMAKE_SOURCE_DIR}/src/samplespage.cpp

    ${CMAKE_SOURCE_DIR}/include/window.hpp
)

target_link_libraries(quaketool PRIVATE Qt6::Widgets)

set_target_properties(quaketool PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)
