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
    :objectName{sourceObject.objectName}, data(sourceObject.data)  //Note * is not used because using address. So works.
{
    std::cout << "\nInside copy constructor for Shallow copy";
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

    /*
    Note:
    The below line will never reach because of exception occuring 
      at destructor for multiple delete
      
      First delete happened when display function create local copy
      but deletes the actual pointer.So the memeory location pointed 
      by data is ivalid.

      Second delete happened while doing Copy using Copy constructor,
      because that also creates a local copy but tries to delete data of
      actual pointer 'data' once agin. 
      Also this the point where exception occurs.

      */
    sbcObjectCreatedFromCopy.setData(50); 

    /*Even if in some compilers if above line executes, it will 
    change the data value of 'data' to 50 in  both  sbcObjectToBeCopied
    and sbcObjectCreatedFromCopy which is unwanted.*/ 

    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor for initialization.
Inside copy constructor for Shallow copy
Inside Display Function..
Object Name: DefaultName
Data =20
Destructor called for DefaultName  ( At this point 'data' was deleted)

Inside copy constructor for Shallow copy
Inside copy constructor for Shallow copy
Inside Display Function..
Object Name: DefaultName
Data =17190560                     (some Garbage value)

*Exception* Occured after this hence no further output 
*/