#include<iostream>

void printInt(int &i)
{
    std::cout<<"\n L-value reference based functionis called";
}

void printInt(int &&i)
{
    std::cout<<"\n R-value reference based functionis called";
}

void printInt(int i)   /*This function creates abuiguity and error */
{
    std::cout<<"\n Ambiguous functionis called";
}


int main()
{
    int a=5;
    printInt(a);  // doesn't know which one to call, ambiguity error
    printInt(6);  // doesn't know which one to call, ambiguity error
    return 0;
}

/*
Conclusion:
You can only overload the function with L-value and R-value reference
*/