#include <iostream>

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


int main()
{
    std::cout << "If we don't fully initialize an array, the g++ standard is to insert zeros.\n";
    std::cout << "I hate this, let's just explicitly initialize our arrays.\n";
    int array[5]{ 7, 4, 5 }; // only initialize first 3 elements

    std::cout << array[0] << '\n';
    std::cout << array[1] << '\n';
    std::cout << array[2] << '\n';
    std::cout << array[3] << '\n';
    std::cout << array[4] << '\n';

    std::cout << "\nWe can use enums to make indexing our arrays more meaningful.\n";
    int testScores[max_students]{}; // allocate 6 integers
    testScores[stan] = 76;

    std::cout << testScores[stan] << '\n';



    return 0;
}
