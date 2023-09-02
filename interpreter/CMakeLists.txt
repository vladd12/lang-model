# Language settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")

# Downloading conan CMake script and using for autodetecting
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(
    DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake" "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake"
    EXPECTED_HASH SHA256=5cdb3042632da3efff558924eecefd580a0e786863a857ca097c3d1d43df5dcd
    TLS_VERIFY ON
  )
endif()
include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)

# Getting boost target with conan
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/FindBoost.cmake")
    # Getting build type, compiler, etc... (other settings)
    conan_cmake_autodetect(settings)
    # Collecting boost as header-only library
    conan_cmake_configure(
      REQUIRES boost/1.82.0
      GENERATORS cmake_find_package
    )
    # Installing libraries
    conan_cmake_install(
      PATH_OR_REFERENCE .
      BUILD missing
      REMOTE conancenter
      SETTINGS ${settings}
    )
endif()

# Finding boost
find_package(Boost COMPONENTS headers REQUIRED)

# Include directory with project's public headers
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_NAME} project include path: ${INCLUDE_PATH}")

# Collecting interpreter's headers
set(INTERPRETER_HEADERS
  include/interpreter.hpp
)

# Collecting interpreter's sources
set(INTERPRETER_SOURCES
  src/interpreter.cpp
  src/main.cpp
)

# Create executable target
add_executable(interpreter ${INTERPRETER_HEADERS} ${INTERPRETER_SOURCES})
target_include_directories(interpreter PRIVATE ${INCLUDE_PATH})
target_link_libraries(interpreter PUBLIC Boost::program_options lang-model)
