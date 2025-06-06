#include "Aligner.h"
#include <algorithm> // std::max
#include <iostream>

Aligner::AlignmentResult Aligner::needlemanWunsch(
    const Sequence& seq1, 
    const Sequence& seq2, 
    const ScoreMatrix& matrix)
{
    size_t n = seq1.getLength() + 1;
    size_t m = seq2.getLength() + 1;

    // Matrices de puntuación y direcciones
    std::vector<std::vector<int>> score_matrix(n, std::vector<int>(m, 0));
    std::vector<std::vector<char>> direction_matrix(n, std::vector<char>(m, '0'));

    int gap = matrix.getGapPenalty();

    // Inicializar primera fila y columna
    for (size_t i = 1; i < n; ++i) {
        score_matrix[i][0] = score_matrix[i - 1][0] + gap;
        direction_matrix[i][0] = 'U'; // Up
    }
    for (size_t j = 1; j < m; ++j) {
        score_matrix[0][j] = score_matrix[0][j - 1] + gap;
        direction_matrix[0][j] = 'L'; // Left
    }

    // Llenar la matriz
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < m; ++j) {
            char a = seq1[i - 1];
            char b = seq2[j - 1];

            int match = score_matrix[i - 1][j - 1] + matrix.getScore(a, b);
            int delete_ = score_matrix[i - 1][j] + gap;
            int insert = score_matrix[i][j - 1] + gap;

            int maxScore = std::max({match, delete_, insert});
            score_matrix[i][j] = maxScore;

            if (maxScore == match) direction_matrix[i][j] = 'D'; // Diagonal
            else if (maxScore == delete_) direction_matrix[i][j] = 'U'; // Up
            else direction_matrix[i][j] = 'L'; // Left
        }
    }

    // Backtracking
    std::string aligned1, aligned2;
    traceback(score_matrix, direction_matrix, seq1, seq2, aligned1, aligned2);

    return {aligned1, aligned2, score_matrix[n - 1][m - 1]};
}

void Aligner::traceback(
    const std::vector<std::vector<int>>& score_matrix,
    const std::vector<std::vector<char>>& direction_matrix,
    const Sequence& seq1,
    const Sequence& seq2,
    std::string& aligned1,
    std::string& aligned2)
{
    size_t i = seq1.getLength();
    size_t j = seq2.getLength();

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && direction_matrix[i][j] == 'D') {
            aligned1 += seq1[i - 1];
            aligned2 += seq2[j - 1];
            --i; --j;
        } else if (i > 0 && direction_matrix[i][j] == 'U') {
            aligned1 += seq1[i - 1];
            aligned2 += '-';
            --i;
        } else if (j > 0 && direction_matrix[i][j] == 'L') {
            aligned1 += '-';
            aligned2 += seq2[j - 1];
            --j;
        }
    }

    // El alineamiento se construye al revés
    std::reverse(aligned1.begin(), aligned1.end());
    std::reverse(aligned2.begin(), aligned2.end());
}
