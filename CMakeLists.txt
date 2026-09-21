cmake_minimum_required(VERSION 3.16)
project(dustbunny LANGUAGES C)

add_library(
	dustbunny STATIC
	include/libdustbunny/nodes.h
	include/libdustbunny/tokens.h
	include/libdustbunny/debug.h
	src/nodes.c
	src/tokens.c
	src/debug.c
)

target_include_directories(
	dustbunny PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
