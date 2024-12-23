project(lang-model-tests LANGUAGES CXX)

# Getting googletest as GTest::GTest target
include(get_gtest)

# Collecting tests sources
set(TESTS_SOURCES
    parser/file_reader_tests.cpp
    parser/scanner_tests.cpp
    parser/tokenizer_tests.cpp
)
# Collecting test's external files
set(TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/read_file_test.meta
)

# Compiling tests as executable file
add_executable(${PROJECT_NAME} ${TESTS_SOURCES})
# Registering test for ctest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# Linking googletest and execstd libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    GTest::GTest
    lang-model
)
# Adding to test environment PATH variable path do lang-model library
set_tests_properties(${PROJECT_NAME}
    PROPERTIES
        # Make sure DLL is found by adding its directory to PATH
        ENVIRONMENT "PATH=$<TARGET_PROPERTY:lang-model,BINARY_DIR>/;$<TARGET_PROPERTY:lang-model,BINARY_DIR>/Release/"
)

# Copy external test's files to binary directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${TEST_FILES} ${CMAKE_CURRENT_BINARY_DIR}
)
