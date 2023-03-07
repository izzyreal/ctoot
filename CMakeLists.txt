cmake_minimum_required(VERSION 3.13)

include(FetchContent)

FetchContent_Declare(moduru
  GIT_REPOSITORY https://github.com/izzyreal/moduru.git
  GIT_TAG        master
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/editables/moduru
)

set(CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS ON)

FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.0
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/deps/Catch2
)

FetchContent_MakeAvailable(moduru Catch2)

project(ctoot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fPIC")

if(APPLE)
  if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    # This is not a typo. See https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE INTERNAL "Minimum iOS deployment version")
  else()
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE INTERNAL "Minimum OS X deployment version")
  endif()
endif()

## Configure main lib ##

set(_src_root_path_main "${CMAKE_CURRENT_SOURCE_DIR}/src/main")

include_directories(${_src_root_path_main} ${moduru_SOURCE_DIR}/src/main)

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
