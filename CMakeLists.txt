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
find_package(Qt5 REQUIRED Widgets Network Test)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Target stuff
set(CMAKE_INSTALL_RPATH .)
set(SOURCES
        src/post.cpp
        src/postparser.cpp
        src/redditquery.cpp
        src/watcher.cpp
        src/postlistmodel.cpp
)
set(UISOURCES
        ui/mainwindow.ui
        ui/mainwindow.cpp
        ui/traycontroller.cpp
        resources/resources.qrc
)
include_directories(src ui)
add_library(core STATIC ${SOURCES})
target_link_libraries(core Qt5::Widgets Qt5::Network)
add_executable(app main.cpp ${UISOURCES})
target_link_libraries(app core)

add_subdirectory(tests)
