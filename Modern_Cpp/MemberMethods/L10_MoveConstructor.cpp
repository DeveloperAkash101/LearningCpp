/*
Note:
With the use of R-values and Move constructor , lots of additional copies 
made unnecessarily can be avoided.

*/

#include <iostream>
#include <string>
#include <vector>

#define IS_MOVE_CONSTRUCTOR_ENABLED 1

class SimpleBaseClass
{
private:
    std::string objectName;
    int *data;

public:
    SimpleBaseClass(std::string inputName, int inputData);
    SimpleBaseClass(const SimpleBaseClass &sourceObject);

#if IS_MOVE_CONSTRUCTOR_ENABLED
    SimpleBaseClass(SimpleBaseClass &&sourceObject) noexcept;
#endif

    std::string getName()
    {
        return objectName;
    }
    void setData(int input)
    {
        *data = input;
    }
    int getData()
    {
        return *data;
    }
    ~SimpleBaseClass();
};

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
{
    objectName = inputName;
    data = new int(inputData);
    std::cout << "\nInside Constructor for initialization.";
}

SimpleBaseClass::SimpleBaseClass(const SimpleBaseClass &sourceObject)
    : SimpleBaseClass{sourceObject.objectName, *sourceObject.data} //Note * is used
{
    std::cout << "\nInside copy constructor for Deep copy";
}

#if IS_MOVE_CONSTRUCTOR_ENABLED
SimpleBaseClass::SimpleBaseClass(SimpleBaseClass &&sourceObject) noexcept
    : objectName{sourceObject.objectName}, data{sourceObject.data} //Note * is not used
{
    sourceObject.data = nullptr;
    std::cout << "\nInside Move constructor.";
}
#endif

SimpleBaseClass::~SimpleBaseClass()
{
    if (data != nullptr)
    {
        std::cout << "\nDestructor freeing data for: " << *data;
    }
    else
    {
        std::cout << "\nDestructor freeing data for nullptr";
    }
    delete data;
    std::cout << "\nDestructor called for " << objectName;
}

void DisplayObjectDetails(SimpleBaseClass objectLocalCopy)
{
    std::cout << "\nInside Display Function..";
    std::cout << "\nObject Name: " << objectLocalCopy.getName() << "\nData =" << objectLocalCopy.getData();
}

int main()
{
    std::vector<SimpleBaseClass> vec;
    vec.push_back(SimpleBaseClass{"Name1", 10});

    std::cout << "\nExiting Main";
    return 0;
}

/*
Output in terminal: ( Notice the additional copy made without Move constructor)
=====================
When IS_MOVE_CONSTRUCTOR_ENABLED = 0
--------------------------------------
Inside Constructor for initialization.
Inside Constructor for initialization.
Inside copy constructor for Deep copy
Destructor freeing data for: 10
Destructor called for Name1

Exiting Main
Destructor freeing data for: 10
Destructor called for Name1

When IS_MOVE_CONSTRUCTOR_ENABLED = 1
--------------------------------------
Inside Constructor for initialization.
Inside Move constructor.
Destructor freeing data for nullptr
Destructor called for Name1

Exiting Main
Destructor freeing data for: 10
Destructor called for Name1

*/