// Exception-only tests for DoublyLinkedList<T>. Behavior tests live in
// test_doubly_linked_list.cpp.
#include <cassert>
#include "../include/DoublyLinkedList.h"

int main()
{
    // removeAtHead() throws on an empty list.
    {
        bool thrown = false;
        DoublyLinkedList<int> empty;
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
        DoublyLinkedList<int> empty;
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

    // update() throws on an empty list.
    {
        bool thrown = false;
        DoublyLinkedList<int> empty;
        try
        {
            empty.update(1, 2);
        }
        catch (const std::runtime_error&)
        {
            thrown = true;
        }
        assert(thrown);
    }

    // update() throws when the key is not found.
    {
        bool thrown = false;
        DoublyLinkedList<int> list;
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
