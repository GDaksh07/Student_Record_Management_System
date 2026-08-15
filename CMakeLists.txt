cmake_minimum_required(VERSION 4.1)
project(Student_Record_Management_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Student_Record_Management_System main.cpp
        student.cpp
        student.h)
