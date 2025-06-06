#ifndef SCORE_MATRIX_H
#define SCORE_MATRIX_H

#include <map>
#include <string>
#include <vector>

class ScoreMatrix {
public:
    ScoreMatrix();
    ScoreMatrix(const std::string& filename);
    
    void loadFromFile(const std::string& filename);
    int getScore(char a, char b) const;
    int getGapPenalty() const;
    void setGapPenalty(int penalty);
    
private:
    std::map<char, std::map<char, int>> matrix;
    int gapPenalty;
    
    void initializeDefaultMatrix();
};

#endif // SCORE_MATRIX_H