# Collecting interpreter's sources
set(INTERPRETER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INTERPRETER_SOURCES
  "${INTERPRETER_SRC_DIR}/main.cpp"
)

# Create executable target
add_executable(interpreter ${INTERPRETER_SOURCES})
target_include_directories(interpreter PRIVATE ${INCLUDE_PATH})
target_link_libraries(interpreter PUBLIC lang-model)
