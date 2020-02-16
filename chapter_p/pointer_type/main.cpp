#include <iostream>
#include <typeinfo>

int main() {
	int x(4);
	std::cout << typeid(x).name() << "\n";   // on my machine, this prints: i
	std::cout << typeid(&x).name() << "\n";  // on my machine, this prints: Pi
	
	return 0;
}
