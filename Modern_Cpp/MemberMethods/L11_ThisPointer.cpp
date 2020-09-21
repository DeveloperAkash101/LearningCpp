/*
Note:
======
'this' is a reserved keyword that acts as a pointer to current object 
inside class scope.

Can be used to:
1.Check if during copy constructor, same object calls itself
2.to isolate local parameter and class variable when they have same name
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
    std::string getName();
    int getData();
    void setData(int data);
    ~SimpleBaseClass();
};

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
{
    objectName = inputName;
    data = inputData;
    std::cout << "\nInside Constructor for initialization.";
}

SimpleBaseClass::SimpleBaseClass(const SimpleBaseClass &sourceObject)
{
    if(this == &sourceObject)
    {
        std::cout<<"\n The same object has called itself for copying data.";
    }
    else
    {
        this->objectName= sourceObject.objectName;
        this->data= sourceObject.data; 
        std::cout << "\nInside copy constructor";
    }
    
    
}
std::string SimpleBaseClass::getName()
    {
        return objectName;
    }

int SimpleBaseClass::getData()
    {
        return data;
    }

void SimpleBaseClass::setData(int data)
{
    this->data = data;  /* Notice the local variable 
                           name and class memeber name 
                           is same here- "data",
                           otherwise zero/garbage will be assigned */ 
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

    SimpleBaseClass sbcObjectToBeCopied("GoodName",25);
    sbcObjectToBeCopied=sbcObjectToBeCopied;
    //SimpleBaseClass sbcObjectToBeCreated(sbcObjectToBeCopied); //Copy Constructor , self copy

    sbcObjectToBeCopied.setData(55);// Value will be copied to local param

    DisplayObjectDetails(sbcObjectToBeCopied);

    std::cout<<"\nExiting Main";
    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor for initialization.
Inside copy constructor
Inside Display Function..
Object Name: GoodName
Data =55
Destructor called for GoodName
Exiting Main
Destructor called for GoodName
*/