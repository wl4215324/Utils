#ifndef WOMAN_H_
#define WOMAN_H_

#include <iostream>

using namespace std;

class PrintNum 
{
public:
    PrintNum(int&);
    void display_num();

private:
    int& age;
};

PrintNum::PrintNum(int& input_num): age(input_num)
{

}

void PrintNum::display_num()
{
    std::cout << "display_num: "<< age << std::endl;
    std::cout <<"display_num: "<< ++age << std::endl;
}

#endif // WOMAN_H_