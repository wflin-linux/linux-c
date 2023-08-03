/*实现了Hello::print()*/
#include <iostream>

#include "shared/Hello.h"

using namespace std;

void Hello::print()
{
    std::cout << "Hello Shared Library!" << std::endl;
}