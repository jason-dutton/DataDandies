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

    Choice getAndSet(int index, Choice choice);
    Choice get(int index);
    void set(int index, Choice choice);
    void add(Choice choice);
    void remove(int index);
    int size();
};

Choice Chromosome::getAndSet(int index, Choice choice)
{
    Choice old_choice = this->choices[index];
    this->choices[index] = choice;
    return old_choice;
}

Choice Chromosome::get(int index)
{
    return this->choices[index];
}

void Chromosome::set(int index, Choice choice)
{
    this->choices[index] = choice;
}

void Chromosome::add(Choice choice)
{
    this->choices.push_back(choice);
}

void Chromosome::remove(int index)
{
    this->choices.erase(this->choices.begin() + index);
}

int Chromosome::size()
{
    return this->choices.size();
}

class Solution {
public:
    deque<Position> problem;
    Chromosome chromosome;
    float fitness;
    float time;

    Solution(deque<Position> problem, Chromosome chromosome, float time, float fitness = 0);
};

Solution::Solution(deque<Position> problem, Chromosome chromosome, float time, float fitness)
{
    this->problem = problem;
    this->chromosome = chromosome;
    this->fitness = fitness;
}