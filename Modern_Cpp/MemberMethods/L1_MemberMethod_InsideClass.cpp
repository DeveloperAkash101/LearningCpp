#include<iostream>

class SimpleBaseClass
{
    private:
        int data;
    public:
        void setData(int inputValue)
        {
            data = inputValue;
        }

        int getData()
        {
            return data; 
        }
};

int main()
{
    SimpleBaseClass sbcObj1;

    int inputData;
    std::cout<<"\nProvide input data for object: ";
    std::cin>>inputData;

    sbcObj1.setData(inputData);
    std::cout<<"\nClass contains value: "<<sbcObj1.getData();
    return 0;
}


/*
Output in terminal:
=====================
Provide input data for object: 25

Class contains value: 25
*/