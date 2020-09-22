#include <iostream>
#include <cstring>
#include <vector>
#include <cctype> //For use of bool

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

    /*below three lines are operators as member function*/
    CustomStringClass operator-() const;                             // make lowercase
    CustomStringClass operator+(const CustomStringClass &rhs) const; // concatenate
    bool operator==(const CustomStringClass &rhs) const;             //check equality

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

// Equality
bool CustomStringClass::operator==(const CustomStringClass &rhs) const
{
    return (std::strcmp(str, rhs.str) == 0);
}

// Make lowercase
CustomStringClass CustomStringClass::operator-() const
{
    char *buff = new char[std::strlen(str) + 1];
    std::strcpy(buff, str);
    for (size_t i = 0; i < std::strlen(buff); i++)
        buff[i] = std::tolower(buff[i]);
    CustomStringClass temp{buff};
    delete[] buff;
    return temp;
}

// Concatentate
CustomStringClass CustomStringClass::operator+(const CustomStringClass &rhs) const
{
    char *buff = new char[std::strlen(str) + std::strlen(rhs.str) + 1];
    std::strcpy(buff, str);
    std::strcat(buff, rhs.str);
    CustomStringClass temp{buff};
    delete[] buff;
    return temp;
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
    std::cout << std::boolalpha << std::endl;

    CustomStringClass larry{"Larry"};
    CustomStringClass moe{"Moe"};

    CustomStringClass stooge = larry;
    larry.display(); // Larry
    moe.display();   // Moe

    std::cout << (larry == moe) << std::endl;    // false
    std::cout << (larry == stooge) << std::endl; // true

    larry.display(); // Larry
    CustomStringClass larry2 = -larry;
    larry2.display(); // larry

    CustomStringClass stooges = larry + "Moe"; // ok with member function
    //CustomStringClass stooges = "Larry" + moe;                                 // Compiler error

    CustomStringClass two_stooges = moe + " " + "Larry";
    two_stooges.display();
    // Moe Larry
    CustomStringClass three_stooges = moe + " " + larry + " " + "Curly";
    three_stooges.display(); //  Moe Larry Curly

    return 0;
}

/*
Command Line Output
====================
Copy constructor used
Larry : 5
Moe : 3
false
true
Larry : 5
larry : 5
Calling destructor for CustomStringClass : Moe
Calling destructor for CustomStringClass : Moe
Calling destructor for CustomStringClass :
Calling destructor for CustomStringClass : Larry
Moe Larry : 9
Calling destructor for CustomStringClass : Moe Larry
Calling destructor for CustomStringClass : Moe Larry
Calling destructor for CustomStringClass : Moe
Calling destructor for CustomStringClass :
Calling destructor for CustomStringClass :
Calling destructor for CustomStringClass : Curly
Moe Larry Curly : 15
Calling destructor for CustomStringClass : Moe Larry Curly
Calling destructor for CustomStringClass : Moe Larry
Calling destructor for CustomStringClass : LarryMoe
Calling destructor for CustomStringClass : larry
Calling destructor for CustomStringClass : Larry
Calling destructor for CustomStringClass : Moe
Calling destructor for CustomStringClass : Larry
*/