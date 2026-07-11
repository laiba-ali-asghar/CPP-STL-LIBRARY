// Exception-only tests for Stack<T>. Behavior tests live in test_stack.cpp.
#include <cassert>
#include "../include/Stack.h"

int main()
{
    // Constructing with capacity 0 throws.
    {
        bool thrown = false;
        try
        {
            Stack<int> bad(0);
        }
        catch (const std::invalid_argument&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // Pushing onto a full stack throws.
    {
        bool thrown = false;
        Stack<int> full(1);
        full.push(1);
        try
        {
            full.push(2);
        }
        catch (const std::overflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // Popping an empty stack throws.
    {
        bool thrown = false;
        Stack<int> empty(1);
        try
        {
            empty.pop();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // Reading the top of an empty stack throws.
    {
        bool thrown = false;
        Stack<int> empty(1);
        try
        {
            empty.stackTop();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    return 0;
}
