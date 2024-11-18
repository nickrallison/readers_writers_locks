cmake_minimum_required(VERSION 3.29)
project(CPSC457_A4 C)

set(CMAKE_C_STANDARD 23)

# compile with this command: gcc -pthread main.c semaphore.c sol1.c sol2.c sol3.c -o rw_solutions

add_executable(CPSC457_A4 main.c semaphore.c semaphore.h sol1.c sol2.c sol3.c)


