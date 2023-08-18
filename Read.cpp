#include "myclass.h"

int main()
{
    MyClass myObject;
    myObject.readFile("input.txt");
    myObject.reverseNames();
    myObject.writeToFile("output.txt");

    return 0;
}