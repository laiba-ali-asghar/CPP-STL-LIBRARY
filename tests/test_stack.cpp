// Behavior tests for Stack<T>. Exceptions are covered separately in
// test_stack_exceptions.cpp.
#include <cassert>
#include "../include/Stack.h"

int main()
{
    Stack<int> stack(4);

    assert(stack.isEmpty());
    assert(stack.size() == 0);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    assert(stack.size() == 3);
    assert(!stack.isEmpty());
    assert(stack.stackTop() == 30);

    assert(stack.pop() == 30);
    assert(stack.stackTop() == 20);
    assert(stack.size() == 2);

    stack.push(40);
    stack.push(50);
    assert(stack.isFull());

    // Copy constructor produces an independent stack.
    Stack<int> copy(stack);
    copy.pop();
    assert(copy.size() == 3);
    assert(stack.size() == 4);

    // Copy assignment produces an independent stack.
    Stack<int> assigned;
    assigned = stack;
    assigned.pop();
    assert(assigned.size() == 3);
    assert(stack.size() == 4);

    // Default constructor gives a usable stack with a non-zero capacity.
    Stack<int> defaultStack;
    defaultStack.push(1);
    assert(defaultStack.stackTop() == 1);

    return 0;
}
