#ifndef FASTA_READER_H
#define FASTA_READER_H

#include <vector>
#include <string>
#include "Sequence.h"

class FastaReader {
public:
    static std::vector<Sequence> readFastaFile(const std::string& filename);
};

#endif
