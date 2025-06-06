#include <gtest/gtest.h>
#include "Sequence.h"

TEST(SequenceTest, ConstructorAndGetters) {
    Sequence seq("seq1", "ACGT");
    
    EXPECT_EQ(seq.getId(), "seq1");
    EXPECT_EQ(seq.getData(), "ACGT");
    EXPECT_EQ(seq.getLength(), 4);
}

TEST(SequenceTest, IndexOperator) {
    Sequence seq("", "ACGT");
    
    EXPECT_EQ(seq[0], 'A');
    EXPECT_EQ(seq[1], 'C');
    EXPECT_EQ(seq[2], 'G');
    EXPECT_EQ(seq[3], 'T');
    
    EXPECT_THROW(seq[4], std::out_of_range);
}

TEST(SequenceTest, Subsequence) {
    Sequence seq("", "ACGTACGT");
    
    EXPECT_EQ(seq.subsequence(0, 4), "ACGT");
    EXPECT_EQ(seq.subsequence(4, 4), "ACGT");
    EXPECT_THROW(seq.subsequence(5, 4), std::out_of_range);
}