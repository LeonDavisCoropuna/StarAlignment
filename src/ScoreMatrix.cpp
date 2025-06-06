#include "ScoreMatrix.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

ScoreMatrix::ScoreMatrix() : gapPenalty(-5) {
    initializeDefaultMatrix();
}

ScoreMatrix::ScoreMatrix(const std::string& filename) : gapPenalty(-5) {
    loadFromFile(filename);
}

void ScoreMatrix::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open score matrix file");
    }
    
    matrix.clear();
    std::string line;
    
    // Read first line to get characters
    std::getline(file, line);
    std::stringstream ss(line);
    std::vector<char> characters;
    char c;
    
    while (ss >> c) {
        characters.push_back(toupper(c));
    }
    
    // Read remaining lines
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss_line(line);
        char row_char;
        ss_line >> row_char;
        row_char = toupper(row_char);
        
        int score;
        size_t i = 0;
        while (ss_line >> score) {
            if (i >= characters.size()) {
                throw std::runtime_error("Invalid file format");
            }
            matrix[row_char][characters[i]] = score;
            i++;
        }
    }
}

int ScoreMatrix::getScore(char a, char b) const {
    a = toupper(a);
    b = toupper(b);
    
    try {
        return matrix.at(a).at(b);
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("Characters not found in score matrix");
    }
}

int ScoreMatrix::getGapPenalty() const {
    return gapPenalty;
}

void ScoreMatrix::setGapPenalty(int penalty) {
    gapPenalty = penalty;
}

void ScoreMatrix::initializeDefaultMatrix() {
    // Simple score matrix (can be replaced by file loading)
    std::string nucleotides = "ACGT";
    
    for (char a : nucleotides) {
        for (char b : nucleotides) {
            matrix[a][b] = (a == b) ? 1 : -1;
        }
    }
}