#include <iostream>
#include <iterator> // for std::size

using namespace std;

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    wendy, // 5
    max_students // 6
};

// FUN FACT: the input array can be defined as "const in prime" if you want to ensure the array isn't edited
void passFixedSizeArray(int prime[5]) // prime is the actual array
{
    prime[0] = 2; // so changing it here will change the original argument!
    prime[1] = 3;
    prime[2] = 5;
    prime[3] = 7;
    prime[4] = 11;
}


int main()
{
    // initializing arrays
    std::cout << "If we don't fully initialize an array, the g++ standard is to insert zeros.\n";
    std::cout << "I hate this, let's just explicitly initialize our arrays.\n";
    int array[5]{ 7, 4, 5 }; // only initialize first 3 elements
    std::cout << array[0] << '\n';
    std::cout << array[1] << '\n';
    std::cout << array[2] << '\n';
    std::cout << array[3] << '\n';
    std::cout << array[4] << '\n';

    // enums to index arrays
    std::cout << "\n\nWe can use enums to make indexing our arrays more meaningful.\n";
    int testScores[max_students]{}; // allocate 6 integers
    testScores[stan] = 76;
    std::cout << testScores[stan] << '\n';

    // functions taking fixed-length arrays
    std::cout << "\n\nPassing arrays of fixed length to functions is very easy (doesn't require pointers):\n";
    int prime[5]{ 0, 1, 2, 3, 4 };
    std::cout << "before passArray: " << prime[0] << " " << prime[1] << " " << prime[2] << " " << prime[3] << " " << prime[4] << '\n';
    passFixedSizeArray(prime);
    std::cout << "after passArray: " << prime[0] << " " << prime[1] << " " << prime[2] << " " << prime[3] << " " << prime[4] << '\n';

    // find the length of an array
    std::cout << "\n\nUsing standard libraries to find the length of an array\n";
    std::cout << std::size(prime) << '\n';  // C++17 compatible
    std::cout << sizeof(prime) / sizeof(prime[0]) << '\n';

    // TODO: more

    std::cout << "\n\n";
    return 0;
}
