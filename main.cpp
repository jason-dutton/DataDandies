#include <string>

#include "Classes/DataReader.hpp"
#include "Classes/ga.hpp"
#include "Classes/utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <input file>"
              << " <output file [default=output.txt]>" << std::endl;
    return 1;
  }

  string input = argv[1];
  string output = "";

  if (argc == 2)
  {
    output = "output.txt";
  }
  else
  {
    output = argv[2];
  }

  TextFileDataReader fileHandler;
  deque<Position> problem = fileHandler.readFile(input);

  for (Position pos : problem)
  {
    cout << pos.x << " " << pos.y << endl;
  }

  GeneticAlgorithm ga = GeneticAlgorithm(problem);
  Solution solution = ga.execute();

  return 0;
}
