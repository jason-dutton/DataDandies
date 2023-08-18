#include <string>

#include "Classes/myClass.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " <input file>" << " <output file>" << std::endl;
    return 1;
  }

  string input = argv[1];
  string output = argv[2];

  MyClass myObject;
  myObject.readFile(input);
  myObject.reverseNames();
  myObject.writeToFile(output);

  return 0;
}
