#include "FastaReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

std::string cleanLine(const std::string &line)
{
  std::string result = line;
  result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
  return result;
}

std::vector<Sequence> FastaReader::readFastaFile(const std::string &filename)
{
  std::vector<Sequence> sequences;
  std::ifstream infile(filename);
  if (!infile)
    return sequences;

  std::string line, id, content;
  while (std::getline(infile, line))
  {
    line = cleanLine(line);

    if (line.empty())
      continue;
    if (line[0] == '>')
    {
      if (!id.empty())
      {
        sequences.emplace_back(id, content);
        content.clear();
      }
      id = line.substr(1); // Skip '>'
    }
    else
    {
      content += line;
    }
  }
  if (!id.empty())
  {
    sequences.emplace_back(id, content);
  }
  return sequences;
}
