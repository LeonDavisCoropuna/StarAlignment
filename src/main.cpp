#include <iostream>
#include <fstream>
#include "Sequence.h"
#include "ScoreMatrix.h"
#include "StarAlignment.h"

using namespace std;

vector<Sequence> loadSequences(const string& filename) {
    vector<Sequence> sequences;
    ifstream file(filename);
    string line, id, data;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!id.empty()) {
                sequences.emplace_back(id, data);
                data.clear();
            }
            id = line.substr(1);
        } else {
            data += line;
        }
    }
    
    if (!id.empty()) {
        sequences.emplace_back(id, data);
    }
    
    return sequences;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <sequences_file> <scores_file>\n";
        return 1;
    }
    
    try {
        // Load data
        auto sequences = loadSequences(argv[1]);
        ScoreMatrix score_matrix(argv[2]);
        
        // Perform star alignment
        auto alignment = StarAlignment::align(sequences, score_matrix);
        
        // Output results
        cout << "Star Alignment Results:\n";
        for (const auto& seq : alignment) {
            cout << seq << "\n";
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}