cmake_minimum_required(VERSION 3.28)
project(P4_pg)

set(CMAKE_CXX_STANDARD 14)

# Since all source and header files are in 'src', we only need to include this directory
include_directories(${PROJECT_SOURCE_DIR}/src)

# Include Google Test
add_subdirectory(googletest)

# Include directories for Google Test
include_directories(googletest/googletest/include)

# Define your main application executable
set(SOURCES
        src/main.cpp
        src/ConstDFA.cpp
        src/IdentifierDFA.cpp
        src/Keyword.cpp
        src/Lexer.cpp
        src/OperatorDFA.cpp
        src/PunctuationDFA.cpp
        src/StringDFA.cpp
        src/WhitespaceDFA.cpp
)
add_executable(P4_pg ${SOURCES})

# Define your test executable
set(TEST_SOURCES
    Test/OperatorDFAtests.cpp
    src/OperatorDFA.cpp
)
add_executable(P4_pg_tests ${TEST_SOURCES})

# Linking Google Test to the test executable
target_link_libraries(P4_pg_tests gtest gtest_main pthread)