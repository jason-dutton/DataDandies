#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
#include <vector>

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

#endif