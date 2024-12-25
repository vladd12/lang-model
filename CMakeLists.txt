# Project definition and settings
cmake_minimum_required(VERSION 3.15)
project(lang-model VERSION 0.1 LANGUAGES CXX)

# Language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding path for cmake scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Library's options
option(LANG_MODEL_STATIC_BUILD        "Build lang-model as static library"      OFF)
option(LANG_MODEL_BUILD_INTERPRETER   "Build interpreter with using lang-model"  ON)
option(LANG_MODEL_BUILD_AST_GENERATOR "Build AST generator for lang-model"       ON)
option(LANG_MODEL_BUILD_TESTS         "Build tests for avm-editor library"       ON)

# Getting dependencies
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(get_magic_enum) # Getting magic_enum library
include(get_conan)      # Getting cmake-conan
include(get_boost)      # Getting boost library with conan
include(get_fmt)        # Getting fmt library

find_package(Boost COMPONENTS boost program_options REQUIRED) # Finding boost

# Collecting project's public headers
set(LANG_MODEL_HDR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}")
set(LANG_MODEL_PUBLIC_HEADERS
  # Core features
  "${LANG_MODEL_HDR_DIR}/export.hpp"
  # Work with files and this parsing
  "${LANG_MODEL_HDR_DIR}/parser/file_reader.hpp"
  "${LANG_MODEL_HDR_DIR}/parser/scanner.hpp"
  "${LANG_MODEL_HDR_DIR}/parser/token.hpp"
  # Some interpreter and compilator tools
  "${LANG_MODEL_HDR_DIR}/utils/error_handler.hpp"
  "${LANG_MODEL_HDR_DIR}/utils/interpreter.hpp"
  # AST tools
  "${LANG_MODEL_HDR_DIR}/ast/expression.hpp"
)

# Collecting project's sources
set(LANG_MODEL_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LANG_MODEL_SOURCES
  # Work with files and this parsing
  "${LANG_MODEL_SRC_DIR}/parser/file_reader.cpp"
  "${LANG_MODEL_SRC_DIR}/parser/scanner.cpp"
  "${LANG_MODEL_SRC_DIR}/parser/token.cpp"
  # Some interpreter and compilator tools
  "${LANG_MODEL_SRC_DIR}/utils/error_handler.cpp"
  "${LANG_MODEL_SRC_DIR}/utils/interpreter.cpp"
  # AST tools
  "${LANG_MODEL_SRC_DIR}/ast/expression.cpp"
)

# Compilation static library
if (LANG_MODEL_STATIC_BUILD)
  message(STATUS "${PROJECT_NAME} is static library")
  add_library(${PROJECT_NAME} STATIC)
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DSTATIC_BUILD)
# Compilation dynamic library
else()
  message(STATUS "${PROJECT_NAME} is dynamic library")
  add_library(${PROJECT_NAME} SHARED)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DLIB_EXPORT)
  target_compile_definitions(${PROJECT_NAME} INTERFACE -DLIB_IMPORT)
endif()
# Setting target source files
target_sources(${PROJECT_NAME} PRIVATE ${LANG_MODEL_PUBLIC_HEADERS} ${LANG_MODEL_SOURCES})

# Include directory with project's public headers
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_NAME} project include path: ${INCLUDE_PATH}")
# Library include settings
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})

# Linking boost::program_options
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::program_options)
# Using magic_enum library (header only)
target_link_libraries(${PROJECT_NAME} PRIVATE magic_enum)

# Building tools
add_subdirectory(tools)

# If enabled building tests for library
if(LANG_MODEL_BUILD_TESTS)
  message(STATUS "Tests building is enabled")
  include(CTest)
  enable_testing(true)
  add_subdirectory(tests)
endif()
