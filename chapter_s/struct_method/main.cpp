#include <iostream>


typedef struct spatial {
  double x { 0 };
  double y { 0 };
  double z { 0 };
} spatial;


// compiled with: g++ main.cpp --std=c++17 -o structs.exe
int main()
{
    spatial v1{-3, 1, 0};
    spatial v2{1.5, 2.5, 0.01};

    std::cout << v1.x << ", " << v1.y << ", " << v1.z << "\n";
    std::cout << v2.x << ", " << v2.y << ", " << v2.z << "\n";
}

