cmake_minimum_required(VERSION 3.15)
project(StudyPlanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(StudyPlanner
    main.cpp
    src/TaskManager.cpp
)

target_link_libraries(StudyPlanner PRIVATE raylib)