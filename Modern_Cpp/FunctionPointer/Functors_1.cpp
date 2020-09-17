/*
Source Credit: https://thispointer.com//designing-callbacks-in-c-part-2-function-objects-functors/

No suppose in our application we want to call this framework API 
three times with 3 different types of encryption logics i.e.

Encrypt by incrementing each letter by 1.
Encrypt by incrementing each letter by 2.
Encrypt by decrementing each letter by 1.

How to this through function pointers,

For this we need to create three different types of functions and use 
them as function pointers while calling this API.
3 different functions here are necessary because normal global 
functions don’t have any state associated with them.

Is there any way to bind state with function pointers?

Answers is yes –  By making the them function objects or functors.

*/

#include <iostream>

class Encryptor 
{
    bool m_isIncremental;
    int m_count;
public:
    Encryptor()  //Default Constructor for initialization
    {
        m_isIncremental = 0;
        m_count = 1;
    }
    Encryptor(bool isInc, int count) 
    {
        m_isIncremental = isInc;
        m_count = count;
    }
    std::string operator()(std::string data) 
    {
        for (int i = 0; i < data.size(); i++)
            if ((data[i] >= 'a' && data[i] <= 'z')
                    || (data[i] >= 'A' && data[i] <= 'Z'))
                if (m_isIncremental)
                    data[i] = data[i] + m_count;
                else
                    data[i] = data[i] - m_count;
        return data;
    }

};

std::string buildCompleteMessage(std::string rawData,
        Encryptor encyptorFuncObj) 
{
    // Add some header and footer to data to make it complete message
    rawData = "[HEADER]" + rawData + "[FooTER]";

    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encyptorFuncObj(rawData);

    return rawData;
}

int main() 
{
    std::string msg = buildCompleteMessage("SampleString", Encryptor(true, 1));
    std::cout << msg << std::endl;

    msg = buildCompleteMessage("SampleString", Encryptor(true, 2));
    std::cout << msg << std::endl;

    msg = buildCompleteMessage("SampleString", Encryptor(false, 1));
    std::cout << msg << std::endl;

    return 0;
}