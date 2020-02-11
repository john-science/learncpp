/* g++ main.cpp --std=c++17 -o pointers.exe

Helpful video on the differences between references and pointers:
https://www.youtube.com/watch?v=sxHng1iufQE

 */
#include <iostream>


int main() {
    int* ptr;
    std::cout << "\nint* ptr;\tprint(ptr)\t" << ptr << "\n\n";      // 0x55e2034d5800

    int var = 7;
    std::cout << "int var = 7;\tprint(var)\t" << var << "\n\n";     // 7

    int foo = 21;
    std::cout << "int foo = 21;\tprint(foo)\t" << foo << "\n\n";    // 21

    ptr = &var;
    std::cout << "ptr = &var;\tprint(ptr)\t" << ptr << "\n\n";      // 0x7ffe905efbd0

    ptr = &foo;
    std::cout << "ptr = &foo;\tprint(ptr)\t" << ptr << "\n\n";      // 0x7ffe905efbd4

    int& ref = var;
    std::cout << "int& ref = var;\tprint(ref)\t" << ref << "\n\n";  // 7


    // testing various other nonsense
    std::cout << "\nprint(ptr)\t" << ptr << "\n\n";                 // 0x7ffe905efbd0

    std::cout << "print(*ptr)\t" << *ptr << "\n";                   // 21
    std::cout << "print(&*ptr)\t" << &*ptr << "\n";                 // 0x7ffe905efbd0
    std::cout << "print(*&*ptr)\t" << *&*ptr << "\n\n";             // 21

    std::cout << "print(&ptr)\t" << &ptr << "\n";                   // 0x7ffe905efbd0
    std::cout << "print(*&ptr)\t" << *&ptr << "\n";                 // 0x7ffe905efbd0
    std::cout << "print(&*&ptr)\t" << &*&ptr << "\n";               // 0x7ffe905efbd0

    return 0;
}
