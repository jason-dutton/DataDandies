#ifndef MYCLASS
#define MYCLASS

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

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

    std::string name;
    while (std::getline(file, name))
    {
        names.push_back(name);
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
