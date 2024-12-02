cmake_minimum_required(VERSION 3.16)

project(finalProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
qt_standard_project_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)

qt_add_executable(pollutantsapp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/sample.cpp
    ${CMAKE_SOURCE_DIR}/src/dataset.cpp
    ${CMAKE_SOURCE_DIR}/src/model.cpp
    ${CMAKE_SOURCE_DIR}/src/window.cpp
    ${CMAKE_SOURCE_DIR}/src/stats.cpp

    ${CMAKE_SOURCE_DIR}/src/cards/overviewcard.cpp

    ${CMAKE_SOURCE_DIR}/src/pages/homepage.cpp
    ${CMAKE_SOURCE_DIR}/src/pages/overviewpage.cpp
    ${CMAKE_SOURCE_DIR}/src/pages/samplespage.cpp

    ${CMAKE_SOURCE_DIR}/include/samplespage.hpp
    ${CMAKE_SOURCE_DIR}/include/homepage.hpp
    ${CMAKE_SOURCE_DIR}/include/overviewcard.hpp
    ${CMAKE_SOURCE_DIR}/include/window.hpp
)

target_link_libraries(pollutantsapp PRIVATE Qt6::Widgets Qt6::Charts)

set_target_properties(pollutantsapp PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)
