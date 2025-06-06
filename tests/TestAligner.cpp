#include <gtest/gtest.h>
#include "Aligner.h"
#include "Sequence.h"
#include "ScoreMatrix.h"

TEST(AlignerTest, NeedlemanWunschSimpleAlignment) {
    Sequence seq1("seq1", "ACGT");
    Sequence seq2("seq2", "ACGT");
    ScoreMatrix matrix;

    auto result = Aligner::needlemanWunsch(seq1, seq2, matrix);

    EXPECT_EQ(result.seq1_aligned, "ACGT");
    EXPECT_EQ(result.seq2_aligned, "ACGT");
    EXPECT_EQ(result.score, 4); // 4 matches × 1
}

TEST(AlignerTest, NeedlemanWunschWithOneGap) {
    Sequence seq1("seq1", "ACGT");
    Sequence seq2("seq2", "AGT");
    ScoreMatrix matrix;

    auto result = Aligner::needlemanWunsch(seq1, seq2, matrix);

    EXPECT_EQ(result.seq1_aligned, "ACGT");
    EXPECT_EQ(result.seq2_aligned, "A-GT");
    EXPECT_EQ(result.score, -2); // Match, gap, match, match = 1 -5 +1 +1 = -2
}

TEST(AlignerTest, NeedlemanWunschAllMismatches) {
    Sequence seq1("seq1", "AAAA");
    Sequence seq2("seq2", "TTTT");
    ScoreMatrix matrix;

    auto result = Aligner::needlemanWunsch(seq1, seq2, matrix);

    EXPECT_EQ(result.seq1_aligned, "AAAA");
    EXPECT_EQ(result.seq2_aligned, "TTTT");
    EXPECT_EQ(result.score, -4); // 4 mismatches × -1
}

TEST(AlignerTest, NeedlemanWunschLeadingTrailingGaps) {
    Sequence seq1("seq1", "CGT");
    Sequence seq2("seq2", "ACGTG");
    ScoreMatrix matrix;

    auto result = Aligner::needlemanWunsch(seq1, seq2, matrix);

    EXPECT_EQ(result.seq1_aligned.length(), result.seq2_aligned.length());
    EXPECT_EQ(result.score, -7); // A gap (-5), C-G-T match (+3), G gap (-5) = -5 + 3 -5 = -7 (example, depends on positions)
}

TEST(AlignerTest, NeedlemanWunschEmptySequences) {
    Sequence seq1("seq1", "");
    Sequence seq2("seq2", "");
    ScoreMatrix matrix;

    auto result = Aligner::needlemanWunsch(seq1, seq2, matrix);

    EXPECT_EQ(result.seq1_aligned, "");
    EXPECT_EQ(result.seq2_aligned, "");
    EXPECT_EQ(result.score, 0);
}

TEST(AlignerTest, NeedlemanWunschOneEmptySequence) {
    Sequence seq1("seq1", "ACGT");
    Sequence seq2("seq2", "");
    ScoreMatrix matrix;

    auto result = Aligner::needlemanWunsch(seq1, seq2, matrix);

    EXPECT_EQ(result.seq2_aligned, "----");
    EXPECT_EQ(result.seq1_aligned, "ACGT");
    EXPECT_EQ(result.score, 4 * matrix.getGapPenalty()); // default is -5 → -20
}
