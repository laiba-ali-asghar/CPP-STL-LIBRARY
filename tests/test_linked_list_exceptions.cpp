// Exception-only tests for LinkedList<T>. Behavior tests live in
// test_linked_list.cpp.
#include <cassert>
#include "../include/LinkedList.h"

int main()
{
    // insertBefore() throws on an empty list.
    {
        bool thrown = false;
        LinkedList<int> empty;
        try
        {
            empty.insertBefore(1, 2);
        }
        catch (const std::runtime_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // insertBefore() throws when the key is not found.
    {
        bool thrown = false;
        LinkedList<int> list;
        list.insertAtHead(1);
        try
        {
            list.insertBefore(999, 2);
        }
        catch (const std::runtime_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // insertAfter() throws when the key is not found.
    {
        bool thrown = false;
        LinkedList<int> list;
        list.insertAtHead(1);
        try
        {
            list.insertAfter(999, 2);
        }
        catch (const std::runtime_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // removeAtHead() throws on an empty list.
    {
        bool thrown = false;
        LinkedList<int> empty;
        try
        {
            empty.removeAtHead();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // removeAtTail() throws on an empty list.
    {
        bool thrown = false;
        LinkedList<int> empty;
        try
        {
            empty.removeAtTail();
        }
        catch (const std::underflow_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // update() throws when the key is not found.
    {
        bool thrown = false;
        LinkedList<int> list;
        list.insertAtHead(1);
        try
        {
            list.update(999, 2);
        }
        catch (const std::runtime_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    return 0;
}
