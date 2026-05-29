#ifndef LIST_H
#define LIST_H

#include <iostream>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t count;
    
public:
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node = nullptr) : current(node) {}
        
        T& operator*() { return current->data; }
        const T& operator*() const { return current->data; }
        
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator temp = *this;
            if (current) current = current->next;
            return temp;
        }
        
        Iterator& operator--() {
            if (current) current = current->prev;
            return *this;
        }
        
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };
    
    List();
    List(const List& other);
    ~List();
    
    List& operator=(const List& other);
    
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void insert(Iterator pos, const T& value);
    void erase(Iterator pos);
    void clear();
    
    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    const Iterator begin() const { return Iterator(head); }
    const Iterator end() const { return Iterator(nullptr); }
};

template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), count(0) {}

template<typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), count(0) {
    Node* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
T& List<T>::front() {
    return head->data;
}

template<typename T>
const T& List<T>::front() const {
    return head->data;
}

template<typename T>
T& List<T>::back() {
    return tail->data;
}

template<typename T>
const T& List<T>::back() const {
    return tail->data;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

template<typename T>
void List<T>::pop_back() {
    if (!tail) return;
    Node* toDelete = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete toDelete;
    count--;
}

template<typename T>
void List<T>::pop_front() {
    if (!head) return;
    Node* toDelete = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete toDelete;
    count--;
}

template<typename T>
void List<T>::insert(Iterator pos, const T& value) {
    if (pos == begin()) {
        push_front(value);
        return;
    }
    
    Node* current = pos.operator->();
    Node* newNode = new Node(value);
    
    newNode->prev = current->prev;
    newNode->next = current;
    if (current->prev) current->prev->next = newNode;
    current->prev = newNode;
    count++;
}

template<typename T>
void List<T>::erase(Iterator pos) {
    if (pos == begin()) {
        pop_front();
        return;
    }
    
    Node* current = pos.operator->();
    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;
    if (current == tail) tail = current->prev;
    delete current;
    count--;
}

template<typename T>
void List<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

#endif
