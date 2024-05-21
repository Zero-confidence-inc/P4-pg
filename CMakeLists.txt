cmake_minimum_required(VERSION 3.28)
project(P4_pg)

set(CMAKE_CXX_STANDARD 14)

# Include the src directory for all targets
include_directories(${PROJECT_SOURCE_DIR}/src)

# Include Google Test
add_subdirectory(googletest)

# Define a library for your source files
set(SOURCES
        src/ConstDFA.cpp
        src/IdentifierDFA.cpp
        src/TypeDFA.cpp
        src/Lexer.cpp
        src/OperatorDFA.cpp
        src/PunctuationDFA.cpp
        src/StringDFA.cpp
        src/WhitespaceDFA.cpp
        src/ControlStatDFA.cpp
        src/LoopStatDFA.cpp
        src/JumpStatDFA.cpp
        src/Parser.cpp
        src/CommentsDFA.cpp
        src/Parser.h
        src/BoolDFA.cpp
        src/ConsoleDFA.cpp
        src/Semantic.cpp
        src/Semantic.h
        src/CodeGenerator.cpp
        src/Semantic.cpp
)

add_library(P4_pg_lib ${SOURCES})

# Define your main application executable
add_executable(P4_pg src/main.cpp)
target_link_libraries(P4_pg P4_pg_lib)

# Define your test executable
set(TEST_SOURCES
        Test/CGunitTests.cpp
        Test/OperatorDFAtests.cpp
        Test/TypeDFAtests.cpp
        Test/IdentifierDFAtest.cpp
        Test/StringDFAtest.cpp
        Test/ConstDFAtest.cpp
        Test/PunctuationDFAtest.cpp
        Test/Lexer_integration_test.cpp
        Test/ParserUnitTests.cpp
        Test/SemanticTest.cpp
)

add_executable(P4_pg_tests ${TEST_SOURCES})

# Linking Google Test and your library to the test executable
target_link_libraries(P4_pg_tests P4_pg_lib gtest gtest_main)

# Enable testing
enable_testing()

# Add tests
add_test(NAME P4_pg_tests COMMAND P4_pg_tests)