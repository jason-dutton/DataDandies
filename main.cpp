#include "Classes/myClass.hpp"

int main()
{
    MyClass myObject;
    myObject.readFile("input.txt");
    myObject.reverseNames();
    myObject.writeToFile("output.txt");

    return 0;
}
