cmake_minimum_required(VERSION 3.10)
project(BioinformaticsAlignment)

# Standard configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include directories
include_directories(include)

# Main executable
add_executable(star_alignment 
    src/main.cpp 
    src/Aligner.cpp 
    src/Sequence.cpp 
    src/ScoreMatrix.cpp 
    src/FastaReader.cpp
    src/StarAlignment.cpp)

# Test configuration with GTest
enable_testing()

# Test executable
add_executable(tests 
    tests/test_main.cpp 
    tests/TestAligner.cpp
    tests/TestSequence.cpp
    tests/TestScoreMatrix.cpp
    tests/TestStarAlignment.cpp
    tests/TestFasta.cpp
    src/Aligner.cpp 
    src/FastaReader.cpp
    src/Sequence.cpp 
    src/ScoreMatrix.cpp 
    src/StarAlignment.cpp)

# Link GTest libraries
target_link_libraries(tests 
    PRIVATE 
    ${GTEST_LIBRARIES} 
    pthread)

add_test(NAME tests COMMAND tests)