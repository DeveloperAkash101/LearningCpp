#include <iostream>
#include <cstring>
#include <vector>
#include <cctype> //For use of bool

class CustomStringClass
{
    friend std::ostream &operator<<(std::ostream &os, const CustomStringClass &rhs);
    friend std::istream &operator>>(std::istream &in, CustomStringClass &rhs);

private:
    char *str; // pointer to a char[] that holds a C-style string
public:
    CustomStringClass();              // No-args contstructor
    CustomStringClass(const char *s); // Overloaded contstructor

    CustomStringClass(const CustomStringClass &source);         // Copy constructor
    CustomStringClass &operator=(const CustomStringClass &rhs); //Copy Assignment

    CustomStringClass(CustomStringClass &&source);         // Move constructor
    CustomStringClass &operator=(CustomStringClass &&rhs); // Move assignment

    ~CustomStringClass(); // Destructor

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
    std::cout << "Copy constructor used" << std::endl;
}

// Move constructor
CustomStringClass::CustomStringClass(CustomStringClass &&source)
    : str(source.str)
{
    source.str = nullptr;
    std::cout << "Move constructor used" << std::endl;
}

// Destructor
CustomStringClass::~CustomStringClass()
{
    if (str == nullptr)
    {
        std::cout << "Calling destructor for CustomStringClass : nullptr" << std::endl;
    }
    else
    {
        std::cout << "Calling destructor for CustomStringClass : " << str << std::endl;
    }
    delete[] str;
}

// Copy assignment
CustomStringClass &CustomStringClass::operator=(const CustomStringClass &rhs)
{
    std::cout << "\nCopy assignment" << std::endl;
    if (this == &rhs)
        return *this;
    delete[] this->str;
    str = new char[std::strlen(rhs.str) + 1];
    std::strcpy(this->str, rhs.str);
    return *this;
}

// Move assignment
CustomStringClass &CustomStringClass::operator=(CustomStringClass &&rhs)
{
    std::cout << "Using move assignment" << std::endl;
    if (this == &rhs)
        return *this;
    delete[] str;
    str = rhs.str;
    rhs.str = nullptr;
    return *this;
}

// overloaded insertion operator
std::ostream &operator<<(std::ostream &osObject, const CustomStringClass &rhs)
{
    osObject << rhs.str;
    return osObject;
}

// overloaded extraction operator
std::istream &operator>>(std::istream &isObject, CustomStringClass &rhs)
{
    char *buff = new char[1000];
    isObject >> buff;
    rhs = CustomStringClass{buff};
    delete[] buff;
    return isObject;
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
    CustomStringClass larry{"Larry"};
    CustomStringClass moe{"Moe"};
    CustomStringClass curly;

    std::cout << "Enter the third stooge's first name: ";
    std::cin >> curly;

    std::cout << "The three stooges are " << larry << ", " << moe << ", and " << curly << std::endl;

    std::cout << "\nEnter the three stooges names separated by a space: ";
    std::cin >> larry >> moe >> curly;

    std::cout << "The three stooges are " << larry << ", " << moe << ", and " << curly << std::endl;

    return 0;
}

/*
Command Line Output
====================
Enter the third stooge's first name: asdf
Using move assignment
Calling destructor for CustomStringClass : nullptr
The three stooges are Larry, Moe, and asdf

Enter the three stooges names separated by a space: asdf ghik lmnp
Using move assignment
Calling destructor for CustomStringClass : nullptr
Using move assignment
Calling destructor for CustomStringClass : nullptr
Using move assignment
Calling destructor for CustomStringClass : nullptr
The three stooges are asdf, ghik, and lmnp
Calling destructor for CustomStringClass : lmnp
Calling destructor for CustomStringClass : ghik
Calling destructor for CustomStringClass : asdf
*/