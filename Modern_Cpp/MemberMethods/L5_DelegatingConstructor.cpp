#include <iostream>
#include <string>

class SimpleBaseClass
{
private:
    std::string objectName;
    int data;

public:
    SimpleBaseClass();
    SimpleBaseClass(std::string inputName);
    SimpleBaseClass(std::string inputName, int inputData);

    ~SimpleBaseClass();
};

SimpleBaseClass::SimpleBaseClass()
    : SimpleBaseClass{"Un-named", 0}
{
    std::cout << "\nInside No argument constructor";
}

SimpleBaseClass::SimpleBaseClass(std::string inputName)
    : SimpleBaseClass{inputName, 0}
{
    std::cout << "\nInside Single argument constructor";
}

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
    : objectName{inputName}, data{inputData}

{
    std::cout << "\nInside Double argument constructor.";
    std::cout << "\nObject Name: " << objectName << "\nData =" << data;
}

SimpleBaseClass::~SimpleBaseClass()
{
    std::cout << "\nDestructor called for " << objectName;
}

int main()
{
    /*Below you can see contructor overloading*/

    {
        SimpleBaseClass sbcUnnamedObj1;
    }

    {
        SimpleBaseClass sbcNamedObj1("NamedObject_1_WithoutData");
    }

    {
        SimpleBaseClass sbcNamedObjWithData1("NamedObjectWithData1", 15);
    }
    SimpleBaseClass *sbcNamedObjWithDataThroughPointer = new SimpleBaseClass("sbcNamedObjWithDataThroughPointer", 20);

    /*Note:
    1.Destructor calling sequence will be based on delete call sequence
    2.If delete call is not provided,objects through Pointer(on heap)
        will not be deleted.
    */
    delete sbcNamedObjWithDataThroughPointer;

    return 0;
}

/*
Output in terminal:
=====================
Inside Double argument constructor.
Object Name: Un-named
Data =0
Inside No argument constructor
Destructor called for Un-named


Inside Double argument constructor.
Object Name: NamedObject_1_WithoutData
Data =0
Inside Single argument constructor
Destructor called for NamedObject_1_WithoutData


Inside Double argument constructor.
Object Name: NamedObjectWithData1
Data =15
Destructor called for NamedObjectWithData1


Inside Double argument constructor.
Object Name: sbcNamedObjWithDataThroughPointer
Data =20
Destructor called for sbcNamedObjWithDataThroughPointer
*/