/*
Note:
 An object's copy constructor is 
 called (automatically, not by the programmer) when it is created, 
 and needs to be initialized to be a copy of an existing object. 
 This happens when an object is:

    1.passed as a value parameter to a function,
    2.returned (by value) as a function result,
    3.declared with initialization from an existing 
      object of the same class. 

To accomplish above, compiler has to(and does) provide 
a copy constructor is not defined by author.

Best Practices:
1.Provide copy constructor(with a const reference parameter) 
   when your class has raw pointers.
2.STL classes already provide copy constructors.

*/

#include <iostream>
#include <string>

class SimpleBaseClass
{
private:
    std::string objectName;
    int data;

public:
    SimpleBaseClass(std::string inputName = "DefaultName", int inputData = 20);
    SimpleBaseClass(const SimpleBaseClass &sourceObject);
    std::string getName()
    {
        return objectName;
    }
    int getData()
    {
        return data;
    }
    ~SimpleBaseClass();
};

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
    : objectName{inputName}, data{inputData}

{
    std::cout << "\nInside Constructor for initialization.";
}

SimpleBaseClass::SimpleBaseClass(const SimpleBaseClass &sourceObject)
    //:objectName{sourceObject.objectName}, data{sourceObject.data}
    : SimpleBaseClass{sourceObject.objectName, sourceObject.data}
{
    std::cout << "\nInside copy constructor";
}

SimpleBaseClass::~SimpleBaseClass()
{
    std::cout << "\nDestructor called for " << objectName;
}

void DisplayObjectDetails(SimpleBaseClass objectLocalCopy)
{
    std::cout << "\nInside Display Function..";
    std::cout << "\nObject Name: " << objectLocalCopy.getName() << "\nData =" << objectLocalCopy.getData();
}

int main()
{

    SimpleBaseClass sbcObjectToBeCopied;
    DisplayObjectDetails(sbcObjectToBeCopied);

    SimpleBaseClass sbcObjectCreatedFromCopy(sbcObjectToBeCopied);
    DisplayObjectDetails(sbcObjectCreatedFromCopy);

    SimpleBaseClass sbcNamedObjWithData("NamedObjectWithData", 10);
    DisplayObjectDetails(sbcNamedObjWithData);
    SimpleBaseClass *sbcNamedObjWithDataThroughPointer = new SimpleBaseClass(sbcNamedObjWithData);
    DisplayObjectDetails(*sbcNamedObjWithDataThroughPointer); //Note the * mark for value

    delete sbcNamedObjWithDataThroughPointer;

    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor for initialization.
Inside Constructor for initialization.
Inside copy constructor
Inside Display Function..
Object Name: DefaultName
Data =20
Destructor called for DefaultName


Inside Constructor for initialization.
Inside copy constructor
Inside Constructor for initialization.
Inside copy constructor
Inside Display Function..
Object Name: DefaultName
Data =20
Destructor called for DefaultName


Inside Constructor for initialization.
Inside Constructor for initialization.
Inside copy constructor
Inside Display Function..
Object Name: NamedObjectWithData
Data =10
Destructor called for NamedObjectWithData

Inside Constructor for initialization.
Inside copy constructor
Inside Constructor for initialization.
Inside copy constructor
Inside Display Function..
Object Name: NamedObjectWithData
Data =10

Destructor called for NamedObjectWithData
Destructor called for NamedObjectWithData
Destructor called for NamedObjectWithData
Destructor called for DefaultName
Destructor called for DefaultName
*/