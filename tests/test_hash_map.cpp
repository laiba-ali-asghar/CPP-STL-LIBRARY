// Behavior tests for HashMap<K, V>. HashMap has no exception-only test file
// because its public API reports failures via return values, not exceptions.
#include <cassert>
#include <string>
#include "../include/HashMap.h"

int main()
{
    HashMap<std::string, int> hm;
    assert(hm.isEmpty());

    hm.insert("apple", 10);
    hm.insert("banana", 20);
    hm.insert("cherry", 30);
    assert(hm.size() == 3);

    int value = 0;
    assert(hm.get("banana", value));
    assert(value == 20);

    hm["apple"] = 50;
    assert(hm["apple"] == 50);

    assert(hm.contains("cherry"));
    assert(!hm.contains("grape"));

    assert(hm.remove("banana"));
    assert(!hm.contains("banana"));
    assert(!hm.remove("banana")); // already removed
    assert(hm.size() == 2);

    // Insert enough entries to trigger a rehash (load factor > 0.75).
    hm.insert("grape", 40);
    hm.insert("melon", 60);
    hm.insert("pear", 70);
    hm.insert("kiwi", 80);
    hm.insert("mango", 90);
    assert(hm.size() == 7);
    assert(hm.contains("mango"));

    LinkedList<std::string> allKeys = hm.keys();
    assert(allKeys.countNodes() == 7);
    assert(allKeys.search("apple"));

    hm.clear();
    assert(hm.isEmpty());
    assert(hm.size() == 0);
    assert(!hm.contains("apple"));

    // Copy constructor produces an independent map.
    HashMap<std::string, int> original;
    original.insert("a", 1);
    HashMap<std::string, int> copy(original);
    copy.insert("b", 2);
    assert(original.size() == 1);
    assert(copy.size() == 2);

    return 0;
}
