#include <iostream>


int main() {
    short value = 7;
    short otherValue = 3;
    short *ptr = &value;

    std::cout << "\n\n";
    std::cout << "The address and value in it can be referred to in a few ways:\n\n";
    std::cout << &value << '\n';  // 0x7fff6ec3ceec
    std::cout << value << '\n';   // 7
    std::cout << ptr << '\n';     // 0x7fff6ec3ceec
    std::cout << *ptr << '\n';    // 7
    std::cout << '\n';

    std::cout << "You can change the value at an address using pointers:\n\n";
    *ptr = 9;
    
    std::cout << &value << '\n';  // 0x7fff6ec3ceec
    std::cout << value << '\n';   // 9
    std::cout << ptr << '\n';     // 0x7fff6ec3ceec
    std::cout << *ptr  << '\n';   // 9
    std::cout << '\n';
    
    std::cout << "You can also re-assign where a pointer is pointing:\n\n";
    ptr = &otherValue;
    
    std::cout << &otherValue << '\n';  // 0x7fff6ec3ceee
    std::cout << otherValue << '\n';   // 3
    std::cout << ptr << '\n';          // 0x7fff6ec3ceee
    std::cout << *ptr << '\n';         // 3
    std::cout << '\n';
    
    std::cout << "A pointer (on my machine) is 8 bytes (64 bits)\n";
    std::cout << sizeof(ptr) << '\n';   // 8
    std::cout << "\nBut the value at the pointer is a short (so 2 bytes)\n";
    std::cout << sizeof(*ptr) << '\n';  // 2
    std::cout << "\n\n";

    return 0;
}

