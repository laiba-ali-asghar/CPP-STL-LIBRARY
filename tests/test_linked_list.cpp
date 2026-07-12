// Behavior tests for LinkedList<T>. Exceptions are covered separately in
// test_linked_list_exceptions.cpp.
#include <cassert>
#include "../include/LinkedList.h"

int main()
{
    LinkedList<int> list;
    assert(list.isEmpty());

    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtTail(5);
    // list is now: 20 10 5
    assert(list.countNodes() == 3);

    list.insertBefore(10, 15);
    list.insertAfter(10, 12);
    // list is now: 20 15 10 12 5
    assert(list.countNodes() == 5);

    assert(list.search(12));
    assert(!list.search(999));

    list.update(15, 150);
    assert(list.search(150));
    assert(!list.search(15));

    list.removeAtHead(); // removes 20
    list.removeAtTail();  // removes 5
    // list is now: 150 10 12
    assert(list.countNodes() == 3);
    assert(list.search(150));
    assert(list.search(10));
    assert(list.search(12));

    list.remove(10);
    assert(list.countNodes() == 2);
    assert(!list.search(10));

    // Copy constructor produces an independent list.
    LinkedList<int> copy(list);
    copy.insertAtTail(999);
    assert(copy.countNodes() == 3);
    assert(list.countNodes() == 2);

    return 0;
}
