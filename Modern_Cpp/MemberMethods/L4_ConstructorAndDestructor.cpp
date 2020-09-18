#include <iostream>
#include <string>

class SimpleBaseClass
{
private:
    std::string objectName;
    int data;

public:
    SimpleBaseClass()
    {
        objectName = "Un-named ObjectWithoutData";
        data = 5;
        std::cout << "\nNo argument constructor called for " << objectName;
    }
    
    SimpleBaseClass(std::string inputName)
    {
        objectName = inputName;
        data = 10;
        std::cout << "\nSingle argument constructor called for " << objectName;
    }
    
    SimpleBaseClass(std::string inputName, int inputData)
    {
        objectName = inputName;
        data = inputData;
        std::cout << "\nDouble argument constructor called for " << objectName;
    }
    
    ~SimpleBaseClass()
    {
        std::cout << "\nDestructor called for " << objectName;

    }
};

int main()
{
    /*Below you can see contructor overloading*/

    {
        SimpleBaseClass sbcUnnamedObj1;
    }

    {
        SimpleBaseClass sbcNamedObj1("NamedObject_1_WithoutData");
        SimpleBaseClass sbcNamedObj2("NamedObject_2_WithoutData");
        SimpleBaseClass sbcNamedObj3("NamedObject_3_WithoutData");
    }

    {
        SimpleBaseClass sbcNamedObjWithData("NamedObjectWithData", 15);
    }
    SimpleBaseClass *sbcNamedObj4 = new SimpleBaseClass("NamedObjectThroughPointer");
    SimpleBaseClass *sbcNamedObjWithDataThroughPointer = new SimpleBaseClass("sbcNamedObjWithDataThroughPointer", 20);

    /*Note:
    1.Destructor calling sequence will be based on delete call sequence
    2.If delete call is not provided,objects through Pointer(on heap)
        will not be deleted.
    */
    delete sbcNamedObj4;
    delete sbcNamedObjWithDataThroughPointer;


    return 0;
}

/*
Output in terminal:
=====================
No argument constructor called for Un-named ObjectWithoutData
Destructor called for Un-named ObjectWithoutData

Single argument constructor called for NamedObject_1_WithoutData
Single argument constructor called for NamedObject_2_WithoutData
Single argument constructor called for NamedObject_3_WithoutData
Destructor called for NamedObject_3_WithoutData
Destructor called for NamedObject_2_WithoutData
Destructor called for NamedObject_1_WithoutData

Double argument constructor called for NamedObjectWithData
Destructor called for NamedObjectWithData

Single argument constructor called for NamedObjectThroughPointer
Double argument constructor called for sbcNamedObjWithDataThroughPointer
Destructor called for NamedObjectThroughPointer
Destructor called for sbcNamedObjWithDataThroughPointer
*/