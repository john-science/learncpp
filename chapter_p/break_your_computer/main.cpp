/* WARNING! This program WILL crash!

The point of this exercise is to show a "working" example of invalid pointers.
If your compiler allows this to compile, the program can't possibly run.

Unfortunately, g++ with --std=c++11 and newer, on my machine, prints "16".
So, people have spent time trying to fix such bugs. But what does this program
MEAN now? How would I unstand this if I found such a bug in the wild?
*/
#include <iostream>


void foo(int *&p) {

}


int main() {
	int* p;
	foo(p);

	std::cout << *p;

	return 0;
}
