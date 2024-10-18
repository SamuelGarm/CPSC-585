cmake_minimum_required(VERSION 3.24)
# specify the toolchain to use the vcpkg toolchain to allow for vcpkg to transparently integrate into CMake
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "VCPKG Target Triplet to use")

project(MaximusOverdrive VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Build the project to a specific output location based on OS target and build type
set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs") #location of compiled static libraries
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}") #Where executable files output

set(SOURCE_FILES 
	src/client/main.cpp)
#dependencies
add_subdirectory(src/engine/messages)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} messages)