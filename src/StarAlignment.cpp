#include "StarAlignment.h"
#include "Aligner.h"
#include <limits>

using namespace std;

vector<string> StarAlignment::align(
    const vector<Sequence>& sequences,
    const ScoreMatrix& matrix) {
    
    if (sequences.empty()) return {};
    
    // Find center sequence
    int center_index = findCenterSequence(sequences, matrix);
    const Sequence& center = sequences[center_index];
    
    // Pairwise alignments with center
    vector<Aligner::AlignmentResult> pairwise_results;
    for (size_t i = 0; i < sequences.size(); ++i) {
        if (i != static_cast<size_t>(center_index)) {
            pairwise_results.push_back(
                Aligner::needlemanWunsch(center, sequences[i], matrix));
        }
    }
    
    // Build multiple alignment (simple approach)
    vector<string> result;
    result.push_back(center.getData()); // Center sequence first
    
    for (const auto& alignment : pairwise_results) {
        result.push_back(alignment.seq2_aligned);
    }
    
    return result;
}

int StarAlignment::findCenterSequence(
    const vector<Sequence>& sequences,
    const ScoreMatrix& matrix) {
    
    int best_index = 0;
    int best_total_score = numeric_limits<int>::min();
    
    for (size_t i = 0; i < sequences.size(); ++i) {
        int total_score = 0;
        
        for (size_t j = 0; j < sequences.size(); ++j) {
            if (i != j) {
                auto result = Aligner::needlemanWunsch(
                    sequences[i], sequences[j], matrix);
                total_score += result.score;
            }
        }
        
        if (total_score > best_total_score) {
            best_total_score = total_score;
            best_index = i;
        }
    }
    
    return best_index;
}