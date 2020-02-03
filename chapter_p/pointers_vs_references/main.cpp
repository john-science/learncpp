/** g++ main.cpp --std=c++17 -o pointers.exe
  *
  * Helpful video on the differences between references and pointers:
  * https://www.youtube.com/watch?v=sxHng1iufQE
  *
  *
  */
#include <iostream>


int main() {
    int* ptr;
    std::cout << "\nint* ptr;\tprint(ptr)\t" << ptr << "\n\n";

    int var = 7;
    std::cout << "int var = 7;\tprint(var)\t" << var << "\n\n";

    int foo = 21;
    std::cout << "int foo = 21;\tprint(foo)\t" << foo << "\n\n";

    ptr = &var;
    std::cout << "ptr = &var;\tprint(ptr)\t" << ptr << "\n\n";

    ptr = &foo;
    std::cout << "ptr = &foo;\tprint(ptr)\t" << ptr << "\n\n";

    int& ref = var;
    std::cout << "int& ref = var;\tprint(ref)\t" << ref << "\n\n";

    return 0;
}