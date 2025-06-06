#ifndef ALIGNER_H
#define ALIGNER_H

#include "Sequence.h"
#include "ScoreMatrix.h"
#include <utility>

class Aligner {
public:
    struct AlignmentResult {
        std::string seq1_aligned;
        std::string seq2_aligned;
        int score;
    };

    static AlignmentResult needlemanWunsch(
        const Sequence& seq1, 
        const Sequence& seq2, 
        const ScoreMatrix& matrix);
    
private:
    static void traceback(
        const std::vector<std::vector<int>>& score_matrix,
        const std::vector<std::vector<char>>& direction_matrix,
        const Sequence& seq1,
        const Sequence& seq2,
        std::string& aligned1,
        std::string& aligned2);
};

#endif // ALIGNER_H