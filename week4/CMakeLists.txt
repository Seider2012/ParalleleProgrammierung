cmake_minimum_required(VERSION 3.15)
project(week4 C)

#set(CMAKE_C_STANDARD 99)
# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -O0 -fopenmp")

add_executable(main main.c)
add_executable(EX2 EX2.c)
add_executable(EX2Clo EX2Clo.c)
add_executable(EX2Spr EX2Spr.c)
add_executable(EX3Seq EX3Seq.c)
add_executable(EX3Par EX3Par.c)
add_executable(EX2M EX2M.c)

message(STATUS "Checking OpenMP")
find_package(OpenMP)
IF(OPENMP_FOUND)
    message("Found OpenMP!")
    # add flags for OpenMP
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ELSE()
    message("Missed OpenMP!")
ENDIF()