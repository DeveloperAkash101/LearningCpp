#include <iostream>
#include "L3_SeparatingHeaderAndSource.h"

int main()
{
    SimpleBaseClass sbcObj1;

    int inputData;
    std::cout << "\nProvide input data for object: ";
    std::cin >> inputData;

    sbcObj1.setData(inputData);
    std::cout << "\nClass contains value: " << sbcObj1.getData();
    return 0;
}

/*
Output in terminal:
=====================
Provide input data for object: 25

Class contains value: 25
*/