# -------------------- #
# (C)2022 madoodia.com #
# -------------------- #

cmake_minimum_required (VERSION 3.17)
cmake_policy(VERSION 3.17)

project($ENV{PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(WIN32)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

include_directories(
	core2
	includes
)

link_directories(
	libs
)

set(SOURCES
    src/main.cpp
		"includes/nolib.cpp" # related to the project, so no need to creat static lib from it
)

# if you want to build static library of core2/api2.cpp
add_library(API2 STATIC "core2/api2.cpp") # needs to create static lib from this file
# set(LIBS ${LIBS} API2) # no need to add it to LIBS, because it will automatically added to libs folder

if(WIN32)
  set(LIBS API API2) # API is built before and we put API.lib in the libs dir
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_executable($ENV{PROJECT_NAME} ${SOURCES})
target_link_libraries($ENV{PROJECT_NAME} ${LIBS})

