cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 11)
project(client)

include_directories(include)

set(SOURCE_FILES
        client/main.c
        client/client.c)

set(SOURCE_FILES_UI
        client/Gui/main.cpp)

add_executable(client ${SOURCE_FILES})

add_executable(test_ui ${SOURCE_FILES_UI})


