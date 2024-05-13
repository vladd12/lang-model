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
option(LANG_MODEL_BUILD_INTERPRETER "Build interpreter with using lang-model" ON)
option(LANG_MODEL_BUILD_TESTS "Build tests for avm-editor library" ON)

include(get_conan) # Getting cmake-conan
include(get_boost) # Getting boost library with conan
find_package(Boost COMPONENTS boost program_options REQUIRED) # Finding boost

# Collecting project's public headers
set(LANG_MODEL_PUBLIC_HEADERS
    #include/${PROJECT_NAME}.hpp
    # Core features
    include/${PROJECT_NAME}/export.hpp
    include/${PROJECT_NAME}/expr.hpp
    include/${PROJECT_NAME}/expr_type.hpp
    include/${PROJECT_NAME}/expr_visitor.hpp
    # Expressions implementation
    include/${PROJECT_NAME}/const_expr.hpp
    # Work with files and this parsing
    include/${PROJECT_NAME}/parser/file_reader.hpp
    include/${PROJECT_NAME}/parser/tokenizer.hpp
    # Some interpreter and compilator tools
    include/${PROJECT_NAME}/tools/interpreter.hpp
    include/${PROJECT_NAME}/tools/error_handler.hpp
)

# Collecting project's sources
set(LANG_MODEL_SOURCES
    src/expr.cpp
    src/expr_visitor.cpp
    src/const_expr.cpp
    src/parser/file_reader.cpp
    src/parser/tokenizer.cpp
    src/tools/interpreter.cpp
    src/tools/error_handler.cpp
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
target_sources(${PROJECT_NAME}
    PRIVATE ${LANG_MODEL_PUBLIC_HEADERS} ${LANG_MODEL_SOURCES}
)

# Include directory with project's public headers
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_NAME} project include path: ${INCLUDE_PATH}")
# Library include settings
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})

# Linking boost::program_options
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::program_options)

# If enabled building interpreter
if(LANG_MODEL_BUILD_INTERPRETER)
    message(STATUS "Example building is enabled")
    add_subdirectory(interpreter)
endif()

# If enabled building tests for library
if(LANG_MODEL_BUILD_TESTS)
    message(STATUS "Tests building is enabled")
    include(CTest)
    enable_testing(true)
    add_subdirectory(tests)
endif()
