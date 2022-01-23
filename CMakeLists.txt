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
        REQUIRED
        )

find_package("SDL")
message(STATUS "SDL Lib: ${SDL_LIBRARY}; Headers: ${SDL_INCLUDE_DIR}; Version: ${SDL_VERSION_STRING}")
include_directories(${SDL_INCLUDE_DIR})

add_executable(edgetx_linux
        boards.h
        CMakeLists.txt
        constants.h
        lcdwidget.cpp
        lcdwidget.h
        main.cpp
        simulatorinterface.h
        joystick.h
        joystick.cpp
        )
target_link_libraries(edgetx_linux
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${SDL_LIBRARY}
        )

