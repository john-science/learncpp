#include <iostream>


int main() {
    int array[]{ 5, 23, -7, 99, 312 };

    std::cout << "Element 0 is at address: " << &array[0] << '\n';
    std::cout << "Element 1 is at address: " << &array[1] << '\n';
    std::cout << "Element 2 is at address: " << &array[2] << '\n';
    std::cout << "Element 3 is at address: " << &array[3] << '\n';
    std::cout << "Element 4 is at address: " << &array[4] << '\n';

    return 0;
}
