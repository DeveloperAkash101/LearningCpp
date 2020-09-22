/*
Note:
Static member function can access only static data members.

*/

#include <iostream>
#include <string>

/*Forward declarations of classes to avoid any error in compilation*/
class OneFriendClass;
class AnotherBaseClass;
class SimpleBaseClass;

class AnotherBaseClass
{
public:
    void displaySimpleBaseClass(SimpleBaseClass &obj); //Member function of another class
};

class SimpleBaseClass
{
private:
    std::string objectName;
    int data;

    /*Friend Declarations below*/
    friend void displaySimpleBaseClass(SimpleBaseClass &obj);                   //non-member friend function
    friend void AnotherBaseClass::displaySimpleBaseClass(SimpleBaseClass &obj); //Member function of another class
    friend class OneFriendClass;                                                //A class as a friend

public:
    SimpleBaseClass(std::string inputName = "DefaultName", int inputData = 20);
    SimpleBaseClass(const SimpleBaseClass &sourceObject);
    ~SimpleBaseClass();
};

SimpleBaseClass::SimpleBaseClass(std::string inputName, int inputData)
    : objectName{inputName}, data{inputData}
{
    std::cout << "\nInside Constructor for initialization.";
}

SimpleBaseClass::~SimpleBaseClass()
{
    std::cout << "\nDestructor called for " << objectName;
}

void displaySimpleBaseClass(SimpleBaseClass &obj) //Member function of another class
{
    obj.objectName = "ChangedName";
    obj.data = 50;
    std::cout << "\nObject Name(changed):  " << obj.objectName;
    std::cout << "\nObject Data(Changed): " << obj.data;
}

void AnotherBaseClass::displaySimpleBaseClass(SimpleBaseClass &obj) //Member function of another class
{
    obj.objectName = "ChangedNameFurther";
    obj.data = 82;
    std::cout << "\nObject Name(changed further):  " << obj.objectName;
    std::cout << "\nObject Data(Changed further): " << obj.data;
}

class OneFriendClass
{
private:
    int friendData;

public:
    void displaySimpleBaseClass(SimpleBaseClass &obj)
    {
        obj.objectName = "ChangedNameFurtherMore";
        obj.data = 98;
        std::cout << "\nObject Name(changed further more):  " << obj.objectName;
        std::cout << "\nObject Data(Changed further more): " << obj.data;
    }
};

int main()
{

    SimpleBaseClass sbcObject{"myName", 50};
    AnotherBaseClass abcObject;
    OneFriendClass ofcObject;

    displaySimpleBaseClass(sbcObject);
    abcObject.displaySimpleBaseClass(sbcObject);
    ofcObject.displaySimpleBaseClass(sbcObject);

    std::cout << "\nExiting Main";
    return 0;
}

/*
Output in terminal:
=====================
Inside Constructor for initialization.

Object Name(changed):  ChangedName
Object Data(Changed): 50

Object Name(changed further):  ChangedNameFurther
Object Data(Changed further): 82

Object Name(changed further more):  ChangedNameFurtherMore
Object Data(Changed further more): 98

Exiting Main
Destructor called for ChangedNameFurtherMore

*/