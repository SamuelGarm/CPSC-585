cmake_minimum_required(VERSION 3.16)

project(MaximusOverdrive VERSION 0.1.1)

#Build the project to a specific output location based on OS target and build type
set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs") #location of compiled static libraries
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}") #Where executable files output
add_executable(${PROJECT_NAME} src/main.cpp)