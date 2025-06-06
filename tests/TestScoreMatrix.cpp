#include <gtest/gtest.h>
#include "ScoreMatrix.h"
#include <fstream>
#include <cstdio>
#include "Aligner.h"

TEST(ScoreMatrixTest, DefaultMatrix) {
    ScoreMatrix matrix;
    
    EXPECT_EQ(matrix.getScore('A', 'A'), 1);
    EXPECT_EQ(matrix.getScore('A', 'C'), -1);
    EXPECT_EQ(matrix.getScore('T', 'T'), 1);
    EXPECT_EQ(matrix.getGapPenalty(), -5);
}

TEST(ScoreMatrixTest, LoadFromFile) {
    // Create temporary test file
    const char* filename = "test_matrix.txt";
    std::ofstream out(filename);
    out << "A C G T\n"
        << "A 1 -1 -1 -1\n"
        << "C -1 1 -1 -1\n"
        << "G -1 -1 1 -1\n"
        << "T -1 -1 -1 1\n";
    out.close();
    
    ScoreMatrix matrix(filename);
    
    EXPECT_EQ(matrix.getScore('A', 'A'), 1);
    EXPECT_EQ(matrix.getScore('A', 'C'), -1);
    EXPECT_EQ(matrix.getScore('G', 'T'), -1);
    EXPECT_EQ(matrix.getScore('T', 'T'), 1);
    
    // Remove temporary file
    std::remove(filename);
}

TEST(ScoreMatrixTest, GapPenalty) {
    ScoreMatrix matrix;
    matrix.setGapPenalty(-10);
    EXPECT_EQ(matrix.getGapPenalty(), -10);
}
