#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>

class Sequence {
public:
    // Constructor
    Sequence(const std::string& id = "", const std::string& data = "");
    
    // Getters
    std::string getId() const;
    std::string getData() const;
    size_t getLength() const;
    
    // Setters
    void setId(const std::string& id);
    void setData(const std::string& data);
    
    // Useful operations
    char operator[](size_t index) const;
    std::string subsequence(size_t start, size_t length) const;
    
private:
    std::string identifier;
    std::string data;
};

#endif // SEQUENCE_H