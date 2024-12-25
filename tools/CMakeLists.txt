# If enabled building interpreter
if(LANG_MODEL_BUILD_INTERPRETER)
    message(STATUS "Interpreter for lang-model building is enabled")
    add_subdirectory(interpreter)
endif()

# If enabled building interpreter
if(LANG_MODEL_BUILD_AST_GENERATOR)
    message(STATUS "Example building is enabled")
    add_subdirectory(ast_generator)
endif()
