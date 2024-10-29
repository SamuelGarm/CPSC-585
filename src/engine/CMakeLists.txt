# Build file for the game engine
# The goal of this make file is for the engine to be a totally self contained project that runs independintly of client,
# To achieve this it has its own VCPkg manager and 3rd party libraries which are ONLY meant to be accessed through
# valid channels from client!

cmake_minimum_required(VERSION 3.24)
project(TempEngine VERSION 0.1.0)

#
# specify the toolchain to use the vcpkg toolchain to allow for vcpkg to transparently integrate into CMake
#
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "VCPKG Target Triplet to use")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
#Build the project to a specific output location based on OS target and build type
#
set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs") #location of compiled static libraries
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}") #Where executable files output

# Dependencies
add_library(${PROJECT_NAME} STATIC)

# systems that make up the engine
add_subdirectory("messages")

# make the include directory visible to modules in the engine
target_include_directories(${PROJECT_NAME} PUBLIC "include")


#target_link_libraries(${PROJECT_NAME} PRIVATE messages_sys)