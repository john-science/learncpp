#include <iostream>
#include "add.h"

#define SOME_TEXT "The sum of "


int main()
{
    std::cout << SOME_TEXT << "3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}
