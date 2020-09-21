/*
Note:
Static member function can access only static data members.

*/

#include <iostream>
#include <string>

class SimpleBaseClass
{
private:
    std::string objectName;
    int data;

public:
    static int numberOfObjects;

    SimpleBaseClass(std::string inputName = "DefaultName", int inputData = 20);
    SimpleBaseClass(const SimpleBaseClass &sourceObject);
    static int getNumberOfObjects();

    ~SimpleBaseClass();
};

int SimpleBaseClass::numberOfObjects = 0;

int SimpleBaseClass::getNumberOfObjects()
{
    return numberOfObjects;
}

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
    : objectName{inputName}, data{inputData}
{
    numberOfObjects++;
    std::cout << "\nInside Constructor for initialization.";
}

SimpleBaseClass::~SimpleBaseClass()
{
    numberOfObjects--;
    std::cout << "\nDestructor called for " << objectName;
}

int main()
{

    SimpleBaseClass sbcObject1;
    std::cout << "\nNumber of objects active: " << SimpleBaseClass::getNumberOfObjects();

    {
        SimpleBaseClass sbcObject2;
        std::cout << "\nNumber of objects active: " << SimpleBaseClass::getNumberOfObjects();
    }
    std::cout << "\nNumber of objects active: " << SimpleBaseClass::getNumberOfObjects();

    SimpleBaseClass *sbcObject3 = new SimpleBaseClass();
    std::cout << "\nNumber of objects active: " << SimpleBaseClass::getNumberOfObjects();

    std::cout << "\nExiting Main";
    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor for initialization.
Number of objects active: 1

Inside Constructor for initialization.
Number of objects active: 2
Destructor called for DefaultName
Number of objects active: 1

Inside Constructor for initialization.
Number of objects active: 2
Exiting Main
Destructor called for DefaultName
*/