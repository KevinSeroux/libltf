cmake_minimum_required(VERSION 2.6)

project(ltf)

# Thanks to SFML for this macro
macro(set_option var default type docstring)
	if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

set_option("BUILD_MODE" "SHARED" STRING "Choose between SHARED or STATIC")

if(NOT ${BUILD_MODE} MATCHES "SHARED")
	if(NOT ${BUILD_MODE} MATCHES "STATIC")
		message(FATAL_ERROR "Please choose between SHARED or STATIC for BUILD_MODE")
	endif()
endif()

include_directories(include)

file(
	GLOB_RECURSE
	source_files
	src/*
	include/*
)

add_library(
	${CMAKE_PROJECT_NAME}
	${BUILD_MODE}
	${source_files}
)