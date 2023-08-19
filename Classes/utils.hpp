#include <deque>
using namespace std;
class Position
{
public:
    int x;
    int y;
};

class Choice
{
public:
    int food;
    Position next;
};

class Chromosome
{
public:
    deque<Choice> choices;
};