#ifndef GA
#define GA

#include <deque>
#include <algorithm>

#include "utils.hpp"

const float SURVIVAL_RATE = 0.2;
const float CROSSOVER_RATE = 0.4;
const float MUTATION_RATE = 0.4;
const int POPULATION_SIZE = 100;

class Specimen
{
public:
    Chromosome chromosome;
    float fitness;

    Specimen(Chromosome chromosome, float fitness = 0);

    void mutate(float mutation_rate = MUTATION_RATE);
    static Specimen randomSpecimen(deque<Position> problem);
    float getFitness();
};

class Population
{
public:
    deque<Specimen> specimens;
    int population_size;

    Population(int population_size = POPULATION_SIZE, deque<Position> problem);

    void cull(float survival_rate = SURVIVAL_RATE);
    void crossover(float crossover_rate = CROSSOVER_RATE);
    void mutate(float mutation_rate = MUTATION_RATE);
};

// Specimen

Specimen::Specimen(Chromosome chromosome, float fitness)
{
    this->chromosome = chromosome;
    this->fitness = fitness;
}

void Specimen::mutate(float mutation_rate)
{
    // TODO
}

float Specimen::getFitness()
{
    //! Remove this line upon implementation of evaluate()
    // this->fitness = this->chromosome.evaluate();
    this->fitness = 0;
    return this->fitness;
}

Specimen Specimen::randomSpecimen(deque<Position> problem)
{
    Chromosome chromosome;
    for (int i = 0; i < problem.size(); i++)
    {
        Choice choice;
        choice.food = rand() % 2;

        // pick a number between 0 and problem.size() - 1
        int next_index = rand() % problem.size();
        choice.next = problem[next_index];
        problem.erase(problem.begin() + next_index);

        chromosome.choices.push_back(choice);
    }
    return Specimen(chromosome);
}

// Population

Population::Population(int population_size, deque<Position> problem)
{
    this->population_size = population_size;
    for (int i = 0; i < population_size; i++)
    {
        this->specimens.push_back(Specimen::randomSpecimen(problem));
    }
}

void Population::cull(float survival_rate)
{
    // Sort specimens by fitness
    sort(specimens.begin(), specimens.end(), [](Specimen a, Specimen b)
         { return a.getFitness() < b.getFitness(); });

    // Remove the worst specimens
    int number_of_specimens_to_remove = (int)(specimens.size() * (1 - survival_rate));
    specimens.erase(specimens.begin(), specimens.begin() + number_of_specimens_to_remove);
}

void Population::crossover(float crossover_rate)
{
    // TODO
}

void Population::mutate(float mutation_rate)
{
    for (auto specimen : specimens)
    {
        specimen.mutate(mutation_rate);
    }
}

#endif