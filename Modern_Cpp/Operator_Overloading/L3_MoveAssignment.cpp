#include <iostream>
#include <cstring>
#include <vector>

class CustomStringClass
{
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
    CustomStringClass a{"Hello"};  // Overloaded constructor
    a = CustomStringClass{"Hola"}; // Overloaded constructor then move assignment
    a = "Bonjour";                 // Overloaded constructor then move assignment

    CustomStringClass empty;          // no-args constructor
    CustomStringClass larry("Larry"); // overloaded constructor
    CustomStringClass stooge{larry};  // copy constructor
    CustomStringClass stooges;        // no-args constructor

    empty = stooge; // copy assignment operator
                    // stooge is an l-value

    empty = "Funny"; // move assignment operator
                     // "Funny" is an r-value

    empty.display();
    larry.display();
    stooge.display();
    empty.display();

    stooges = "Larry, Moe, and Curly";
    stooges.display();

    std::vector<CustomStringClass> stooges_vec;
    stooges_vec.push_back("Larry"); // Move constructor
    stooges_vec.push_back("Moe");   // Move constructor
    stooges_vec.push_back("Curly"); // Move constructor

    std::cout << "=== Loop 1 ==================" << std::endl;
    for (const CustomStringClass &s : stooges_vec)
        s.display();

    std::cout << "=== Loop 2 ==================" << std::endl;
    for (CustomStringClass &s : stooges_vec)
        s = "Changed"; // move assignment

    std::cout << "=== Loop 3 ==================" << std::endl;
    for (const CustomStringClass &s : stooges_vec)
        s.display();

    return 0;
}

/*
Command Line Output
====================
Using move assignment
Calling destructor for CustomStringClass : nullptr
Using move assignment
Calling destructor for CustomStringClass : nullptr
Copy constructor used

Copy assignment
Using move assignment
Calling destructor for CustomStringClass : nullptr
Funny : 5
Larry : 5
Larry : 5
Funny : 5
Using move assignment
Calling destructor for CustomStringClass : nullptr
Larry, Moe, and Curly : 21
Move constructor used
Calling destructor for CustomStringClass : nullptr
Move constructor used
Copy constructor used
Calling destructor for CustomStringClass : Larry
Calling destructor for CustomStringClass : nullptr
Move constructor used
Copy constructor used
Copy constructor used
Calling destructor for CustomStringClass : Larry
Calling destructor for CustomStringClass : Moe
Calling destructor for CustomStringClass : nullptr
=== Loop 1 ==================
Larry : 5
Moe : 3
Curly : 5
=== Loop 2 ==================
Using move assignment
Calling destructor for CustomStringClass : nullptr
Using move assignment
Calling destructor for CustomStringClass : nullptr
Using move assignment
Calling destructor for CustomStringClass : nullptr
=== Loop 3 ==================
Changed : 7
Changed : 7
Changed : 7
Calling destructor for CustomStringClass : Changed
Calling destructor for CustomStringClass : Changed
Calling destructor for CustomStringClass : Changed
Calling destructor for CustomStringClass : Larry, Moe, and Curly
Calling destructor for CustomStringClass : Larry
Calling destructor for CustomStringClass : Larry
Calling destructor for CustomStringClass : Funny
Calling destructor for CustomStringClass : Bonjour
*/