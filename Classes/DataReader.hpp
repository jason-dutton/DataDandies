#ifndef TEXTFILEDATAREADER_HPP
#define TEXTFILEDATAREADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <deque>
#include <cstdlib>
#include "utils.hpp"

using namespace std;

class TextFileDataReader
{
public:
  deque<Position> readFile(const std::string &filename);
};

deque<Position> TextFileDataReader::readFile(const std::string &filename)
{
  deque<Position> tupleDeque;
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return tupleDeque;
  }

  char openingParenthesis, comma, closingParenthesis;
  Position pos;

  string line;
  getline(file, line);

  size_t startPos = line.find('(');
  while (startPos != std::string::npos) {
      size_t commaPos1 = line.find(',', startPos);
      size_t closingPos = line.find(')', startPos);

      pos.x = std::atoi(line.substr(startPos + 1, commaPos1 - startPos - 1).c_str());
      pos.y = std::atoi(line.substr(commaPos1 + 1, closingPos - commaPos1).c_str());

      tupleDeque.emplace_back(pos);

      startPos = line.find('(', closingPos);
  }

  file.close();

  return tupleDeque;
}

#endif
