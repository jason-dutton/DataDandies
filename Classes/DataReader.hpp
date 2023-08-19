#ifndef TEXTFILEDATAREADER_HPP
#define TEXTFILEDATAREADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <deque>
#include <cstdlib>
#include "utils.hpp"

using namespace std;

class TextFileDataReader
{
public:
  deque<Position> readFile(const std::string &filename);
  void writeChromosome(Chromosome c, const std::string &filename);
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
inline void TextFileDataReader::writeChromosome(Chromosome c, const std::string &filename)
{
  std::ofstream outputFile("output.txt");
  if (!outputFile.is_open()) {
      std::cerr << "Error opening output file." << std::endl;
      return;
  }

  outputFile << "[\n";
    for (size_t i = 0; i < c.choices.size(); ++i) {
        const Choice& choice = c.choices[i];

        outputFile << "[" << choice.food << ", ";
        if (i + 1 < c.choices.size() && c.choices[i + 1].food == 0) {
            const Choice& nextChoice = c.choices[i + 1];
            outputFile << "[(" << choice.next.x << ", " << choice.next.y << "), "
                       << "(" << nextChoice.next.x << ", " << nextChoice.next.y << ")]";
            ++i; // Skip the next choice
        } else {
            outputFile << "[(" << choice.next.x << ", " << choice.next.y << ")]";
        }
        outputFile << "]";
        
        if (i < c.choices.size()) {
            outputFile << ",\n";
        }
    }
    outputFile << "]" << std::endl;

  outputFile.close();
  return;
}
#endif
