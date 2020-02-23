# Some example memory leaks in C++

> All of these have to do with dynamically allocated memory.


First, let's use `new` to allocate memory, but we'll never use `delete` to free it before we leave scope:

    void do_something() {
        int *ptr = new int;
    }

Next, we will reassign a pointer we originally created with a `new` statement:

    int value = 5;
    int *ptr = new int; // allocate memory
    ptr = &value;       // old address lost, memory leak results

Lastly, we will use `new` twice on the same pointer:

    int *ptr = new int;
    ptr = new int;       // old address lost, memory leak results


Well, that was catstrophic fun.

The solution in all of these cases is to use the `delete` keyword:

    int value = 5;
    int *ptr = new int; // allocate memory
    delete ptr;         // return memory back to operating system
    ptr = &value;       // reassign pointer to address of value

