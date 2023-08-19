#ifndef MYCLASS
#define MYCLASS

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <deque>
#include <cstdlib>

using namespace std;

class MyClass
{
public:
  void readFile(const std::string &filename);
  void reverseNames();
  void writeToFile(const std::string &filename) const;
  void printNames() const;

private:
  std::vector<std::string> names;
};

void MyClass::readFile(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  deque<tuple<int, int>> pairDeque;

  char openingParenthesis, comma, closingParenthesis;
  int x, y;

  string line;
  getline(file, line);

  size_t startPos = line.find('(');
  while (startPos != std::string::npos) {
      size_t commaPos1 = line.find(',', startPos);
      size_t closingPos = line.find(')', startPos);

      int x = std::atoi(line.substr(startPos + 1, commaPos1 - startPos - 1).c_str());
      int y = std::atoi(line.substr(commaPos1 + 1, closingPos - commaPos1).c_str());

      pairDeque.emplace_back(x, y);

      startPos = line.find('(', closingPos);
  }

  file.close();
}

void MyClass::reverseNames()
{
  for (std::string &name : names)
  {
    std::reverse(name.begin(), name.end());
  }
}

void MyClass::writeToFile(const std::string &filename) const
{
  std::ofstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  for (const std::string &name : names)
  {
    file << name << std::endl;
  }

  file.close();
}

void MyClass::printNames() const
{
  for (const std::string &name : names)
  {
    std::cout << name << std::endl;
  }
}

#endif
