cmake_minimum_required(VERSION 3.21)
project(edgetx_linux)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(edgetx_linux
        boards.h
        CMakeLists.txt
        constants.h
        lcdwidget.cpp
        lcdwidget.h
        main.cpp
        simulatorinterface.h
        )
target_link_libraries(edgetx_linux
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

