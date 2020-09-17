/*
Source Credit: https://thispointer.com//designing-callbacks-in-c-part-1-function-pointers/

Using Function Pointer as callback:
====================================
From a framework we got an API that can build complete message from provided raw data. 
This API will perform following steps,

1.) Add header and footer in raw Data to make the message.
2.) Encrypt the complete message.
3.) Return the message

Now this API knows what header and footer to apply but don’t know about exact 
encryption logic, because that is not fixed to Framework, that can change from 
application to application. As, Encryption Logic is application dependent, therefore 
in this API provides a provision to pass encryption logic as a callback function pointer. 
This API will call back the code of application by calling this passed function pointer.
*/

#include<iostream>
#include<string>


//This encrypt function increment all letters in string by 1.
std::string encryptDataByLetterInc(std::string data)
{
    for(int i = 0; i < data.size(); i++)
    {
        if( (data[i] >= 'a' && data[i] <= 'z' ) || (data[i] >= 'A' && data[i] <= 'Z' ) )
            data[i]++;
    }
    return data;
}

std::string encryptDataByLetterDec(std::string data)
{
    for(int i = 0; i < data.size(); i++)
    {
        if( (data[i] >= 'a' && data[i] <= 'z' ) || (data[i] >= 'A' && data[i] <= 'Z' ) )
            data[i]--;
    }
    return data;
}

std::string buildCompleteMessage(std::string rawData, std::string (* encrypterFunPtr)(std::string) )
{
    // Add some header and footer to data to make it complete message
    rawData = "[HEADER]" + rawData + "[FooTER]";
    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encrypterFunPtr(rawData);
    return rawData;
}


int main()
{
    std::string msg1 = buildCompleteMessage("SampleString1", &encryptDataByLetterInc);
    std::cout<<msg1<<std::endl;

    std::string msg2 = buildCompleteMessage("SampleString2", &encryptDataByLetterDec);
    std::cout<<msg2<<std::endl;

    return 0;
}