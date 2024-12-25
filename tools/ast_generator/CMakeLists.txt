# Collecting sources for AST generator
set(AST_GEN_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(AST_GEN_SOURCES
  "${AST_GEN_SRC_DIR}/ast_generator.cpp"
)

# Create executable target
add_executable(ast_generator ${AST_GEN_SOURCES})
