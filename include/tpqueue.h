// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template<class T>
class TPQueue {
    // реализация шаблона очереди с приоритетом на связанном списке
 public:
     TPQueue():head(nullptr), tail(nullptr) {}
     ~TPQueue();
     void push(const T&);
     T pop();
     void print()const;
    //добавление
     void insert(int element);
    //удалить
     void remove(const TPQueue&, int);
 private:
     TPQueue::SYM* create(const T&);
     void ChangeElements(int*, int*);
     void sort(const TPQueue&, int);
     SYM* head;
     SYM* tail;
}

struct SYM {
    char ch;
    int prior;
};

template<class T>
typename TPQueue<T>::SYM* TPQueue<T>::create(const T& data) {
    SYM* sb = new SYM;
    sb->data = data;
    sb->next = nullptr;
    return sb;
}

template<class T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template<class T>
void TPQueue<T>::push(const T& data) {
    if (tail && head) {
        tail->next = create(data);
        tail = tail->next;
    } else {
        head = create(data);
        tail = head;
    }
}

template<class T>
T TPQueue<T>::pop() {
    if (head) {
        SYM* tmp = head->next;
        T data = head->data;
        head = tmp;
        return data;
    } else {
        throw std::string("Empty!");
    }
}

template<class T>
void TPQueue<T>::ChangeElements(int* a, int* b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

template<class T>
void TPQueue<T>::sort(const TPQueue<T>& parent, int i) {
    int size = parent.size();
    int largest = i;
    int leftchild = 2 * i + 1;
    int rightchild = 2 * i + 2;
    if (leftchild < size && parent[leftchild] > parent[largest]) {
        largest = leftchild;
    }
    if (rightchild < size && parent[rightchild] > parent[largest]) {
        largest = rightchild;
    }
    if (largest != i) {
        ChangeElements(&parent[i], &parent[largest]);
        sort(parent, largest);
    }
}

template<class T>
void TPQueue<T>::insert(int element) {
    SYM* newElement = new SYM; //создали новый узел
    newElement->ch = element;
    newElement->nest = nullptr; //новый узел в конце
    if (head == nullptr) {
        head = newElement;
    } else {
        SYM* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = newElement;
    }
}

template<class T>
void TPQueue<T>::remove(const TPQueue<T>& parent, int element) {
    int size = parent.size();
    int i;
    for (int i = 0; i < size; i++) {
        if (element == parent[i]) {
            break;
        }
    }

    ChangeElements(parent[i], parent[size - 1]);

    parent.pop_back();
    for (int i = size / 2 - 1; i >= 0; i--) {
        sort(parent, i);
    }
}

#endif  // INCLUDE_TPQUEUE_H_
