#include <iostream>
#include <cstring>

class CustomStringClass
{
private:
    char *str; // pointer to a char[] that holds a C-style string
public:
    CustomStringClass();                                // No-args contstructor
    CustomStringClass(const char *s);                   // Overloaded contstructor
    CustomStringClass(const CustomStringClass &source); // Copy constructor
    ~CustomStringClass();                               // Destructor
    void display() const;
    int getLength() const; // getters
    const char *getString() const;
};

// No-args constructor
CustomStringClass::CustomStringClass()
    : str{nullptr}
{
    str = new char[1];
    *str = '\0';
}

// Overloaded constructor
CustomStringClass::CustomStringClass(const char *s)
    : str{nullptr}
{
    if (s == nullptr)
    {
        str = new char[1];
        *str = '\0';
    }
    else
    {
        str = new char[std::strlen(s) + 1];
        std::strcpy(str, s);
    }
}

// Copy constructor
CustomStringClass::CustomStringClass(const CustomStringClass &source)
    : str{nullptr}
{
    str = new char[std::strlen(source.str) + 1];
    std::strcpy(str, source.str);
}

// Destructor
CustomStringClass::~CustomStringClass()
{
    delete[] str;
}

// Display method
void CustomStringClass::display() const
{
    std::cout << str << " : " << getLength() << std::endl;
}

// length getter
int CustomStringClass::getLength() const
{
    return std::strlen(str);
}

// string getter
const char *CustomStringClass::getString() const
{
    return str;
}


int main() 
{
    CustomStringClass cscObj1;                      // no-args constructor
    CustomStringClass cscObj2("DefaultString");             // overloaded constructor
    CustomStringClass cscObj3{cscObj2};            // copy constructor 
    
    cscObj1.display();
    cscObj2.display();
    cscObj3.display();
    
    return 0;
}

/*
Command Line Output
====================
 : 0      -------------------> Represents empty string
DefaultString : 13
DefaultString : 13
*/