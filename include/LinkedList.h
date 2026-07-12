#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>

/**
 * @brief Singly linked list node.
 *
 * @tparam T Type of value stored in the node.
 */
template <typename T>
class Node
{
public:
    T info;
    Node<T>* next;

    /**
     * @brief Constructs a node holding a default-constructed value with no successor.
     */
    Node() : info(T()), next(nullptr) {}

    /**
     * @brief Constructs a node holding @p val with no successor.
     *
     * @param val Value to store in the node.
     */
    explicit Node(const T& val) : info(val), next(nullptr) {}
};

/**
 * @brief Singly linked list.
 *
 * @tparam T Type of element stored in the list.
 */
template <typename T>
class LinkedList
{
private:
    Node<T>* head;
    std::size_t count;

    /**
     * @brief Deep-copies all nodes from @p other into this list.
     *
     * Assumes this list is currently empty.
     *
     * @param other List to copy from.
     */
    void copyFrom(const LinkedList& other)
    {
        Node<T>* src = other.head;
        Node<T>* tail = nullptr;
        while (src != nullptr)
        {
            Node<T>* newNode = new Node<T>(src->info);
            if (head == nullptr)
            {
                head = newNode;
            }
            else
            {
                tail->next = newNode;
            }
            tail = newNode;
            src = src->next;
        }
        count = other.count;
    }

    /**
     * @brief Deletes every node in the list and resets it to empty.
     */
    void clearAll()
    {
        Node<T>* curr = head;
        while (curr != nullptr)
        {
            Node<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        count = 0;
    }

public:
    /**
     * @brief Constructs an empty list.
     */
    LinkedList() : head(nullptr), count(0) {}

    /**
     * @brief Copy constructor. Performs a deep copy of all nodes.
     *
     * @param other List to copy from.
     */
    LinkedList(const LinkedList& other) : head(nullptr), count(0)
    {
        copyFrom(other);
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of all nodes.
     *
     * @param other List to copy from.
     * @return Reference to this list.
     */
    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other)
        {
            clearAll();
            copyFrom(other);
        }
        return *this;
    }

    /**
     * @brief Destructor. Deletes all nodes.
     */
    ~LinkedList()
    {
        clearAll();
    }

    /**
     * @brief Inserts a new element at the front of the list.
     *
     * @param val Value to insert.
     */
    void insertAtHead(const T& val)
    {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
        ++count;
    }

    /**
     * @brief Inserts a new element at the end of the list.
     *
     * @param val Value to insert.
     */
    void insertAtTail(const T& val)
    {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node<T>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        ++count;
    }

    /**
     * @brief Inserts a new element immediately before the first node whose
     * value equals @p key.
     *
     * @param key Value to search for.
     * @param val Value to insert before the matching node.
     *
     * @throws std::runtime_error if the list is empty or @p key is not found.
     */
    void insertBefore(const T& key, const T& val)
    {
        if (head == nullptr)
        {
            throw std::runtime_error("insertBefore: list is empty");
        }
        if (head->info == key)
        {
            insertAtHead(val);
            return;
        }
        Node<T>* prev = head;
        Node<T>* curr = head->next;
        while (curr != nullptr)
        {
            if (curr->info == key)
            {
                Node<T>* newNode = new Node<T>(val);
                newNode->next = curr;
                prev->next = newNode;
                ++count;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        throw std::runtime_error("insertBefore: key not found");
    }

    /**
     * @brief Inserts a new element immediately after the first node whose
     * value equals @p key.
     *
     * @param key Value to search for.
     * @param val Value to insert after the matching node.
     *
     * @throws std::runtime_error if @p key is not found.
     */
    void insertAfter(const T& key, const T& val)
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            if (temp->info == key)
            {
                Node<T>* newNode = new Node<T>(val);
                newNode->next = temp->next;
                temp->next = newNode;
                ++count;
                return;
            }
            temp = temp->next;
        }
        throw std::runtime_error("insertAfter: key not found");
    }

    /**
     * @brief Removes the element at the front of the list.
     *
     * @throws std::underflow_error if the list is empty.
     */
    void removeAtHead()
    {
        if (head == nullptr)
        {
            throw std::underflow_error("List is empty");
        }
        Node<T>* old = head;
        head = head->next;
        delete old;
        --count;
    }

    /**
     * @brief Removes the element at the end of the list.
     *
     * @throws std::underflow_error if the list is empty.
     */
    void removeAtTail()
    {
        if (head == nullptr)
        {
            throw std::underflow_error("List is empty");
        }
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            --count;
            return;
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr->next != nullptr)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = nullptr;
        delete curr;
        --count;
    }

    /**
     * @brief Removes the first node whose value equals @p val, if any.
     *
     * Does nothing if the list is empty or @p val is not found.
     *
     * @param val Value to search for and remove.
     */
    void remove(const T& val)
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->info == val)
        {
            removeAtHead();
            return;
        }
        Node<T>* prev = head;
        Node<T>* curr = head->next;
        while (curr != nullptr)
        {
            if (curr->info == val)
            {
                prev->next = curr->next;
                delete curr;
                --count;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    /**
     * @brief Checks whether @p key exists in the list.
     *
     * @param key Value to search for.
     * @return true if a node with value @p key exists, false otherwise.
     */
    bool search(const T& key) const
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            if (temp->info == key)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    /**
     * @brief Updates the value of the first node whose value equals @p key.
     *
     * @param key Value to search for.
     * @param val New value to assign.
     *
     * @throws std::runtime_error if @p key is not found.
     */
    void update(const T& key, const T& val)
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            if (temp->info == key)
            {
                temp->info = val;
                return;
            }
            temp = temp->next;
        }
        throw std::runtime_error("update: key not found");
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current element count.
     */
    std::size_t countNodes() const { return count; }

    /**
     * @brief Checks whether the list has no elements.
     *
     * @return true if the list is empty, false otherwise.
     */
    bool isEmpty() const { return head == nullptr; }

    /**
     * @brief Prints the list's elements, space-separated, to standard output.
     */
    void display() const
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->info << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Returns the raw head node pointer.
     *
     * Exposed so other containers (e.g. HashMap) can traverse buckets directly.
     *
     * @return Pointer to the head node, or nullptr if the list is empty.
     */
    Node<T>* getHead() const { return head; }
};
