#include <string>

#include <cmath>

#include "Classes/DataReader.hpp"
#include "Classes/ga.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  // if (argc < 2)
  // {
  //   std::cerr << "Usage: " << argv[0] << " <input file>"
  //             << " <output file [default=output.txt]>" << std::endl;
  //   return 1;
  // }

  string input = "1.txt";
  string output = "output.txt";

  // if (argc == 2)
  // {
  //   output = "output.txt";
  // }
  // else
  // {
  //   output = argv[2];
  // }

  TextFileDataReader fileHandler;
  deque<Position> problem = fileHandler.readFile(input);

  for (Position pos : problem)
  {
    cout << pos.x << " " << pos.y << endl;
  }

  int total = problem.back().x + problem.back().y;
  Chromosome::totalDistance = total;

  GeneticAlgorithm ga = GeneticAlgorithm(problem);
  Solution solution = ga.execute();

  cout << "Solution: " << endl;
  for (Choice choice : solution.chromosome.choices)
  {
    cout << choice.food << " " << choice.next.x << " " << choice.next.y << endl;
  }
  cout << "Fitness: " << solution.fitness << endl;
  cout << "Total time: " << solution.time << endl;

  fileHandler.writeChromosome(solution.chromosome, output);

  return 0;
}
