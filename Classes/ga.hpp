#ifndef GA
#define GA

#include <deque>
#include <algorithm>
#include <random>

#include "utils.hpp"

const float SURVIVAL_RATE = 0.2;
const float CROSSOVER_RATE = 0.4;
const float MUTATION_RATE = 0.4;
const float MUTATION_FOOD_RATE = 0.4;
const float MUTATION_FOOD_STD = 0.4;
const int POPULATION_SIZE = 100;

class Specimen
{
public:
    Chromosome chromosome;
    float fitness;

    Specimen(Chromosome chromosome, float fitness = 0);

    void mutate(float mutation_rate = MUTATION_RATE, float mutation_food_rate = MUTATION_FOOD_RATE, float mutation_food_std = MUTATION_FOOD_STD);
    static Specimen randomSpecimen(deque<Position> problem);
    float getFitness();
};

class Population
{
public:
    deque<Specimen> specimens;
    int population_size;
    deque<Position> problem;

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

void Specimen::mutate(float mutation_rate, float mutation_food_rate, float mutation_food_std)
{
    // randomly swap choices
    for (Choice choice : this->chromosome.choices)
    {
        if (rand() % 100 < mutation_rate * 100)
        {
            // pick a number between 0 and problem.size() - 1
            int next_index = rand() % this->chromosome.choices.size();
            Choice next_choice = this->chromosome.choices[next_index];

            this->chromosome.choices[next_index] = choice;
            this->chromosome.choices.push_back(next_choice);
        }
    }

    // randomly change the food value for each choice

    for (Choice choice : this->chromosome.choices)
    {
        if (rand() % 100 < mutation_food_rate * 100)
        {   
            normal_distribution<double> normalDist(0, mutation_food_std);
            default_random_engine generator;

            double deltaFood = normalDist(generator);
            choice.food += deltaFood;
        }
    }
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
    this->problem = problem;

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
    // Find two random specimens
        int specimen_1_index = rand() % specimens.size();
        int specimen_2_index = rand() % specimens.size();
        if (specimen_1_index == specimen_2_index)
        {
            specimen_2_index = (specimen_2_index + 1) % specimens.size();
        }

        Specimen specimen_1 = specimens[specimen_1_index];
        Specimen specimen_2 = specimens[specimen_2_index];

        // Generate new population from crossover

        deque<Specimen> new_specimens;

        for (int i = 0; i < POPULATION_SIZE / 2; i++)
        {
            Chromosome chromosome_1 = specimen_1.chromosome;
            Chromosome chromosome_2 = specimen_2.chromosome;

            // Crossover

            for (int j = 0; j < problem.size(); j++)
            {
                if ((float)rand() / RAND_MAX < crossover_rate)
                {
                    Choice old_value = chromosome_1.getAndSet(j, chromosome_2.get(j));
                    chromosome_2.getAndSet(j, old_value);
                }
            }

            // Add new specimens to new population

            Specimen new_specimen_1 = Specimen(chromosome_1);
            Specimen new_specimen_2 = Specimen(chromosome_2);

            new_specimens.push_back(new_specimen_1);
            new_specimens.push_back(new_specimen_2);
        }

        // Replace old population with new population
        specimens = new_specimens;
}

void Population::mutate(float mutation_rate)
{
    for (auto specimen : specimens)
    {
        specimen.mutate(mutation_rate);
    }
}

#endif