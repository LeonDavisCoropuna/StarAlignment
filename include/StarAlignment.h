#ifndef STAR_ALIGNMENT_H
#define STAR_ALIGNMENT_H

#include <vector>
#include "Sequence.h"
#include "ScoreMatrix.h"

class StarAlignment {
public:
    static std::vector<std::string> align(
        const std::vector<Sequence>& sequences,
        const ScoreMatrix& matrix);
    
private:
    static int findCenterSequence(
        const std::vector<Sequence>& sequences,
        const ScoreMatrix& matrix);
};

#endif // STAR_ALIGNMENT_H