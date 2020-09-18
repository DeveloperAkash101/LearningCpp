#ifndef __L3_SeparatingHeaderAndSource_H__
#define __L3_SeparatingHeaderAndSource_H__

/*Instead of Header guards
#pragma once 
can be used
*/

class SimpleBaseClass
{
private:
    int data;

public:
    void setData(int inputValue);

    int getData();
};


#endif




