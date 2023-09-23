# Include directory with project's public headers
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_NAME} project include path: ${INCLUDE_PATH}")

# Collecting interpreter's headers
set(INTERPRETER_HEADERS
#  include/interpreter.hpp
)

# Collecting interpreter's sources
set(INTERPRETER_SOURCES
  src/main.cpp
)

# Create executable target
add_executable(interpreter ${INTERPRETER_HEADERS} ${INTERPRETER_SOURCES})
target_include_directories(interpreter PRIVATE ${INCLUDE_PATH})
target_link_libraries(interpreter PUBLIC lang-model)
