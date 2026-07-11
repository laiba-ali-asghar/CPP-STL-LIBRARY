// Exception-only tests for Queue<T>. Behavior tests live in test_queue.cpp.
#include <cassert>
#include "../include/Queue.h"

int main()
{
    // Constructing with capacity 0 throws.
    {
        bool thrown = false;
        try
        {
            Queue<int> bad(0);
        }
        catch (const std::invalid_argument&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // Dequeuing an empty queue throws.
    {
        bool thrown = false;
        Queue<int> empty(2);
        try
        {
            empty.dequeue();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // Reading the front of an empty queue throws.
    {
        bool thrown = false;
        Queue<int> empty(2);
        try
        {
            empty.front();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    return 0;
}
