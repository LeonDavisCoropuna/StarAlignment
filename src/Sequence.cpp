#include "Sequence.h"
#include <stdexcept>

Sequence::Sequence(const std::string& id, const std::string& data) 
    : identifier(id), data(data) {}

std::string Sequence::getId() const {
    return identifier;
}

std::string Sequence::getData() const {
    return data;
}

size_t Sequence::getLength() const {
    return data.length();
}

void Sequence::setId(const std::string& id) {
    identifier = id;
}

void Sequence::setData(const std::string& data) {
    this->data = data;
}

char Sequence::operator[](size_t index) const {
    if (index >= data.length()) {
        throw std::out_of_range("Index out of range in Sequence");
    }
    return data[index];
}

std::string Sequence::subsequence(size_t start, size_t length) const {
    if (start + length > data.length()) {
        throw std::out_of_range("Subsequence out of range");
    }
    return data.substr(start, length);
}