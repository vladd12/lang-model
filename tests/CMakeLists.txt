project(lang-model-tests LANGUAGES CXX)

# Getting googletest as GTest::GTest target
include(get_gtest)

# Collecting tests sources
set(TESTS_SOURCES
    tests.cpp
)

# Compiling tests as executable file
add_executable(${PROJECT_NAME} ${TESTS_SOURCES})
# Linking googletest and execstd libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    GTest::GTest
    lang-model
)

# Register test for ctest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
