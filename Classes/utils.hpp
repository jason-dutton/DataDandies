#ifndef UTILS
#define UTILS

#include <deque>
#include <cmath>
#include <iostream>
using namespace std;

class Position
{
public:
    Position();
    Position(int x, int y);
    int x;
    int y;
};

Position::Position()
{
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

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
    int static totalDistance;

    Choice getAndSet(int index, Choice choice);
    Choice get(int index);
    void set(int index, Choice choice);
    void add(Choice choice);
    void remove(int index);
    int size();
    double fitness();

private:
    int calculateNotEnoughFoodPenalty();
    int calculateTravelledDistance();
    int calculatePackagesSent();
    int calculateRecoveryMinutes();
    int distanceInStep(int index);
    int calculateWeightPenalty();
};

int Chromosome::totalDistance = 0;

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

double Chromosome::fitness()
{
    double fitness = 0;
    double eqOne = (0.1 * totalDistance * ((calculateTravelledDistance() + 0.01) / totalDistance));
    // cout << "log EqOne: " << log(eqOne) << endl;
    fitness = log(eqOne) + pow(0.8, calculatePackagesSent()) - pow(1.1, calculateRecoveryMinutes()) + (10 / (1 + calculateWeightPenalty()));
    // cout << "Fitness 1: " << fitness << endl;
    fitness = pow(20, fitness);
    // cout << "Fitness before penalty: " << fitness << ", penalty: " << calculateNotEnoughFoodPenalty() << endl;
    // fitness -= calculateNotEnoughFoodPenalty();
    // cout << "Fitness after penalty: " << fitness << endl;
    return fitness;
}

int Chromosome::calculateNotEnoughFoodPenalty()
{
    // calculate from 0 to first node
    int penalty = 0;
    int distance = choices[0].next.x + choices[0].next.y;
    int requiredFood = distance / 10;
    if (distance % 10 > 4)
    {
        requiredFood++;
    }
    if (choices[0].food < requiredFood)
    {
        penalty += requiredFood - choices[0].food;
    }
    // caculate for every subsequent node
    for (int i = 1; i < choices.size(); i++)
    {
        distance = distanceInStep(i);
        requiredFood = distance / 10;
        if (distance % 10 > 4)
        {
            requiredFood++;
        }
        if (choices[i].food < requiredFood)
        {
            penalty += requiredFood - choices[i].food;
        }
    }
    return penalty * 100;
}

/**
 * @brief Calculates the total distance travelled by the team
 */
int Chromosome::calculateTravelledDistance()
{
    // add dist from 0 to first Node
    int travelledDist = choices[0].next.x + choices[0].next.y;
    // start from first entry with its next node
    for (int i = 0; i < choices.size() - 1; i++)
    {
        travelledDist += abs(choices[i].next.x - choices[i + 1].next.x) + abs(choices[i].next.y - choices[i + 1].next.y);
    }
    // cout << "Travelled distance: " << travelledDist << endl;
    return travelledDist;
}

/**
 * @brief Calculates the total packages sent by the team
 */
int Chromosome::calculatePackagesSent()
{
    int packagesSent = 0;
    for (int i = 0; i < choices.size(); i++)
    {
        packagesSent += choices[i].food;
    }
    // cout << "Packages sent: " << packagesSent << endl;
    return packagesSent;
}

/**
 * @brief Calculates the total recovery minutes of the team
 * i.e. if the total food * 10 is greater than the distance between two nodes
 */
int Chromosome::calculateRecoveryMinutes()
{
    // calculate from 0 to first node
    int recoveryMinutes = 0;
    if (choices[0].food * 10 > choices[0].next.x + choices[0].next.y)
    {
        recoveryMinutes += choices[0].food * 10 - choices[0].next.x - choices[0].next.y;
    }
    // start from first entry with its next node using current food number of packages and next node as the destination and previous node's next as the current node
    for (int i = 1; i < choices.size(); i++)
    {
        int recov = choices[i].food * 10 - distanceInStep(i);
        if (recov > 0)
        {
            recoveryMinutes += recov;
        }
    }
    // cout << "Recovery minutes: " << recoveryMinutes << endl;
    return recoveryMinutes;
}

/**
 * @brief Calculates the distance between previous node and current node's next
 *
 * @param index
 * @return int
 */
int Chromosome::distanceInStep(int index)
{
    return abs(choices[index - 1].next.x - choices[index].next.x) + abs(choices[index - 1].next.y - choices[index].next.y);
}

/**
 * @brief Calculates the weight penalty of the team - how many packages are being carried every 10 minutes
 */
int Chromosome::calculateWeightPenalty()
{
    // calculate from 0 to first node
    int weightPenalty = 0;
    int distance = choices[0].next.x + choices[0].next.y;
    for (int i = 1; i < distance; i += 10)
    {
        weightPenalty += i / 10;
    }
    // calculate for every subsequent node
    for (int i = 1; i < choices.size(); i++)
    {
        distance = distanceInStep(i);
        for (int i = 1; i < distance; i += 10)
        {
            weightPenalty += i / 10;
        }
    }
    // cout << "Weight penalty: " << weightPenalty << endl;
    return weightPenalty;
}

class Solution
{
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
    this->time = time;
}

#endif // UTILS
