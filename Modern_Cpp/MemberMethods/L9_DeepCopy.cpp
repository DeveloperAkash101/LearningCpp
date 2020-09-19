/*
Note:
For demonstration of shallow copy raw pointer is necessary.
It will show only pointer getting copied instead of 
creation of new data on heap.This is where problem arises.

*/

#include <iostream>
#include <string>

class SimpleBaseClass
{
private:
    std::string objectName;
    int *data;

public:
    SimpleBaseClass(std::string inputName = "DefaultName", int inputData = 20);
    SimpleBaseClass(const SimpleBaseClass &sourceObject);
    std::string getName()
    {
        return objectName;
    }
    void setData(int input)
    {
        *data=input;
    }
    int getData()
    {
        return *data;
    }
    ~SimpleBaseClass();
};

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
    : objectName{inputName}

{
    data = new int(inputData);
    std::cout << "\nInside Constructor for initialization.";
}

SimpleBaseClass::SimpleBaseClass(const SimpleBaseClass &sourceObject)
    :SimpleBaseClass{sourceObject.objectName,*(sourceObject.data)}  //Note * is used
{
    std::cout << "\nInside copy constructor for Deep copy";
}

SimpleBaseClass::~SimpleBaseClass()
{
    delete data;  // Exception Occured at this point because of multiple delete
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

    std::cout<<"\nFinal Display";
    sbcObjectCreatedFromCopy.setData(50); 
    DisplayObjectDetails(sbcObjectToBeCopied); 
    DisplayObjectDetails(sbcObjectCreatedFromCopy);

    std::cout<<"\nExiting Main";
    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor for initialization.
Inside Constructor for initialization.
Inside copy constructor for Deep copy
Inside Display Function..
Object Name: DefaultName
Data =20
Destructor called for DefaultName

Inside Constructor for initialization.
Inside copy constructor for Deep copy
Inside Constructor for initialization.
Inside copy constructor for Deep copy
Inside Display Function..
Object Name: DefaultName
Data =20
Destructor called for DefaultName

Final Display

Inside Constructor for initialization.
Inside copy constructor for Deep copy
Inside Display Function..
Object Name: DefaultName
Data =20
Destructor called for DefaultName

Inside Constructor for initialization.
Inside copy constructor for Deep copy
Inside Display Function..
Object Name: DefaultName
Data =50
Destructor called for DefaultName

Exiting Main

Destructor called for DefaultName
Destructor called for DefaultName
*/