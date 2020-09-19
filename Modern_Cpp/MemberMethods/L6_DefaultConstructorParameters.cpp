#include <iostream>
#include <string>

class SimpleBaseClass
{
private:
    std::string objectName;
    int data;

public:
    //SimpleBaseClass();   //Not required as Constructor with Default Params exists
    //SimpleBaseClass(std::string inputName); //Not required as Constructor with Default Params exists
    SimpleBaseClass(std::string inputName = "DefaultName", int inputData = 20);

    ~SimpleBaseClass();
};

// SimpleBaseClass::SimpleBaseClass()
//     : SimpleBaseClass{"Un-named", 0}
// {
//     std::cout << "\nInside No argument constructor";
// }

// SimpleBaseClass::SimpleBaseClass(std::string inputName)
//     : SimpleBaseClass{inputName, 0}
// {
//     std::cout << "\nInside Single argument constructor";
// }

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
    : objectName{inputName}, data{inputData}

{
    std::cout << "\nInside Constructor with default arguments.";
    std::cout << "\nObject Name: " << objectName << "\nData =" << data;
}

SimpleBaseClass::~SimpleBaseClass()
{
    std::cout << "\nDestructor called for " << objectName;
}

int main()
{

    SimpleBaseClass sbcUnnamedObj;

    SimpleBaseClass sbcNamedObj("NamedObjectWithoutData");

    SimpleBaseClass sbcNamedObjWithData("NamedObjectWithData", 10);
    SimpleBaseClass *sbcNamedObjWithDataThroughPointer = new SimpleBaseClass("sbcNamedObjWithDataThroughPointer", 15);

    delete sbcNamedObjWithDataThroughPointer;

    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor with default arguments.
Object Name: DefaultName
Data =20

Inside Constructor with default arguments.
Object Name: NamedObjectWithoutData
Data =20

Inside Constructor with default arguments.
Object Name: NamedObjectWithData
Data =10

Inside Constructor with default arguments.
Object Name: sbcNamedObjWithDataThroughPointer
Data =15

Destructor called for sbcNamedObjWithDataThroughPointer
Destructor called for NamedObjectWithData
Destructor called for NamedObjectWithoutData
Destructor called for DefaultName
*/