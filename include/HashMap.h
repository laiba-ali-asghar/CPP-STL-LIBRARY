#pragma once

#include <cstddef>
#include <functional> // std::hash - a hashing utility, not a container
#include <iostream>
#include <stdexcept>

#include "LinkedList.h"

/**
 * @brief A simple key-value pair used as the element type stored in each
 * HashMap bucket.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 */
template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    /**
     * @brief Constructs a pair with default-constructed key and value.
     */
    Pair() : key(K()), value(V()) {}

    /**
     * @brief Constructs a pair from a given key and value.
     *
     * @param k Key.
     * @param v Value.
     */
    Pair(const K& k, const V& v) : key(k), value(v) {}

    /**
     * @brief Compares two pairs by key only.
     *
     * This lets us reuse LinkedList::search/remove for bucket management,
     * where lookups are always performed by key.
     *
     * @param other Pair to compare against.
     * @return true if both pairs have the same key, false otherwise.
     */
    bool operator==(const Pair& other) const { return key == other.key; }
};

/**
 * @brief Streams a pair as "(key, value)".
 *
 * @param os Output stream to write to.
 * @param p Pair to print.
 * @return Reference to @p os.
 */
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Pair<K, V>& p)
{
    os << "(" << p.key << ", " << p.value << ")";
    return os;
}

/**
 * @brief Separate-chaining hash map: an array of singly linked list buckets.
 *
 * Automatically rehashes (doubling the bucket count) once the load factor
 * exceeds 0.75.
 *
 * @tparam K Key type. Must be usable with std::hash and support operator==.
 * @tparam V Value type.
 */
template <typename K, typename V>
class HashMap
{
private:
    LinkedList<Pair<K, V>>* table;
    std::size_t count;
    std::size_t capacity;

    /**
     * @brief Computes the bucket index for @p key.
     *
     * @param key Key to hash.
     * @return Bucket index in the range [0, capacity).
     */
    std::size_t hashFunction(const K& key) const
    {
        return std::hash<K>()(key) % capacity;
    }

    /**
     * @brief Doubles the number of buckets and reinserts every existing
     * element into the new table.
     */
    void rehash()
    {
        std::size_t oldCapacity = capacity;
        LinkedList<Pair<K, V>>* oldTable = table;

        capacity *= 2;
        table = new LinkedList<Pair<K, V>>[capacity];
        count = 0;

        for (std::size_t i = 0; i < oldCapacity; ++i)
        {
            Node<Pair<K, V>>* node = oldTable[i].getHead();
            while (node != nullptr)
            {
                insert(node->info.key, node->info.value);
                node = node->next;
            }
        }
        delete[] oldTable;
    }

public:
    /**
     * @brief Constructs an empty hash map with a given number of buckets.
     *
     * A capacity of 0 is treated as 1.
     *
     * @param cap Initial number of buckets (default 10).
     */
    explicit HashMap(std::size_t cap = 10)
        : table(new LinkedList<Pair<K, V>>[cap == 0 ? 1 : cap]),
          count(0), capacity(cap == 0 ? 1 : cap)
    {
    }

    /**
     * @brief Copy constructor. Performs a deep copy of every bucket.
     *
     * @param other Hash map to copy from.
     */
    HashMap(const HashMap& other)
        : table(new LinkedList<Pair<K, V>>[other.capacity]),
          count(other.count), capacity(other.capacity)
    {
        for (std::size_t i = 0; i < capacity; ++i)
        {
            table[i] = other.table[i];
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of every bucket.
     *
     * @param other Hash map to copy from.
     * @return Reference to this hash map.
     */
    HashMap& operator=(const HashMap& other)
    {
        if (this != &other)
        {
            LinkedList<Pair<K, V>>* newTable = new LinkedList<Pair<K, V>>[other.capacity];
            for (std::size_t i = 0; i < other.capacity; ++i)
            {
                newTable[i] = other.table[i];
            }
            delete[] table;
            table = newTable;
            count = other.count;
            capacity = other.capacity;
        }
        return *this;
    }

    /**
     * @brief Destructor. Releases the bucket array.
     */
    ~HashMap()
    {
        delete[] table;
    }

    /**
     * @brief Returns the number of key-value pairs currently stored.
     *
     * @return Current element count.
     */
    std::size_t size() const { return count; }

    /**
     * @brief Returns the current load factor (element count divided by
     * bucket count).
     *
     * @return Current load factor.
     */
    double loadFactor() const { return static_cast<double>(count) / static_cast<double>(capacity); }

    /**
     * @brief Checks whether the map has no elements.
     *
     * @return true if the map is empty, false otherwise.
     */
    bool isEmpty() const { return count == 0; }

    /**
     * @brief Inserts a key-value pair, or updates the value if @p key
     * already exists. Triggers a rehash if the load factor exceeds 0.75
     * after insertion.
     *
     * @param key Key to insert or update.
     * @param value Value to associate with @p key.
     */
    void insert(const K& key, const V& value)
    {
        std::size_t index = hashFunction(key);
        Node<Pair<K, V>>* node = table[index].getHead();
        while (node != nullptr)
        {
            if (node->info.key == key)
            {
                node->info.value = value;
                return;
            }
            node = node->next;
        }
        table[index].insertAtHead(Pair<K, V>(key, value));
        ++count;
        if (loadFactor() > 0.75)
        {
            rehash();
        }
    }

    /**
     * @brief Looks up @p key and, if found, copies its value into @p value.
     *
     * @param key Key to look up.
     * @param value Output parameter set to the found value.
     * @return true if @p key was found, false otherwise.
     */
    bool get(const K& key, V& value) const
    {
        std::size_t index = hashFunction(key);
        Node<Pair<K, V>>* node = table[index].getHead();
        while (node != nullptr)
        {
            if (node->info.key == key)
            {
                value = node->info.value;
                return true;
            }
            node = node->next;
        }
        return false;
    }

    /**
     * @brief Checks whether @p key exists in the map.
     *
     * @param key Key to search for.
     * @return true if @p key exists, false otherwise.
     */
    bool contains(const K& key) const
    {
        V dummy;
        return get(key, dummy);
    }

    /**
     * @brief Removes the entry with the given key, if present.
     *
     * @param key Key to remove.
     * @return true if an entry was removed, false if @p key was not found.
     */
    bool remove(const K& key)
    {
        std::size_t index = hashFunction(key);
        Pair<K, V> probe(key, V());
        if (table[index].search(probe))
        {
            table[index].remove(probe);
            --count;
            return true;
        }
        return false;
    }

    /**
     * @brief Removes all key-value pairs from the map.
     */
    void clear()
    {
        for (std::size_t i = 0; i < capacity; ++i)
        {
            while (!table[i].isEmpty())
            {
                table[i].removeAtHead();
            }
        }
        count = 0;
    }

    /**
     * @brief Collects all keys currently in the map.
     *
     * @return A LinkedList containing every key, in bucket-traversal order.
     */
    LinkedList<K> keys() const
    {
        LinkedList<K> result;
        for (std::size_t i = 0; i < capacity; ++i)
        {
            Node<Pair<K, V>>* node = table[i].getHead();
            while (node != nullptr)
            {
                result.insertAtTail(node->info.key);
                node = node->next;
            }
        }
        return result;
    }

    /**
     * @brief Collects all values currently in the map.
     *
     * @return A LinkedList containing every value, in bucket-traversal order.
     */
    LinkedList<V> values() const
    {
        LinkedList<V> result;
        for (std::size_t i = 0; i < capacity; ++i)
        {
            Node<Pair<K, V>>* node = table[i].getHead();
            while (node != nullptr)
            {
                result.insertAtTail(node->info.value);
                node = node->next;
            }
        }
        return result;
    }

    /**
     * @brief Prints every bucket's contents, one bucket per line, to
     * standard output.
     */
    void display() const
    {
        std::cout << "HashMap contents:" << std::endl;
        for (std::size_t i = 0; i < capacity; ++i)
        {
            std::cout << i << ": ";
            table[i].display();
        }
    }

    /**
     * @brief Returns a reference to the value associated with @p key,
     * inserting a default-constructed value if @p key does not exist.
     * Triggers a rehash if the load factor exceeds 0.75 after an insertion.
     *
     * @param key Key to look up or insert.
     * @return Reference to the value associated with @p key.
     *
     * @throws std::runtime_error if an internal invariant is violated
     * (should not occur under normal use).
     */
    V& operator[](const K& key)
    {
        std::size_t index = hashFunction(key);
        Node<Pair<K, V>>* node = table[index].getHead();
        while (node != nullptr)
        {
            if (node->info.key == key)
            {
                return node->info.value;
            }
            node = node->next;
        }

        table[index].insertAtHead(Pair<K, V>(key, V()));
        ++count;
        if (loadFactor() > 0.75)
        {
            rehash();
        }

        index = hashFunction(key);
        node = table[index].getHead();
        while (node != nullptr)
        {
            if (node->info.key == key)
            {
                return node->info.value;
            }
            node = node->next;
        }
        throw std::runtime_error("HashMap::operator[] - internal error, key not found after insert");
    }
};
