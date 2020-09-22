#include <iostream>
#include <cstring>
#include <vector>

class CustomStringClass
{
private:
    char *str; // pointer to a char[] that holds a C-style string
public:
    CustomStringClass();                                // No-args contstructor
    CustomStringClass(const char *s);                   // Overloaded contstructor
    CustomStringClass(const CustomStringClass &source); // Copy constructor

    CustomStringClass &operator=(const CustomStringClass &rhs); //Copy Assignment

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
}

// Destructor
CustomStringClass::~CustomStringClass()
{
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
    CustomStringClass a{"Hello"}; // overloaded constructor
    CustomStringClass b;          // no-args contructor
    b = a;                        // copy assignment
                                  // b.operator=(a)
    b = "This is a test";         // b.operator=("This is a test");

    CustomStringClass empty;          // no-args constructor
    CustomStringClass larry("Larry"); // overloaded constructor
    CustomStringClass stooge{larry};  // copy constructor
    CustomStringClass stooges;        // no-args constructor

    empty = stooge; // copy assignment operator

    empty.display();  // Larry : 5
    larry.display();  // Larry : 5
    stooge.display(); // Larry : 5
    empty.display();  // Larry : 5

    stooges = "Larry, Moe, and Curly";
    stooges.display(); // Larry, Moe, and Curly : 21

    std::vector<CustomStringClass> stooges_vec;
    stooges_vec.push_back("Larry");
    stooges_vec.push_back("Moe");
    stooges_vec.push_back("Curly");

    std::cout << "\n=== Loop 1 ==================" << std::endl;
    for (const CustomStringClass &s : stooges_vec)
        s.display(); // Larry
                     // Moe
                     //Curly
    std::cout << "\n=== Loop 2 ==================" << std::endl;
    for (CustomStringClass &s : stooges_vec)
        s = "Changed"; // copy assignment

    std::cout << "\n=== Loop 3 ================" << std::endl;
    for (const CustomStringClass &s : stooges_vec)
        s.display(); // Changed
                     // Changed
                     // Changed

    return 0;
}

/*
Command Line Output
====================
Copy assignment

Copy assignment

Copy assignment
Larry : 5
Larry : 5
Larry : 5
Larry : 5

Copy assignment
Larry, Moe, and Curly : 21

=== Loop 1 ==================
Larry : 5
Moe : 3
Curly : 5

=== Loop 2 ==================

Copy assignment

Copy assignment

Copy assignment

=== Loop 3 ================
Changed : 7
Changed : 7
Changed : 7
*/