#ifndef GA
#define GA

#include <deque>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

#include "utils.hpp"

const float SURVIVAL_RATE = 0.5;
const float CROSSOVER_RATE = 0.4;
const float MUTATION_RATE = 0.4;
const float MUTATION_FOOD_RATE = 0.6;
const float MUTATION_FOOD_STD = 1;
const int POPULATION_SIZE = 10000;
const int MAX_GENERATIONS = 10000;

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

    Population(int population_size = POPULATION_SIZE, deque<Position> problem = deque<Position>());

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
    this->fitness = this->chromosome.fitness();
    return this->fitness;
}

Specimen Specimen::randomSpecimen(deque<Position> problem)
{
    Chromosome chromosome = Chromosome();
    
    for (Position position : problem)
    {
        Choice choice;
        choice.food = rand() % 10;
        choice.next = position;
        chromosome.choices.push_back(choice);
    }

    // while (problem.size() > 0)
    // {
    //     Choice choice;
    //     choice.food = rand() % 10;

    //     // pick a number between 0 and problem.size() - 1
    //     int next_index = rand() % problem.size();
    //     choice.next = problem[next_index];
    //     problem.erase(problem.begin() + next_index);

    //     chromosome.choices.push_back(choice);
    // }

    return Specimen(chromosome);
}

// Population

Population::Population(int population_size, deque<Position> problem)
{
    this->problem = problem;

    this->population_size = population_size;

    for (int i = 0; i < population_size; i++)
    {
        this->specimens.push_back(Specimen::randomSpecimen(this->problem));
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
    // until we have enough new specimens, duplicate a random specimen and mutate it

    while (specimens.size() < POPULATION_SIZE) {
        int specimen_index = rand() % specimens.size();
        Specimen specimen = specimens[specimen_index];
        specimen.mutate();
        specimens.push_back(specimen);
    }

    // // Find two random specimens
    // int specimen_1_index = rand() % specimens.size();
    // int specimen_2_index = rand() % specimens.size();
    // if (specimen_1_index == specimen_2_index)
    // {
    //     specimen_2_index = (specimen_2_index + 1) % specimens.size();
    // }

    // Specimen specimen_1 = specimens[specimen_1_index];
    // Specimen specimen_2 = specimens[specimen_2_index];

    // // Generate new population from crossover

    // deque<Specimen> new_specimens;

    // for (int i = 0; i < POPULATION_SIZE / 2; i++)
    // {
    //     Chromosome chromosome_1 = specimen_1.chromosome;
    //     Chromosome chromosome_2 = specimen_2.chromosome;

    //     // Crossover

    //     for (int j = 0; j < problem.size(); j++)
    //     {
    //         if ((float)rand() / RAND_MAX < crossover_rate)
    //         {
    //             Choice old_value = chromosome_1.getAndSet(j, chromosome_2.get(j));
    //             chromosome_2.getAndSet(j, old_value);
    //         }
    //     }

    //     // Add new specimens to new population

    //     Specimen new_specimen_1 = Specimen(chromosome_1);
    //     Specimen new_specimen_2 = Specimen(chromosome_2);

    //     new_specimens.push_back(new_specimen_1);
    //     new_specimens.push_back(new_specimen_2);
    // }

    // // Replace old population with new population
    // specimens = new_specimens;
}

void Population::mutate(float mutation_rate)
{
    for (auto specimen : specimens)
    {
        specimen.mutate(mutation_rate);
    }
}

class GeneticAlgorithm
{
    Population population = Population(0);
    deque<Position> problem;

public:
    GeneticAlgorithm(deque<Position> problem)
    {
        this->problem = problem;
        this->population = Population(POPULATION_SIZE, problem);
    }

    Solution execute(int number_of_generations = MAX_GENERATIONS)
    {
        srand(time(NULL));

        auto start_time = std::chrono::high_resolution_clock::now();

        float best_fitness = 0;

        // Evolution
        for (int generation = 0; generation < number_of_generations; generation++)
        {
            // Cull
            population.cull();

            best_fitness = max(best_fitness, population.specimens[0].getFitness());

            // Crossover
            // population.crossover();

            // Mutate
            population.mutate();
        }

        // Sort specimens by fitness
        sort(population.specimens.begin(), population.specimens.end(), [](Specimen a, Specimen b)
             { return a.getFitness() < b.getFitness(); });

        auto end_time = std::chrono::high_resolution_clock::now();
        long elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

        cout << "Best Fitness Found: " << best_fitness << endl;

        best_fitness = population.specimens[0].getFitness();
        
        // Return best specimen
        return Solution(problem, population.specimens[0].chromosome, elapsed_time, best_fitness);
    }
};
#endif