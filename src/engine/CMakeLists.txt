# Build file for the game engine
# The goal of this make file is for the engine to be a totally self contained project that runs independintly of client,
# To achieve this it has its own VCPkg manager and 3rd party libraries which are ONLY meant to be accessed through
# valid channels from client!

cmake_minimum_required(VERSION 3.21...3.30)

#
# specify the toolchain to use the vcpkg toolchain to allow for vcpkg to transparently integrate into CMake
#
#set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
 # CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "VCPKG Target Triplet to use")

project(MaxEngine VERSION 0.1.0 LANGUAGES C CXX)
add_library(engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
#Build the project to a specific output location based on OS target and build type
#
#set(OSBitness 32)
#if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#	set(OSBitness 64)
#endif()
#set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
#set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs") #location of compiled static libraries
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}") #Where executable files output


# make the include directory visible to modules in the engine
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
target_include_directories(engine PUBLIC ${INCLUDE_DIR})
message("Include directory is ${INCLUDE_DIR}")

#================
# Dependencies
#================
# Physx
#----------------
# PhysX does not have a find_package setup therefore we have to find it manually
# https://github.com/microsoft/vcpkg/issues/10233
include(SelectLibraryConfigurations)

set(PHYSX_LIB_RELEASE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/physx/Release/")
set(PHYSX_LIB_DEBUG_PATH "${CMAKE_SOURCE_DIR}/thirdparty/physx/Debug/")
set(PHYSX_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/physx/")

message( "PHYSX_LIB_DIR : ${PHYSX_LIB_DIR}" )
message( "PHYSX_LIB_PATH : ${PHYSX_LIB_RELEASE_PATH}" )
message( "PHYSX_LIB_DEBUG_PATH : ${PHYSX_LIB_DEBUG_PATH}" )

#I'm not sure why Dylan put this in the original project so I will investigate later
#if(MSVC)
# target_compile_options(${CMAKE_PROJECT_NAME}_client PRIVATE "/MP")
#endif()


find_library(PhysXPvdSDK_LIBRARY_RELEASE NAMES PhysXPvdSDK_64 PhysXPvdSDK_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysXPvdSDK_LIBRARY_DEBUG NAMES PhysXPvdSDK_64 PhysXPvdSDK_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysXPvdSDK)

find_library(PhysXExtensions_LIBRARY_RELEASE NAMES PhysXExtensions_64 PhysXExtensions_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysXExtensions_LIBRARY_DEBUG NAMES PhysXExtensions_64 PhysXExtensions_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysXExtensions)

find_library(PhysXFoundation_LIBRARY_RELEASE NAMES PhysXFoundation_64 PhysXFoundation_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysXFoundation_LIBRARY_DEBUG NAMES PhysXFoundation_64 PhysXFoundation_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysXFoundation)

find_library(PhysXCommon_LIBRARY_RELEASE NAMES PhysXCommon_64 PhysXCommon_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysXCommon_LIBRARY_DEBUG NAMES PhysXCommon_64 PhysXCommon_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysXCommon)

find_library(PhysXVehicle2_LIBRARY_RELEASE NAMES PhysXVehicle2_64 PhysXVehicle2_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysXVehicle2_LIBRARY_DEBUG NAMES PhysXVehicle2_64 PhysXVehicle2_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysXVehicle2)

find_library(PhysXCooking_LIBRARY_RELEASE NAMES PhysXCooking_64 PhysXCooking_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysXCooking_LIBRARY_DEBUG NAMES PhysXCooking_64 PhysXCooking_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysXCooking)

find_library(PhysX_LIBRARY_RELEASE NAMES PhysX_64 PhysX_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_RELEASE_PATH} NO_DEFAULT_PATH REQUIRED)
find_library(PhysX_LIBRARY_DEBUG NAMES PhysX_64 PhysX_static_64 PATH_SUFFIXES lib PATHS ${PHYSX_LIB_DEBUG_PATH} NO_DEFAULT_PATH REQUIRED)
select_library_configurations(PhysX)

target_link_libraries(engine PRIVATE 
	${PhysXPvdSDK_LIBRARY} ${PhysXExtensions_LIBRARY} ${PhysXFoundation_LIBRARY} ${PhysXCommon_LIBRARY} ${PhysXCooking_LIBRARY} ${PhysXVehicle2_LIBRARY}  ${PhysX_LIBRARY} 
)

#copy dlls and link
add_custom_command(TARGET engine PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PHYSX_LIB_DIR}$<CONFIGURATION>/shared/" $<TARGET_FILE_DIR:engine>/libs
) 

#----------------
# glm
#----------------
find_package(glm CONFIG REQUIRED)

#==============================
# compile the sub-systems that make up the engine
#==============================
#add_subdirectory("messages")
add_subdirectory("core")

target_link_directories(engine PRIVATE "${BINARY_DIR}/libs")
target_link_libraries(engine PUBLIC glm::glm)


