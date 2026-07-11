// Minimal usage example for Stack<T>.
// Run: g++ -std=c++17 -Iinclude examples/example_stack.cpp -o example_stack

#include <iostream>
#include "Stack.h"

int main()
{
    // Create a stack
    Stack<int> stack;

    // Push values
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Read the top
    std::cout << "Top: " << stack.stackTop() << std::endl; // 30

    // Pop values
    std::cout << "Popped: " << stack.pop() << std::endl;   // 30
    std::cout << "Popped: " << stack.pop() << std::endl;   // 20
    std::cout << "Popped: " << stack.pop() << std::endl;   // 10

    // Handle an exception (popping an empty stack)
    try
    {
        stack.pop();
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
