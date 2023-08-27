project(lang-model-tests LANGUAGES CXX)

# Getting googletest as GTest::GTest target
include(get_gtest)

# Collecting tests sources
set(TESTS_SOURCES
    parser/file_reader_tests.cpp
    parser/tokenizer_tests.cpp
)
# Collecting test's external files
set(TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/read_file_test.meta
)

# Compiling tests as executable file
add_executable(${PROJECT_NAME} ${TESTS_SOURCES})
# Linking googletest and execstd libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    GTest::GTest
    lang-model
)

# Copy external test's files to binary directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${TEST_FILES} ${CMAKE_CURRENT_BINARY_DIR}
)

# Register test for ctest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
