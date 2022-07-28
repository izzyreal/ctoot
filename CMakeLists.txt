cmake_minimum_required(VERSION 3.13)

include(cmake/CPM.cmake)

CPMAddPackage("gh:izzyreal/moduru#no-conan")
CPMAddPackage("gh:catchorg/Catch2#v3.1.0")

set(CTOOT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Setting CTOOT_SOURCE_DIR")
set(CTOOT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Setting CTOOT_BINARY_DIR")

project(ctoot)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fPIC -DCATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS")

if(DEFINED ENV{APPLE_M1})
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE INTERNAL "")
endif()

if(APPLE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE INTERNAL "Minimum OS X deployment version")
endif()

## Configure main lib ##

set(_src_root_path_main "${CMAKE_CURRENT_SOURCE_DIR}/src/main")

include_directories(${_src_root_path_main} ${MODURU_SOURCE_DIR}/src/main)

link_directories(${MODURU_BINARY_DIR})

file(
    GLOB_RECURSE _source_list_main
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_src_root_path_main}/*.c*"
    "${_src_root_path_main}/*.cpp*"
    "${_src_root_path_main}/*.hpp*"
	"${_src_root_path_main}/*.hxx*"
)

foreach(_source IN ITEMS ${_source_list_main})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

if(MSVC)
	ADD_DEFINITIONS(-DUNICODE)
	ADD_DEFINITIONS(-D_UNICODE)
endif(MSVC)

add_library(ctoot ${_source_list_main})
target_link_libraries(ctoot PUBLIC moduru)

if(MSVC)
	target_compile_options(ctoot PRIVATE "/MP")
endif(MSVC)

## Configure test suite application ##

set(_src_root_path_test "${CMAKE_CURRENT_SOURCE_DIR}/src/test")

include_directories(${_src_root_path_test})

file(
    GLOB_RECURSE _source_list_test
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_src_root_path_test}/*.c*"
    "${_src_root_path_test}/*.cpp*"
    "${_src_root_path_test}/*.hpp*"
)

foreach(_source IN ITEMS ${_source_list_test})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

add_executable(ctoot-tests ${_source_list_test})
target_link_libraries(ctoot-tests ctoot Catch2::Catch2WithMain)
