// Behavior tests for DoublyLinkedList<T>. Exceptions are covered separately
// in test_doubly_linked_list_exceptions.cpp.
#include <cassert>
#include "../include/DoublyLinkedList.h"

int main()
{
    DoublyLinkedList<int> list;
    assert(list.isEmpty());

    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);
    // list is now: 30 20 10
    assert(list.countNodes() == 3);

    list.insertAtTail(40);
    list.insertAtTail(50);
    // list is now: 30 20 10 40 50
    assert(list.countNodes() == 5);

    list.update(20, 200);
    assert(list.search(200));
    assert(!list.search(20));

    list.removeAtHead(); // removes 30
    list.removeAtTail();  // removes 50
    // list is now: 200 10 40
    assert(list.countNodes() == 3);

    list.remove(10);
    // list is now: 200 40
    assert(list.countNodes() == 2);
    assert(!list.search(10));

    assert(list.search(200));
    assert(!list.search(999));

    // Copy constructor produces an independent list.
    DoublyLinkedList<int> copy(list);
    copy.insertAtTail(999);
    assert(copy.countNodes() == 3);
    assert(list.countNodes() == 2);

    return 0;
}
