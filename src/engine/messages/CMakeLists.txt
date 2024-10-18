cmake_minimum_required(VERSION 3.24)
project(messages)

set(SOURCE_FILES
	src/hello.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
 target_include_directories(${PROJECT_NAME} PUBLIC include)