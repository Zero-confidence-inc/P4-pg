set(CMAKE_CXX_COMPILER "C:/TDM-GCC-64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/TDM-GCC-64/bin/gcc.exe")

cmake_minimum_required(VERSION 3.28)
project(P4_pg)

set(CMAKE_C_COMPILER GCC)
set(CMAKE_CXX_COMPILE GCC)
set(CMAKE_CXX_STANDARD 14)
enable_language(CXX)

# Since all source and header files are in 'src', we only need to include this directory
include_directories(${PROJECT_SOURCE_DIR}/src)

# Include Google Test
add_subdirectory(googletest)

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories for Google Test
include_directories(googletest/googletest/include)

# Define your main application executable
set(SOURCES
        src/main.cpp
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
        src/Parser.h
        src/Lexer.h
)
add_executable(P4_pg ${SOURCES})

# Define your test executable
set(TEST_SOURCES
    Test/OperatorDFAtests.cpp
        src/OperatorDFA.cpp
    Test/TypeDFAtests.cpp
        src/TypeDFA.cpp
    Test/IdentifierDFAtest.cpp
        src/IdentifierDFA.cpp
    Test/StringDFAtest.cpp
        src/StringDFA.cpp
    Test/ConstDFAtest.cpp
        src/ConstDFA.cpp
    Test/PunctuationDFAtest.cpp
        src/PunctuationDFA.cpp
    Test/Lexer_integration_test.cpp
        src/Lexer.cpp
        src/LoopStatDFA.cpp
        src/ControlStatDFA.cpp
        src/WhitespaceDFA.cpp
    Test/ParserTests.cpp
        src/Parser.cpp
        src/Parser.h
        
)
add_executable(P4_pg_tests ${TEST_SOURCES})

# Linking Google Test to the test executable
target_link_libraries(P4_pg_tests gtest gtest_main pthread)