cmake_minimum_required(VERSION 3.26)

project(ExerciseGameUsingMotionDetection LANGUAGES C CXX)

# Set the available build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "Limited Configs" FORCE)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

if(MSVC)
	add_compile_options(/EHsc)
endif()

# Use the generator expression $<0:> so that the specified folder is used directly, without any configuration-dependent suffix.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")

find_package(OpenCV CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

add_subdirectory("Application")