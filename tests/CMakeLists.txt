cmake_minimum_required(VERSION 3.14.0)
project(rn_tests)

# Testing
set(TESTSOURCES
    redditqueryingtest.cpp
    configstest.cpp
)

find_package(Catch2 REQUIRED)
add_executable(test main.cpp ${TESTSOURCES})
target_link_libraries(test core Catch2::Catch2 Qt5::Test)
