cmake_minimum_required(VERSION 3.25)
project(wwu_ps_semaphore_c C)

set(CMAKE_C_STANDARD 11)

add_executable(wwu_ps_semaphore_c main.c semaphore.h semaphore.c)
