#include<iostream>

void printInt(int &i)
{
    std::cout<<"\n L-value reference based functionis called";
}

void printInt(int &&i)
{
    std::cout<<"\n R-value reference based functionis called";
}

int main()
{
    int a=5;
    printInt(a);  // Call printInt(int &i)  --> L-value
    printInt(6);  // Call printInt(int &&i) --> R-value
    return 0;
}