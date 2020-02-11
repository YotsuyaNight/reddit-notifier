cmake_minimum_required(VERSION 3.14.0)
project(rn)
set(CMAKE_CXX_STANDARD 11)

# Build type stuff
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Qt5 Stuff
find_package(Qt5 COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Target stuff
set(CMAKE_INSTALL_RPATH .)
set(SOURCES
        resources/resources.qrc
        src/mainwindow.ui
        src/mainwindow.cpp
        src/traycontroller.cpp
)
include_directories(src)
add_executable(app main.cpp ${SOURCES})
target_link_libraries(app Qt5::Widgets)
