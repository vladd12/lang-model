# Project definition and settings
cmake_minimum_required(VERSION 3.15)
project(lang-model VERSION 0.1 LANGUAGES CXX)

# Language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding path for cmake scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Library's options
option(LANG_MODEL_STATIC_BUILD "Build lang-model as static library" OFF)
option(LANG_MODEL_BUILD_EXAMPLE "Build example application with using lang-model" ON)
option(LANG_MODEL_BUILD_TESTS "Build tests for avm-editor library" ON)

# Include directory with project's public headers
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_NAME} project include path: ${INCLUDE_PATH}")
include_directories(${INCLUDE_PATH})

# Collecting project's public headers
set(LANG_MODEL_PUBLIC_HEADERS
    include/${PROJECT_NAME}.hpp
    # Core features
    include/${PROJECT_NAME}/export.hpp
    include/${PROJECT_NAME}/expr.hpp
    include/${PROJECT_NAME}/expr_type.hpp
    include/${PROJECT_NAME}/expr_visitor.hpp
    # Expressions implementation
    include/${PROJECT_NAME}/const_expr.hpp
    # Work with files and this parsing
    include/${PROJECT_NAME}/parser/file_reader.hpp
    include/${PROJECT_NAME}/parser/lexer.hpp
)

# Collecting project's sources
set(LANG_MODEL_SOURCES
    src/expr.cpp
    src/expr_visitor.cpp
    src/const_expr.cpp
    src/parser/file_reader.cpp
    src/parser/lexer.cpp
)

# Compilation static library
if (LANG_MODEL_STATIC_BUILD)
    message(STATUS "${PROJECT_NAME} is static library")
    add_library(${PROJECT_NAME} STATIC
        ${LANG_MODEL_PUBLIC_HEADERS}
        ${LANG_MODEL_SOURCES}
    )
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DSTATIC_BUILD)
# Compilation dynamic library
else()
    message(STATUS "${PROJECT_NAME} is dynamic library")
    add_library(${PROJECT_NAME} SHARED
        ${LANG_MODEL_PUBLIC_HEADERS}
        ${LANG_MODEL_SOURCES}
    )
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DLIB_EXPORT)
    target_compile_definitions(${PROJECT_NAME} INTERFACE -DLIB_IMPORT)
endif()

# Library compilation settings
target_compile_definitions(${PROJECT_NAME} PUBLIC -DCMAKE_CONFIG)
target_include_directories(${PROJECT_NAME} INTERFACE ${INCLUDE_PATH})

# If enabled building example
if(LANG_MODEL_BUILD_EXAMPLE)
    message(STATUS "Example building is enabled")
#    add_subdirectory(example)
endif()

# If enabled building tests for library
if(LANG_MODEL_BUILD_TESTS)
   message(STATUS "Tests building is enabled")
    include(CTest)
    enable_testing(true)
    add_subdirectory(tests)
endif()
