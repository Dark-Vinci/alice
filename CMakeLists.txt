cmake_minimum_required(VERSION 3.29)
project(passwordmanager)

set(CMAKE_CXX_STANDARD 20)

add_executable(passwordmanager main.cpp
        service.h
        database.h
        controller.h
        util.h
        controller.cpp
        ui.cpp
        database.cpp
        service.cpp
        util.cpp)
